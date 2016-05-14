#include "Environment.h"

using namespace std;

Environment::Environment(){

}

Environment::~Environment(){
}

//intialize the maze
bool Environment::initialize(void) {
	maze3x3[0][0] = 1;
	maze3x3[0][1] = 1;
	maze3x3[0][2] = 1;
	maze3x3[0][3] = 1;
	maze3x3[0][4] = 1;

	maze3x3[1][0] = 1;
	maze3x3[1][1] = 0;
	maze3x3[1][2] = 2;  //goal
	maze3x3[1][3] = 0;
	maze3x3[1][4] = 1;

	maze3x3[2][0] = 1;
	maze3x3[2][1] = 1;
	maze3x3[2][2] = 1;
	maze3x3[2][3] = 0;
	maze3x3[2][4] = 1;

	maze3x3[3][0] = 1;
	maze3x3[3][1] = 0;
	maze3x3[3][2] = 0;
	maze3x3[3][3] = 0;
	maze3x3[3][4] = 1;

	maze3x3[4][0] = 1;
	maze3x3[4][1] = 1;
	maze3x3[4][2] = 1;
	maze3x3[4][3] = 1;
	maze3x3[4][4] = 1;

	return true;
}



//get maze content
bool Environment::getMaze(char maze_out[][5]){
	std::copy(&maze3x3[0][0], &maze3x3[0][0]+5*5, &maze_out[0][0]);
	return true;
}

//check collsion state at a given position
bool Environment::collision_check(int x, int y, bool& collision_state) {
	int in_maze_col = x+2;
	int in_maze_row = -y+3; //y is inverted from col index)

	collision_state = maze3x3[in_maze_row][in_maze_col] == 1;
	
	return collision_state;

}

bool Environment::goal_check(int x, int y, bool& goal_state) {
	int in_maze_col = x+2;
	int in_maze_row = -y+3; //y is inverted from col index)

	goal_state = maze3x3[in_maze_row][in_maze_col] == 2;
	
	return goal_state;
}
