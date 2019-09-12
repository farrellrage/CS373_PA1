#ifndef main_h
#define main_h

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

//transition	q	a	r	b	x
//q = current state
//a = symbol the machine reads
//r = state the machine transitions to
//b = value the machine writes on top of 'a'
//x = move back (L) or forward (R) one symbol

enum __StateTypes__
{
	NORMAL = 0,
	START = 1,
	ACCEPT = 2,
	REJECT = 3
} stateTypes; // !__StateTypes__

enum __ShiftDirections__
{
	LEFT = 0,
	RIGHT = 1
}; // !__ShiftDirections__

struct transition;

struct state
{
	//Unique numerical ID for the state
	int id = -1;

	//Used to determine if the input brings the machine to a special state
	__StateTypes__ type = NORMAL;

	//List of transitions leading out of this state
	vector<transition*> transitions;
}; // !state

struct transition
{
	//Indicates the required input symbol to follow this transition
	char symbol;

	//Indicates the input symbol to shift to after following this transition
	__ShiftDirections__ shift;

	//Points to the state at the end of this transition
	state* nextState = NULL;
}; // !transition


#endif // !main_h
