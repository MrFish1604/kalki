#include <iostream>
#include <vector>

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