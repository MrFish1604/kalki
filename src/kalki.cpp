#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>

#define SEP ':'
#define NEPER 2.718281828459
#define PI 3.141592653590

using namespace std;

double calcRPN(string expr, const char sep=SEP);

double aplusb(const double a, const double b) {return a+b;}
double aminusb(const double a, const double b) {return a-b;}
double atimesb(const double a, const double b) {return a*b;}
double aonb(const double a, const double b) {return a/b;}

int main(int argc, char const *argv[])
{
	map<const char*, double(*)(const double, const double)> binope;
	map<const char*, double(*)(const double)> unope;
	map<const char*, double> var;

	var["pi"] = PI;
	var["e"] = NEPER;

	binope["+"] = aplusb;
	binope["-"] = aminusb;
	binope["*"] = atimesb;
	binope["/"] = aonb;
	binope["^"] = pow;

	unope["log"] = log;
	unope["ln"] = log;
	unope["log10"] = log10;
	unope["log2"] = log2;
	unope["exp"] = exp;
	unope["sqrt"] = sqrt;
	unope["cos"] = cos;
	unope["sin"] = sin;
	unope["tan"] = tan;
	unope["arccos"] = acos;
	unope["arcsin"] = asin;
	unope["arctan"] = atan;
	for(int i=0; i<argc; i++)
	{
		if(argv[i]=="--help" || argv[i]=="-h")
		{
			cout << "Usage : kalki [OPTION]... [EXPRESSION]..." << endl;
			cout << "\nExpressions must be separate by spaces." << endl;
			cout << "Terms must be separate by ':'.\te.g. (1+2)*3 => 1:2:+:3:*\n" << endl;
			cout << "  -c\t\tstart consol, use space rather than ':'." << endl;
			cout << "  -l\t\tlist operators, constants and functions availables." << endl;
			cout << "  -h, --help\tshow this help." << endl;
			exit(0);
		}
		if(argv[i]=="-l")
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
			exit(0);
		}
		if(argv[i]=="-c")
		{
			// Start consol
			continue;	
		}
		
		cout << calcRPN(argv[i]) << endl;
	}
	return 0;
}

double calcRPN(string expr, const char sep)
{
	stack<double> stck;
	string word = "";
	for(int i=0; i<expr.length(); i++)
	{
		const char& c = expr[i];
		if(c==':')
		{

		}
		else
		{
			word += c;
		}
	}
	return 0.;
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