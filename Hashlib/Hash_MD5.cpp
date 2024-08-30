#include"Hash_MD5.h"
void Hash_MD5::mainLoop(unsigned int* M)
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
		b = b + op_shift((a + f + Hash_MD5::k[i] + M[g]), Hash_MD5::s[i]);
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
unsigned int* Hash_MD5::add(string str)
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
string Hash_MD5::changeHex(int a)
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
			str1.insert(0, 1, Hash_MD5::str16[b % 16]);
			b = b / 16;
		}
		str += str1;
	}
	return str;
}
string Hash_MD5::getMD5(string source)
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