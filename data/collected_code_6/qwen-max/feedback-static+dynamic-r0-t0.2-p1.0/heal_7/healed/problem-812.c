#include <stdio.h>
#include <string.h>
#include <stdint.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            char *next = pos + 4;
            uint64_t len = 0;
            for (char *p = next; *p != '\0'; p++, len++);
            memmove(pos + 3, next, len + 1);
            *(pos + 2) = '.';
        }
        str = pos + 3;
    }
}

int main() {
    char input[] = "Please use the road or the other road, not the old road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}