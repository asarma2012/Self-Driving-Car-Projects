/**
	helpers.cpp

	Purpose: helper functions which are useful when
	implementing a 2-dimensional histogram filter.

*/

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "helpers.h"
// #include "debugging_helpers.cpp"

using namespace std;

vector< vector<float> > normalize(vector< vector <float> > grid) {
	
	/**

	Normalizes a grid of numbers.

	Input: param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability
		   associated with that grid cell.

	Output: a new normalized two dimensional grid where the sum of
		   all probabilities is equal to one.
	*/

	vector< vector<float> > newGrid;
	float sumGrid = 0.0;
	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();
	vector<float> vec;

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			sumGrid += grid[r][c];
		}
	}

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			vec.push_back(grid[r][c]/sumGrid);
		}
		newGrid.push_back(vec);
		vec.clear();
	}

	return newGrid;
}

vector < vector <float> > blur(vector < vector < float> > grid, float blurring) {

	/**

	Blurs (and normalizes) a grid of probabilities by spreading
	probability from each cell over a 3x3 "window" of cells. This
	function assumes a cyclic world where probability "spills
	over" from the right edge to the left and bottom to top.

	EXAMPLE - After blurring (with blurring=0.12) a localized
	distribution like this:

	0.00  0.00  0.00
	0.00  1.00  0.00
	0.00  0.00  0.00

	would look like this:

	0.01  0.02	0.01
	0.02  0.88	0.02
	0.01  0.02  0.01

	Input:
	@param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability
		   associated with that grid cell.

	@param blurring - a floating point number between 0.0 and 1.0
		   which represents how much probability from one cell
		   "spills over" to it's neighbors. If it's 0.0, then no
		   blurring occurs.

	Output: a new normalized two dimensional grid where probability
		   has been blurred.
	*/

	if (blurring == 0.0) {
		return normalize(grid);
	}

	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();
	vector < vector <float> > newGrid = zeros(height,width);

	float center_prob = 1.0 - blurring;
	float corner_prob = blurring / 12.0;
	float adjacent_prob = blurring / 6.0;

	vector< vector<float> > window;
	vector<float> middle;
	middle.push_back(adjacent_prob);
	middle.push_back(center_prob);
	middle.push_back(adjacent_prob);
	vector<float> topbottom;
	topbottom.push_back(corner_prob);
	topbottom.push_back(adjacent_prob);
	topbottom.push_back(corner_prob);
	window.push_back(topbottom);
	window.push_back(middle);
	window.push_back(topbottom);

	int new_r, new_c;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			for (int dx = -1; dx < 2; dx++) {
				for (int dy = -1; dy < 2; dy++) {
					new_r = (height + r + dy) % height;
					new_c = (width + c + dx) % width;
					newGrid[new_r][new_c] += window[dx + 1][dy + 1] * grid[r][c];
				}
			}
		}
	}

	return normalize(newGrid);
}



bool close_enough(vector < vector <float> > g1, vector < vector <float> > g2) {

	/**
	Determines when two grids of floating point numbers
	are "close enough" that they should be considered
	equal. Useful for battling "floating point errors".

	Input:
	@param g1 - a grid of floats

	@param g2 - a grid of floats

	Output: A boolean (True or False) indicating whether
	these grids are (True) or are not (False) equal.
	*/

	int i, j;
	float v1, v2;
	if (g1.size() != g2.size()) {
		return false;
	}

	if (g1[0].size() != g2[0].size()) {
		return false;
	}
	for (i=0; i<g1.size(); i++) {
		for (j=0; j<g1[0].size(); j++) {
			v1 = g1[i][j];
			v2 = g2[i][j];
			if (abs(v2-v1) > 0.0001 ) {
				return false;
			}
		}
	}
	return true;
}

bool close_enough(float v1, float v2) { 
	if (abs(v2-v1) > 0.0001 ) {
		return false;
	} 
	return true;
}


vector <char> read_line(string s) {
	
	/**
	Helper function for reading in map data

	Input:
	@param s - a string representing one line of map data.

	Output: A row of chars, each of which represents the
	color of a cell in a grid world.
	*/

	vector <char> row;

	size_t pos = 0;
	string token;
	string delimiter = " ";
	char cell;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());

		cell = token.at(0);
		row.push_back(cell);
	}

	return row;
}


vector < vector <char> > read_map(string file_name) {
	
	/**
	Helper function for reading in map data

	Input:
	@param file_name - The filename where the map is stored.

	Output: A grid of chars representing a map.
	*/

	ifstream infile(file_name);
	vector < vector <char> > map;
	if (infile.is_open()) {

		char color;
		vector <char> row;
		
		string line;

		while (std::getline(infile, line)) {
			row = read_line(line);
			map.push_back(row);
		}
	}
	return map;
}


vector < vector <float> > zeros(int height, int width) {

	/**
	Creates a grid of zeros

	For example:

	zeros(2, 3) would return

	0.0  0.0  0.0
	0.0  0.0  0.0

	Input:
	@param height - the height of the desired grid

	@param width - the width of the desired grid.

	Output: a grid of zeros (floats)
	*/

	int i, j;
	vector < vector <float> > newGrid;
	vector <float> newRow;

	for (i=0; i<height; i++) {
		newRow.clear();
		for (j=0; j<width; j++) {
			newRow.push_back(0.0);
		}
		newGrid.push_back(newRow);
	}
	return newGrid;
}

// int main() {
// 	vector < vector < char > > map = read_map("maps/m1.txt");
// 	show_grid(map);
// 	return 0;
// }
