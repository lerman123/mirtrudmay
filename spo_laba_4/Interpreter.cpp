#include "Interpreter.h"

vector<string> Interpreter::get_reverse_polish_notation(vector<token_pair> code)
{
	vector<string> rpn;

	vector<token_pair> buff;
	vector<token_pair> buff2;
	vector<token_pair> buff3;

	vector<int> labels;
	code.push_back({ "end", "end" });

	for (int i = 0; i < code.size(); ++i)
	{
		if (i == 57)
			int s = 13;

		if (code[i].name == "KW_IF" || code[i].name == "KW_FOR")
			buff3.push_back(code[i]);
		else
		{
			if (code[i].name == "LBRACE")
				buff2.push_back(code[i]);
			else
			{
				if (code[i].name == "DIGIT" || code[i].name == "VAR" || code[i].name == "UNA_ARITHM_OPER")
					rpn.push_back(code[i].value);
				else
				{
					if (buff.empty() && code[i].value != "=" && code[i].value != "}" && code[i].value != ";" && code[i].value != "end")
						buff.push_back(code[i]);
					else
					{
						if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
						{
							while (!buff.empty())
							{
								if (buff.back().name == "BIN_ARITHM_OPER")
								{
									rpn.push_back(buff.back().value);
									buff.pop_back();
								}
								else break;
							}
							buff.push_back(code[i]);
						}

						if (code[i].value == "*" || code[i].value == "/")
						{
							if (buff.back().value == "*" || buff.back().value == "/")
							{
								rpn.push_back(buff.back().value);
								buff.pop_back();
							}
							else
								buff.push_back(code[i]);
						}

						if (code[i].value == ")")
						{
							while (buff.back().value != "(")
							{
								rpn.push_back(buff.back().value);
								buff.pop_back();
							}

							if (buff.back().value == "(")
								buff.pop_back();
							
							if (buff3.back().value == "if" && buff3.size() > labels.size())
							{
								labels.push_back(rpn.size());
								rpn.push_back("void_label");
								rpn.push_back("!F");
							}

							if (!buff2.empty() && buff2.back().value != "{")
								buff2.pop_back();
						}

						if (code[i].value == "(")
							buff.push_back(code[i]);

						if (code[i].value == "}")
						{
							if (!buff2.empty())
							{
								if (buff2.back().value == "{" && buff3.back().name == "KW_IF")
								{
									rpn[labels.back()] = "@" + to_string(rpn.size() + 1);
									labels.pop_back();
									buff2.pop_back();
									buff3.pop_back();
								}
								else
								{
									if (buff2.back().value == "{" && buff3.back().name == "KW_FOR")
									{
										rpn.push_back("@" + to_string(labels.back() + 1));
										rpn.push_back("!");
										labels.pop_back();
										buff2.pop_back();
										buff3.pop_back();

										rpn[labels.back()] = "@" + to_string(rpn.size() + 1);
										labels.pop_back();
										buff2.pop_back();
										buff3.pop_back();
									}
								}
							}
						}

						if (code[i].value == "=")
							buff2.push_back(code[i]);

						if (code[i].value == ";")
						{
							while (!buff.empty() && buff.back().value != "(")
							{
								rpn.push_back(buff.back().value);
								buff.pop_back();
							}

							while (!buff2.empty() && buff2.back().value != "{")
							{
								rpn.push_back(buff2.back().value);
								buff2.pop_back();
							}

							if (!buff3.empty())
							{
								if (buff3.back().name == "KW_FOR")
								{
									if (buff3.size() > labels.size())
										labels.push_back(rpn.size());
									else
									{
										if (buff3.size() == labels.size())
										{
											if (buff3.back().value == "for")
											{
												buff3.push_back({ "KW_IF", "if" });
												labels.push_back(rpn.size());
												rpn.push_back("void_label");
												rpn.push_back("!F");
											}
										}
									}
								}
							}
						}

						if (code[i].value == "end")
						{
							while (!buff.empty())
							{
								rpn.push_back(buff.back().value);
								buff.pop_back();
							}
							while (!buff3.empty())
							{
								if (buff3.back().name == "KW_IF")
								{
									rpn[labels.back()] = "@" + to_string(rpn.size() + 1);
									labels.pop_back();
									buff3.pop_back();
								}
							}
						}
					}
				}
			}
		}
	}

	return rpn;
}

vector<string> Interpreter::getSimpleRPN(vector<token_pair> code)
{
	vector<string> rpn;
	vector<token_pair> buff;
	code.push_back({ "end", "end" });

	for (int i = 0; i < code.size(); ++i)
	{
		if (code[i].name == "DIGIT" || code[i].name == "VAR")
			rpn.push_back(code[i].value);
		else
		{
			if (buff.empty())
				buff.push_back(code[i]);
			else
			{
				if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
				{
					while (!buff.empty())
					{
						if (buff.back().name == "BIN_ARITHM_OPER")
						{
							rpn.push_back(buff.back().value);
							buff.pop_back();
						}
						else break;
					}
					buff.push_back(code[i]);
				}

				if (code[i].value == "*" || code[i].value == "/")
				{
					if (buff.back().value == "*" || buff.back().value == "/")
					{
						rpn.push_back(buff.back().value);
						buff.pop_back();
					}
					else
						buff.push_back(code[i]);
				}

				if (code[i].value == ")")
				{
					while (buff.back().value != "(")
					{
						rpn.push_back(buff.back().value);
						buff.pop_back();
					}

					if (buff.back().value == "(")
						buff.pop_back();
				}

				if (code[i].value == "(")
					buff.push_back(code[i]);

				if (code[i].value == "end")
				{
					while (!buff.empty())
					{
						rpn.push_back(buff.back().value);
						buff.pop_back();
					}
				}
			}
		}
	}

	return rpn;
}