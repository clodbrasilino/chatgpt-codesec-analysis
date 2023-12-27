#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(char** list, size_t size) {
    size_t i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - i - 1; j++) {
            size_t length_j = strlen(list[j]);
            size_t length_jplus1 = strlen(list[j + 1]);
            if (length_j > length_jplus1) {
                swap(&list[j], &list[j + 1]);
            }
            else if (length_j == length_jplus1) {
                if (strcmp(list[j], list[j + 1]) > 0) {
                    swap(&list[j], &list[j + 1]);
                }
            }
        }
    }
}

int main() {
    char* list[] = {"apple", "banana", "cat", "dog", "elephant"};
    size_t size = sizeof(list) / sizeof(list[0]);

    bubbleSort(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}