#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(pos + 4);
        memmove(pos + 3, pos + 4, len + 1);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(pos, "rd.", 3);
        str = pos + 3;
    }
}

int main() {
    char str[] = "Welcome to the long and winding road, it's a road that never ends.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}