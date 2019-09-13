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

struct transition;

struct state
{
	//Unique numerical ID for the state
	int id = -1;

	//Used to determine if the input brings the machine to a special state
	string type = "normal";

	//List of transitions leading out of this state
	vector<transition*> transitions;
}; // !state

struct transition
{
	//Indicates the required input symbol to follow this transition
	char symbol = '-';

	//Indicates the symbol to overwrite the current input symbol before
	//following the transition to the next state
	char overwriteSymbol = '-';

	//Indicates the input symbol to shift to after following this transition
	char shift = '-';

	//Points to the state at the end of this transition
	state* nextState = NULL;
}; // !transition


#endif // !main_h
