#define _CRT_SECURE_NO_WARNINGS // для fopen, оно ругается
#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>

static int size2;

std::string functionString(const std::string& Source);

char* functionC(char* destination, const char* source, const int size);

int main() {
	// Открытие файла 
	std::ifstream fin;
	std::string path = "test.txt";
	fin.open(path);
	if (fin.is_open()) { // проверка открытия
		std::cout << "read success" << "\n";
	}
	else {
		std::cout << "read failure" << "\n";
		return -1;
	}
	// считывание строки 
	std::string namesize; 
	std::string name;
	std::getline(fin, namesize);
	std::getline(fin, name);
	int nameSizeNumbered = atoi(namesize.c_str());
	std::cout << std::endl;
	std::string s = functionString(name);
	fin.close();
	//
	std::ofstream fout; // запись в файл
	std::string path2 = "test2.txt";
	fout.open(path2); // fout.open(path2, std::fstream::app) - Для записи без удаления информации из файла
	if (fout.is_open()) { // проверка открытия
		std::cout << "read success" << "\n";
	}
	else {
		std::cout << "read failure" << "\n";
		return -1;
	}
	fout << s << std::endl; 
	// c-style ñòðîêè
	std::ifstream fin2;
	std::string path3 = "test.txt";
	fin2.open(path3);
	char* dest = new char[nameSizeNumbered];
	std::string a_;
	std::getline(fin2, a_);
	char c;
	for (int i = 0; i < nameSizeNumbered; i++) {
		fin2 >> c;
		dest[i] = c;
	}
	char* src = new char[nameSizeNumbered];
	std::ofstream fout2;
	fout2.open(path2, std::fstream::app);
	fout2 << functionC(src, dest, nameSizeNumbered);
	fout2.close();
	delete[] dest;
	delete[] src;
	return 0;
}

std::string functionString(const std::string& Source) {
	std::vector<char> curSym;
	std::string bna = Source;
	if (bna.size() == 0) {
		return "";
	}
	curSym.push_back(bna[0]);
	for (auto& i : bna) {
		int t = 0;
		for (int j = 0; j < curSym.size(); j++) {
			if (i == curSym[j]) {
				t = 1;
			}
		}
		if (t > 0) {
			t = 0;
		}
		else {
			curSym.push_back(i);
		}
	}
	std::string abs;
	for (int k = 0; k < curSym.size(); k++) {
		abs += curSym[k];
	}
	return abs;
}

char* functionC(char* destination, const char* source, const int size) {
	std::vector<char> curSym;
	const char* bna = source;
	if (size == 0) {
		return nullptr;
	}
	curSym.push_back(bna[0]);
	for (int i = 0; i < size; i++) {
		int t = 0;
		for (int j = 0; j < curSym.size(); j++) {
			if (source[i] == curSym[j]) {
				t = 1;
			}
		}
		if (t > 0) {
			t = 0;
		}
		else {
			curSym.push_back(source[i]);
		}
	}
	for (int k = 0; k < curSym.size(); k++) {
		destination[k] = curSym[k];
	}
	static int size2 = curSym.size();
	std::cout << curSym.size() << std::endl;
	char* destination2 = new char[size2+1];
	for (int i = 0; i < size2; i++) {
		destination2[i] = destination[i];
	}
	destination2[size2 + 1] = '\0';
	char * ptr = destination2; //создаем и возвращаем указатель
	return ptr;
}
