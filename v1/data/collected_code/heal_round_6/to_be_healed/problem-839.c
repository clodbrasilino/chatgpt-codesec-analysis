#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void swapStrings(char* str1, char* str2, int size) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char tmp[size];
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(tmp, str1, size - 1);
    tmp[size - 1] = '\0';

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(str1, str2, size - 1);
    str1[size - 1] = '\0';

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(str2, tmp, size - 1);
    str2[size - 1] = '\0';
}

void sortTuples(char tuples[][MAX_SIZE], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(tuples[j], tuples[j + 1]) > 0) {
                swapStrings(tuples[j], tuples[j + 1], MAX_SIZE);
            }
        }
    }
}

int main() {
    char tuples[][MAX_SIZE] = {"b2", "a1", "c3"};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for (int i = 0; i < size; i++) {
        printf("(%s) ", tuples[i]);
    }

    return 0;
}