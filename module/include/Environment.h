#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>


class Environment {
private:

	char **maze;

	int maze_width;
	int maze_height;
	int maze_expanded_width;
	int maze_expanded_height;

	bool start_exist;
	int start_x;
	int start_y;
	int start_x_expanded;	// w.r.t. boundary expanded array coordinate system
	int start_y_expanded;

	bool goal_exist;
	int goal_x;
	int goal_y;
	int goal_x_expanded;	// w.r.t. boundary expanded array coordinate system
	int goal_y_expanded;
	//int goal_state[2];		// state coordinate system, y axis inverted to expanded coordinate (array) system

public:
	Environment();
	~Environment();
	bool initialize(void);
	bool getMaze(char **maze_out);
	bool collision_check(int maze_x, int maze_y, bool& collision_state);
	bool goal_check(int maze_x, int maze_y, bool& goal_state);
	bool print(void);
	bool load_maze(char[]);
};

#endif