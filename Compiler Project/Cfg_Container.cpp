#include "Cfg_Container.h"

void CFG_Container::recur(vector<pair<string, string>> tokens, int iter, string non_terminal) {
	static bool isChildMatched = false;
	static int innerCounter = 0;
	int tempIter = 0;
	int iterRealVal = iter;
	static int nestedCounter = 1;
	bool shouldExit = false;
	vector< vector<string> > symbols = this->cfg_conatiner.find(non_terminal)->second;
	vector<string>::const_iterator itr_col;
	for (auto& itr_row : symbols) {
		if (isChildMatched)
			break;
		for (itr_col = itr_row.begin(); itr_col != itr_row.end(); itr_col++) {
			if (isNonTerminal(*itr_col)) {
				//cout << "Non_Terminal: " << *itr_col << endl;
				recur(tokens, iter, *itr_col);
				if (isChildMatched) {
					iter += innerCounter + nestedCounter;
					nestedCounter++;
				}
			}
			else {
				if (*itr_col == tokens[iter].second) {
					if (itr_col == itr_row.end() - 1) {
						//cout << "\nAll Matched: " << non_terminal << endl;
						this->lineTypes.push_back(non_terminal);
						innerCounter = tempIter;
						isChildMatched = true;
						break;
					}
				}
				else
				{
					this->lineTypes.clear();
					iter = iterRealVal;
					if (isChildMatched) isChildMatched = false;
					break;
				}
				iter++;
				tempIter++;
				if (iter == tokens.size())
					break;
			}
		}
	}
}

