#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        size_t len = strlen(pos + 4);
        memmove(pos + 3, pos + 4, len + 1);
        if (len + 3 < (size_t)(strlen(str) - (pos - str) + 1)) {
            if (pos + 3 <= str + sizeof(str) - 1 && pos + 3 - str < strlen(str)) {
                memcpy(pos, "rd.", 3);
            }
        }
        str = pos + 3;
    }
}

int main() {
    char str[] = "Welcome to the long and winding road, it's a road that never ends.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}