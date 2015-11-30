#include<stdio.h>
#include<stdlib.h>

int mergerSort(int* array,int begin,int end);

int main(){
	int array[5] = {5,2,4,2,1};
	int i = 0;	     
	for(i = 0;i<5;i++){
	    printf("%d\t",array[i]);
	}
		 
	printf("\n");
			  
	mergerSort(array,0,4);
				   
	for(i = 0;i<5;i++){
		printf("%d\t",array[i]);
	 }
	return 0;
}

int mergerSort(int* array,int begin,int end){
	if(begin >= end){
		return 1;
	}
		    
	int middle = (begin + end)/2;
			     
  	mergerSort(array,begin,middle);
	mergerSort(array, middle + 1,end);
					       
	int *arraytemp = (int *)malloc(sizeof(int)*(end - begin + 1));
			 
 	int *p = arraytemp;
	int i = begin,j = middle + 1;
		  
	while(i <= middle && j <= end){
		if(array[i] > array[j]){
	 		*(p++) = array[j++];
	  	}else{
			*(p++) = array[i++];
		}         
	}
		  
	while(i<=middle){
		*(p++) = array[i++];
	}
		  
	while(j<=end){
		*(p++) = array[j++];
	}

	int lenght = end - begin + 1;
	i = 0;
	p = arraytemp;
						 
						 
	for(i = begin, p = arraytemp; i <= end;i++){
		array[i] = *(p);
 		p++;
	}
						 
	free(arraytemp);
	return 1;

}
