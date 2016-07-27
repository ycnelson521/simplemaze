#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>



class State {
private:
	int x;
	int y;


public:
	State();
	~State();
	bool initialize(void);
	int get_x(void);
	int get_y(void);
	bool set(int x, int y);
	void print(void);
	
};

#endif