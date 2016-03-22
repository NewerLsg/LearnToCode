#include<cstring>
#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

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
