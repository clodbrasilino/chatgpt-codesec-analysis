#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 256
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void sortTuples(char tuples[][MAX_SIZE], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(tuples[j], tuples[j + 1]) > 0) {
                /* Possible weaknesses found:
                 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
                 */
                char temp[MAX_SIZE];
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(temp, tuples[j], MIN(strlen(tuples[j]), MAX_SIZE-1));
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                temp[MIN(strlen(tuples[j]), MAX_SIZE-1)] = '\0';
                
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(tuples[j], tuples[j + 1], MIN(strlen(tuples[j + 1]), MAX_SIZE-1));
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                tuples[j][MIN(strlen(tuples[j]), MAX_SIZE-1)] = '\0';
                
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(tuples[j + 1], temp, MIN(strlen(temp), MAX_SIZE-1));
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                tuples[j + 1][MIN(strlen(temp), MAX_SIZE-1)] = '\0';
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