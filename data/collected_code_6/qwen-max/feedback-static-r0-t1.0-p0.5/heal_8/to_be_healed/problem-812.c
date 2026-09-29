#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str, size_t len) {
    char *pos = strstr(str, "road");
    while (pos != NULL && (pos - str + 4) < len) {
        if ((pos == str || !isalpha(*(pos - 1))) && 
            /* Possible weaknesses found:
             *  Redundant condition: pos[4]!='\0'. 'pos[4]=='\0' || (pos[4]!='\0' && !isalpha(pos[4]))' is equivalent to 'pos[4]=='\0' || !isalpha(pos[4])' [redundantCondition]
             */
            (pos[4] == '\0' || (pos[4] != '\0' && !isalpha(pos[4])))) {
            size_t remaining_len = len - (pos - str + 4);
            memmove(pos + 3, pos + 4, remaining_len + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, "rd", 2);
            pos[2] = '.';
        }
        pos = strstr(pos + 3, "road");
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    size_t len = sizeof(str);
    abbreviate_road(str, len - 1);
    printf("%s\n", str);
    return 0;
}