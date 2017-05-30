#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

struct token_pair
{
	string name;
	string value;
};

class Lexer
{
public:
	vector<token_pair> getTokens(string fname);
	struct tokens
	{
		string name;
		string rx;
		int priority;
	};
	vector<Lexer::tokens> getRegexFromFile();
	vector<Lexer::tokens> findMatch(string str, vector<Lexer::tokens> & myRegex);
private:
	void eraseWhitespaces(string & str);
	string readCodeFromFile(string fname);
};