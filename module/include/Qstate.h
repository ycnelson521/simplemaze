#ifndef QSTATE_H
#define QSTATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>

#include "Qstate_entry.h"


class Qstate {
private:
	std::vector<Qstate_entry> Qstate_vector;


public:
	Qstate();
	~Qstate();
	bool initialize(void);
	bool add_entry(State state, char action, float action_value);
	bool get_entry_Q(State state, char action, float& action_value);
	bool max_entry_Q(State state, char& max_action, float& max_action_value); //return entry's max Q action and max Q
	bool update_entry_Q(State state, char action, float action_value);
	bool check_entry(State state, char action);
	void print(void);
	
	
};

#endif