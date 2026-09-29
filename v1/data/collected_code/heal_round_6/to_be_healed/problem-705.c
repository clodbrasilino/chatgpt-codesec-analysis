#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

bool isValidString(const char* str) {
    if (str == NULL)
        return false;

    while (*str) {
        if (!isprint((unsigned char)*str++))
            return false;
    }

    return true;
}

void bubbleSort(char** list, size_t size) {
    size_t i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (isValidString(list[j]) && isValidString(list[j + 1])) {
                int compare = strcmp(list[j], list[j + 1]);
                if (compare > 0) {
                    swap(&list[j], &list[j + 1]);
                } else if (compare == 0) {
                    /* Possible weaknesses found:
                     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                     */
                    if (strlen(list[j]) > strlen(list[j + 1]))
                        swap(&list[j], &list[j + 1]);
                }
            }
        }
    }
}

int main() {
    char* list[] = {"apple", "banana", "cat", "dog", "elephant"};
    size_t size = sizeof(list) / sizeof(char*);

    bubbleSort(list, size);

    for (size_t i = 0; i < size; i++) {
        if(isValidString(list[i])) {
            printf("%s\n", list[i]);
        }
    }

    return 0; 
}
