#pragma once
#include "Lexer.h"

struct token
{
	string name;
	string rx;
};

class Parser
{
public:
	bool checkSyntax(vector<token_pair> tokens);
	vector<token> getSyntaxRegex();
private:
	vector<token> getRegexFromFile();
};