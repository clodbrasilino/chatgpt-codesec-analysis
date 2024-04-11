#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **list, int listSize, int stringSize) {
    char **result = calloc(listSize, sizeof(char *));
    if (!result) {
        return NULL;
    }
    int count = 0;
    for(int i = 0; i < listSize; i++) {
        if(strlen(list[i]) == stringSize) {
            /* Possible weaknesses found:
             *  write of 8 bytes to beyond the end of the region
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            result[count] = malloc((stringSize + 1) * sizeof(char));
            /* Possible weaknesses found:
             *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             *  read of 8 bytes from after the end of the region
             */
            if (!result[count]) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[count], list[i]);
            count++;
        }
    }
    char **tmp = realloc(result, count * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    if (!tmp) {
        for(int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }
    result = tmp;
    return result;
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming", "Language"};
    int listSize = sizeof(list) / sizeof(list[0]);
    int stringSize = 5;
    char **result = extractStrings(list, listSize, stringSize);
    if (!result) {
        return 1;
    }
    /* Possible weaknesses found:
     *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     *  read of 8 bytes from after the end of the region
     *  use of uninitialized value '*result_26 + _10' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    for(int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}