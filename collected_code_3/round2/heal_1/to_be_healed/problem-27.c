#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **removeDigits(char **strList, int size) {
    char **newList = malloc(size * sizeof(char *));
    for(int i = 0; i < size; i++) {
        int len = strlen(strList[i]);
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        newList[i] = malloc(len * sizeof(char));
        int index = 0;
        for(int j = 0; j < len; j++) {
            if(!isdigit(strList[i][j])) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL '*newList_52 + _29 + (sizetype)index' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                newList[i][index++] = strList[i][j];
            }
        }
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*newList_52 + _37 + (sizetype)index' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        newList[i][index] = '\0';
    }
    return newList;
}

int main() {
    int size = 3;
    char **strList = malloc(size * sizeof(char *));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'strList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    strList[0] = "abc123";
    strList[1] = "def456";
    strList[2] = "ghi789";

    char **newList = removeDigits(strList, size);

    for(int i = 0; i < size; i++) {
        printf("%s\n", newList[i]);
        free(newList[i]);
    }
    free(newList);
    free(strList);

    return 0;
}