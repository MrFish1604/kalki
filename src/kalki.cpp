#include <iostream>
#include <vector>
#include <cmath>

#define SEP ':'
#define NEPER 2.718281828459
#define PI 3.141592653590

using namespace std;

double calcRPN(string expr, unsigned char* error, double* vars, const char sep=SEP);
double calcRPN(string expr, double* lastResult, unsigned char* error, double* vars, const char sep=SEP);
/*double calcRPN(string expr, unsigned char* error, bool verbose);*/

int main(int argc, char const *argv[])
{
	const char* help = "--help";
	if(argc>1)
	{
		if(string(argv[1])=="--help" || string(argv[1])=="-h")
		{
			cout << "Usage : kalki [OPTION]... [EXPRESSION]..." << endl;
			cout << "\nExpressions must be separate by spaces." << endl;
			cout << "Terms must be separate by ':'.\te.g. (1+2)*3 => 1:2:+:3:*\n" << endl;
			cout << "  -c\t\tstart consol, use space rather than ':'." << endl;
			cout << "  -l\t\tlist operators, constants and functions availables." << endl;
			cout << "  -h, --help\tshow this help." << endl;
		}
		else if(string(argv[1])=="-l")
		{	
			cout << "Operators :" << endl;
			cout << "+\t-\t*\t/\t^" << endl;
			cout << "You can use '$' to get the last result.\te.g. 1:2:+ 3:$:*  OUTPUT  3 9" << endl;

			cout << "\nConstants :" << endl;
			cout << "pi\te" << endl;

			cout << "\nFunctions :" << endl;
			cout << "cos\tsin\ttan" << endl;
			cout << "arccos\tarcsin\tarctan" << endl;
			cout << "exp\tln\tlog2" << endl;
			cout << "log10\tsqrt" << endl;
		}
	}
	unsigned char error;
	double result;
	std::vector<string> params;
	double lastResult;
	bool lastResultSet = false;
	double vars[26];
	for(int i=0; i<26; i++) vars[i]=0;
	for (int i = 1; i < argc; i++)
	{
		if(argv[i][0]=='-')
		{
			if(string(argv[i])=="-c")
			{
				cout << "Enter 'exit' to leave the program\n" << endl;
				while(true)
				{
					string expr;
					cout << "> ";
					getline(cin, expr);
					if(expr == "exit")
						break;
					if(lastResultSet)
						result = calcRPN(expr, &lastResult, &error, vars, ' ');
					else
					{
						result = calcRPN(expr, &error, vars, ' ');
						lastResultSet = true;
					}
					lastResult = result;
					if(error==0)
						cout << "= " << result << endl << endl;
					else
						cout << "error= " << (int)error << endl;
				}
			}
			else
				params.push_back(argv[i]);
		}
		else
		{
			if(lastResultSet)
				result = calcRPN(argv[i], &lastResult, &error, vars, SEP);
			else
			{
				result = calcRPN(argv[i], &error, vars, SEP);
				lastResultSet = true;
			}
			lastResult = result;
			if(error==0)
				cout << result << endl;
			else
				cout << "error=" << (int)error << endl;
		}
	}
	return 0;
}

