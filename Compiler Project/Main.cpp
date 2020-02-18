#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include "Parser.h"
#include "Cfg_Container.h"
#include "ExpressionSolver.h"

using namespace std;
int varCounter = 0;
vector<string> usedVars;
string getType(string token) {
	if (token == "int")
		return "keyword";
	if (isdigit(token[0]))
	{
		return "Constant";
	}

	if (token == ";" || token == "(" || token == ")" || token == "{" || token == "}" || token == "="
		|| token == "if" || token == "else"
		|| token == "for" || token == "while" || token == "do"
		|| token == "==" || token == "!=" || token == "<=" || token == ">=")
		return token;

	return "Identifier";
}
vector<pair< string, string >> parseLine(string line) {
	string word = "";
	pair<string, string> temp;
	vector<pair< string, string >> tokens;

	for (int i = 0; i < line.length(); i++) {
		if (isspace(line[i])) {
			tokens.push_back(pair<string, string>(word, getType(word)));
			word.clear();
		}
		else
			word += line[i];
	}
	return tokens;
}
string threeAccessCode(string type, vector<pair<string, string>> tokens);

void main() {
	string threeAddressCode;
	Parser parse;
	vector<pair<string, string>> tokens;
	CFG_Container* obj_Cfg = new CFG_Container();
	vector<string> lineTypes;
	//obj_Cfg->showCfg();
	//system("pause");
	string type;
	string line;
	ifstream file;
	file.open("input.txt");
	bool flag = false;
	string expression;
	while (getline(file, line))
	{
		cout <<"Line : " << line << endl;
	
		tokens = parse.tokenize(line);
		int count = 0;
		for (auto i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].first == "+" || tokens[i].first == "-" || tokens[i].first == "*" || tokens[i].first == "/")
			{
				count++;
			}
		}
		if (count > 1)
		{
			for (auto i = 0; i < tokens.size(); i++)
			{
				if (flag)
				{
					expression += tokens[i].first;
				}
				if (tokens[i].first == "=")
				{
					flag = true;
				}
			}
			expression.pop_back();
			ExpressionSolver solveExp;
			solveExp.setVarCounter(varCounter);
			threeAddressCode += solveExp.getThreeAccessCodeForArithmetic(expression);
			varCounter = solveExp.getVarCounter();
			if (tokens[0].first == "int") {
				threeAddressCode += tokens[1].first + " = " + to_string(varCounter) + "\n";
			}
			else {
				threeAddressCode += tokens[0].first + " = " + to_string(varCounter) + "\n";
			}
			expression.clear();
			count = 0;
			flag = false;
		}
		else
		{
			obj_Cfg->recur(tokens, 0, "stmt");
			lineTypes = obj_Cfg->getLineTypes();
			if (!lineTypes.empty())
			{
				cout << "\nMain Type of Line: " << lineTypes.back() << endl << endl;
				threeAddressCode += threeAccessCode(lineTypes.back(), tokens) + "\n";
				
			}
			else {
				cout << "Invalid Line Detected\n";
			}
		}
		
		tokens.clear();
		system("pause");
	}
	
	cout << "TAC: \n\n" << threeAddressCode << endl;
	
	//vector<string> tac = parse.getTACtoken();
	//cout << "\n\nTac Tokens : " << endl;
	//for (auto i = 0; i < tac.size(); i++)
	//{
	//	cout << tac[i] << endl;
	//}

	system("pause");
	return;
}
string threeAccessCode(string type, vector<pair<string, string>> tokens) {
	string tac = "";
	if (type == "whileLoop") {

	}
	if (type == "doWhileLoop") {

	}
	if (type == "forLoop") {

	}
	if (type == "declareWithoutKeywordIdentifier") {

	}
	if (type == "declareWithoutKeywordConstant") {

	}
	if (type == "simpleDeclare") {
		cout << tokens[1].first << endl;
		tac = "temp" + to_string(varCounter) + " = " + tokens[1].first + " ;\n";
		varCounter++;
	}
	if (type == "ifAndElseStatment") {

	}
	return tac;
}
