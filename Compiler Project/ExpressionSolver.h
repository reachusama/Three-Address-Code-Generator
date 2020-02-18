#pragma once
#include<stack>
#include<string>
using namespace std;

class ExpressionSolver {
	int varCounter;
public:
	ExpressionSolver() {
		varCounter = 0;
	}
	ExpressionSolver(int varCounter) {
		this->varCounter = varCounter;
	}
	bool isAlphabetOrDigit(char c);
	int getPrecedence(char c);
	string convertInfixToPostfix(string expression);
	string getThreeAccessCodeForArithmetic(string postfix);
	bool isOpenBracketStarted(char);
	bool isOpenBracketEnded(char);
	bool isWhiteSpace(char);
	bool isOperator(char);
	int getVarCounter();
	void setVarCounter(int count);
};
