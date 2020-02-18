#include "Parser.h"
vector<pair<string,string>> Parser::tokenize(string line)
{
	table.clearTable();
	string tok = "";
	string state = "";
	string temp;
	for (int i = 0; i < line.length(); i++)
	{
		while (isalnum(line[i]) || line[i] == '_' || line[i] == '.')
		{
			tok += line[i]; i ++;
		}
		if (tok != "")
		{
			state = check.checkValidity(tok);
			if (state != "" && state == "Constant")
				table.push(tok, state);
			else if (state != "" && state == "ID")
				table.push(tok, table.getType(tok));
			tok = "";
		}
		if(line[i] == '{' || line[i] == ';' || line[i] == '}' || line[i] == '(' || line[i] == ')' || line[i] == ':'||
			line[i] == '!' || line[i] == '<' || line[i] == '>' ||line[i] == '=' || line[i] == '-' ||
			line[i] == '+' || line[i] == '/' || line[i] == '*')
		{
			if ((line[i] == '>' || line[i] == '<' || line[i] == '=' || line[i] == '!') && line[i + 1] == '=')
			{
					
				temp = line[i];
				temp += line[i + 1];
				i++;
				table.push(temp);
				//cout << "Token : " << line[i] << line[i + 1] << endl; i++;
			}
			else
			{
				temp = line[i];
				table.push(temp);
				//cout << "Token : " << line[i] << endl;
			}
		}
	}
	//table.displayTable();
	vector<pair<string, string>> tac = table.getTable();
	for (auto i = 0; i < tac.size(); i++)
	{
		if (tac[i].first == "{")
		{
			i++;
			while (tac[i].first != "}")
			{
				tacTokens.push_back(tac[i].first);
				i++;
			}
			tacTokens.push_back("end");
		}
	}
	return table.getTable();
}