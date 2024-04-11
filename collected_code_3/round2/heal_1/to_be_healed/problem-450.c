#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int numStrings, int size) {
    char **result = malloc(numStrings * sizeof(char *));
    int index = 0;

    for (int i = 0; i < numStrings; i++) {
        if (strlen(strings[i]) == size) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             *  write of 8 bytes to beyond the end of the region
             */
            result[index] = malloc((size + 1) * sizeof(char));
            strcpy(result[index], strings[i]);
            index++;
        }
    }

    result = realloc(result, index * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return result;
}

int main() {
    char *strings[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int numStrings = sizeof(strings) / sizeof(char *);
    int size = 5;

    char **result = extractStrings(strings, numStrings, size);

    /* Possible weaknesses found:
     *  dereference of NULL 'result' [CWE-476] [-Wanalyzer-null-dereference]
     *  read of 8 bytes from after the end of the region
     *  use of uninitialized value '*result_24 + _10' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     */
    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    return 0;
}