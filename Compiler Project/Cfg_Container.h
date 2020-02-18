#pragma once
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class CFG_Container {
	map<string, vector< vector<string> > > cfg_conatiner;
	vector<string> lineTypes;
public:
	CFG_Container() {
		ifstream fin;
		fin.open("cfgData.txt");
		cfg_conatiner = this->processFile(fin);
	}
	void showCfg() {
		for (auto& itr_map : getCfgConatiner()) {
			cout << "Non-Terminal: " << itr_map.first << endl;
			for (auto& itr_vector_row : itr_map.second) {
				cout << "Symbols: ";
				for (auto& itr_vector_col : itr_vector_row)
					cout << itr_vector_col << " " << itr_vector_col.length() << "  ";
				cout << endl;
			}
			cout << endl;
		}
	}
	map<string, vector< vector<string> > > getCfgConatiner() {
		return cfg_conatiner;
	}

	bool isAddable(char c) {
		return (c == '(') || (c == ')')
			|| (c == '{') || (c == '}')
			|| (c == ';')
			|| (c == '=')
			|| (c == '!')
			|| (c == '<')
			|| (c == '>');
	}
	map<string, vector< vector<string> > > processFile(ifstream& fin) {
		string line = "";
		//Temp Holder
		vector<string> rules;
		string nonTerminal = "";
		string tempWord = "";
		int i;
		while (getline(fin, line))
		{
			if (line != "") {

				i = 0;
				while (isspace(line[i]))
					i++;
				while (!isspace(line[i]))
					nonTerminal += line[i++];
				while (!(isalpha(line[i]) || isAddable(line[i])))
					i++;

				while (i <= line.length())
				{

					if (isalnum(line[i]) || isAddable(line[i]))
						tempWord += line[i];
					else if (line[i] == '|') {
						cfg_conatiner.insert(pair<string, vector< vector<string> > >(nonTerminal, vector< vector<string> >()));
						cfg_conatiner[nonTerminal].push_back(rules);
						rules.clear();
						i++;
					}
					else if (isspace(line[i]) || line[i] == '\0') {
						if (tempWord != "")
						{
							rules.push_back(tempWord);
							tempWord.clear();
						}
					}
					i++;
				}
				cfg_conatiner.insert(pair<string, vector< vector<string> > >(nonTerminal, vector< vector<string> >()));
				cfg_conatiner[nonTerminal].push_back(rules);
				rules.clear();
				tempWord.clear();
				nonTerminal.clear();
			}
		}
		return cfg_conatiner;
	}
	bool isNonTerminal(string word) {
		return cfg_conatiner.find(word) != cfg_conatiner.end();
	}
	void clearLines()
	{
		this->lineTypes.clear();
	}
	vector<string> getLineTypes()
	{
		vector<string> temp = this->lineTypes;
		this->lineTypes.clear();
		return temp;
	}
	void recur(vector<pair<string, string>> tokens, int iter, string non_terminal);
};


