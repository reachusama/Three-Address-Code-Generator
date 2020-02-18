#include<vector>
#include "List.h"
class SymbolTable
{
	vector<pair<string, string>> table;
public:
	string getType(string);
	void push(string,string type = "" );
	void displayTable();
	vector<pair<string, string>> getTable();
	void clearTable();
};

