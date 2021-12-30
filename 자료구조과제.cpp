#include <iostream>
#include <string>
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

void Stack::push(string element){
	stackarr[++stacktop] = element;
}

string Stack::pop(){
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

int main() {
	int input;
	string order;
	cin >> input;
	cin.ignore();
	Stack s;
		for (int i = 0; i <input; i++) {
			getline(cin, order);
			if (order == "pop") {
				cout << s.pop() << endl;
			}
			else if (order == "size") {
				cout << s.size() << endl;
			}
			else if (order == "empty") {
				cout << s.empty() << endl;
			}
			else if (order == "top") {
				cout << s.top() << endl;
			}
			else{
				string element;
				element = order.erase(0, 5);
				s.push(element);
			}
	}
	
}