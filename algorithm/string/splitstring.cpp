#include<cstring>
#include<iostream>
#include<vector>
#include<stdlib.h>

/**
	splitStringCXX:c++实现主要利用string的find成员函数	
	splitString:c实现主要利用cstring的index函数	
*/
using namespace std;
void splitStringCXX(const string &src, char delima, vector<string> &vec) {
	if (src.empty()) return ;
				
	string tmp(src); 

	cout<<tmp<<endl;

	while(!tmp.empty()) {
		size_t pos = tmp.find(delima);

		if (pos == string::npos) {
			break;
		}
		cout<<tmp.substr(0,pos)<<endl;
		vec.push_back(tmp.substr(0,pos));
		tmp.erase(0,pos + 1);
																
	}
	vec.push_back(tmp);	

}

void splitString(const char* src, char delima, vector<string> &vec) {
	if (src == NULL) return ;	

	char *tmp = const_cast<char*>(src);
	char *pos = NULL;
	int size;
	int cur = 0;

	while( tmp != '\0' ) {
		pos = index(tmp, delima);

		if (pos != NULL) {
			size = pos - tmp;
			string str(tmp,0,size);	
			vec.push_back(str);
			tmp = pos + 1;
		}else{
			break;
		}
	}
	string str(tmp);	
	vec.push_back(str);
}

int main() {
	vector<string> vec;	
	string ptr = "123;abc;89zsdj";

	splitString(ptr.c_str(),';', vec);

	for(int i = 0; i < vec.size(); i++) {
		cout<<vec[i].c_str()<<endl;
	}

	return 0;
}
