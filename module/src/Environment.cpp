#include "Environment.h"

using namespace std;

Environment::Environment(){

}

Environment::~Environment(){
	
	/*
	for(int i=0; i<maze_expanded_height; i++) {
		delete maze[i];
	}
	delete maze;
	*/
}

//intialize the maze
bool Environment::initialize(void) {

	int x=0;
	int y=0;

	goal_exist = false;
	start_exist = false;

	return true;
}



//get maze content
bool Environment::getMaze(char **maze_out){						//not checked yet
	std::copy(&maze[0][0], &maze[0][0]+5*5, &maze_out[0][0]);
	return true;
}

//check collsion state at a given position
bool Environment::collision_check(int maze_x, int maze_y, bool& collision_state) {

	int array_x = maze_x + start_x_expanded;
	int array_y = -maze_y + start_y_expanded; // array_y is inverted from maze_y

	collision_state = maze[array_y][array_x] == 1;
	
	return collision_state;

}

bool Environment::goal_check(int maze_x, int maze_y, bool& goal_state) {
	int array_x = maze_x + start_x_expanded;
	int array_y = -maze_y + start_y_expanded; // array_y is inverted from maze_y

	goal_state = maze[array_y][array_x] == 2;
	
	return goal_state;
}

bool Environment::print(void) {

	int array_y;
	int array_x;

	cout << "Environment::print():" << endl;

	for(array_y = 0; array_y < maze_expanded_height; array_y++) {
		cout << setw(2) << (-array_y + start_y_expanded) << "> " ;
		for(array_x = 0; array_x < maze_expanded_width; array_x++) {
			cout << maze[array_y][array_x] << " ";
		}
		cout << endl;
	}

	return true;
}

bool Environment::load_maze(char filename[]){
	string line;
	stringstream line_stream;
	string token_0, token_1, token_2, token_3, token_4;
	int tmp;


	fstream maze_file;
	
	maze_file.open(filename, ios::in);  // open maze file

	if(maze_file.is_open()) {
		// read config file
		getline(maze_file, line);  //get line 1 from maze file
		line_stream << line ;
		line_stream >> token_0 >> token_1;

		if(token_0.compare("simple_maze") == 0) {
			cout << "Ok! It's an simple_maze file" << endl;
		} else {
			cerr << "Error! Not a simple_maze file!" << endl;
			exit(1);
		}
		
		getline(maze_file, line);  //get line 1 from maze file
		line_stream.clear();  //clear string stream to reuse it
		line_stream << line;
		line_stream >> token_0 >> tmp;
		if(token_0.compare("maze_width") == 0) {
			maze_width = tmp;
			cout << "maze_width = "<< maze_width << endl;
		} else {
			cerr << "Error! Should read \"maze_width\" but read \"" << token_0 << endl;
			exit(1);
		}

		getline(maze_file, line);  //get line 1 from maze file
		line_stream.clear();  //clear string stream to reuse it
		line_stream << line;
		line_stream >> token_0 >> tmp;
		if(token_0.compare("maze_height") == 0) {
			maze_height = tmp;
			cout << "maze_height = "<< maze_height << endl;
		} else {
			cerr << "Error! Should read \"maze_height\" but read \"" << token_0 << endl;
			exit(1);
		}

		maze_expanded_width = maze_width + 2;
		maze_expanded_height = maze_height + 2;

		//dynamically allocate maze array
		// destructor has not been implemented yet
		maze = new char*[maze_expanded_height];

		for(int i=0; i<maze_expanded_height; i++) {
			maze[i] = new char[maze_expanded_width];
		}

		start_exist = false;
		goal_exist = false;
		// read in each row 
		for(int i=0; i<maze_expanded_height; i++) {
			getline(maze_file, line);  //get line 1 from maze file
			line_stream.clear();  //clear string stream to reuse it
			line_stream << line;
			for(int j=0; j<maze_expanded_width; j++) {
				line_stream >>  tmp;
				maze[i][j] = (char)tmp;
				//check and update goal position
				if(tmp==2) {
					goal_exist = true;
					goal_y_expanded = i;
					goal_x_expanded = j;
					goal_y = goal_y_expanded - 1;
					goal_x = goal_x_expanded - 1;
				}

				//check and update start position
				if(tmp==3) {
					start_exist = true;
					start_y_expanded = i;
					start_x_expanded = j;
					start_y = start_y_expanded - 1;
					start_x = start_x_expanded - 1;
				}
			}
		}
	
	}else{
		cerr << "error open file" << endl;
	}

}

