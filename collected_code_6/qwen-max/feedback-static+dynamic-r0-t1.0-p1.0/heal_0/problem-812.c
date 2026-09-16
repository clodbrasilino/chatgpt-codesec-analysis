#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        memmove(pos + 2, pos + 4, strlen(pos + 4) + 1);
        memcpy(pos, "rd.", 3);
        str = pos + 3;
    }
}

int main() {
    char str[] = "Welcome to the long and winding road, it's a road that never ends.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}