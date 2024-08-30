#include"Hashlib.h"
string Hashlib::MD5(string s)
{
	Hash_MD5 md5;
	return md5.getMD5(s);
}
string SeewoMD5(int code)
{
	string s;
	s = to_string(code);
	int l = s.size();
	string ss;
	for (int i = 1; i <= 6 - l; i++)ss += '0';
	ss += s;
	return Hashlib::MD5(Hashlib::MD5(ss) + Hashlib::MD5("hugo")).substr(8, 16);
}
string SeewoMD5(string ss)
{
	return Hashlib::MD5(Hashlib::MD5(ss) + Hashlib::MD5("hugo")).substr(8, 16);
}

