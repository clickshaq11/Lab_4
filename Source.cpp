#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>

static int size2;

std::string functionString(const std::string& Source);

char* functionC(char* destination, const char* source, const int size);

std::ifstream openToRead(std::string path);

void openToWrite(std::string path, std::string string);
void openToWrite(std::string path, char* array);

std::string execString(std::ifstream& file);

void execC(std::ifstream& file);

void isValid(std::string toValidate);

int main() {
	std::ifstream fin = openToRead("test.txt");
	std::string s = execString(fin);
	openToWrite("test2.txt", s);
	// c-style строки
	std::ifstream fin2 = openToRead("test.txt");
	execC(fin2);
	return 0;
}

std::ifstream openToRead(std::string path) {
	std::ifstream file;
	file.open(path);
	if (file.is_open()) { // проверка открытия
		return file;
	}
	else {
		std::cerr << "read failure" << "\n";
		exit(1);
	}
}

void openToWrite(std::string path, std::string string) {
	std::ofstream file;
	file.open(path);
	if (file.is_open()) { // проверка открытия
		file << string << std::endl;
	}
	else {
		std::cerr << "write failure" << "\n";
		exit(1);
	}
	file.close();
}

void openToWrite(std::string path, char* array) {
	std::ofstream file;
	file.open(path, std::fstream::app);
	if (file.is_open()) { // проверка открытия
		file << array;
	}
	else {
		std::cerr << "write failure" << "\n";
		exit(1);
	}
	file.close();
}

std::string execString(std::ifstream& file) {
	std::string namesize;
	std::string name;
	std::getline(file, namesize);
	isValid(namesize);
	std::getline(file, name);
	
	int nameSizeNumbered = atoi(namesize.c_str());
	if (name.size() != nameSizeNumbered) {
		std::cerr << "Ошибка размеров" << std::endl;
		exit(1);
	}
	std::cout << std::endl;
	std::string s = functionString(name);
	file.close();
	return s;
}

void execC(std::ifstream& file) {
	std::string namesize;
	std::getline(file, namesize);
	int nameSizeNumbered = atoi(namesize.c_str());
	char* dest = new char[nameSizeNumbered];
	char c;
	for (int i = 0; i < nameSizeNumbered; i++) {
		file >> c;
		dest[i] = c;
	}
	char* src = new char[nameSizeNumbered];
	char* dest2 = functionC(src, dest, nameSizeNumbered);
	openToWrite("test2.txt", dest2);
	delete[] dest;
	delete[] src;
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
	char* destination2 = new char[size2+1];
	for (int i = 0; i < size2; i++) {
		destination2[i] = destination[i];
	}
	destination2[size2 + 1] = '\0';
	char * ptr = destination2; //создаем и возвращаем указатель
	return ptr;
}

void isValid(std::string toValidate) {
	for (int i = 0; i < toValidate.size(); i++) {
		char c;
		c = toValidate[i];
		if (!(c > '0' || c < '9')) {
			throw "Неверный формат длины строки";
			exit(1);
		}
	}
}