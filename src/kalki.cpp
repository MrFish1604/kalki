#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>
#include <stdexcept>

#define SEP ':'
#define NEPER 2.718281828459
#define PI 3.141592653590

using namespace std;

double calcRPN(string expr, const char sep=SEP);

double aplusb(const double a, const double b) {return a+b;}
double aminusb(const double a, const double b) {return a-b;}
double atimesb(const double a, const double b) {return a*b;}
double aonb(const double a, const double b) {return a/b;}

map<const string, double(*)(const double, const double)> binope;
map<const string, double(*)(const double)> unope;
map<const string, double> var;

int main(int argc, char const **argv)
{
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

	for(int i=1; i<argc; i++)
	{
		if(string(argv[i])=="--help" || string(argv[i])=="-h")
		{
			cout << "Usage : kalki [OPTION]... [EXPRESSION]..." << endl;
			cout << "\nExpressions must be separate by spaces." << endl;
			cout << "Terms must be separate by ':'.\te.g. (1+2)*3 => 1:2:+:3:*\n" << endl;
			cout << "  -c\t\tstart consol, use space rather than ':'. (not yet)" << endl;
			cout << "  -l\t\tlist operators, constants and functions availables." << endl;
			cout << "  -h, --help\tshow this help." << endl;
			continue;
		}
		if(string(argv[i])=="-l")
		{
			cout << "Operators :" << endl;
			cout << "+\t-\t*\t/\t^" << endl;
			cout << "You can use '$' to get the last result.\te.g. 1:2:+ 3:$:*  OUTPUT  3 9 (not yet)" << endl;

			cout << "\nConstants :" << endl;
			cout << "pi\te" << endl;

			cout << "\nFunctions :" << endl;
			cout << "cos\tsin\ttan" << endl;
			cout << "arccos\tarcsin\tarctan" << endl;
			cout << "exp\tln\tlog2" << endl;
			cout << "log10\tsqrt" << endl;
			continue;
		}
		if(argv[i]=="-c")
		{
			// TODO -- Start console mode
			continue;	
		}
		cout << argv[i] << "\t=\t";
		cout << calcRPN(argv[i], SEP) << endl;
	}
	return 0;
}

int make_calc(stack<double>& stck, string& word)
{
	try{
		double (*f)(const double, const double) = binope.at(word);
		if(stck.size()<2)
		{
			return 1;
		}
		double b = stck.top();
		stck.pop();
		double& a = stck.top();
		a = f(a, b);
	}
	catch(const out_of_range&)
	{
		try{
			double (*f)(const double) = unope.at(word);
			if(stck.empty())
				return 1;
			
			stck.top() = f(stck.top());
		}
		catch(const out_of_range& err)
		{
			// TODO -- Manage variables
			try{
				stck.push(stod(word));
			}
			catch(const invalid_argument&)
			{
				return 2;
			}
		}
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
			make_calc(stck, word);
			word = "";
		}
		else
		{
			word += c;
		}
	}
	if(word!="")
		make_calc(stck, word);
	return stck.top();
}