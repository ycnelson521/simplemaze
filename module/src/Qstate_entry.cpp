#include "Qstate_entry.h"

using namespace std;



Qstate_entry::Qstate_entry(){
	//id = 0;
}

Qstate_entry::~Qstate_entry(){
}

void Qstate_entry::initialize(void)
{
	state.set(0, 0);
	action = 0;
	action_value = 0;
}

int Qstate_entry::get_x(void)
{
	int x;
	x = state.get_x();
	return x;
}

int Qstate_entry::get_y(void)
{
	int y;
	y = state.get_y();
	return y;
}

char Qstate_entry::get_action(void)
{
	return action;
}

float Qstate_entry::get_action_value(void)
{
	return action_value;
}

bool Qstate_entry::update_action_value(float new_action_value)
{
	action_value = new_action_value;
	return true;
}

void Qstate_entry::print(void)
{
	cout << setw(2) <<"Q([" << state.get_x() << ", " << state.get_y() << "], " << (int)action << ")= " << setprecision(2) << action_value << endl;

}

bool Qstate_entry::set(State new_state, char new_action, float new_action_value)
{
	int new_x;
	int new_y;

	new_x = new_state.get_x();
	new_y = new_state.get_y();
	state.set( new_x, new_y);

	action = new_action;
	action_value = new_action_value;

	return true;
}
