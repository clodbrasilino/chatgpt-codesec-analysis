#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        if (pos > str && pos[-1] >= 'a' && pos[-1] <= 'z' || pos == str) {
            if (pos[4] == '\0' || (pos[4] >= 'a' && pos[4] <= 'z') || (pos[4] >= 'A' && pos[4] <= 'Z') || pos[4] == ' ') {
                memmove(pos + 2, pos + 4, strlen(pos + 4) + 1);
                *(pos + 2) = '.';
                pos += 3;
            } else {
                pos += 4;
            }
        } else {
            pos += 4;
        }
        pos = strstr(pos, "road");
    }
}

int main() {
    char str[] = "Please use the Elm Street road and turn right at the first road.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}