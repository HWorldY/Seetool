#include"iniReader.h"

iniReader::iniReader(FILE* f)
{
	this->file = f;
}

string iniReader::ReadNode(string node)
{
	fseek(file, 0, SEEK_SET);
	string ss;
	int len =(int) node.size();
	char single;
	int pos = 0;
	while (!feof(file)) {
		fread(&single, sizeof(char), 1, file);
		while (single == node[pos]&&pos<=len-1) {
			ss += single;
			fread(&single, sizeof(char), 1, file);
			pos++;
		}
		if (pos == len)break;
		else ss.clear();
	}
	string re;
	while (1) {
		fread(&single, sizeof(char), 1, file);
		if (single == '\n'||feof(file))break;
		re += single;
	}
	return re;
}
