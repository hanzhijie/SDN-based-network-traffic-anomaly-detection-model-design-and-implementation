#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int main()
{
ifstream inFile;
inFile.open("of.txt"); // 打开文件
ofstream outf("aa.txt");
string str; // 行字符串缓存
char *ch;
char* ptr;
int pos=0;
int a[2]={0,0};

int b;
if(inFile.is_open()){ // 若成功打开文件
    while(!inFile.eof()){ // 若未到文件结束
        getline(inFile, str, '\n'); // 读取一行内容，并存入缓存str中，'\n'表示一行结束的回车符
		ch = const_cast<char*>(str.c_str());
		ptr = strstr(ch, "packet_count:");
		pos = ptr-ch;
		if (ptr){
				//cout<<str.substr(pos+14)<<endl;
				a[1]=atoi(str.substr(pos+14).c_str());
				b=a[1]-a[0];
				a[0]=a[1];
				if(b>0){
				//b=0;
					cout<<b<<endl;
				outf<<b<<endl;
				}
		}
	}
}
else{
	cout <<"打开文件失败"<< endl;
}

inFile.close();
outf.close();
system("pause");
return 0;
}

