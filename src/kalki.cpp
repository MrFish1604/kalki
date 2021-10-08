#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

#define SEP ':'
#define NEPER 2.718281828459
#define PI 3.141592653590

using namespace std;

double calcRPN(string expr);

int main(int argc, char const *argv[])
{
//--------------- ARGS -------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
	cout << calcRPN(argv[1]) << endl;
	return 0;
}

double calcRPN(string expr)
{
	stack<double> stck;
	string word = "";
	for(int i=0; i<expr.length(); i++)
	{
		if(expr[i]==':')
		{
			if(word=="+")
			{
				if(stck.size()>1)
				{
					double a = stck.top();
					stck.pop();
					stck.top() += a;
				}
			}
			else if(word=="-")
			{
				if(stck.size()>1)
				{
				double a = stck.top();
				stck.pop();
				stck.top() -= a;
				}
			}
			else if(word=="*")
			{
				if(stck.size()>1)
				{
				double a = stck.top();
				stck.pop();
				stck.top() *= a;
				}
			}
			else if(word=="/")
			{
				if(stck.size()>1)
				{
				double a = stck.top();
				stck.pop();
				stck.top() /= a;
				}
			}
			else
			{
				stck.push(stod(word));
			}
			word = "";
		}
		else
		{
			word += expr[i];
		}
	}
	return stck.top();
}