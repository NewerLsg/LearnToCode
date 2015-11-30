int insertVauleSearch(int* array,int length,int key){
	int s = 0 ,e = length;
			     
	while(s <= e){
   		int r = s + ((key - array[s])/(array[e] - array[s]))*(e - s);
			
		if(r >= length) r = length - 1;
					  
		if(array[r] > key){
			e = r - 1;
		}else if(array[r] < key){
			s = r + 1;
		}else{
			return r;
		}    
										      
	}

	return -1;
}
