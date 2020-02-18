#include<iostream>
#include<fstream>
#include "Dfa.h"
#include "SymbolTable.h"
using namespace std;

class Parser
{
private :
	
	string token;
	Dfa check;
	SymbolTable table;
	vector<string> tacTokens;
public:
	vector<pair<string, string>> tokenize(string);
	vector<string> getTACtoken()
	{
		return tacTokens;
	}
};

