#include <iostream>
#include <vector>
#include <cmath>

#define SEP ':'

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc>1)
	{
		string expr = argv[1];
		vector<double> stack;
		string word = "";
		for (int i = 0; i < expr.length(); i++)
		{
			if(expr[i]==SEP)
			{
				if(word == "+")
				{
					if(stack.size()>1)
					{
						double a = stack.back();
						stack.pop_back();
						double& b = stack.back();
						// cout << b << '+' << a << endl;
						b = b + a;
					}
					else
						{cout << "RPN syntaxe error" << endl; break;}
				}
				else if(word == "-")
				{
					if(stack.size()>1)
					{
						double a = stack.back();
						stack.pop_back();
						double& b = stack.back();
						// cout << b << '-' << a << endl;
						b = b - a;
					}
					else
						{cout << "RPN syntaxe error" << endl; break;}
				}
				else if (word == "*")
				{
					if(stack.size()>1)
					{
						double a = stack.back();
						stack.pop_back();
						double& b = stack.back();
						// cout << b << '*' << a << endl;
						b = b * a;
					}
					else
						{cout << "RPN syntaxe error" << endl; break;}
				}
				else if (word == "/")
				{
					if(stack.size()>1)
					{
						double a = stack.back();
						stack.pop_back();
						double& b = stack.back();
						// cout << b << '/' << a << endl;
						b = b / a;
					}
					else
						{cout << "RPN syntaxe error" << endl; break;}
				}
				else if (word == "cos")
					stack.back() = cos(stack.back());
				else if (word == "sin")
					stack.back() = sin(stack.back());
				else if (word == "tan")
					stack.back() = tan(stack.back());
				else if(word == "arccos" or word == "acos")
					stack.back() = acos(stack.back());
				else if(word == "arcsin" or word == "asin")
					stack.back() = asin(stack.back());
				else if(word == "arctan" or word == "atan")
					stack.back() = atan(stack.back());
				else if (word == "exp")
					stack.back() = exp(stack.back());
				else if (word == "ln" or word == "log")
					stack.back() = log(stack.back());
				else if (word == "log2")
					stack.back() = log2(stack.back());
				else if (word == "log10")
					stack.back() = log10(stack.back());
				else
				{
					try 
					{
						stack.push_back(stod(word));
					}
					catch(invalid_argument)
					{
						cout << word << " was not declared" << endl;
						break;
					}
				}
				word = "";
			}
			else
				word += expr[i];
		}
		if(stack.size()>0)
			cout << stack[0] << endl;
	}
	return 0;
}