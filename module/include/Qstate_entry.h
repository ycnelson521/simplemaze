#ifndef QSTATE_ENTRY_H
#define QSTATE_ENTRY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>

class Qstate_entry {
private:
	char x;
	char y;
	char action;
	float action_value;


public:
	Qstate_entry();
	~Qstate_entry();
	void initialize(void);
	void print(void);

	char get_x(void);
	char get_y(void);
	char get_action(void);
	float get_action_value(void);
	bool update_action_value(float new_action_value);
	bool set(char new_x, char new_y, char new_action, float new_action_value);
	
	
};

#endif