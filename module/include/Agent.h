#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <random>

#include "Environment.h"
#include "Qstate.h"

#define DEFAULT_LEARNING_RATE 1.0
#define DEFAULT_REWARD_COLLISION -50.0
#define DEFAULT_REWARD_GOAL 50.0
#define DEFAULT_DISCOUNT_FACTOR 0.5
#define DEFAULT_REWARD_STEP -1.0
#define DEFAULT_MAX_STEP 20000

class Agent {
private:
	int initial_state[2];
	int current_state[2];
	int next_state[2];
	int goal_pos[2];

	Qstate Qstate_table;

	char action;
	bool collision_state;
	bool goal_state;

	float reward;

	int step;
	int max_step;

	float epsilon;
	float learning_rate;
	float discount_factor;

public:
	Agent();
	~Agent();
	bool initialize(void);
	bool act(Environment env);
	bool select_action(void);
	bool update_next_state(void);
	bool set_epsilon(float);
	bool set_learning_rate(float); 
	bool set_discount_factor(float);
	bool action_value_iteration_update(void);
	bool termination_check(bool collision_state, bool goal_state);
	bool update_state_after_action(int &state_x, int &state_y, char input_action);
	bool print_best_path(Environment env); 
	bool dumpQstate_table(void);
};

#endif