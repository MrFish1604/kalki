#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>
#include <stdexcept>

#define SEP ':'
#define NEPER M_E
#define PI M_PI


using namespace std;

double calcRPN(string expr, const char sep=SEP);

double aplusb(const double a, const double b) {return a+b;}
double aminusb(const double a, const double b) {return a-b;}
double atimesb(const double a, const double b) {return a*b;}
double aonb(const double a, const double b) {return a/b;}

map<const string, double(*)(const double, const double)> binope;
map<const string, double(*)(const double)> unope;
map<const string, double> vars;

int main(int argc, char const **argv)
{
	vars["pi"] = PI;
	vars["e"] = NEPER;

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
			cout << "  -c\t\tstart consol, use space rather than ':'." << endl;
			cout << "  -l\t\tlist operators, constants and functions availables." << endl;
			cout << "  -h, --help\tshow this help." << endl;
			continue;
		}
		if(string(argv[i])=="-l")
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
			continue;
		}
		if(string(argv[i])=="-c")
		{
			while(true)
			{
				string uentry;
				cout << ">> ";
				getline(cin, uentry);
				try{
					vars["$"] = calcRPN(uentry, ' ');
					cout << vars["$"] << endl << endl;
				}
				catch(const exception& err){
					cout << err.what() << endl;
				}
			}
			continue;
		}
		try{
			vars["$"] = calcRPN(argv[i], SEP);
			cout << argv[i] << "\t=\t";
			cout << vars["$"] << endl;
		}
		catch(const exception& err)
		{
			cerr << err.what() << endl;
		}
	}
	return 0;
}

void make_calc(stack<double>& stck, string& word)
{
	double (*f2)(const double, const double) = nullptr;
	try{
		f2 = binope.at(word);
	}
	catch(const out_of_range&)
	{
		double (*f1)(const double) = nullptr;
		try{
			f1 = unope.at(word);
		}
		catch(const out_of_range&)
		{
			try{
				stck.push(stod(word));
				return;
			}
			catch(const invalid_argument&)
			{
				try{
					stck.push(vars.at(word));
					return;
				}
				catch(const out_of_range&){
					if(word[0]=='=')
					{
						const string varname = string(word.c_str()+1);
						if(stck.empty())
							throw out_of_range("Unable to set " + varname + " (the stack is empty)");
						vars[varname] = stck.top();
						return;
					}
					throw invalid_argument("Unable to interpret " + word);
				}
			}
		}
		if(stck.empty())
			throw out_of_range(word + " needs 1 operands (" + to_string(stck.size()) + " remain in stack)");
		stck.top() = f1(stck.top());
		return;
	}
	if(stck.size()<2)
	{
		throw out_of_range(word + " needs 2 operands (" + to_string(stck.size()) + " remain in stack)");
	}
	double b = stck.top();
	stck.pop();
	double& a = stck.top();
	a = f2(a, b);
}

double calcRPN(string expr, const char sep)
{
	stack<double> stck;
	string word = "";
	for(int i=0; i<expr.length(); i++)
	{
		const char& c = expr[i];
		if(c==sep)
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
	if(stck.empty())
		throw out_of_range("The stack is empty");
	return stck.top();
}