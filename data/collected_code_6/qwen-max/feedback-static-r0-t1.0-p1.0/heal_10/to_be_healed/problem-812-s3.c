#include <stdio.h>
#include <string.h>
#include <stddef.h>

char* abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (*(pos + 4) == ' ' || *(pos + 4) == ',' || *(pos + 4) == '.' || *(pos + 4) == '\0' || *(pos + 4) == ';' || *(pos + 4) == ':') {
            /* Possible weaknesses found:
             *  Variable 'end' can be declared as pointer to const [constVariablePointer]
             */
            char *end = strchr(pos + 4, '\0');
            size_t len = end - (pos + 4);
            memmove(pos + 3, pos + 4, len + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, "rd.", 3);
            str = pos + 3;
        } else {
            str = pos + 1;
        }
    }
    return str;
}

int main() {
    char str[] = "Welcome to the long road called life. Another road leads to success.";
    printf("Original: %s\n", str);
    abbreviate_road(str);
    printf("Abbreviated: %s\n", str);
    return 0;
}