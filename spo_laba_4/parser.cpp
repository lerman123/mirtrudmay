#include "Parser.h"

bool Parser::checkSyntax(vector<token_pair> tokens)
{
	string tokensStr;
	for (int i = 0; i < tokens.size(); ++i)
		tokensStr = tokensStr + tokens[i].name + " ";

	tokensStr.erase(tokensStr.size() - 1, 1);
	cout << "tokensInStr --> ~" << tokensStr << "~\n";

	vector<token> syntax_rx = getSyntaxRegex();

	cout << "\n";
	for (int i = 0; i < syntax_rx.size(); ++i)
	{
		tr1::regex rx(syntax_rx[i].rx);
		tr1::match_results<const char *> name;
		if (tr1::regex_search(tokensStr.c_str(), name, rx))
			cout << left << setw(18) << syntax_rx[i].name << " found\n";
		else
			cout << left << setw(18) << syntax_rx[i].name << " not found!\n";
	}

	tr1::regex rx(syntax_rx[0].rx);
	return tr1::regex_search(tokensStr.c_str(), rx);
}

vector<token> Parser::getRegexFromFile()
{
	vector<token> res;
	ifstream rxFile("syntax.txt");

	if (!rxFile.is_open())
	{
		cout << "\nFile with regular expressions syntax.txt can't be opened!\n";
		exit(0);
	}
	else
	{
		token syntax;
		while (!rxFile.eof())
		{
			string regx;
			getline(rxFile, regx);
			if (regx.empty())
				break;

			string rxName;
			string rxRx;

			tr1::regex rxN("^[a-z_]+");
			tr1::match_results<const char *> name;

			tr1::regex_search(regx.c_str(), name, rxN);
			rxName = name.str();
			regx.erase(0, name.str().size() + 2);
			rxRx = regx;
			
			res.push_back(token{ rxName , rxRx });
		}
		rxFile.close();
	}
	return res;
}

vector<token> Parser::getSyntaxRegex()
{
	vector<token> syntaxRx = getRegexFromFile();

	for (int k = 0; k < 5; ++k)
		for (int i = 0; i < syntaxRx.size(); ++i)
			for (int j = 0; j < syntaxRx.size(); ++j)
			{
				tr1::regex rxN(syntaxRx[j].name);
				syntaxRx[i].rx = tr1::regex_replace(syntaxRx[i].rx.c_str(), rxN, syntaxRx[j].rx);
			}
	syntaxRx[0].rx = "^" + syntaxRx[0].rx + "$";

	return syntaxRx;
}