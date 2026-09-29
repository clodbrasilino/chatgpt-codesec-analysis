#include <stdio.h>
#include <stdlib.h>

int findDigits(int num) {
    int count = 0;
    if(num == 0) return 1;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

void swap(int* a, int* b) {
    if(a != NULL && b != NULL) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void sortTupleList(int tuples[], int size) {
    if(tuples != NULL) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                int digits1 = findDigits(tuples[j]);
                int digits2 = findDigits(tuples[j + 1]);
                if (digits1 > digits2) {
                    swap(&tuples[j], &tuples[j + 1]);
                }
            }
        }
    }
}

int main() {
    int tuples[] = { 123, 9, 95, 876, 45678 };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTupleList(tuples, size);

    printf("Sorted Tuple List: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tuples[i]);
    }

    return 0;
}