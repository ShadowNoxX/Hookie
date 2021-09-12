#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

std::string slurp(const char* filename) {
	using namespace std;
	ifstream fs;
	fs.open(filename, ios::binary);
	if (fs.fail()) {
		cerr << "Failed to open file!\n";
		return "No";
	}
	fs.seekg(0, ios::end);
	size_t i = fs.tellg();
	char* buf = new char[i];
	fs.seekg(0, ios::beg);
	fs.read(buf, i);
	fs.close();
	string s;
	s.assign(buf, i);
	delete[] buf;
	return s;
}

int main(int argc, char* argv[])
{
	using namespace std;
	if (argc == 1 || argc > 2) {
		cerr << "You need to specify a file!" << endl;
		return 1;
	}
	regex regexp(R"(https:\/\/discord\.com\/api\/webhooks\/[^\/]+\/[^\/]{68})");
	string s = slurp(argv[1]);
	if (s == "No") {
		return 1;
	}
	smatch m;
	regex_search(s, m, regexp);

	
	bool found = false;
	for (auto x : m) {
		found = true;
		cout << "Found : " << x << endl;
	}

	if (!found) {
		cout << "This file doesn't contain any webhook string" << endl;
	}
}

