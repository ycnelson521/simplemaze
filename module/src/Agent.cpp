#include "Agent.h"

using namespace std;

Agent::Agent(){

}

Agent::~Agent(){
}

//intialize the maze
bool Agent::initialize(void) {
	//initial_state[0] = 0;
	//initial_state[1] = 0;
	initial_state.set(0, 0);

	//current_state[0] = initial_state[0];
	//current_state[1] = initial_state[1];
	current_state.set(initial_state.get_x(), initial_state.get_y() );

	collision_state = false;
	goal_state = false;
	Qstate_table.initialize();

	epsilon = 0.9; //default epsilon is 1, 100% chance of random exploration
	learning_rate = DEFAULT_LEARNING_RATE;
	discount_factor = DEFAULT_DISCOUNT_FACTOR;

	return true;
}

// Main try logic
bool Agent::act(Environment env) {
	
	bool terminate = false;
	
	goal_state = false;
	step = 0;
	max_step = DEFAULT_MAX_STEP;

	//reset state before trial run
	// don't touch Qstate_table
	//current_state[0] = initial_state[0];
	//current_state[1] = initial_state[1];
	current_state.set(initial_state.get_x(), initial_state.get_y() );

	collision_state = false;
	goal_state = false;

	// start trial run
	Qstate_table.add_entry(current_state, 0, 0);

	while(!terminate) {
	
	//	if((current_state[0] == 1) && (current_state[1]==2)) // && action==1)
	//			cout <<"gotcha" << endl;

		// epsilon-greedy-selection
		// select the action with highest Q(s,a) value under (1-epsilon) probability
		// this->action is updated
		select_action();

		// update the next state after action a (s, a) -> s'
		//this->next_state is updated based on this->action
		update_next_state();


		// check collision_state and goal_state
		// this->collision_state and this->goal_state are updated based on this->next_state from env;
		env.collision_check(next_state.get_x(), next_state.get_y(), collision_state);
		env.goal_check(next_state.get_x(), next_state.get_y(), goal_state);

		// compute immediate reward
		if( collision_state ) {
			reward = DEFAULT_REWARD_COLLISION;
			Qstate_table.add_entry(next_state, 0, -50);
		}else if( goal_state ) {
			reward = DEFAULT_REWARD_GOAL;
			Qstate_table.add_entry(next_state, 0, 50);
		}else{
			reward = DEFAULT_REWARD_STEP;
			Qstate_table.add_entry(next_state, 0, 0);
		}

		


		// update Q(s,a)
		action_value_iteration_update();

		// step increment
		step++;

		// update current_state with next_state if no collision happened
		if(!collision_state) {
			current_state.set( next_state.get_x(), next_state.get_y() );
			//current_state[0] = next_state[0];
			//current_state[1] = next_state[1];
		}

		// check for termination, collision/goal/max steps reached
		terminate = termination_check(collision_state, goal_state);

	} // endof while(!terminate)

	return goal_state;
}

bool Agent::select_action(void)
{
	float max_action_value;
	bool max_action_value_found=false;
	
	int tmp_rand = 0;
	int epsilon_100x_threshold = 0;

	char chk_action;
	bool entry_exist;
	bool not_all_action_tried = false;

	//random seed
	random_device rd;
	// Initialize Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());
	// Generate pseudo-random numbers
    // uniformly distributed in range (1, 100)
    uniform_int_distribution<> dis(1, 100);


	if(!max_action_value_found)
	{
		//use tmp_rand as a dice event [1~100]

		//generate uniformly distributed random value
		tmp_rand = dis(gen);

		epsilon_100x_threshold = (int)(epsilon * 100) +1 ;  // scale input epsilon up 100 times

		not_all_action_tried = false;
		for(chk_action = 0; chk_action<4; chk_action++) {
			entry_exist = Qstate_table.check_entry(current_state, chk_action);
			if(!entry_exist) {
				not_all_action_tried = true;
				break;
			}
		}

		if(not_all_action_tried) {
			for(chk_action = 0; chk_action<4; chk_action++) {
				action = tmp_rand % 4; // max action count
				entry_exist = Qstate_table.check_entry(current_state, action);
				if(!entry_exist)
					break;
			}
			Qstate_table.add_entry(current_state, action, 0); //check and add the new entry
		}else{ // all action tried

			if(tmp_rand > epsilon_100x_threshold) { // 1-epsilon - best case
				max_action_value_found = Qstate_table.max_entry_Q(current_state, action, max_action_value);
			}else{ // epsilon - random case
				action = tmp_rand % 4; // max action count
				Qstate_table.add_entry(current_state, action, 0); //check and add the new entry
			}
		}
	}
	//dbg info
	//cout << "dbg: select_action: ( [" << current_state.get_x() << ", " << current_state.get_y() << "], " << (int)action << ")" << " " << (int)tmp_rand << endl;

	return true;
}

