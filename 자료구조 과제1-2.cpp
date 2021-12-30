#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Stack {
private:
	int stacktop;
	string* stackarr;
public:
	Stack() {
		stacktop = -1;
		stackarr = new string[10000];
	}
	void push(string element);
	string pop();
	int size();
	string empty();
	string top();
};

void Stack::push(string element) {
	stackarr[++stacktop] = element;
}

string Stack::pop() {
	if (stacktop == -1) {
		return "empty";
	}
	else return stackarr[stacktop--];
}

int Stack::size() {
	return stacktop + 1;
}

string Stack::empty() {
	if (stacktop == -1) {
		return "empty";
	}
	else return "not empty";
}

string Stack::top() {
	if (stacktop == -1) { return "empty"; }
	else return stackarr[stacktop];

}
//연산자 우선순위 메소드
inline int prec(char op) {
	switch (op) {
	case'(': case')': return 0;
	case'+': case'-': return 1;
	case'*': case'/': return 2;
	}
	return -1;
}

vector<string> infix_to_postfix(const vector<string>& expr) {
	vector<string> postfix;
	Stack cal;
	Stack num;
	char op;
	for (int i = 0; i < expr.size(); i++) {
		if (expr[i] == "(") {
			cal.push(expr[i]);
		}
		else if (expr[i] == ")") {
			while (cal.empty() != "empty") {
				op = cal.top()[0];
				if (op == '(') { cal.pop(); break; }
				else postfix.push_back(cal.pop());
			}
		}
		else if (expr[i] == "-" || expr[i] == "+" || expr[i] == "*" || expr[i] == "/") {
			while (cal.empty() != "empty") {
				//cal.push(expr[i]);
				op = cal.top()[0];
				if (prec(expr[i][0]) <= prec(op)) {
					postfix.push_back(cal.pop());
				}

				else break;
			}
			cal.push(expr[i]);
		}
		else {
			postfix.push_back(expr[i]); //숫자들어감 
		}
	}
	while (cal.empty() != "empty") {
		postfix.push_back(cal.pop());
	}
	return postfix;
}

double calc_postfix(const vector<string>& expr) {
	double result = 0.0;
	Stack s;
	double first, second;
	for (int i = 0; i < expr.size(); i++) {
		if (expr[i] == "+") {
			second = stod(s.pop());
			first = stod(s.pop());
			result = first + second;
			s.push(to_string(result));
		}
		else if (expr[i] == "-") {
			second = stod(s.pop());
			first = stod(s.pop());
			result = first - second;
			s.push(to_string(result));
		}
		else if (expr[i] == "*") {
			second = stod(s.pop());
			first = stod(s.pop());
			result = first * second;
			s.push(to_string(result));
		}
		else if (expr[i] == "/") {
			second = stod(s.pop());
			first = stod(s.pop());
			if (second == 0) {
				throw runtime_error("zero division error");
			}
			else result = first / second;

			s.push(to_string(result));
		}
		else {
			s.push(expr[i]);
		}
	}


	return result;
}

int main() {
	vector<string> expr;
	vector<string> aa;
	string line, token;

	getline(cin, line);
	stringstream ss(line);

	while (getline(ss, token, ' '))
		expr.push_back(token);


	try {
		cout << fixed << setprecision(2);
		cout << calc_postfix(infix_to_postfix(expr)) << endl;
	}
	catch (const std::runtime_error& error) {
		cout << error.what() << endl;
	}

	return 0;
}