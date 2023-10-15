//===- Software-Verification-Teaching Assignment 2-------------------------------------//
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
 // Software-Verification-Teaching Assignment 2 : ICFG graph traversal (Control-flow reachability analysis)
 //
 // 
 */

#include "Assignment-2.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility> // for std::pair
#include <type_traits>

using namespace SVF;
using namespace SVFUtil;

// check if a set of pairs contains an element, check only first member of pairs for equality
template <typename T, typename U>
bool pairSetContainsFirst(const Set<std::pair<T, U>>& set, const T& elem) {
    for (auto it = set.cbegin(); it != set.cend(); ++it) {
        const T first = it->first;
        if (first == elem) {
            return true;
        }
    }

    return false;
}

/// TODO: Implement your context-sensitive ICFG traversal here to traverse each program path (once for any loop) from src edge to dst node
void ICFGTraversal::dfs(const ICFGEdge *src, const ICFGNode *dst) {
    const ICFGNode* dst_node = dst; // renaming here
    const ICFGNode* src_node = src->getSrcNode();

    // visit this edge
    std::pair<const ICFGEdge*, ICFGTraversal::CallStack> edge_ctx = std::make_pair(src, callstack);
    visited.insert(edge_ctx);
    
    path.push_back(src);

    const ICFGNode* next_node = src->getDstNode();
    if (next_node->getId() == dst_node->getId()) {
        printICFGPath();
    }

    for (ICFGEdge* e : next_node->getOutEdges()) {
        //const SVFInstruction* = e->getCallsite();

        //if (!visited.count(e->getDstNode()) {
        //const ICFGNode* nextNode = e->getDstNode();
        if (!pairSetContainsFirst(visited, static_cast<const ICFGEdge*>(e))) {
            
            if (e->isCallCFGEdge()) {
                CallCFGEdge* ce = SVFUtil::dyn_cast<CallCFGEdge>(e);
                //if (ce != nullptr) {
                callstack.push_back(ce->getCallSite());
                //}
            } else if (e->isRetCFGEdge()) {
                RetCFGEdge* re = SVFUtil::dyn_cast<RetCFGEdge>(e);
                if (callstack.size() && callstack.back() == re->getCallSite()) {
                    callstack.pop_back();
                }
            } else if (!e->isIntraCFGEdge()) {
                continue;
            }

            dfs(e, dst_node); // recurse
        }
    }

    path.pop_back(); 
}

/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START: 1->2->4->5->END", where -> indicate an ICFGEdge connects two ICFGNode IDs
void ICFGTraversal::printICFGPath()
{
    std::stringstream ss;
    
    // print first item before for loop start
    std::vector<const ICFGEdge*>::const_iterator e = path.cbegin();
    ss << "START: " << (*e)->getDstNode()->getId();
    ++e;

    for (; e != path.cend(); ++e) {
        ss << "->" << (*e)->getDstNode()->getId();
    }

    ss << "->END";

    const std::string s = ss.str();
    
    paths.insert(s);

    std::cout << s << "\n";  
}

/// Program entry, do not change
void ICFGTraversal::analyse()
{
    std::set<const ICFGNode *> sources;
    std::set<const ICFGNode *> sinks;
    for (const ICFGNode *src : identifySource(sources)) {
        assert(SVFUtil::isa<GlobalICFGNode>(src) && "dfs should start with GlobalICFGNode!");
        for (const ICFGNode *sink: identifySink(sinks)) {
            const IntraCFGEdge* startEdge = new IntraCFGEdge(nullptr,const_cast<ICFGNode*>(src));
            handleIntra(startEdge);
            dfs(startEdge, sink);
            resetSolver();
        }
    }
}
