#include<stdio.h>
#include<stdlib.h>

#define ARRAY_LENGTH 5

void find_modulo(int* list_a, int* list_b, int* result, int length) {
    for(int i=0; i<length; i++) {
        if(list_b[i] != 0) {
            result[i] = list_a[i] % list_b[i];
        } else {
            printf("Division by zero detected. Exiting the program.\n");
            exit(1);
        }
    }
}

int main(){
    int list_a[ARRAY_LENGTH] = {1, 2, 3, 4, 5};
    int list_b[ARRAY_LENGTH] = {2, 0, 1, 2, 0};

    int result[ARRAY_LENGTH];

    find_modulo(list_a, list_b, result, ARRAY_LENGTH);

    for(int i=0; i<ARRAY_LENGTH; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}