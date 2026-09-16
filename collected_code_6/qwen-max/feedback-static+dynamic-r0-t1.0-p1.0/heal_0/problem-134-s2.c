#include <stdio.h>

void performOperation(int *array, int length, int p) {
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < length - 1; ++j) {
            array[j] = array[j] + array[j + 1];
        }
    }
}

int isLastElementEven(int *array, int p) {
    performOperation(array, 5, p);
    return (array[4] % 2) == 0;
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int p = 2;

    if (isLastElementEven(array, p)) {
        printf("The last element is even.\n");
    } else {
        printf("The last element is odd.\n");
    }

    return 0;
}