#include "State.h"

using namespace std;


State::State(){
	//id = 0;
}

State::~State(){
}

bool State::initialize(void)
{
	x=0;
	y=0;

	return true;	
}

int State::get_x(void)
{
	return x;
}

int State::get_y(void)
{
	return y;
}

bool State::set(int x_in, int y_in)
{
	x = x_in;
	y = y_in;

	return true;
}


void State::print(void)
{
	cout << "State = (" << x << ", "<< y << ")" << endl;
	
}
