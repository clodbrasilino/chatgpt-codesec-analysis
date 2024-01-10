#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char** a, char** b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    char* temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    /* Possible weaknesses found:
     *  Cannot determine that 'temp' is initialized [premium-bughuntingUninit]
     */
    *b = temp;
}

void bubbleSort(char** list, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // Compare length
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (strlen(list[j]) > strlen(list[j + 1])) {
                swap(&list[j], &list[j + 1]);
            }
            // If length is equal, compare the values
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            else if (strlen(list[j]) == strlen(list[j + 1])) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'list[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
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