bool Agent::update_next_state()
{
	switch(action)
	{
		case 0: //forward
			//next_state[0] = current_state[0];
			//next_state[1] = current_state[1] + 1;
			next_state.set( current_state.get_x(), current_state.get_y() + 1 );
			break;
		case 1: // left
			//next_state[0] = current_state[0] - 1;
			//next_state[1] = current_state[1];
			next_state.set( current_state.get_x() - 1, current_state.get_y() );
			break;
		case 2: // right
			//next_state[0] = current_state[0] + 1;
			//next_state[1] = current_state[1];
			next_state.set( current_state.get_x() + 1, current_state.get_y() );
			break;
		case 3: //back
			//next_state[0] = current_state[0];
			//next_state[1] = current_state[1] - 1;
			next_state.set( current_state.get_x(), current_state.get_y() - 1 );
			break;
	}
	return true;
}

bool Agent::set_epsilon(float value)
{
	epsilon = value;
	return true;
}

bool Agent::set_learning_rate(float value)
{
	learning_rate = value;
	return true;
}

bool Agent::set_discount_factor(float value)
{
	discount_factor = value;
	return true;
}


bool Agent::action_value_iteration_update(void)
{
	float old_action_value;
	float new_action_value;
	float max_action_value;
	float learned_value;
	float estimated_optimal_future_value;
	char next_state_max_action;

	//if(current_state.get_x()==-3 && current_state.get_y()==1 && action ==0)
	//	cout << "dbg: -3, 1, 0" << endl;
	
	Qstate_table.get_entry_Q(current_state, action, old_action_value);

	Qstate_table.max_entry_Q(next_state, next_state_max_action, estimated_optimal_future_value); 
	
	learned_value = reward + discount_factor * estimated_optimal_future_value; 

	new_action_value = old_action_value + learning_rate * (learned_value - old_action_value);

	//dbg
/*	cout << "dbg: action_value_update: old_action_value=" << old_action_value << 
		", est_optimal_future_value=" << estimated_optimal_future_value <<
		", learned_value=" << learned_value <<
		", new_action_value =" << new_action_value << endl;
*/
	//update new action value
	Qstate_table.update_entry_Q(current_state, action, new_action_value);
	
	return true;
}

// Terminatino condition check within Agent::Act(env)
bool Agent::termination_check(bool collision_state, bool goal_state)
{
	if( goal_state)
		return true;
	else if( step > max_step)
		return true;
	else
		return false;
}

//bool Agent::update_state_after_action(int &state_x, int &state_y, char input_action)
bool Agent::update_state_after_action(State &state, char input_action)
{
	int state_x;
	int state_y;
	state_x = state.get_x();
	state_y = state.get_y();

	switch(input_action)
	{
		case 0: //forward
			state_x = state_x;
			state_y = state_y + 1;
			break;
		case 1: // left
			state_x = state_x - 1;
			state_y = state_y;
			break;
		case 2: // right
			state_x = state_x + 1;
			state_y = state_y;
			break;
		case 3: //back
			state_x = state_x;
			state_y = state_y - 1;
			break;
	}
	state.set( state_x, state_y);
	return true;
}

bool Agent::print_best_path(Environment env)
{
	//int tmp_state[2];
	State tmp_state;
	char tmp_action;
	float tmp_action_value;
	Qstate_entry tmp_entry;
	bool tmp_collision_state;
	bool tmp_goal_state;

	//tmp_state[0] = initial_state[0];
	//tmp_state[1] = initial_state[1];
	tmp_state.set( initial_state.get_x(), initial_state.get_y() );

	tmp_collision_state = false;
	tmp_goal_state = false;
	
	if(!collision_state && !goal_state)
		return false;

	Qstate_table.print();

	cout << endl << "The best path:" << endl;
	while( !tmp_collision_state && !tmp_goal_state )
	{
		Qstate_table.max_entry_Q(tmp_state, tmp_action, tmp_action_value);
		tmp_entry.set(tmp_state, tmp_action, tmp_action_value);
		tmp_entry.print();
		update_state_after_action(tmp_state, tmp_action);
		
		//check if collision happened or goal is reached
		env.collision_check(tmp_state.get_x(), tmp_state.get_y(), tmp_collision_state);
		env.goal_check(tmp_state.get_x(), tmp_state.get_y(), tmp_goal_state);

	}
	if(tmp_collision_state)
		cout << "Collision!" << endl;

	if(tmp_goal_state)
		cout << "Goal reached!!" << endl;

	return true;
}

bool Agent::dumpQstate_table(void)
{
	Qstate_table.print();
	cout << endl;
	return true;
}