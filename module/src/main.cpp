#include <stdio.h>
#include <iostream>

#include "Environment.h"
#include "Agent.h"

using namespace std;

int main(void)
{
	/*
	char name[20];
	cout << "Hello! I am a Hello World program!" << endl;
	cout << "What is your name?" << endl;
	cin >> name;
	cout << "Greetings, " << name << "." << endl;
	cout << "Nelson says he loves " << name << " :) " << endl;
	cout << name << " said little bin bin is a loser." << endl;
	*/
	Environment env;
	
	Agent agent;

	env.initialize(); 

	agent.initialize();

	bool goal_state = false;
	for(int episode = 0; episode <200; episode++)
	{
		cout << "Start Episode = " << episode << " ----" << endl;
		goal_state = agent.act(env);

		cout << "Dumping Qstate_table @ episode = " << episode << ":" << endl;
		agent.dumpQstate_table();
		
		if(goal_state) {
			cout << "Printing the best path @ episode = " << episode << ":" << endl;
			agent.print_best_path(env);
		}
		cout << endl;
	}


	/*
	Environment env;

	env.initialize();

	bool btmp=false;
	for(int y = -1; y<4; y++)
		for(int x =-2; x<3; x++) {
			cout << "(x,y)= ("<< x << "," << y << ") collsion_state=" << env.collision_check(x,y, btmp) << endl;
		}
	
	cout << endl;
	
	for(int y = -1; y<4; y++)
		for(int x =-2; x<3; x++) {
			cout << "(x,y)= ("<< x << "," << y << ") goal_state=" << env.goal_check(x,y, btmp) << endl;
		}
	cout << endl;
	*/
	return 0;
}