#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            size_t len = strlen(pos + 4) + 1;
            memmove(pos + 3, pos + 4, len);
            pos[2] = '.';
            pos[3] = '\0';
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