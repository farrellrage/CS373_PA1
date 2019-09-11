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
} stateTypes;

struct transition;

struct state
{
	int id = -1;
	__StateTypes__ type = NORMAL;
	vector<transition*> transitions;
};

struct transition
{
	char symbol;
	state* nextState = NULL;
};

int main(int argc, char** argv)
{
	int currentState;
	int nextState;

	char currentSymbol;
	char nextSymbol;
	char shift;

	bool readingState;
	bool currentStateFound;
	bool nextStateFound;

	string input;

	state* startState = NULL;
	state* currentStatePtr = NULL;
	state* nextStatePtr = NULL;

	transition* newTransition = NULL;

	ifstream fin;

	vector<state*> stateList;

	//Determine whether the correct number of arguments was passed in
	if (argc < 4)
	{
		//Output an error message to standard out
		cout << "Error - need to pass in:" << endl
			<< "Machine input text file" << endl
			<< "Input string" << endl
			<< "Maximum number of transitions" << endl;

		return -1;
	} // !if

	//The input file name is the second argument, after the program name
	string inputFileName(argv[1]);
	cout << inputFileName << endl;

	//Open the input file
	fin.open(inputFileName);

	//Get the first value from the input file
	fin >> input;

	//Determine whether the first value is invalid
	if (input != "state")
	{
		return -1;
	} // !if

	//Set the flag for reading in states
	readingState = true;

	//Create a new state for the start state
	startState = new state;

	//Add the start state to the state list
	stateList.push_back(startState);

	//Get special state data from the input file
	while (readingState && !fin.eof())
	{
		//Read in the current state's id
		fin >> input;

		//Set the current state's id number
		stateList.at(stateList.size())->id = atoi(input.c_str());

		//Read in the current state's state type
		fin >> input;

		//Determine what type this state is
		if (input == "start")
		{
			//The current state is a start state
			stateList.at(stateList.size())->type = START;
		} // !if
		else if (input == "accept")
		{
			//The current state is an accept state
			stateList.at(stateList.size())->type = ACCEPT;
		} // !else if
		else
		{
			//The current state is a reject state
			stateList.at(stateList.size())->type = REJECT;
		} // !else

		//Read in the next state from the input file
		fin >> input;

		//Determine whether we have started reading in transitions
		if (input == "transition")
		{
			readingState = false;
		} // !if
		else
		{
			//Add a new special state to the state list
			stateList.push_back(new state);
		} // !else
	} // !while

	//Get transition data from the input file
	while (!fin.eof())
	{
		//Determine whether the current input line begins with "transition"
		if (input != "transition")
		{
			//Ignore the rest of the input file line
			fin.ignore(1000, '\n');

			//Get the first value of the next input file line
			fin >> input;

			//Continue to the next input file line
			continue;
		} // !if

		//Create a new transition to go between states
		newTransition = new transition;

		//Get the 'current state' of the transition from the input file
		fin >> currentState;

		//Get the 'current symbol' of the transition from the input file
		fin >> currentSymbol;

		//Get the 'next state' of the transition from the input file
		fin >> nextState;

		//Get the right or left shift value from the input file
		fin >> shift;

		//Save the symbol for the current transition
		newTransition->symbol = currentSymbol;
		
		//For each state in the list of states
		currentStateFound = false;
		nextStateFound = false;
		for (int i = 0;
			((i < stateList.size())
			&& !currentStateFound
			&& !nextStateFound);
			i++)
		{
			//Determine whether the current state id matches the current state from
			//the list
			if (currentState == stateList[i]->id)
			{
				//The state already exisits
				currentStateFound = true;

				//Save a pointer to the current state
				currentStatePtr = stateList[i];
			} // !if

			//Determine whether the next state id matches the current state from
			//the list
			if (nextState == stateList[i]->id)
			{
				//The next state already exists
				nextStateFound = true;

				//Save a pointer to the next state
				nextStatePtr = stateList[i];
			} // !if
		} // !for





		//Determine whether the state was found
		if (currentStateFound)
		{

		} // !if











	} // !while








	system("pause");


	fin.close();

	return 0;
} // !main