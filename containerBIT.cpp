#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <cctype>
#include <algorithm>


void pause() {
    std::cout << "Enter any key to exit...\n";
    std::getchar();
}

enum menu_options {
    m_min = 1, m_upload = m_min, m_bldfile, m_parsefile, m_assocSTL, m_exit, m_invalid
};
void print_menu();
int get_menu_option();
void menu_driver();

std::string get_filename();
void uploadFile();
void buildFile();

bool is_alphastring(std::string s);
void sort_file(std::ifstream & f,
    std::vector<std::string> &sv,
    std::vector<int> &iv,
    std::vector<std::string> &miscv);
void parseFile();

void assocBIT();


int main()
{
    menu_driver();
    pause();
    return 0;
}

void print_menu() {
    std::cout << "(" << m_upload << ") - Upload existing file\n";
    std::cout << "(" << m_bldfile << ") - Build new file\n";
    std::cout << "(" << m_parsefile << ") - Parse file (strings/ints/misc)\n";
    std::cout << "(" << m_assocSTL << ") - Associative Container BIT\n";
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
        case m_upload:
            uploadFile();
            break;
        case m_bldfile:
            buildFile();
            break;
        case m_parsefile:
            parseFile();
            break;
        case m_assocSTL:
            assocBIT();
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

void uploadFile() {
    std::ifstream file;
    file.open(get_filename());

    if (file.is_open()) {
        std::string input;
        while (std::getline(file, input))
            std::cout << input << "\n";
        file.close();
    }
    else std::cout << "(ERR - uploadFile) Failed to open file\n";
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

void assocBIT() {
    std::cout << "assocBIT\n";
}
