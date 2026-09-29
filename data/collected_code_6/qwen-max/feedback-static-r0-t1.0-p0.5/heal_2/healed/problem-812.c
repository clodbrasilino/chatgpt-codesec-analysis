#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str) {
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        if ((pos == str || !isalpha(*(pos - 1))) && 
            (pos[4] == '\0' || !isalpha(pos[4]))) {
            size_t len = strlen(pos + 4);
            memmove(pos + 2, pos + 4, len + 1);
            memcpy(pos, "rd", 2);
            pos[2] = '.';
        }
        pos = strstr(pos + 1, "road");
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}