#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;
#define VALID_COLOR
#define INVALID_COLOR
class Menu;
struct Option;
typedef void(*OPT_FUNC)(Option*);
struct Option {
	string ID;
	string text;
	bool enable;
	bool leaf;
	Menu* menu;
	OPT_FUNC func;
};
string input(string start);
void SystemPause();
class Menu {
	public:
		Menu(Menu* parent);
		~Menu();
		void Run();
		bool AddSubMenuFunc(string ID, OPT_FUNC func);
		Option* ParsePath(string path);
		string GetPath();
		void AddSubMenu(string ID,string text,bool end,OPT_FUNC func=nullptr, bool enable = true);
		bool DeleteMenu(string ID);
		Option* GetOption(string ID);
		Menu* GetMenu(string ID);
		void Enable(bool enable);
		string Title;
		Option opt;
	private:
		Menu* parent;
		vector<Option> menu;
};
