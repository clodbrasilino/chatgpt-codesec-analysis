#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decode(char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(sizeof(char) * len * 10);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            int count = str[i] - '0';
            while (count--) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[j++] = str[i + 1];
            }
            i++;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j++] = str[i];
        }
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "2a3b4c";
    char* decoded_str = decode(str);
    printf("%s\n", decoded_str);
    free(decoded_str);
    return 0;
}