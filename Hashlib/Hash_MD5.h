#pragma once
#include <string>
using namespace std;
#define op_shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define op_F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define op_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define op_H(x, y, z) ((x) ^ (y) ^ (z))
#define op_I(x, y, z) ((y) ^ ((x) | (~z)))
#define op_A 0x67452301
#define op_B 0xefcdab89
#define op_C 0x98badcfe
#define op_D 0x10325476
//strBaye的长度
class Hash_MD5 {
	unsigned int strlength;
	//op_A,op_B,op_C,op_D的临时变量
	unsigned int atemp;
	unsigned int btemp;
	unsigned int ctemp;
	unsigned int dtemp;
	//常量ti unsigned int(abs(sin(i+1))*(2pow32))
	static constexpr unsigned int k[] = {
			0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
			0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
			0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
			0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
			0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
			0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
			0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
			0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
			0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
			0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
			0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
			0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
			0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };
	//向左位移数
	static constexpr unsigned int s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,
			12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
			4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
			15,21,6,10,15,21,6,10,15,21,6,10,15,21 };
	static constexpr char str16[] = "0123456789abcdef";
	void mainLoop(unsigned int* M);
	/*
	*填充函数
	*处理后应满足bits≡448(mod512),字节就是bytes≡56（mode64)
	*填充方式为先加一个1,其它位补零
	*最后加上64位的原来长度
	*/
	unsigned int* add(string str);
	string changeHex(int a);
public:
	string getMD5(string source);
};
