#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int numStrings, int size) {
    int index = 0;
    char **result = (char **)calloc(numStrings, sizeof(char *));

    if (result == NULL)
        return NULL;

    for (int i = 0; i < numStrings; i++) {
        if (strlen(strings[i]) == size) {
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             *  write of 8 bytes to beyond the end of the region
             */
            result[index] = (char *)malloc((size + 1) * sizeof(char));
            /* Possible weaknesses found:
             *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             *  read of 8 bytes from after the end of the region
             */
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) free(result[j]);
                free(result);
                return NULL;
            }
            strcpy(result[index], strings[i]);
            index++;
        }
    }

    result = (char **)realloc(result, index * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return result;
}

int main() {
    char *strings[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);
    int size = 5;

    char **result = extractStrings(strings, numStrings, size);

    if (result == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < numStrings; i++) {
        /* Possible weaknesses found:
         *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  use of uninitialized value '*result_26 + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  read of 8 bytes from after the end of the region
         */
        if (result[i] == NULL)
            break;
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    return 0;
}