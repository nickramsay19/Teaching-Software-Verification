
//===- Teaching-Software-Verification Assignment 1-------------------------------------//
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
 // Teaching-Software-Verification Assignment 1 : Graph Traversal
 //
 // 
 */


#include "Assignment-1.h"
//using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>

/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START: 1->2->4->5->END", where -> indicate an edge connecting two node IDs
void GraphTraversal::printPath(std::vector<const Edge*> &path) {
    std::stringstream ss;
    
    // print first item before for loop start
    std::vector<const Edge*>::const_iterator e = path.cbegin();
    ss << "START: " << (*e)->getDst()->getNodeID();
    ++e;

    for (; e != path.cend(); ++e) {
        ss << "->" << (*e)->getDst()->getNodeID();
    }

    ss << "->END";

    const std::string s = ss.str();
    
    paths.insert(s);

    std::cout << s << "\n"; 
};

/// TODO: Implement your depth first search here to traverse each program path (once for any loop) from src to dst
void GraphTraversal::DFS(const Edge* src_edge, const Node* dst) {

    // visit source node
    const Node* src = src_edge->getSrc();
    visited.insert(src);
    
    path.push_back(src_edge);

    const Node* next = src_edge->getDst();
    if (next->getNodeID() == dst->getNodeID()) {
        //std::cout << pathToString(path);
        printPath(path);        
    }

    for (const Edge* e : next->getOutEdges()) {
        DFS(e, dst); // recurse
    }

    path.pop_back();
}
