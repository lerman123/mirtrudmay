#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа 4\n\n";
	cout << "Введите имя файла:\n";
	string filename;
	cin >> filename;

	Lexer lexer;
	vector<token_pair> tokens = lexer.getTokens(filename);

	if (!tokens.empty())
	{
		cout << "\nЛексер не нашел ошибок.\n";

		Parser parser;
		bool correct = parser.checkSyntax(tokens);
		if (correct)
			cout << "\nПарсер не нашел ошибок.\n";
		else
			cout << "\nПарсер нашел ошибки.\n";
	}
	else
		cout << "\nЛексер нашел ошибки.\n";

	Interpreter interpr;
	vector<string> rpn = interpr.get_reverse_polish_notation(tokens);

	cout << endl;
	for (int i = 0; i < rpn.size(); ++i)
		cout << i + 1 << " " << rpn[i] << "\n";

	cout << "\n";
	system("pause");
}