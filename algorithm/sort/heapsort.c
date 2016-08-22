#include<stdio.h>


#define LChild(i) (2*(i))

#define RChild(i) (2*(i) + 1)

#define Parent(i) ((i)/2)

//堆调整
void MaxHeapify(int* array,int lenght,int i);
//数组堆化
void BuildMaxHeap(int* array,int lenght);
//排序
void HeapSort(int* array,int length);

int main(){
	int array[] = {
		-11,2,1,4,0,-1,6
	}; 
	
	BuildMaxHeap(array,6);
		 
  	int i;
  	for(i = 1;i< 7;i++){
		printf("%d\t",array[i]);
  	}
	printf("\n");
		   
	HeapSort(array,6);
				
	for(i = 1;i< 7;i++){
		printf("%d\t",array[i]);
	}

}

void MaxHeapify(int* array,int lenght,int i){
		    
	if(i > lenght){
		return ;
	}
		    
	int max = i;
		 
	if(LChild(i) <=lenght && array[LChild(i)] > array[max]){
		max = LChild(i);
	}
		 
	if(RChild(i) <=lenght && array[RChild(i)] > array[max]){
		max = RChild(i);
	}
		 
	if(max != i){
		int temp = array[i];
		array[i] = array[max];
		array[max] = temp;
		MaxHeapify(array,lenght,max);//对子节点调整
	 }
			          
}


void BuildMaxHeap(int* array,int lenght){
	int s = lenght/2;
			     
	while(s > 0){
		MaxHeapify(array,lenght,s);//由子堆开始调整。
		s--;
	}

}


void HeapSort(int* array,int length){
	int i;

	for(i = length ;i > 0 ;i--){
		int temp = array[1];
 		array[1] = array[i];
   		array[i] = temp;
												 
		MaxHeapify(array,i - 1 ,1);//每次置换后调整
	}

} 

