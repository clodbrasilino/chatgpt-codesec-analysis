#include<stdio.h>

void print_int(int i){
    printf("%d\n", i);
}

void map(void (*func)(int), int* array, size_t size) {
    for(size_t i = 0; i < size; i++)
        (*func)(array[i]);
}

void print_array_n_times(int* array, size_t size, int n) {
    for(int i = 0; i < n; ++i)
        map(print_int, array, size);
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    print_array_n_times(array, sizeof(array)/sizeof(array[0]), 3);
    
    return 0;
}