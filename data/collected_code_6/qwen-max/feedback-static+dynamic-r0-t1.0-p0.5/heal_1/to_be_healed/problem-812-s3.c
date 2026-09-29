#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(pos + 2, pos + 4, strlen(pos + 4) + 1);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncpy(pos, "rd.", 3);
            str = pos + 3;
        } else {
            str = pos + 1;
        }
    }
}

int main() {
    char input[] = "Please use the road to get to the next road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}