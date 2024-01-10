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
            if(list[j] == NULL || list[j + 1] == NULL) {
                continue;
            }

            int compare = strcmp(list[j], list[j+1]);
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            if (compare > 0 || ((compare == 0) && (strlen(list[j]) > strlen(list[j+1])))) {
                swap(&list[j], &list[j + 1]);
            }
        }
    }
}

int main() {
    char* list[] = {"apple", "banana", "cat", "dog", "elephant"};
    size_t size = sizeof(list) / sizeof(list[0]);

    bubbleSort(list, size);

    for (size_t i = 0; i < size; i++) {
        if(list[i] != NULL) {
            printf("%s\n", list[i]);
        }
    }

    return 0;
}