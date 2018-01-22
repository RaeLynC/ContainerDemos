// ContainerDemo.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>


void pause() {
	std::cout << "Enter any key to exit...\n";
	std::getchar();
}

enum menu_options {
	m_min = 1, m_bldfile = m_min, m_parsefile, m_pairSTL, m_tupleSTL, \
	m_setSTL, m_multisetSTL, m_exit, m_invalid
};
void print_menu();
int get_menu_option();
void menu_driver();

std::string get_filename();
void buildFile();

bool is_alphastring(std::string s);
void sort_file(std::ifstream & f,
	std::vector<std::string> &sv,
	std::vector<int> &iv,
	std::vector<std::string> &miscv);
void parseFile();

void pairBIT();
void tupleBIT();
void setBIT();
void multisetBIT();


int main()
{
	menu_driver();
	pause();
	return 0;
}

void print_menu() {
	std::cout << "(" << m_bldfile << ") - Build new file\n";
	std::cout << "(" << m_parsefile << ") - Parse file (strings/ints/misc)\n";
	std::cout << "(" << m_pairSTL << ") - Associative Container BIT (pair)\n";
	std::cout << "(" << m_tupleSTL << ") - Associative Container BIT (tuple)\n";
	std::cout << "(" << m_setSTL << ") - Associative Container BIT (set)\n";
	std::cout << "(" << m_multisetSTL << ") - Associative Container BIT (multiset)\n";
	std::cout << "(" << m_exit << ") - Exit\n";
}

int get_menu_option() {
	int option = m_invalid;
	std::string input;
	while (option == m_invalid) {
		print_menu();
		std::cout << "Enter option: ";
		std::getline(std::cin, input);
		try {
			option = std::stoi(input);
			if ((option < m_min) || (option >= m_invalid))
				option = m_invalid;
		}
		catch (std::exception e) {
			std::cout << "Caught exc(" << e.what() << ")\n";
			std::cout << "Invalid option entered (" << input << ")\n";
			option = m_invalid;
		}
	}
	return option;
}

void menu_driver() {
	int option = m_invalid;
	while (option != m_exit) {
		option = get_menu_option();
		switch (option) {
		case m_bldfile:
			buildFile();
			break;
		case m_parsefile:
			parseFile();
			break;
		case m_pairSTL:
			pairBIT();
			break;
		case m_tupleSTL:
			tupleBIT();
			break;
		case m_setSTL:
			setBIT();
			break;
		case m_multisetSTL:
			multisetBIT();
			break;
		default:
			break;
		}
	}
}

std::string get_filename() {
	std::string fname;
	std::cout << "Enter file name: ";
	std::getline(std::cin, fname);
	fname += ".txt";
	return fname;
}

void buildFile() {
	std::ofstream file;
	file.open(get_filename());

	std::vector<std::string> svec;
	std::string input;
	std::cout << "Enter random line or 'exit':\n";
	while (1) {
		std::getline(std::cin, input);
		if (input != "exit")
			svec.push_back(input);
		else break;
	}

	if (file.is_open()) {
		for (auto i : svec)
			file << (i + "\n");
		file.close();
	}
	else std::cout << "(ERR - buildFile) Failed to open file\n";
}

bool is_alphastring(std::string s) {
	return (std::find_if(s.begin(), s.end(), [](char c) { return !std::isalpha(c); }) == s.end());
}

void sort_file(std::ifstream &f,
	std::vector<std::string> &sv,
	std::vector<int> &iv,
	std::vector<std::string> &miscv)
{
	std::string input;
	std::string s;

	while (std::getline(f, input)) {
		std::stringstream ss(input);
		while (std::getline(ss, s, ' ')) {
			if (is_alphastring(s))
				sv.push_back(s);
			else {
				try {
					int value = std::stoi(s);
					iv.push_back(value);
				}
				catch (std::exception e) {
					miscv.push_back(s);
				}
			}
		}
	}
}

void parseFile() {
	std::ifstream file;
	file.open(get_filename());    
	std::vector<std::string> svec;
	std::vector<int> ivec;
	std::vector<std::string> miscvec;

	// Effectively: parse on "\n ", sorting ints/strings/mixed.
	if (file.is_open()) {
		sort_file(file, svec, ivec, miscvec);
		file.close();
	}
	else std::cout << "(ERR - parseStrings) Failed to open file\n";

	std::cout << "Sorted lists:\n";
	std::cout << "Strings:\n";
	for (auto i : svec)
		std::cout << "\t" << i << "\n";
	std::cout << "Numeric:\n";
	for (auto i : ivec)
		std::cout << "\t" << i << "\n";
	std::cout << "Misc:\n";
	for (auto i : miscvec)
		std::cout << "\t" << i << "\n";
}

std::pair<std::string, int> mypairfct(std::string s) {
	return{ s + "hi", 5 };
}

void pairBIT() {
	std::cout << "Pair BIT:\n";

	std::pair<std::string, int> pr{ "Rylee", 4 };
	std::pair<std::string, int> pr1 = make_pair(std::string("Josh"), 11);
	auto pr2 = std::make_pair(std::string("Rylee"), 4);
	auto pr3 = std::make_pair(std::string("Rylee"), 2);

	std::cout << "pr: " << pr.first << " " << pr.second << "\n";
	std::cout << "pr1: " << pr1.first << " " << pr1.second << "\n";
	std::cout << "pr2: " << pr2.first << " " << pr2.second << "\n";

	if (pr == pr1) std::cout << "pr == pr1\n";
	else std::cout << "pr != pr1\n";
	if (pr == pr2) std::cout << "pr == pr2\n";
	else std::cout << "pr != pr2\n";
	if (pr2 < pr3) std::cout << "pr2 < pr3\n";
	else std::cout << "!(pr2 < pr3)\n";

	auto pr4 = mypairfct("yo");
	std::cout << "pr4: " << pr4.first << " " << pr4.second << "\n";
}

void tupleBIT() {

}

void setBIT() {
	std::cout << "Set BIT:\n";
	std::vector<std::string> svec;
	std::vector<int> ivec;
	std::vector<std::string> miscvec;
	std::ifstream file;
	file.open(get_filename());

	// Effectively: parse on "\n ", sorting ints/strings/mixed.
	if (file.is_open()) {
		sort_file(file, svec, ivec, miscvec);
		file.close();
	}
	else std::cout << "(ERR - parseStrings) Failed to open file\n";

	std::cout << "Set BIT:\n";
	std::set<int> myset{ 1, 3, 5, 7, 9, 11 };
	std::initializer_list<int> il = { 0, 2, 4, 6, 8, 10 };
	std::set<int> myset1(il);

	std::cout << "myset:\n";
	for (auto &i : myset)
		std::cout << i << " ";
	std::cout << "\n";
	std::cout << "myset1:\n";
	for (std::set<int>::iterator it = myset1.begin(); it != myset1.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";

	std::cout << "myset vs. svec:\n";
	for (const auto &i : ivec) {
		if (myset.find(i) != myset.end())
			std::cout << i << " is in myset\n";
	}
	std::cout << "myset1 vs. svec:\n";
	for (const auto &i : ivec) {
		if (myset1.find(i) != myset1.end())
			std::cout << i << " is in myset1\n";
	}

	auto retval = myset.emplace(11);
	if (retval.second) std::cout << "11 inserted: " << *retval.first << "\n";
	auto retval1 = myset.emplace(13);
	if (retval1.second) std::cout << "13 inserted: " << *retval1.first << "\n";
}

void multisetBIT() {

}
