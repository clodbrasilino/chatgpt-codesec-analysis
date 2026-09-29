#include <stdio.h>

void print_sub_lists(int *set, int size){
	int counter,num_of_subs;
	int i, j, k;
	
	num_of_subs = 1<<size;
	
	for(counter = 0; counter < num_of_subs; counter++){
		for(j = 0; j < size; j++){
			if(counter & (1<<j)){
				printf("%d ", set[j]);
			}
		}
 
		printf("\n");
	}
}

int main(){
	int set[]= {1,2,3};
	print_sub_lists(set,3);
	
	return 0;
}