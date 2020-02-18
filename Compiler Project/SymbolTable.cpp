#include "SymbolTable.h"
string SymbolTable::getType(string token)
{

	if (token == "for" || token == "while" || token == "do")
		return token;
	else if (token == "if" || token == "else")
		return token;
	else if (token == "int" || token == "double")
		return "var";
	else if (isalpha(token[0]))
		return "ID";
	else
		return token;
}
void SymbolTable::push(string token, string type)
{
	if(type == "")
		table.push_back(pair<string, string>(token, getType(token)));
	else
		table.push_back(pair<string, string>(token, type));
}

void SymbolTable::displayTable()
{
	for (auto i = table.begin(); i != table.end(); i++)
	{
		cout << "Token : " << (i->first) << " Type : " << i->second << endl;
	}
}
vector<pair<string, string>> SymbolTable::getTable()
{
	return table;
}
void SymbolTable::clearTable() {
	table.clear();
}