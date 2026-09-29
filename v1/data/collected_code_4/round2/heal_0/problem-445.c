#include <stdio.h>

void multiply_tuples(int tuple1[], int tuple2[], int mult_result[], int size) {
    if(size<=0 || !tuple1 || !tuple2 || !mult_result) {
        return;
    }

    for(int i = 0; i < size; i++) {
        mult_result[i] = tuple1[i] * tuple2[i];
    }
}

int main() {
    int size = 3;
    int tuple1[] = {2, 3, 4};
    int tuple2[] = {5, 6, 7};
    int mult_result[size];

    multiply_tuples(tuple1, tuple2, mult_result, size);

    printf("The result of the tuple multiplication is: \n");
    for(int i = 0; i < size; i++) {
        printf("%d ", mult_result[i]);
    }
    printf("\n");

    return 0;
}