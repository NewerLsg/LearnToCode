#include<stdio.h>
#include<stdlib.h>

void insertSort(int *array,int length);

int main(){
	int array[5] = {5,4,3,2,1};
	insertSort(array,5);
			  
	int i;

	for(i = 0;i<5;i++){
		printf("%d\t",array[i]);
	}

}

void insertSort(int *array,int length){
	int i = 0;
		    
	for(i = 1;i<length;i++)
	{
		int temp = array[i];
		int j;
									         
		for(j = i - 1; j >= 0; j--)
		{
			if(array[j]>temp){
				array[j+1]=array[j];
			}else{
				break;
			}         
		}

		array[++j] = temp;
	}

}

