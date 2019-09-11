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
	REJECT = 3,
} stateTypes; // !__StateTypes__

struct transition;

struct state
{
	int id = -1;
	__StateTypes__ type = NORMAL;
	vector<transition*> transitions;
}; // !state

struct transition
{
	char symbol;
	state* nextState = NULL;
}; // !transition


#endif // !main_h