double calcRPN(string expr, unsigned char* error, double* vars, const char sep)
{
	vector<double> stack;
	vector<char> toDef;
	vector<string> defed;
	string word = "";
	*error = 0;
	for (int i = 0; i <= expr.length(); i++)
	{
		if(i==expr.length() || expr[i]==sep)
		{
			if(word == "+")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b + a;
				}
				else
					{*error=1;}
			}
			else if(word == "-")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b - a;
				}
				else
					{*error=1;}
			}
			else if (word == "*")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b * a;
				}
				else
					{*error=1;}
			}
			else if (word == "/")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b / a;
				}
				else
					{*error=1;}
			}
			else if (word == "^")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = pow(b, a);
				}
				else
					{*error=1;}
			}
			else if (word == "sqrt")
			{
				if(stack.size()>0)
					stack.back() = sqrt(stack.back());
				else
					*error = 1;
			}
			else if (word == "cos")
			{
				if(stack.size()>0)
					stack.back() = cos(stack.back());
				else
					*error = 1;
			}
			else if (word == "sin")
			{
				if(stack.size()>0)
					stack.back() = sin(stack.back());
				else
					*error = 1;
			}
			else if (word == "tan")
			{
				if(stack.size()>0)
					stack.back() = tan(stack.back());
				else
					*error = 1;
			}
			else if(word == "arccos" or word == "acos")
			{
				if(stack.size()>0)
					stack.back() = acos(stack.back());
				else
					*error = 1;
			}
			else if(word == "arcsin" or word == "asin")
			{
				if(stack.size()>0)
					stack.back() = asin(stack.back());
				else
					*error = 1;
			}
			else if(word == "arctan" or word == "atan")
			{
				if(stack.size()>0)
					stack.back() = atan(stack.back());
				else
					*error = 1;
			}
			else if (word == "exp")
			{
				if(stack.size()>0)
					stack.back() = exp(stack.back());
				else
					*error = 1;
			}
			else if (word == "ln" or word == "log")
			{
				if(stack.size()>0)
					stack.back() = log(stack.back());
				else
					*error = 1;
			}
			else if (word == "log2")
			{
				if(stack.size()>0)
					stack.back() = log2(stack.back());
				else
					*error = 1;
			}
			else if (word == "log10")
			{
				if(stack.size()>0)
					stack.back() = log10(stack.back());
				else
					*error = 1;
			}
			else if (word == "=")
			{
				double a = stack.back();
				stack.pop_back();
				stack.pop_back();
				vars[toDef.back()-25] = a;
				defed.push_back("");
				defed.back() = defed.back() + toDef.back() + '=' + to_string(a);
				toDef.pop_back();
			}
			else
			{
				if(i==expr.length() && stack.size()!=0)
					*error = 4;
				else
				{
					try
						{stack.push_back(stod(word));}
					catch(invalid_argument)
					{
						if(word=="e")
							stack.push_back(NEPER);
						else if (word=="pi")
							stack.push_back(PI);
						else if (word.length()==1)
						{
							if(word[0]>96 && word[0]<123)
							{
								stack.push_back(vars[word[0]-25]);
								toDef.push_back(word[0]);
							}
							else
							{
								*error = 2;
								break;
							}
						}
						else
						{
							*error = 2;
							break;
						}
					}
				}
			}
			word = "";
		}
		else
			word += expr[i];
	}
	if(stack.size()==1)
		return stack[0];
	else
	{
		if(defed.size()==0)
			*error = *error==0 ? (unsigned char)3 : *error;
		return 0;
	}
}

double calcRPN(string expr, double* lastResult, unsigned char* error, double* vars, const char sep)
{
	vector<double> stack;
	vector<char> toDef;
	vector<string> defed;
	string word = "";
	*error = 0;
	for (int i = 0; i <= expr.length(); i++)
	{
		if(i==expr.length() || expr[i]==sep)
		{
			if(word == "+")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b + a;
				}
				else
					{*error=1;}
			}
			else if(word == "-")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b - a;
				}
				else
					{*error=1;}
			}
			else if (word == "*")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b * a;
				}
				else
					{*error=1;}
			}
			else if (word == "/")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b / a;
				}
				else
					{*error=1;}
			}
			else if (word == "^")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = pow(b, a);
				}
				else
					{*error=1;}
			}
			else if (word == "sqrt")
			{
				if(stack.size()>0)
					stack.back() = sqrt(stack.back());
				else
					*error = 1;
			}
			else if (word == "cos")
			{
				if(stack.size()>0)
					stack.back() = cos(stack.back());
				else
					*error = 1;
			}
			else if (word == "sin")
			{
				if(stack.size()>0)
					stack.back() = sin(stack.back());
				else
					*error = 1;
			}
			else if (word == "tan")
			{
				if(stack.size()>0)
					stack.back() = tan(stack.back());
				else
					*error = 1;
			}
			else if(word == "arccos" or word == "acos")
			{
				if(stack.size()>0)
					stack.back() = acos(stack.back());
				else
					*error = 1;
			}
			else if(word == "arcsin" or word == "asin")
			{
				if(stack.size()>0)
					stack.back() = asin(stack.back());
				else
					*error = 1;
			}
			else if(word == "arctan" or word == "atan")
			{
				if(stack.size()>0)
					stack.back() = atan(stack.back());
				else
					*error = 1;
			}
			else if (word == "exp")
			{
				if(stack.size()>0)
					stack.back() = exp(stack.back());
				else
					*error = 1;
			}
			else if (word == "ln" or word == "log")
			{
				if(stack.size()>0)
					stack.back() = log(stack.back());
				else
					*error = 1;
			}
			else if (word == "log2")
			{
				if(stack.size()>0)
					stack.back() = log2(stack.back());
				else
					*error = 1;
			}
			else if (word == "log10")
			{
				if(stack.size()>0)
					stack.back() = log10(stack.back());
				else
					*error = 1;
			}
			else if (word == "=")
			{
				double a = stack.back();
				stack.pop_back();
				stack.pop_back();
				vars[toDef.back()-25] = a;
				defed.push_back("");
				defed.back() = defed.back() + toDef.back() + '=' + to_string(a);
				toDef.pop_back();
			}
			else
			{
				if(i==expr.length() && stack.size()!=0)
					*error = 4;
				else
				{
					try
						{stack.push_back(stod(word));}
					catch(invalid_argument)
					{
						if(word=="e")
							stack.push_back(NEPER);
						else if (word=="pi")
							stack.push_back(PI);
						else if (word=="$")
							stack.push_back(*lastResult);
						else if (word.length()==1)
						{
							if(word[0]>96 && word[0]<123)
							{
								stack.push_back(vars[word[0]-25]);
								toDef.push_back(word[0]);
							}
							else
							{
								*error = 2;
								break;
							}
						}
						else
						{
							*error = 2;
							break;
						}
					}
				}
			}
			word = "";
		}
		else
			word += expr[i];
	}
	if(stack.size()==1)
		return stack[0];
	else
	{
		if(defed.size()==0)
			*error = *error==0 ? (unsigned char)3 : *error;
		return 0;
	}
}

