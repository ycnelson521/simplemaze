#include "Qstate.h"

using namespace std;


Qstate::Qstate(){
	//id = 0;
}

Qstate::~Qstate(){
}

bool Qstate::initialize(void)
{
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		iter->initialize();
	}

	return true;	
}

bool Qstate::add_entry(int x, int y, char action, float action_value)
{
	bool entry_exist = false;
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		entry_exist = (iter->get_x() == x) &&
						(iter->get_y() == y) && 
						(iter->get_action() == action);
		if(entry_exist)
		{
			// no entry updated
			return false;
		}
	}
	Qstate_entry tmp_state_entry;
	tmp_state_entry.set(x, y, action, action_value);
	Qstate_vector.push_back(tmp_state_entry);

	return true;
}

// return action value Q(s,a)
bool Qstate::get_entry_Q(int x, int y, char action, float& action_value)
{

	bool entry_exist = false;
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		entry_exist = (iter->get_x() == x) &&
						(iter->get_y() == y) && 
						(iter->get_action() == action);
		if(entry_exist)
		{
			action_value = iter->get_action_value();
			return true;
		}
	}

	return false;

	return true;
}

bool Qstate::max_entry_Q(int x, int y, char& max_action, float& max_action_value) //return entry's max Q action and max Q
{
	bool entry_exist = false;
	bool max_entry_found = false;

	char tmp_max_action; //=random number between 0~3
	float tmp_max_action_value=-999;

	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		entry_exist = (iter->get_x() == x) &&
						(iter->get_y() == y);
		if(entry_exist)
		{
			if( tmp_max_action_value < iter->get_action_value() )
			{
				tmp_max_action = iter->get_action();
				tmp_max_action_value = iter->get_action_value();
				max_entry_found = true;
			}
		}
	}

	if(max_entry_found)
	{
		max_action = tmp_max_action;
		max_action_value = tmp_max_action_value;
		return true;
	}
	return false;
}

bool Qstate::update_entry_Q(int x, int y, char action, float action_value)
{
	bool entry_exist = false;
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		entry_exist = (iter->get_x() == x) &&
						(iter->get_y() == y) && 
						(iter->get_action() == action);
		if(entry_exist)
		{
			iter->update_action_value(action_value);
			return true;
		}
	}

	return false;
	
}

bool Qstate::check_entry(int x, int y, char action)
{
	bool entry_exist = false;
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		entry_exist = (iter->get_x() == x) &&
						(iter->get_y() == y) && 
						(iter->get_action() == action);
		if(entry_exist)
			return true;
	}

	return false;
}


void Qstate::print(void)
{
	vector<Qstate_entry>::iterator iter =Qstate_vector.begin();
	cout << "Dumping Qstate Table: " << endl;
	for(iter; iter !=Qstate_vector.end(); ++iter)
	{
		iter->print();
		//cout << iter << ": State (x,y)= (" << iter->get_x() << ", "<< iter->get_y() << ")  Action (a)= (" << iter->get_action << ")  Action Value S(a)= (" << iter->get_action_value << ")" << endl;
	}

}
