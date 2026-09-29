#include <stdio.h>
#include <string.h>

char* abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (*(pos + 4) == ' ' || *(pos + 4) == ',' || *(pos + 4) == '.' || *(pos + 4) == '\0' || *(pos + 4) == ';' || *(pos + 4) == ':') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(pos + 4);
            memmove(pos + 3, pos + 4, len + 1);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncpy(pos, "rd.", 3);
            pos[2] = '.';
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