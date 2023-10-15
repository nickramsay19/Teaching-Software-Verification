//===- Software-Verification-Teaching Assignment 3-------------------------------------//
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
 // Software-Verification-Teaching Assignment 3 : Manual assertion-based verification (Z3 Example)
 //
 // 
 */

#include "Assignment-3.h"
using namespace z3;
using namespace SVF;

/*
    // A simple example

    int main() {
        int* p;
        int q;
        int* r;
        int x;

        p = malloc1(..);
        q = 5;
        *p = q;
        x = *p;
        assert(x==10);
    }
*/
void Z3ExampleMgr::test0(){

    //  int** p;
    expr p = getZ3Expr("p");

    //  int* q;
    expr q = getZ3Expr("q");

    //  int* r;
    expr r = getZ3Expr("r");

    //  int x;
    expr x = getZ3Expr("x");

    // p = malloc(..);
    expr malloc1 = getMemObjAddress("malloc1");
    addToSolver(p == malloc1);

    // q = 5;
    addToSolver(q == getZ3Expr(5));

    // *p = q;
    storeValue(p, q);

    // x = *p;
    addToSolver(x == loadValue(p));

    // assert(x==5);
    std::cout<< getEvalExpr(x == getZ3Expr(5)) << "\n";
}

/*
// Simple integers

    int main() {
        int a;
        int b;
        a = 0;
        b = a + 1;
        assert(b>0);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test1(){

    //  int a;
    expr a = getZ3Expr("a");    

    //  a = 0;
    addToSolver(a == getZ3Expr(0));

    //  int b;
    expr b = getZ3Expr("b");    

    //  b = a + 1;
    addToSolver(b == a + getZ3Expr(1)); // TODO: confirm this line?
    
    //  assert(b > 0);
    //addToSolver(b > getZ3Expr(0));
    std::cout << getEvalExpr(b > getZ3Expr(0)) << "\n";
}

/*
  // One-level pointers

    int main() {
        int* p;
        int q;
        int b;
        int a;
        p = &a;
        *p = 0;
        q = *p;
        *p = 3;
        b = *p + 1;
        assert(b>3);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test2(){

    // int* p;
    expr p = getZ3Expr("p");    

    // int q;
    expr q = getZ3Expr("q");    

    // int b
    expr b = getZ3Expr("b");    

    // int a;
    expr a = getZ3Expr("a");    

    // p = &a;
    expr a_addr = getMemObjAddress("a");
    addToSolver(p == a_addr);

    // *p = 0;
    storeValue(p, getZ3Expr(0));

    // q = *p
    addToSolver(q == loadValue(p));

    // *p = 3;
    storeValue(p, getZ3Expr(3));

    // b = *p + 1;
    addToSolver(b == loadValue(p) + getZ3Expr(1));

    // assert(b > 3);
    std::cout << getEvalExpr(b > getZ3Expr(3)) << "\n";
}


/*
    // Mutiple-level pointers

    int main() {
        int** p;
        int* q;
        int* r;
        int x;

        p = malloc1(..);
        q = malloc2(..);
        *p = q;
        *q = 10;
        r = *p;
        x = *r;
        assert(x==10);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test3(){

    //  int** p;
    expr p = getZ3Expr("p");

    //  int* q;
    expr q = getZ3Expr("q");

    //  int* r;
    expr r = getZ3Expr("r");

    //  int x;
    expr x = getZ3Expr("x");

    // p = malloc(..);
    expr malloc1 = getMemObjAddress("malloc1");
    addToSolver(p == malloc1);

    // q = malloc(..);
    expr malloc2 = getMemObjAddress("malloc2");
    addToSolver(q == malloc2);

    // *p = q;
    storeValue(p, q);

    // *q = 10;
    storeValue(q, getZ3Expr(10));

    // r = *p;
    addToSolver(r == loadValue(p));

    // x = *r;
    addToSolver(x == loadValue(r));

    // assert(x==10);
    std::cout << getEvalExpr(x == getZ3Expr(10)) << "\n";
}
/*
   // Array and pointers

    int main() {
        int* p;
        int* x;
        int* y;
        int a;
        int b;
        p = malloc;
        x = &p[0];
        y = &p[1]
        *x = 10;
        *y = 11;
        a = *x;
        b = *y;
        assert((a + b)>20);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test4(){

    //  int* p;
    expr p = getZ3Expr("p");

    //  int* x;
    expr x = getZ3Expr("x");

    //  int* y;
    expr y = getZ3Expr("y");

    //  int a;
    expr a = getZ3Expr("a");

    //  int b;
    expr b = getZ3Expr("b");

    //  p = malloc;
    expr malloc = getMemObjAddress("malloc");
    addToSolver(p == malloc);    

    //  x = &p[0];
    addToSolver(x == getGepObjAddress(p, 0));

    //  y = &p[1];
    addToSolver(y == getGepObjAddress(p, 1));

    //  *x = 10;
    storeValue(x, getZ3Expr(10));

    //  *y = 11;
    storeValue(y, getZ3Expr(11));

    //  a = *x;
    addToSolver(a == loadValue(x));

    // b = *y;
    addToSolver(b == loadValue(y));

    //  assert((a + b)>20);
    std::cout << getEvalExpr(a + b > getZ3Expr(20)) << "\n";
}



/*
    // Struct and pointers

    struct A{ int f0; int* f1;};
    int main() {
       struct A* p;
       int a;
       int* x;
       int* q;
       int** r;
       int* y;
       int z;

       p = malloc;
       x = &a;
       *x = 5;
       q = &(p->f0);
       *q = 10;
       r = &(p->f1);
       *r = x;
       y = *r;
       z = *q + *y;
       assert(z==15);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test5(){

    // struct A* p;
    expr p = getZ3Expr("p");

    // int a;
    expr a = getZ3Expr("a");

    // int* x;
    expr x = getZ3Expr("x");

    // int* q;
    expr q = getZ3Expr("q");

    // int** r;
    expr r = getZ3Expr("r");

    // int* y;
    expr y = getZ3Expr("y");

    // int z;
    expr z = getZ3Expr("z");

    //  p = malloc;
    expr malloc1 = getZ3Expr("malloc1");
    addToSolver(p == malloc1);

    //  x = &a;
    addToSolver(x == getMemObjAddress("a")); // re-using "a" ??

    //  *x = 5;
    storeValue(x, getZ3Expr(5));

    //  q = &(p->f0);
    addToSolver(q == getGepObjAddress(p, 0));

    //  *q = 10;
    storeValue(q, getZ3Expr(10));

    //   r = &(p->f1);
    addToSolver(r == getGepObjAddress(p, 1));

    //   *r = x;
    storeValue(r, x); 

    //   y = *r;
    addToSolver(y == loadValue(r));

    //   z = *q + *y
    addToSolver(z == loadValue(q) + loadValue(y));

    //  assert(z==15);
    std::cout << getEvalExpr(z == getZ3Expr(15)) << "\n";
}


/*
    // Branches

    int main(int argv) {
    int a;
    int b;
    a = argv + 1;
    b = 5;
    if(a > 10)
       b = a;
    assert(b>=5);
    }
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test6(){

    // int argv
    expr argv = getZ3Expr("argv");

    //  int a;
    expr a = getZ3Expr("a");

    //  int b;
    expr b = getZ3Expr("b");

    //  a = argv + 1;
    addToSolver(a == argv + getZ3Expr(1));

    //  b = 5;
    addToSolver(b == getZ3Expr(5));

    // if(a > 10)
    // b = a;
    addToSolver(a <= getZ3Expr(10) || b == a);

    //  assert(b>=5);
    std::cout << getEvalExpr(b >= getZ3Expr(5)) << "\n";
}

/*
int foo(int z) {
    k = z;
    return k;
}
int main() {
  int x;
  int y;
  y = foo(2);
  x = foo(3);
  assert(x== 3 && y==2);    
}
*/
/// TODO: Implement your translation for each C statement to a Z3 constraint
void Z3ExampleMgr::test7(){

    // ==== MAIN ====
    // int x;
    expr x = getZ3Expr("x");

    // int y;
    expr y = getZ3Expr("y");

    // = CALL FOO =
    solver.push();

    // int z; // To Yulei: Remove this hint
    expr z = getZ3Expr("z");

    // int k;
    //expr k = getZ3Expr("k");

    // y = foo(2);
    addToSolver(z == getZ3Expr(2));
    // ==== FOO ====
    //addToSolver(k == z);
    expr k = getEvalExpr(z);
    solver.pop();

    // ==== MAIN ====
    addToSolver(y == k); 

    // = CALL FOO =
    solver.push();

    // x = foo(3);
    addToSolver(z == getZ3Expr(3)); 
    
    // ==== FOO ====
    //addToSolver(k == z);
    k = getEvalExpr(z);

    // = FOO RETURN =
    solver.pop();
    // ==== MAIN ====
    addToSolver(x == k); 

    
    // assert(x== 3 && y== 2); 
    std::cout << getEvalExpr(x == getZ3Expr(3) && y == getZ3Expr(2)) << "\n";

}
