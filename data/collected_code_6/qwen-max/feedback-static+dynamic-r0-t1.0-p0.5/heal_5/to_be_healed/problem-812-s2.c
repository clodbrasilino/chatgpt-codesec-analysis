#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(pos + 4);
            memmove(pos + 2, pos + 4, len + 1);
            if (len + 2 <= (size_t)(-1 - (pos - str))) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(pos, "rd.", 3);
            }
            str = pos + 3;
        } else {
            str = pos + 1;
        }
    }
}

int main() {
    char input[] = "Please use the road or the other road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}