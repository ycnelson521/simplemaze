#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>

#include "Environment.h"
#include "Qstate.h"

#define DEFAULT_LEARNING_RATE 1.0
#define DEFAULT_REWARD_COLLISION -50.0
#define DEFAULT_REWARD_GOAL 50.0
#define DEFAULT_DISCOUNT_FACTOR 0.5
#define DEFAULT_REWARD_STEP -1.0
#define DEFAULT_MAX_STEP 100

class Agent {
private:
	char initial_state[2];
	char current_state[2];
	char next_state[2];
	
	Qstate Qstate_table;

	char action;
	bool collision_state;
	bool goal_state;

	float reward;

	int step;
	int max_step;

public:
	Agent();
	~Agent();
	bool initialize(void);
	bool act(Environment env);
	bool select_action(float epsilon);
	bool update_next_state(void);
	float learning_rate(); 
	bool action_value_iteration_update(float learning_rate, float discount_factor);
	bool termination_check(bool collision_state, bool goal_state);
	bool update_state_after_action(char &state_x, char &state_y, char input_action);
	bool print_best_path(Environment env); 
	bool Agent::dumpQstate_table(void);
};

#endif