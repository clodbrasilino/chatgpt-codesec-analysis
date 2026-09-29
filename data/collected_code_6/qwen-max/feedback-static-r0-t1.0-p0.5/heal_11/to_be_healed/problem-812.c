#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str, size_t len) {
    char *pos = str;
    while ((pos = strstr(pos, "road")) != NULL && (size_t)(pos - str + 4) < len) {
        if ((pos == str || !isalpha(*(pos - 1))) && 
            (pos[4] == '\0' || !isalpha(pos[4]))) {
            size_t remaining_len = len - (pos - str + 4);
            memmove(pos + 3, pos + 4, remaining_len + 1);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncpy(pos, "rd.", 3);
            pos[3] = '\0';
        }
        pos += 3;
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    size_t len = sizeof(str) - 1;
    abbreviate_road(str, len);
    printf("%s\n", str);
    return 0;
}