#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **list, int listSize, int stringSize) {
    char **result = malloc(listSize * sizeof(char *));
    int count = 0;
    for(int i = 0; i < listSize; i++) {
        if(strlen(list[i]) == stringSize) {
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  write of 8 bytes to beyond the end of the region
             */
            result[count] = malloc((stringSize + 1) * sizeof(char));
            strcpy(result[count], list[i]);
            count++;
        }
    }
    result = realloc(result, count * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return result;
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming", "Language"};
    int listSize = sizeof(list) / sizeof(list[0]);
    int stringSize = 5;
    char **result = extractStrings(list, listSize, stringSize);
    /* Possible weaknesses found:
     *  dereference of NULL 'result' [CWE-476] [-Wanalyzer-null-dereference]
     */
    for(int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}