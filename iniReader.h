#pragma once
#include<iostream>
#include<string>
using namespace std;
class iniReader {
public:
	iniReader(FILE* file);
	string ReadNode(string node);
private:
	FILE* file;
};