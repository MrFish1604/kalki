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
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b + a;
				}
				else if(word == "-")
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b - a;
				}
				else if (word == "*")
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b * a;
				}
				else if (word == "/")
				{
					double a = stack.back();
					stack.pop_back();
					double& b = stack.back();
					b = b / a;
				}
				else
					stack.push_back(stod(word));
				word = "";
			}
			else
				word += expr[i];
		}
		cout << stack[0] << endl;
	}
	return 0;
}