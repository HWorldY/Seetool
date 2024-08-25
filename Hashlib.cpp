#include"Hashlib.h"
void Hashlib::mainLoop(unsigned int* M)
{
	unsigned int f, g;
	unsigned int a = atemp;
	unsigned int b = btemp;
	unsigned int c = ctemp;
	unsigned int d = dtemp;
	for (unsigned int i = 0; i < 64; i++)
	{
		if (i < 16) {
			f = op_F(b, c, d);
			g = i;
		}
		else if (i < 32)
		{
			f = op_G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48) {
			f = op_H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else {
			f = op_I(b, c, d);
			g = (7 * i) % 16;
		}
		unsigned int tmp = d;
		d = c;
		c = b;
		b = b + op_shift((a + f + k[i] + M[g]), s[i]);
		a = tmp;
	}
	atemp = a + atemp;
	btemp = b + btemp;
	ctemp = c + ctemp;
	dtemp = d + dtemp;
}
/*
*��亯��
*�����Ӧ����bits��448(mod512),�ֽھ���bytes��56��mode64)
*��䷽ʽΪ�ȼ�һ��1,����λ����
*������64λ��ԭ������
*/
unsigned int* Hashlib::add(string str)
{
	unsigned int num = ((str.length() + 8) / 64) + 1;//��512λ,64���ֽ�Ϊһ��
	unsigned int* strByte = new unsigned int[num * 16];    //64/4=16,������16������
	strlength = num * 16;
	for (unsigned int i = 0; i < num * 16; i++)
		strByte[i] = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		strByte[i >> 2] |= (str[i]) << ((i % 4) * 8);//һ�������洢�ĸ��ֽڣ�i>>2��ʾi/4 һ��unsigned int��Ӧ4���ֽڣ�����4���ַ���Ϣ
	}
	strByte[str.length() >> 2] |= 0x80 << (((str.length() % 4)) * 8);//β�����1 һ��unsigned int����4���ַ���Ϣ,������128����
	/*
	*���ԭ���ȣ�����ָλ�ĳ��ȣ�����Ҫ��8��Ȼ����С�������Է��ڵ����ڶ���,���ﳤ��ֻ����32λ
	*/
	strByte[num * 16 - 2] = str.length() * 8;
	return strByte;
}
string Hashlib::changeHex(int a)
{
	int b;
	string str1;
	string str = "";
	for (int i = 0; i < 4; i++)
	{
		str1 = "";
		b = ((a >> i * 8) % (1 << 8)) & 0xff;   //������ÿ���ֽ�
		for (int j = 0; j < 2; j++)
		{
			str1.insert(0, 1, str16[b % 16]);
			b = b / 16;
		}
		str += str1;
	}
	return str;
}
string Hashlib::getMD5(string source)
{
	atemp = op_A;    //��ʼ��
	btemp = op_B;
	ctemp = op_C;
	dtemp = op_D;
	unsigned int* strByte = add(source);
	for (unsigned int i = 0; i < strlength / 16; i++)
	{
		unsigned int num[16];
		for (unsigned int j = 0; j < 16; j++)
			num[j] = strByte[i * 16 + j];
		mainLoop(num);
	}
	delete[] strByte;
	return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
}
string GetMD5(string sourse)
{
	Hashlib md5;
	return md5.getMD5(sourse);
}

string SeewoMD5(int code)
{
	string s;
	s = to_string(code);
	int l = s.size();
	string ss;
	for (int i = 1; i <= 6 - l; i++)ss += '0';
	ss += s;
	return GetMD5(GetMD5(ss) + GetMD5("hugo")).substr(8, 16);
}
string SeewoMD5(string ss)
{
	return GetMD5(GetMD5(ss) + GetMD5("hugo")).substr(8, 16);
}
