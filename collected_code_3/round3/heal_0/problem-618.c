#include <stdio.h>

void divide_lists(double list1[], double list2[], double result[], int size) {
    for(int i = 0; i < size; i++) {
        if(list2[i] != 0) {
            result[i] = list1[i] / list2[i];
        } else {
            result[i] = 0;
        }
    }
}

int main() {
    double list1[] = {10, 20, 30, 40, 50};
    double list2[] = {2, 4, 5, 8, 10};
    double result[5];

    divide_lists(list1, list2, result, 5);

    for(int i = 0; i < 5; i++) {
        printf("%f ", result[i]);
    }

    return 0;
}