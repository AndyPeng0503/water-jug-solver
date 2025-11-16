/* The code uses standard STL containers and algorithms including vector, queue, 
 * priority_queue, and string.
 *
 * The Jug class constructor takes nine parameters:
 *   Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA.
 *
 * The solve() method returns:
 *   -1 if inputs are invalid;
 *    0 if inputs are valid but no solution exists;
 *    1 if a solution is found (solution string holds the steps);
 */
#ifndef JUG_H
#define JUG_H

#include <string>
using namespace std;

class Jug {
public:
    Jug(int, int, int, int, int, int, int, int, int);
    ~Jug();

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);

private:
    //anything else you need
    int Ca, Cb, N;
    int cfA, cfB, ceA, ceB, cpAB, cpBA;
};

#endif