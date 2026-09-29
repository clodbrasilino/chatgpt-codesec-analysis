#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char character;
    int count;
} CharCount;

int compare(const void *a, const void *b) {
    return ((CharCount *)b)->count - ((CharCount *)a)->count;
}

void findMostCommonElements(const char *text, CharCount *result, int *resultSize) {
    int counts[256] = {0};
    for (int i = 0; text[i] != '\0'; ++i) {
        counts[(unsigned char)text[i]]++;
    }

    *resultSize = 0;
    for (int i = 0; i < 256; ++i) {
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (counts[i] > 0) {
            result[*resultSize].character = (char)i;
            result[*resultSize].count = counts[i];
            (*resultSize)++;
        }
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: result
     *  Uninitialized variable: result [uninitvar]
     */
    qsort(result, *resultSize, sizeof(CharCount), compare);
}

int main() {
    const char *text = "hello world hello";
    CharCount result[256];
    int resultSize;

    /* Possible weaknesses found:
     *  Calling function 'findMostCommonElements', 2nd argument 'result' value is <Uninit>
     */
    findMostCommonElements(text, result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("Character: '%c', Count: %d\n", result[i].character, result[i].count);
    }

    return 0;
}