#include<stdio.h>
#include<stdlib.h>

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
    const int array_length = 5;

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int list_a[array_length] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int list_b[array_length] = {2, 0, 1, 2, 0};

    int result[array_length];

    find_modulo(list_a, list_b, result, array_length);

    for(int i=0; i<array_length; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}