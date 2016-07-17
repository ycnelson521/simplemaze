#include <stdio.h>
#include <iostream>

#include "Environment.h"
#include "Agent.h"

using namespace std;

#define DEFAULT_NUM_EPISODE 120
#define EXPLORE_NUM_EPISODE 20
#define EPS_80_NUM_EPISODE 10
#define EPS_60_NUM_EPISODE 10
#define EPS_40_NUM_EPISODE 10
#define EPS_20_NUM_EPISODE 10

int main(void)
{

	char maze_file[30] = "SimpleMaze15x15.txt";

	Environment env;
	
	Agent agent;

	env.initialize(); 

	cout << "Loading environment: " << maze_file << " ..." << endl;
	env.load_maze(maze_file);

	env.print();

	cout << "Initialize agent..." << endl;
	agent.initialize();

	cout << "Start learning... " << endl;

	bool goal_state = false;
	for(int episode = 0; episode < EXPLORE_NUM_EPISODE; episode++)
	{
		cout << "Start episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		cout << "End episode =  " << episode << "----" << endl;
	}

	for(int episode = EXPLORE_NUM_EPISODE; episode < EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE; episode++)
	{
		cout << "Start episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		cout << "End episode =  " << episode << "----" << endl;
	}

	for(int episode = EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE; episode < EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE+EPS_60_NUM_EPISODE; episode++)
	{
		cout << "Start episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		cout << "End episode =  " << episode << "----" << endl;
	}

	for(int episode = EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE+EPS_60_NUM_EPISODE; episode < EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE+EPS_60_NUM_EPISODE+EPS_40_NUM_EPISODE; episode++)
	{
		cout << "Start episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		cout << "End episode =  " << episode << "----" << endl;
	}

	for(int episode = EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE+EPS_60_NUM_EPISODE+EPS_40_NUM_EPISODE; episode < EXPLORE_NUM_EPISODE+EPS_80_NUM_EPISODE+EPS_60_NUM_EPISODE+EPS_40_NUM_EPISODE+EPS_20_NUM_EPISODE; episode++)
	{
		cout << "Start episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		cout << "End episode =  " << episode << "----" << endl;
	}
	cout << endl << "Printing the final best path :" << endl;
	agent.print_best_path(env);
	cout << endl;

	return 0;
}