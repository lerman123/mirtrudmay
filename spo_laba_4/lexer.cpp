#include "Lexer.h"

vector<token_pair> Lexer::getTokens(string fname)
{
	string s_code = readCodeFromFile(fname);
	vector<Lexer::tokens> regEx = getRegexFromFile();
	vector<token_pair> tokens;

	while (!s_code.empty())
	{
		eraseWhitespaces(s_code);
		vector<Lexer::tokens> tmpTokens;
		string buff;
		bool solved = false;
		if (s_code.size() != 0)
		{
			do
			{
				buff.push_back(s_code[0]);
				tmpTokens = findMatch(buff, regEx);
				if (tmpTokens.empty())
				{
					buff.erase(buff.size() - 1, 1);
					tmpTokens = findMatch(buff, regEx);
					if (tmpTokens.empty())
					{
						buff.push_back(s_code[0]);
						cout << "\n\nОшибка! Неизвестный символ \"" << buff << "\"\n";
						tokens.clear();
						return tokens;
					}

					Lexer::tokens tempResult = tmpTokens[0];
					for (int i = 1; i < tmpTokens.size(); ++i)
					{
						if (tmpTokens[i].priority < tempResult.priority)
							tempResult = tmpTokens[i];
					}

					tokens.push_back({ tempResult.name, buff });
					solved = true;
				}
				else
					s_code.erase(0, 1);
			} while (!solved);
		}
	}

	return tokens;
}

vector<Lexer::tokens> Lexer::getRegexFromFile()
{
	vector<Lexer::tokens> result;
	ifstream regexfile("regex.txt");

	if (!regexfile.is_open())
	{
		cout << "\nФайл с регулярными выражениями regex.txt не может быть открыт!\n";
		exit(0);
	}
	else
	{
		while (!regexfile.eof())
		{
			string regEx;
			getline(regexfile, regEx);
			if (regEx.empty())
				break;
			string rgxName;
			string rgxRx;
			int rx_pr;

			tr1::regex rxN("^[A-Z_]+");
			tr1::match_results<const char *> name;
			tr1::regex_search(regEx.c_str(), name, rxN);

			rgxName = name.str();
			regEx.erase(0, name.str().size() + 1);

			rgxRx = regEx.substr(0, regEx.size() - 2);
			regEx.erase(0, rgxRx.size() + 1);

			rx_pr = atoi(regEx.c_str());

			result.push_back(Lexer::tokens{ rgxName , rgxRx , rx_pr });
		}

		regexfile.close();
	}
	return result;
}

vector<Lexer::tokens> Lexer::findMatch(string str, vector<Lexer::tokens> & myRegex)
{
	vector<tokens> match;
	for (int j = 0; j < myRegex.size(); ++j)
	{
		tr1::regex rx(myRegex[j].rx);
		if (tr1::regex_match(str.begin(), str.end(), rx))
			match.push_back(myRegex[j]);
	}
	return match;
}

void Lexer::eraseWhitespaces(string & str)
{
	char space = ' ';
	char tab = '	';
	char newLine = '\n';
	while (str[0] == space || str[0] == tab || str[0] == newLine)
		str.erase(0, 1);
}

string Lexer::readCodeFromFile(string fname)
{
	ifstream file(fname);
	string code;

	if (!file.is_open())
	{
		cout << "Файл с исходным кодом не может быть открыт!\n";
		exit(0);
	}
	else
	{
		while (!file.eof())
		{
			string buffer;
			getline(file, buffer);
			code = code + " " + buffer;
		}

		file.close();
	}

	return code;
}
