/**
	localizer.cpp

	Purpose: implements a 2-dimensional histogram filter
	for a robot living on a colored cyclical grid by 
	correctly implementing the "initialize_beliefs", 
	"sense", and "move" functions.

*/

#include "localizer.h"
#include "helpers.cpp"
#include <stdlib.h>
#include "debugging_helpers.cpp"

using namespace std;


vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {

    /**

    Initializes a grid of beliefs to a uniform distribution.

    Input: param grid - a two dimensional grid map (vector of vectors
           of chars) representing the robot's world. For example:

           g g g
           g r g
           g g g

           would be a 3x3 world where every cell is green except
           for the center, which is red.

    Output: normalized two dimensional grid of floats. For
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
    */

	vector< vector <float> > newGrid;
    float height = grid.size();
    float width = grid[0].size();
    float belief_per_cell = 1.0 / (height * width);
    vector<float> vec;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            vec.push_back(belief_per_cell);
        }
        newGrid.push_back(vec);
        vec.clear();
    }

	return newGrid;
}


vector< vector <float> > move(int dy, int dx, vector < vector <float> > beliefs,float blurring) {

    /**

    Implements robot motion by updating beliefs based on the
    intended dx and dy of the robot.

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00

    Inputs:

    dy - the intended change in y position of the robot

    dx - the intended change in x position of the robot

    beliefs - a two dimensional grid of floats representing
         the robot's beliefs for each cell before sensing. For
         example, a robot which has almost certainly localized
         itself in a 2D world might have the following beliefs:

         0.01 0.98
         0.00 0.01

    blurring - A number representing how noisy robot motion
           is. If blurring = 0.0 then motion is noiseless.

    Output:a normalized two dimensional grid of floats
         representing the updated beliefs for the robot.
    */

    vector<float>::size_type height = beliefs.size();
    vector<float>::size_type width = beliefs[0].size();
    vector < vector <float> > newGrid = zeros(height, width);
    int new_r;
    int new_c;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            new_r = (r + dy) % height;
            new_c = (c + dx) % width;
            newGrid[new_r][new_c] = beliefs[r][c];
        }
    }

    return blur(newGrid, blurring);
}


vector< vector <float> > sense(char color, vector< vector <char> > grid, vector< vector <float> > beliefs, float p_hit, float p_miss) {

    /**

    Implements robot sensing by updating beliefs based on the
    color of a sensor measurement

    Inputs:
    color - the color the robot has sensed at its location

    grid - the current map of the world, stored as a grid
           (vector of vectors of chars) where each char represents a
           color. For example:

           g g g
           g r g
           g g g

    beliefs - a two dimensional grid of floats representing
           the robot's beliefs for each cell before sensing. For
           example, a robot which has almost certainly localized
           itself in a 2D world might have the following beliefs:

           0.01 0.98
           0.00 0.01

    p_hit - the RELATIVE probability that any "sense" is
           correct. The ratio of p_hit / p_miss indicates how many
           times MORE likely it is to have a correct "sense" than
           an incorrect one.

    p_miss - the RELATIVE probability that any "sense" is
           incorrect. The ratio of p_hit / p_miss indicates how many
           times MORE likely it is to have a correct "sense" than
           an incorrect one.

    return: normalized two dimensional grid of floats
           representing the updated beliefs for the robot.
    */

	vector< vector <float> > newGrid;
    vector<float>::size_type height = grid.size();
    vector<float>::size_type width = grid[0].size();
    vector<float> vec;
    bool hit;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            hit = (color == grid[r][c]);
            vec.push_back(beliefs[r][c] * (int(hit) * p_hit + int(!hit) * p_miss));
        }
        newGrid.push_back(vec);
        vec.clear();
    }

	return normalize(newGrid);
}