#include"Hashlib.h"
#include"iniReader.h"
#include"Menu.h"
#include"ProcessBar.h"
#include <Windows.h>
using namespace std;
void HelpFunc(Option* opt) {
	printf( "You can type a path to get the corresponding service.\n");
	SystemPause();
}
void AboutFunc(Option* opt) {
	printf( "Sourse code link: https://github.com/HWorldY/Seetool\n");
	SystemPause();
}
void BasicRun(Option* opt) {
	char buffer[256] = {};
	DWORD dsize = 256;
	GetUserName(buffer, &dsize);
	string UserName = buffer;
	////////////////////////////////////////////
	string FullPath = (string)"C:\\Users\\" + UserName + "\\Roaming\\AppData\\Seewo\\SeewoAbility\\SeewoLockConfig.ini";
	string FullPath2 = (string)"C:\\ProgramData\\Seewo\\SeewoCore\\SeewoCore.ini";
	////////////////////////////////////////////
	FILE* f = fopen(FullPath.c_str(), "r");
	if (f == nullptr) {
		f = fopen(((string)"C:\\Users\\" + UserName + "\\AppData\\Roaming\\Seewo\\SeewoAbility\\SeewoLockConfig.ini").c_str(), "r");
	}
	if (f == nullptr)printf( "Error:file does not exists\n");
	else {
		iniReader reader(f);
		string re = reader.ReadNode("LockPasswordV2");
		if (re == "") {
			re = reader.ReadNode("LockPasswordV3");
		}
		int password = 0;
		printf( "Progress:");
		COORD coord = getxy();
		ProcessBar PB(1000000, 25, coord.X, coord.Y);
		PB.Begin();
		while (password <= 999999 && re != SeewoMD5(password)) {
			PB.Update(password);
			password++;
		}
		printf("\n");
		if (password == 1000000)printf( "Error:can't decrypt \'%s\'\n",re.c_str());
		else printf("Screen lock password : %d\n",password);
		fclose(f);
	}
	/////////////////////////////////////////////

	FILE* f2 = fopen(FullPath2.c_str(), "r");
	if (f2 == nullptr)printf( "Error:file does not exists\n");
	else {
		iniReader reader2(f2);
		string re2 = reader2.ReadNode("PASSWORDV2");
		if (re2 == "") {
			re2 = reader2.ReadNode("PASSWORDV3");
		}
		int password2 = 0;
		printf( "Progress:");
		COORD coord = getxy();
		ProcessBar PB2(1000000, 25, coord.X, coord.Y);
		PB2.Begin();
		while (password2 <= 999999 && re2 != SeewoMD5(password2)) {
			PB2.Update(password2);
			password2++;
		}
		printf("\n");
		if (password2 == 1000000)printf( "Error:can't decrypt \'%s\'\n",re2.c_str());
		else printf( "Administrator password: %d\n",password2);
		fclose(f2);
	}
	SystemPause();
}
void DebugRun(Option* opt) {
	char buffer[256] = {};
	DWORD dsize = 256;
	GetUserName(buffer, &dsize);
	string UserName = buffer;
	////////////////////////////////////////////
	string FullPath = (string)"C:\\Users\\" + UserName + "\\Roaming\\AppData\\Seewo\\SeewoAbility\\SeewoLockConfig.ini";
	string FullPath2 = (string)"C:\\ProgramData\\Seewo\\SeewoCore\\SeewoCore.ini";
	printf( "UserName:%s\n",UserName.c_str());
	printf( "(Screen lock password)FullPath:%s\n",FullPath.c_str());
	printf( "(Administrator password)FullPath:%s\n" ,FullPath2.c_str());
	printf( "Decryption mode:V2-md5(md5(password)+md5(\"hugo\"))\n" );
	////////////////////////////////////////////
	FILE* f = fopen(FullPath.c_str(), "r");
	printf("Open file:%s\n", ((f == nullptr) ? "Failed" : "Success"));
	if (f == nullptr) {
		f = fopen(((string)"C:\\Users\\" + UserName + "\\AppData\\Roaming\\Seewo\\SeewoAbility\\SeewoLockConfig.ini").c_str(), "r");
		printf( "Open file again:%s\n",((f == nullptr) ? "Failed" : "Success"));
	}
	if (f == nullptr)printf( "Error:file does not exists\n");
	else {
		iniReader reader(f);
		string re = reader.ReadNode("LockPasswordV2");
		if (re == "") {
			re = reader.ReadNode("LockPasswordV3");
		}
		int password = 0;
		printf( "Progress:");
		COORD coord = getxy();
		ProcessBar PB(1000000, 25, coord.X, coord.Y);
		PB.Begin();
		while (password <= 999999 && re != SeewoMD5(password)) {
			PB.Update(password);
			password++;
		}
		printf("\n");
		if (password == 1000000)printf( "Error:can't decrypt \'%s\'\n",re.c_str());
		else printf("Screen lock password:%d\n" ,password);
		fclose(f);
	}
	/////////////////////////////////////////////

	FILE* f2 = fopen(FullPath2.c_str(), "r");
	printf( "Open file:%s\n",((f2 == nullptr) ? "Failed" : "Success"));
	if (f2 == nullptr)printf( "Error:file does not exists\n");
	else {
		iniReader reader2(f2);
		string re2 = reader2.ReadNode("PASSWORDV2");
		if (re2 == "") {
			re2 = reader2.ReadNode("PASSWORDV3");
		}
		int password2 = 0;
		printf( "Progress:");
		COORD coord = getxy();
		ProcessBar PB2(1000000, 25, coord.X, coord.Y);
		PB2.Begin();
		while (password2 <= 999999 && re2 != SeewoMD5(password2)) {
			PB2.Update(password2);
			password2++;
		}
		printf("\n");
		if (password2 == 1000000)printf("Error:can't decrypt \'%s\'\n", re2.c_str());
		else printf("Administrator password:%d\n", password2);
		fclose(f2);
	}
	SystemPause();
}
void ManualRun(Option* opt) {
	printf("Decryption mode:V2-md5(md5(password)+md5(\"hugo\"))\n");
	string re = input("Input encrypted message:");
	int password = 0;
	printf( "Progress:");
	COORD coord = getxy();
	ProcessBar PB(1000000, 25, coord.X, coord.Y);
	PB.Begin();
	while (password <= 999999 && re != SeewoMD5(password)) {
		PB.Update(password);
		password++;
	}
	printf("\n");
	if (password == 1000000)printf("Error:can't decrypt \'%s\'\n", re.c_str());
	else printf( "Password:%d\n",password);
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
	MainMenu.AddSubMenu("q", "Quit", 1, [](Option* opt) {Continue = false;});

	MainMenu.GetMenu("r")->Title = "Run";
	MainMenu.GetMenu("r")->AddSubMenu("b", "Brief information", 1, BasicRun);
	MainMenu.GetMenu("r")->AddSubMenu("d", "More details", 1, DebugRun);
	MainMenu.GetMenu("r")->AddSubMenu("m", "Manual input", 1, ManualRun);
	MainMenu.GetMenu("r")->AddSubMenu("e", "Encrypt", 1, EncryptFunc);

	while (Continue)MainMenu.Run();
	return 0;
}/*
import hashlib
import os

def md5(text) :
	return hashlib.md5(text.encode()).hexdigest()

	hugo = md5('hugo')

	def enc(pwd) :
	return md5(md5(pwd) + hugo)[8:24]

	def trypwd(tar) :
	for i in range(0, 1000000) :
		pwd = f'{i:06}'
		if enc(pwd) == tar :
			return pwd
			return None

			def main() :
			print('计算还原密码请用记事本打开 op_C:\\ProgramData\\Seewo\\SeewoCore\\SeewoCore.ini 并记录 PASSWORDV2 的值\n计算锁屏密码请用记事本打开 op_C:\\Users\\当前用户名\\Roaming\\AppData\\Seewo\\SeewoAbility\\SeewoLockConfig.ini 并记录 LockPasswardV2 的值')
			tar = input('请输入值：')
			print('正在计算...')
			ans = trypwd(tar)
			if ans is None :
print('失败：密码不是六位数字')
			else:
print('密码是：' + ans)
os.system('pause ')

if __name__ == '__main__' :
	main()
*/