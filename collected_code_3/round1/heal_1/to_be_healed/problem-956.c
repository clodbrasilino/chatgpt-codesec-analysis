#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void split_string(char *str) {
    int i, len = strlen(str);
    char *temp = (char *)malloc(sizeof(char) * len);

    for(i = 0; i < len; i++) {
        if(isupper(str[i])) {
            /* Possible weaknesses found:
             *  use of possibly-NULL 'temp' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
             */
            printf("%s\n", temp);
            memset(temp, 0, len);
        } else {
            strncat(temp, &str[i], 1);
        }
    }
    /* Possible weaknesses found:
     *  use of possibly-NULL 'temp' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     */
    printf("%s\n", temp);
    free(temp);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    split_string(str);
    return 0;
}