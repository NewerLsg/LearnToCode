
#include<stdio.h>
#include<stdlib.h>

int fibonacciSearch(int *array,int n,int key);

int main(){
	int array[] = {
		1,2,3,4,5,6,7,8,9
	};
		    
	int pos = fibonacciSearch(array,9,9);
	if(pos > -1){
		printf("found,pos:%d",pos);
	}else{
		printf("not found");
	}

	return 0;
}


void initFibonacci(int *array,int n){
	if(n < 2) return;
		 
	array[0] = 0;
	array[1] = 1;
				   
	int i;
	for(i = 2;i < n; i++){
		array[i] = array[i - 1] + array[i - 2];
	}

}


int fibonacciSearch(int *array,int n,int key){
	int *fibonacciArray = (int*)malloc(sizeof(int)*n);
  	initFibonacci(fibonacciArray,n);

	int i;
	int k = 0;    

	while(n > fibonacciArray[k]){//确定数组大小在斐波那契数列中的位置
   		k++;
	}
								     
	int s = 0,e = n;
									      
	while(s <= e){
											           
		int r = s +  fibonacciArray[k - 1] - 1;
														         
		if(r >= n ) r = n - 1 ; //保证不能越界
   
		if(array[r] > key){
			e =  r - 1;
			k = k - 1;
		}else if(array[r] < key){
			s = r  + 1;
			k = k - 2;
		}else{
			return r;
		  }

	}

	return -1;    
}
