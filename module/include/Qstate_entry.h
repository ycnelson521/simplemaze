#ifndef QSTATE_ENTRY_H
#define QSTATE_ENTRY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>

#include "State.h"

class Qstate_entry {
private:
	
	State state;
	char action;
	float action_value;


public:
	Qstate_entry();
	~Qstate_entry();
	void initialize(void);
	void print(void);

	int get_x(void);
	int get_y(void);
	char get_action(void);
	float get_action_value(void);
	bool update_action_value(float new_action_value);
	bool set(State new_state, char new_action, float new_action_value);
	
	
};

#endif