#include <ctype.h>
#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        if ((pos == str || !isalpha(*(pos - 1))) && 
            (pos[4] == '\0' || !isalpha(pos[4]))) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(pos + 4);
            memmove(pos + 3, pos + 4, len + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, "rd.", 3);
            pos[3] = '\0';
        }
        pos = strstr(pos + 1, "road");
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}