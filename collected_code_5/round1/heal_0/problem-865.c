#include <stdio.h>
#include <stdlib.h>

typedef void (*FunctionPointers)(int);

void printNumber(int n) {
    printf("%d\n", n);
}

void map(int *array, size_t size, FunctionPointers func) {
    for(int i = 0; i < size; i++)
        (*func)(array[i]);
}

void printNTimes(int *array, size_t size, int n) {
    for(int i = 0; i < n; i++)
        map(array, size, printNumber);
}

int main() {
    int n;
    printf("Enter how many times to print: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Invalid input. n should be greater than 0.\n");
        return 0;
    }

    int data[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(data)/sizeof(data[0]);

    printNTimes(data, size, n);
    
    return 0;
}