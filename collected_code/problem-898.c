#include <stdio.h>

void extractElements(int* list, int size, int numElements) {
    if (numElements > size) {
        printf("Error: Number of elements to extract exceeds list size.\n");
        return;
    }

    printf("Extracted elements: ");
    for (int i = 0; i < size - numElements + 1; i++) {
        for (int j = i; j < i + numElements; j++) {
            printf("%d ", list[j]);
        }
        printf("\n");
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numElements = 3;
    int size = sizeof(list) / sizeof(list[0]);

    extractElements(list, size, numElements);

    return 0;
}