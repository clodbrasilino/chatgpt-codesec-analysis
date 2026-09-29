#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

int occur[MAX_ELEMENTS] = {0};

void count_n_print_occur(int* arr, int size) {
    for(int i = 0;i < size; i++) {
		int val = arr[i];
        if(val < MAX_ELEMENTS && val >= 0) {
			occur[val] ++;
		}
        else {
			printf("Error: Value out of range\n");
            exit(0);
		}
    }
   
    for(int i = 0;i < MAX_ELEMENTS; i++) {
		if(occur[i] != 0) {
			printf("Element %d occurs %d times\n", i, occur[i]);
		}
	}
}

int main() {
    int arr[] = {1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 4, 2, 3};
    int len = sizeof(arr)/sizeof(arr[0]);
	
    count_n_print_occur(arr, len);

    return 0;
}