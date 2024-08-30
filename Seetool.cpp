#include"Hashlib/Hashlib.h"
#include"iniReader.h"
#include"Menu.h"
#include"ProcessBar.h"
#include <Windows.h>
using namespace std;
string GetCurrentUserName() {
	char buffer[256] = {};
	DWORD dsize = 256;
	GetUserName(buffer, &dsize);
	return (string)buffer;
}
void HelpFunc(Option* opt) {
	printf("You can type a path to get the corresponding service.\n");
	SystemPause();
}
void AboutFunc(Option* opt) {
	printf("Sourse code link: https://github.com/HWorldY/Seetool\n");
	SystemPause();
}
int decrypt(string re) {
		int password = 0;
		COORD coord = getxy();
		ProcessBar PB("Progress:",1000000, 25, coord.X, coord.Y);
		PB.Begin();
		while (password <= 999999 && re != SeewoMD5(password)) {
			PB.Update(password);
			password++;
		}
		printf("\n");
		return password;
}
void Run(bool debug) {
	string UserName = GetCurrentUserName();
	string FullPath = (string)"C:\\Users\\" + UserName + "\\AppData\\Roaming\\Seewo\\SeewoAbility\\SeewoLockConfig.ini";
	string FullPath2 = (string)"C:\\ProgramData\\Seewo\\SeewoCore\\SeewoCore.ini";
	if (debug) {
		printf("UserName:%s\n", UserName.c_str());
		printf("(Screen lock password)FullPath:%s:LockPasswardV*\n", FullPath.c_str());
		printf("(Administrator password)FullPath:%s:PASSWORDV*\n", FullPath2.c_str());
		printf("Decryption mode:V2-md5(md5(password)+md5(\"hugo\"))\n");
	}

	FILE* f = fopen(FullPath.c_str(), "r");
	if(debug)printf("Open file:%s\n", ((f == nullptr) ? "failed" : "success"));
	if (f == nullptr)printf("Error:file does not exists\n");
	else {
		iniReader reader(f);
		string re = reader.ReadNode("LockPasswardV2");
		if (re == "")re = reader.ReadNode("LockPasswardV3");
		int password = decrypt(re);
		if (password <= 999999)printf("Administrator password: %d\n", password);
		else printf("Error:can't decrypt \'%s\'\n", re.c_str());
		fclose(f);
	}
	FILE* f2 = fopen(FullPath2.c_str(), "r");
	if (debug)printf("Open file:%s\n", ((f2 == nullptr) ? "failed" : "success"));
	if (f2 == nullptr)printf("Error:file does not exists\n");
	else {
		iniReader reader2(f2);
		string re2 = reader2.ReadNode("PASSWORDV2");
		if (re2 == "")re2 = reader2.ReadNode("PASSWORDV3");
		int password2 = decrypt(re2);
		if (password2 <= 999999)printf("Administrator password: %d\n", password2);
		else printf("Error:can't decrypt \'%s\'\n", re2.c_str());
		fclose(f2);
	}
	SystemPause();
}
void ManualRun(Option* opt) {
	printf("Decryption mode:V2-md5(md5(password)+md5(\"hugo\"))\n");
	string re = input("Input encrypted message:");
	int password2 = decrypt(re);
	if (password2 <= 999999)printf("Password: %d\n", password2);
	else printf("Error:can't decrypt \'%s\'\n", re.c_str());
	SystemPause();
}
void EncryptFunc(Option* opt) {
	string re = input("Original text:");
	printf("%s\n", SeewoMD5(re).c_str());
	SystemPause();
}
bool Continue = true;
int main() {
	SetConsoleTitle("Seetool-v0.1");
	Menu MainMenu(nullptr);
	MainMenu.Title = "Main";
	MainMenu.AddSubMenu("r", "Run", 0, nullptr);
	MainMenu.AddSubMenu("h", "Help", 1, HelpFunc);
	MainMenu.AddSubMenu("a", "About", 1, AboutFunc);
	MainMenu.AddSubMenu("o", "Use online Seewo service (INVALID)",1,nullptr,0);
	MainMenu.AddSubMenu("q", "Quit", 1, [](Option* opt) {Continue = false; });

	MainMenu.GetMenu("r")->Title = "Run";
	MainMenu.GetMenu("r")->AddSubMenu("b", "Brief information", 1, [](Option* opt) {Run(0);});
	MainMenu.GetMenu("r")->AddSubMenu("d", "More details", 1, [](Option* opt) {Run(1);});
	MainMenu.GetMenu("r")->AddSubMenu("m", "Manual input", 1, ManualRun);
	MainMenu.GetMenu("r")->AddSubMenu("e", "Encrypt", 1, EncryptFunc);
	MainMenu.GetMenu("r")->AddSubMenu("o", "Use external program (INVALID)", 1,nullptr,0);

	while (Continue)MainMenu.Run();
	return 0;
}