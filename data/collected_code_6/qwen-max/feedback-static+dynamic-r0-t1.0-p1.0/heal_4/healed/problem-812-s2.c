#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str) {
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        if ((pos == str || !isalpha((unsigned char)pos[-1])) && 
            (pos[4] == '\0' || !isalpha((unsigned char)pos[4]))) {
            size_t remaining_len = strlen(pos + 4) + 1;
            if (remaining_len <= sizeof(char) * 2) {
                memmove(pos + 2, pos + 4, remaining_len);
                memcpy(pos, "rd", 2);
                pos += 2;
            }
        } else {
            pos += 4;
        }
        pos = strstr(pos, "road");
    }
}

int main() {
    char str[] = "This is a long road that has many turns and another road ahead.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}