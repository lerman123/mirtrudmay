#pragma once
#include "Parser.h"

class Interpreter
{
public:
	vector<string> get_reverse_polish_notation(vector<token_pair> code);
private:
	vector<string> getSimpleRPN(vector<token_pair> code);
};