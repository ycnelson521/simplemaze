#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

class Environment {
private:
	char maze3x3[5][5];

public:
	Environment();
	~Environment();
	bool initialize(void);
	bool getMaze(char maze_out[][5]);
	bool collision_check(int x, int y, bool& collision_state);
	bool goal_check(int x, int y, bool& goal_state);

};

#endif