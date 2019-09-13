#include "main.h"

//transition	q	a	r	b	x
//q = current state
//a = symbol the machine reads
//r = state the machine transitions to
//b = value the machine writes on top of 'a'
//x = move back (L) or forward (R) one symbol

int main(int argc, char** argv)
{
	int currentStateId;
	int nextStateId;
	int maximumTransitions;
	int transitionCount = 0;
	int inputStringLength;

	char currentSymbol;
	char nextSymbol;
	char shift;

	bool readingState;
	bool currentStateFound;
	bool nextStateFound;

	string input;
	string executionStatus;

	state* startState = NULL;
	state* currentStatePtr = NULL;
	state* nextStatePtr = NULL;

	transition* newTransition = NULL;

	ifstream fin;

	vector<state*> stateList;
	vector<int> visitedStates;
	vector<char> inputCharArray;

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

	//Save the input string
	string inputString(argv[2]);
	inputStringLength = inputString.length();
	//inputString = argv[2];

	for (int i = 0; i < inputStringLength; i++)
	{
		inputCharArray.push_back(inputString.at(i));
	} // !for

	//Save the number of maximum transitions
	maximumTransitions = atoi(argv[3]);

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

	//Add the start state to the state list
	stateList.push_back(new state);

	//Get special state data from the input file
	while (readingState && !fin.eof())
	{
		//Read in the current state's id
		fin >> input;

		//Set the current state's id number
		stateList.at(stateList.size() - 1)->id = atoi(input.c_str());

		//Read in the current state's state type
		fin >> input;

		//Save the state type
		stateList.at(stateList.size() - 1)->type = input;

		//Determine whether the current special state is the start state
		if (input == "start") { startState = stateList.at(stateList.size() - 1); }
		
		//Read in the next state from the input file
		fin >> input;

		//Determine whether we have started reading in transitions
		if (input == "transition")
		{
			//We are no longer reating the "state" lines of input
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
		//Create a new transition to go between states
		newTransition = new transition;

		//Get the 'current state' of the transition from the input file
		fin >> currentStateId;

		//Get the 'current symbol' of the transition from the input file
		fin >> currentSymbol;

		//Get the 'next state' of the transition from the input file
		fin >> nextStateId;

		//Get the 'next symbol' of the transition from the input file
		fin >> nextSymbol;

		//Get the right or left shift value from the input file
		fin >> shift;

		//Save the symbols for the current transition
		newTransition->symbol = currentSymbol;
		newTransition->overwriteSymbol = nextSymbol;
		newTransition->shift = shift;
		
		//For each state in the list of states
		//Search for a matching state in the state list for the current state
		currentStateFound = false;
		for (size_t i = 0; ((i < stateList.size()) && !currentStateFound); i++)
		{
			//Determine whether the 'current state' id matches the current
			//state from the list
			if (currentStateId == stateList[i]->id)
			{
				//The state already exisits
				currentStateFound = true;

				//Save a pointer to the current state
				currentStatePtr = stateList[i];
			} // !if
		} // !for

		//Determine whether the transition's originating state was found
		if (currentStateFound)
		{
			//Add this transition to the transition list for the originating
			//state
			currentStatePtr->transitions.push_back(newTransition);
		} // !if
		else
		{
			//Create a new generic state to add to the state list
			stateList.push_back(new state);

			//Set the new generic state's id to the value read from the input
			//file
			stateList.at(stateList.size() - 1)->id = currentStateId;

			//Set the new generic state's state type
			stateList.at(stateList.size() - 1)->type = "normal";

			//Add this transition to the transition list for the new state
			stateList.at(stateList.size() - 1)->transitions.push_back(newTransition);
		} // !else

		//For each state in the list of states
		//Search for a matching state in the state list for the next state
		nextStateFound = false;
		for (size_t i = 0; ((i < stateList.size()) && !nextStateFound); i++)
		{
			//Determine whether the next state id matches the current state from
			//the list
			if (nextStateId == stateList[i]->id)
			{
				//The next state already exists
				nextStateFound = true;

				//Save a pointer to the next state
				nextStatePtr = stateList[i];
			} // !if
		} // !for

		//Determine whether the transition's destination state was found
		if (nextStateFound)
		{
			//Set this transition's destination state to the destination state
			newTransition->nextState = nextStatePtr;
		} // !if
		else
		{
			//Add the new state to the state list
			stateList.push_back(new state);

			//Set the new generic state's id to the value read from the
			//input file
			stateList.at(stateList.size() - 1)->id = nextStateId;

			//Set the new generic state's state type
			stateList.at(stateList.size() - 1)->type = "normal";

			//Set this transitions's destination state to the new destination
			//state
			newTransition->nextState = stateList.at(stateList.size() - 1);
		} // !else

		//Get the next transition from the input file
		fin >> input;
	} // !while

	//Initialize input processing variables
	int inputIndex = 0;
	bool endProcess = false;

	//Maintain a pointer to the current state while processing the input
	currentStatePtr = startState;

	//Add the start state to the visited states list
	visitedStates.push_back(currentStatePtr->id);

	//Now that we have all the states and transitions set up, process
	//the input string until we accept or reject
	while (!endProcess)
	{
		//Search through the list of transitions from the current state for
		//the transition matching the current input symbol
		for (size_t i = 0; i < currentStatePtr->transitions.size(); i++)
		{
			//Determine whether the current transition's symbol matches the
			//input symbol
			if (currentStatePtr->transitions[i]->symbol
				== inputCharArray[inputIndex])
			{
				//Overwrite the current input symbol with the overwrite symbol
				//for the transition
				inputCharArray[inputIndex]
					= currentStatePtr->transitions[i]->overwriteSymbol;

				//Determine whether to move to the left or right input symbol
				if (currentStatePtr->transitions[i]->shift == 'R')
				{
					//Move to the next symbol on the right
					inputIndex++;
				} // !if
				else
				{
					//Move to the next symbol on the left
					inputIndex--;
				} // !else

				//Move to the next state
				currentStatePtr = currentStatePtr->transitions[i]->nextState;

				//Add the ID for the currently visited state to the visited states
				//list
				visitedStates.push_back(currentStatePtr->id);

				//Increment the number of taken transitions
				transitionCount++;

				//Exit the for loop
				break;
			} // !if
		} // !for

		//Determine whether the current state is an accept or reject state
		if ((currentStatePtr->type == "accept") || (currentStatePtr->type == "reject"))
		{
			//We have reached an accept or reject state
			endProcess = true;

			//Save the execution status
			executionStatus = currentStatePtr->type;
		} // !if
		//Determine whether we have exceeded the maximum number of transitions
		else if (transitionCount >= maximumTransitions)
		{
			//Stop processing input
			endProcess = true;

			//Save the execution status
			executionStatus = "quit";
		} // !else if
	} // !while

	//Print the traversed states to standard output
	for (size_t i = 0; i < visitedStates.size(); i++)
	{
		//Output the current visited state
		cout << visitedStates[i];

		//Determine whether to output a '->'
		if (i != (visitedStates.size() - 1))
		{
			//Output the separator characters between state id's
			cout << "->";
		} // !if
	} // !for

	//Output the execution states to standard output
	cout << ' ' << executionStatus << endl;
	
	fin.close();

	return 0;
} // !main
