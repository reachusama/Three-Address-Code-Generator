#include "Dfa.h"

string Dfa::checkValidity(string a)
{
	state = "START";
	inputstr = a;
	for (i = 0; inputstr[i] != NULL; i++)
	{
		nextSymbol = inputstr[i];

		if (state == "INVALID")
			break;

		if(state == "START")
		{
			if (isdigit(nextSymbol))
				state = "Constant";
			else if (isalpha(nextSymbol))
				state = "ID";
			else if (nextSymbol == '.')
				state = "S1";
			else
				state = "INVALID";
		}
		else if(state == "ID")  
		{
			if (isdigit(nextSymbol))
				state = "ID";
			else if (isalpha(nextSymbol))
				state = "ID";
			else if (nextSymbol == '_')
				state = "ID";
			else
				state = "INVALID";
		}
		else if(state == "Constant")
		{
			if (isdigit(nextSymbol))
				state = "Constant";
			else if(nextSymbol == '.')
				state = "Constant";
			else
				state = "INVALID";
		}
		else if(state == "Constant") 
		{
			if (isdigit(nextSymbol))
				state = "Constant";
			else
				state = "INVALID";
		}
		else if(state == "S1") 
		{
			if (isdigit(nextSymbol))
				state = "Constant";
			else
				state = "INVALID";
		}

	}
	if ((state == "S1") || (state == "INVALID"))
	{
		cout << "Token : " << inputstr << endl;
		cout << "INVALID INPUT";
		return "";
	}
	else
	{
		
		cout << "Token : " << inputstr << endl;
		cout << "String State is : " << state << endl;
		return state;
	}
	
	
}