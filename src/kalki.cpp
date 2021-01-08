#include <iostream>
#include <vector>
#include <cmath>

#define SEP ':'
#define NEPER 2.718281828459
#define PI 3.141592653590

using namespace std;

double calcRPN(string expr, unsigned char* error);
double calcRPN(string expr, unsigned char* error, bool verbose);

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
			cout << "  -l\t\tlist operators, constants and functions availables." << endl;
			cout << "  -h, --help\tshow this help." << endl;
		}
		else if(string(argv[1])=="-l")
		{	
			cout << "Operators :" << endl;
			cout << "+\t-\t*\t/\t^" << endl;

			cout << "\nConstants :" << endl;
			cout << "pi\te" << endl;

			cout << "\nFunctions :" << endl;
			cout << "cos\tsin\ttan" << endl;
			cout << "arccos\tarcsin\tarctan" << endl;
			cout << "exp\tln\tlog2" << endl;
			cout << "log10" << endl;
		}
	}
	else
	{
		unsigned char error;
		double result;
		std::vector<string> params;
		for (int i = 1; i < argc; i++)
		{
			if(argv[i][0]=='-')
			{
				params.push_back(argv[i]);
			}
			else
			{
				result = calcRPN(argv[i], &error);
				if(error==0)
					cout << result << endl;
				else
					cout << "error=" << (int)error << endl;
			}
		}
	}
	return 0;
}

double calcRPN(string expr, unsigned char* error)
{
	vector<double> stack;
	string word = "";
	*error = 0;
	for (int i = 0; i <= expr.length(); i++)
	{
		if(i==expr.length() || expr[i]==SEP)
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
			else
			{
				if(i==expr.length())
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
		*error = *error==0 ? (unsigned char)3 : *error;
		return 0;
	}
}

double calcRPN(string expr, unsigned char* error, bool verbose)
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
}