/*double calcRPN(string expr, unsigned char* error, double* vars, bool verbose)
{
	vector<double> stack;
	string word = "";
	*error = 0;
	for (int i = 0; i < expr.length(); i++)
	{
		if(verbose)
		{
			cout << "\nstack=";
			for(int n=0; n<stack.size(); n++)
				cout << stack[n] << ":";
			cout << "\t";
		}
		if(expr[i]==SEP)
		{
			if(word == "+")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					if(verbose) cout << b << '+' << a;
					b = b + a;
				}
				else
					{*error=1; cout << "RPN syntaxe error" << endl; break;}
			}
			else if(word == "-")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					if(verbose) cout << b << '-' << a;
					b = b - a;
				}
				else
					{*error=1; cout << "RPN syntaxe error" << endl; break;}
			}
			else if (word == "*")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					if(verbose) cout << b << '*' << a;
					b = b * a;
				}
				else
					{*error=1; cout << "RPN syntaxe error" << endl; break;}
			}
			else if (word == "/")
			{
				if(stack.size()>1)
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					if(verbose) cout << b << '/' << a;
					b = b / a;
				}
				else
					{*error=1; cout << "RPN syntaxe error" << endl; break;}
			}
			else if (word == "sqrt")
			{
				if(stack.size()>0)
					stack.back() = sqrt(stack.back());
				else
					*error = 1;
			}
			else if (word == "cos")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = cos(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "sin")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = sin(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "tan")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = tan(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if(word == "arccos" or word == "acos")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = acos(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if(word == "arcsin" or word == "asin")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = asin(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if(word == "arctan" or word == "atan")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = atan(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "exp")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = exp(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "ln" or word == "log")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = log(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "log2")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = log2(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "log10")
			{
				if(stack.size()>0)
				{
					double& a = stack.back();
					a = log10(a);
					if(verbose)
						cout << word << '(' << a << ')';
				}
				else
					*error = 1;
			}
			else if (word == "=")
			{
				double a = stack.back();
				stack.pop_back();
				char c = stack.back();
			}
			else
			{
				try 
				{
					stack.push_back(stod(word));
				}
				catch(invalid_argument)
				{
					cout << word << " was not declared" << endl;
					*error = 2;
					break;
				}
			}
			word = "";
		}
		else
			word += expr[i];
	}
	cout << endl;
	if(stack.size()==1)
		return stack[0];
	else
	{
		*error = *error==0 ? (unsigned char)3 : *error;
		return 0;
	}
}*/