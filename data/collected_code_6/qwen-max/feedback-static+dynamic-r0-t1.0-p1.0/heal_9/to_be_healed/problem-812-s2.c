#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str, size_t len) {
    for (char *pos = str; (pos = strstr(pos, "road")) != NULL; ) {
        if ((pos == str || !isalpha((unsigned char)pos[-1])) && 
            (pos + 4 - str < len && (!isalpha((unsigned char)pos[4]) || pos[4] == '\0'))) {
            size_t remaining_len = len - (pos - str + 4);
            memmove(pos + 2, pos + 4, remaining_len);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, "rd", 2);
            pos += 2;
        } else {
            pos += 4;
        }
    }
}

int main() {
    char str[] = "This is a long road that has many turns and another road ahead.";
    abbreviate_road(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}