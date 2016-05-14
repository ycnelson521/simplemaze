#include "Qstate_entry.h"

using namespace std;



Qstate_entry::Qstate_entry(){
	//id = 0;
}

Qstate_entry::~Qstate_entry(){
}

void Qstate_entry::initialize(void)
{
	x = 0;
	y = 0;
	action = 0;
	action_value = 0;
}

char Qstate_entry::get_x(void)
{
	return x;
}

char Qstate_entry::get_y(void)
{
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
	cout << setw(2) <<"Q([" << (int)x << ", " << (int)y << "], " << (int)action << ")= " << setprecision(2) << action_value << endl;

}

bool Qstate_entry::set(char new_x, char new_y, char new_action, float new_action_value)
{
	x = new_x;
	y = new_y;
	action = new_action;
	action_value = new_action_value;

	return true;
}
