#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������������ ������ 4\n\n";
	cout << "������� ��� �����:\n";
	string filename;
	cin >> filename;

	Lexer lexer;
	vector<token_pair> tokens = lexer.getTokens(filename);

	if (!tokens.empty())
	{
		cout << "\n������ �� ����� ������.\n";

		Parser parser;
		bool correct = parser.checkSyntax(tokens);
		if (correct)
			cout << "\n������ �� ����� ������.\n";
		else
			cout << "\n������ ����� ������.\n";
	}
	else
		cout << "\n������ ����� ������.\n";

	Interpreter interpr;
	vector<string> rpn = interpr.get_reverse_polish_notation(tokens);

	cout << endl;
	for (int i = 0; i < rpn.size(); ++i)
		cout << i + 1 << " " << rpn[i] << "\n";

	cout << "\n";
	system("pause");
}