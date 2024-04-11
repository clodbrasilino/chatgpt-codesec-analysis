#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

#define MAX_CHAR 256

char* minimizeString(char* str) {
    int count[MAX_CHAR] = {0};
    int len = strlen(str), min = len, min_index = -1;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    char* res = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
        count[str[i]]++;

    for (int i = 0; i < MAX_CHAR; i++)
        if (count[i] < min && count[i] != 0) {
            min = count[i];
            min_index = i;
        }

    int j = 0;
    for (int i = 0; i < len; i++)
        if (str[i] != min_index)
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'res' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            res[j++] = str[i];

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'res' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    res[j] = '\0';

    return res;
}

int main() {
    char str[] = "example string";
    char* res = minimizeString(str);
    printf("%s\n", res);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(res);
    return 0;
}