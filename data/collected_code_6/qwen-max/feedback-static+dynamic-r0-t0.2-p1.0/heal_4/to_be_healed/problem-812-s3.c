#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == ',' || pos[4] == '.' || pos[4] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(pos + 4);
            memmove(pos + 2, pos + 4, len + 1);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncpy(pos, "rd", 2);
            str = pos + 2;
        } else {
            str = pos + 1;
        }
    }
}

int main() {
    char input[] = "Please use the road or take the other road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}