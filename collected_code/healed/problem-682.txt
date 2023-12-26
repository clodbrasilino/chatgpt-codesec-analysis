#include <stdio.h>

void multiplyLists(const int list1[], const int list2[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = list1[i] * list2[i];
    }
}

int main() {
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {2, 4, 6, 8, 10};
    int size = sizeof(list1) / sizeof(list1[0]);

    int result[size];

    multiplyLists(list1, list2, result, size);

    printf("Resultant list: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}