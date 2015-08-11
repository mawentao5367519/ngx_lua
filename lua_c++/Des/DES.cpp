#include "CDes.h"
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{	

	unsigned char  key[]="12345678";
	char in[]="aaaaaaaa";
	unsigned char out[100] = {0};
	unsigned char out2[100] = {0};
	CDES cs;
	bool b = cs.RunDes(cs.ENCRYPT, cs.ECB, (const unsigned char* )in, out, strlen((char *)in), key, strlen((char *)key));
	string str = cs.base64_encode((unsigned char *)out, strlen((char *)out));
	printf("%s\n",str.c_str());

	string str2 = cs.base64_decode(str);
	//cout << "out2:" << str2 << endl;
	b = cs.RunDes(cs.DECRYPT, 0, (const unsigned char* )str2.c_str(), out2, str2.length(), key, strlen((char *)key));
	cout << "out2:" << out2 << endl;
	return 0;
}

