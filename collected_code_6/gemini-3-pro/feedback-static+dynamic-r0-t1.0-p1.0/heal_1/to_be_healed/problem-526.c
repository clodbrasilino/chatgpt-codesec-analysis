#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalizeFirstAndLast(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        int start = i;

        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }

        int end = i - 1;

        if (start == end) {
            str[start] = toupper((unsigned char)str[start]);
        } else {
            str[start] = toupper((unsigned char)str[start]);
            str[end] = toupper((unsigned char)str[end]);
        }
    }
}

int main(void) {
    char testStr[] = "hello world this is a test";

    capitalizeFirstAndLast(testStr);
    
    printf("%s\n", testStr);

    return 0;
}