#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main() {

	string input;
	string tmp;

	string nc = "\033[0m";
	string color[] = { "\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m", "\033[0;37m",
						"\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m" };
	int j = 0;

	while (getline(cin, tmp))
		input += tmp + "\n";

	map<string, string> m;

	for (size_t i=0; i<input.size(); i++) {
		if (input[i] == '(') {
			string addr = input.substr(i+1, input.find_first_of(')', i) - i - 1);
			if (!m.count(addr)) {
				m[addr] = color[j++];
			}
			cout << m[addr];
		}
		else if (input[i] == ')')
			cout << nc;
		else
			cout << input[i];
	}

	return 0;
}