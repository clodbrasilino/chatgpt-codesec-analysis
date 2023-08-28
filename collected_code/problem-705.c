#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(char** list, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // Compare length
            if (strlen(list[j]) > strlen(list[j + 1])) {
                swap(&list[j], &list[j + 1]);
            }
            // If length is equal, compare the values
            else if (strlen(list[j]) == strlen(list[j + 1])) {
                if (strcmp(list[j], list[j + 1]) > 0) {
                    swap(&list[j], &list[j + 1]);
                }
            }
        }
    }
}

int main() {
    char* list[] = {"apple", "banana", "cat", "dog", "elephant"};
    int size = sizeof(list) / sizeof(list[0]);
    
    bubbleSort(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}