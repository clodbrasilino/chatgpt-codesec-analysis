#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str, size_t len) {
    char *pos = str;
    while ((pos = strstr(pos, "road")) != NULL && pos - str + 4 < len) {
        size_t remaining_len = len - (pos - str + 4);
        memmove(pos + 3, pos + 4, remaining_len);
        if (remaining_len >= 3) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, "rd.", 3);
        }
        pos += 3;
    }
}

int main() {
    char str[] = "Welcome to the long and winding road, it's a road that never ends.";
    abbreviate_road(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}