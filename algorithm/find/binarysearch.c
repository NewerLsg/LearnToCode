#include<stdio.h>

int binarySearch(int* array,int length,int key);

int main(){
	int array[] = {
		  1,2,3,4,5,6,7,8
	};

	int pos = binarySearch(array,8,7);

	if(pos > -1){
		printf("found,pos:%d",pos);
							
	}else{
		printf("not found");
	}

	return 0;
}

int binarySearch(int* array,int length,int key){
		    
	int s=0,e = length;
		 
	while(s <= e){
		int mid = (s + e)/2;
				
		if(array[mid] > key){
			e = mid - 1;
	   }else if(array[mid] < key){
			s = mid + 1;
	   }else{
			return mid;
	   }

		printf("mid:%d\t",array[mid]);
	}

	return -1;
}
