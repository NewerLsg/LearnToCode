#include<stdio.h>
#include<stdlib.h>


void fastSort(int *array,int start,int end);


int main(){
		int array[] = {
				2,3,1,0,4,-1,5
		};
		fastSort(array,0,6);
}


void fastSort(int* array,int start,int end){
		if(start >= end){
				return ;

		}

		int s = start,e = end;
		int base = array[start];

		while(s < e){
			while(e > s){
				if(array[e]>base)
					e--;
				else {
					array[s++] =  array[e];
					break;
				}  

			}
				
			while(s < e){
				if(array[s] < base)
					s++;
				else {
					array[e--]  = array[s];
					break;
					}
			}
		}

		array[s] = base;
		fastSort(array,start,s -1 );
		fastSort(array,s+1,end);
}


