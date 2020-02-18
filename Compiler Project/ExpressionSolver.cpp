#include "ExpressionSolver.h"

bool ExpressionSolver::isAlphabetOrDigit(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9');
}
int ExpressionSolver::getPrecedence(char c) {
	if (c == '^')
		return 4;
	if (c == '/')
		return 3;
	if (c == '*')
		return 2;
	if (c == '+' || c == '-')
		return 1;
	return -1;
}
bool ExpressionSolver::isWhiteSpace(char c) {
	return c == ' ';
}
bool ExpressionSolver::isOpenBracketStarted(char c) {
	return c == '(';
}
bool ExpressionSolver::isOpenBracketEnded(char c) {
	return c == ')';
}
bool ExpressionSolver::isOperator(char c) {
	return c == '-' || c == '+' || c == '/' || c == '*' || c == '=' || c == '^';
}
string ExpressionSolver::convertInfixToPostfix(string expression) {
	int len = expression.length();
	string tempWord = "";
	string postFixExpression = "";
	stack<string> dataStore;
	for (int i = 0; i < len; i++) {
		if (!isWhiteSpace(expression[i])) {
			if (isAlphabetOrDigit(expression[i]))
			{
				tempWord = expression[i];
				if ((i + 1) < len && isAlphabetOrDigit(expression[i + 1])) {
					tempWord += expression[++i];
					while ((i + 1) < len && isAlphabetOrDigit(expression[i + 1])) {
						tempWord += expression[i + 1];
						i++;
					}
				}
				postFixExpression += tempWord + " ";
			}
			else if (isOpenBracketStarted(expression[i]))
				dataStore.push("(");
			else if (isOpenBracketEnded(expression[i])) {
				while (!dataStore.empty() && dataStore.top() != "(")
				{
					postFixExpression += dataStore.top() + " ";
					dataStore.pop();
				}
				if (dataStore.top() == "(")
					dataStore.pop();
			}
			else {
				while (!dataStore.empty() && getPrecedence(expression[i]) <= getPrecedence(dataStore.top()[0]))
				{
					postFixExpression += dataStore.top() + " ";
					dataStore.pop();
				}
				tempWord = expression[i];
				dataStore.push(tempWord);
			}
		}
	}
	while (!dataStore.empty()) {
		postFixExpression += dataStore.top() + " ";
		dataStore.pop();
	}
	return postFixExpression;
}
string ExpressionSolver::getThreeAccessCodeForArithmetic(string postfix) {
	postfix = convertInfixToPostfix(postfix);
	stack<string> dataStore;
	string threeAccessCode = "";
	string newVarName = "";
	string oldLine, newLine;
	oldLine = newLine = "";
	int len = postfix.length();
	string tempWord = "";
	for (int i = 0; i < len; i++) {
		if (isWhiteSpace(postfix[i])) {
			if (!isOperator(tempWord[0])) {
				newVarName = "temp";
				newVarName += to_string(this->getVarCounter());
				threeAccessCode += newVarName + " = " + tempWord + ";\n";
				setVarCounter(getVarCounter() + 1);
				dataStore.push(newVarName);
			}
			else {
				string firstVar = dataStore.top();
				dataStore.pop();
				string secondVar = dataStore.top();
				dataStore.pop();
				newVarName = "temp";
				newVarName += to_string(this->getVarCounter());
				newLine = secondVar + " " + tempWord[0] + " " + firstVar + ";\n";
				if (oldLine != newLine)
				{
					threeAccessCode += newVarName + " = " + newLine;
					this->setVarCounter(this->getVarCounter() + 1);
					dataStore.push(newVarName);
				}
				else {
					newLine = "temp" + to_string(this->getVarCounter() - 1);
					dataStore.push(newLine);
					dataStore.push(newLine);
				}
				oldLine = newLine;
			}
			tempWord.clear();
		}
		else {
			tempWord += postfix[i];
		}
	}

	return threeAccessCode;
}
int ExpressionSolver::getVarCounter() {
	return this->varCounter;
}
void ExpressionSolver::setVarCounter(int count) {
	varCounter = count;
}