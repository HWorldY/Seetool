#include"Menu.h"
string input(string start)
{
	string re;
	char ch;
	while (re.empty()) {
		printf( start.c_str());
		while ((ch = getchar()) != '\n')re += ch;
	}
	return re;
}
void SystemPause() {
	printf( "Press any key to contionue");
	char ch=getchar();
}
Menu::Menu(Menu* parent) {
	this->parent = parent;
	return;
}
Menu::~Menu() {
	return;
}
void Menu::Run() {
	system("cls");
	printf("%s\n", Title.c_str());
	for (auto it = menu.begin(); it != menu.end(); it++) {
		printf("%s-%s\n", it->ID.c_str(), it->text.c_str());
	}
	Option* it = nullptr;
	while (it == nullptr) {
		string re = input((string)">>>" + GetPath());
		it = ParsePath(re);
		if (it == nullptr)printf("Error:path \'%s\' is invalid\n", re.c_str());
	}
	if (it->func != nullptr)it->func(it);
	if (it->leaf == false)it->menu->Run();
}
bool Menu::AddSubMenuFunc(string ID, OPT_FUNC func)
{
	auto opt = GetOption(ID);
	if (opt == nullptr)return false;
	else {
		opt->func = func;
		return true;
	}
}
Option* Menu::ParsePath(string path) {
	//if ()return nullptr;
	if (this == nullptr)return nullptr;
	int length = (int)path.size();
	Option* opt = nullptr;
	for (int pos = 0; pos <= length - 1; pos++) {
		if (path[pos] == '/' || pos == length - 1) {
			opt = GetOption(path.substr(0, pos + (bool)(path[pos] != '/')));
			if (pos == length - 1 || opt == nullptr)return opt;
			else return opt->menu->ParsePath(path.substr(pos + 1));
			break;
		}
	}
	return 0;
}
string Menu::GetPath()
{
	if (this == nullptr)return string();
	if (parent == nullptr)return "Seetool/";
	return this->parent->GetPath() + opt.ID + '/';
}
void Menu::AddSubMenu(string ID, string text, bool end, OPT_FUNC func) {
	Menu* newmenu = nullptr;
	if (!end) newmenu = new Menu(this);
	Option option = { ID,text,true,end,newmenu,func };
	menu.push_back(option);
	if (newmenu != nullptr) {
		newmenu->opt.enable = option.enable;
		newmenu->opt.func = option.func;
		newmenu->opt.ID = option.ID;
		newmenu->opt.leaf = option.leaf;
		newmenu->opt.text = option.text;
	}
}
Option* Menu::GetOption(string ID)
{

	auto it = menu.begin();
	for (; it != menu.end(); it++) {
		if (it->ID == ID)return &(*it);
	}
	return nullptr;
}
Menu* Menu::GetMenu(string ID)
{
	auto opt = GetOption(ID);
	if (opt == nullptr)return nullptr;
	else return opt->menu;
}
void Menu::Enable(bool enable) {
	return;
}
