//===- Software-Verification-Teaching Assignment 4-------------------------------------//
//
//     SVF: Static Value-Flow Analysis Framework for Source Code
//
// Copyright (C) <2013->
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // Software-Verification-Teaching Assignment 4 : Automated assertion-based verification (Static symbolic execution)
 //
 // 
 */

#include "Assignment-4.h"
#include "WPA/Andersen.h"
#include "SVF-LLVM/LLVMUtil.h"
#include "Util/Options.h"
#include "Util/CommandLine.h"



using namespace SVF;
using namespace SVFUtil;

/*
 // Software-Verification-Teaching Assignment 4 main function entry
 // To run your program with testcases , please set the assembly file from testcase/bc/ for "args" in file'.vscode/launch.json'
 // e.g. To check test1, set "args": ["Assignment-4/testcase/bc/test1.ll"] in file'.vscode/launch.json'
 */
int main(int argc, char **argv)
{
    int arg_num = 0;
    int extraArgc = 4;
    char **arg_value = new char *[argc + extraArgc];
    for (; arg_num < argc; ++arg_num) {
        arg_value[arg_num] = argv[arg_num];
    }
    std::vector<std::string> moduleNameVec;

    int orgArgNum = arg_num;
    arg_value[arg_num++] = (char*) "-model-arrays=true";
    arg_value[arg_num++] = (char*) "-pre-field-sensitive=false";
    arg_value[arg_num++] = (char*) "-model-consts=true";
    arg_value[arg_num++] = (char*) "-stat=false";
    assert(arg_num == (orgArgNum + extraArgc) && "more extra arguments? Change the value of extraArgc");
    
    moduleNameVec = OptionBase::parseOptions(
            arg_num, arg_value, "Software-Verification-Teaching Assignment 4", "[options] <input-bitcode...>"
    );

    SVFModule *svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
    LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf");

    SVFIRBuilder builder(svfModule);
    SVFIR *svfir = builder.build();

    PTACallGraph* callgraph = AndersenWaveDiff::createAndersenWaveDiff(svfir)->getPTACallGraph();
    builder.updateCallGraph(callgraph);

    /// ICFG
    ICFG *icfg = svfir->getICFG();
    icfg->updateCallGraph(callgraph);
    icfg->dump(moduleNameVec[0] + ".icfg");

    SSE *sse = new SSE(svfir, icfg);
    sse->analyse();

    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::SVFIR::releaseSVFIR();

    delete sse;
    return 0;
}
