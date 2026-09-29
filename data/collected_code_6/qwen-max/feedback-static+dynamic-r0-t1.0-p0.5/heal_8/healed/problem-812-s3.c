#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.') {
            size_t len = strlen(pos + 4);
            if (len + 3 < (size_t)(strlen(str) - (pos - str))) {
                memmove(pos + 3, pos + 4, len + 1);
                if (len + 3 < (size_t)(strlen(str) - (pos - str))) {
                    memcpy(pos, "rd", 2);
                    pos[2] = '.';
                    str = pos + 3;
                } else {
                    break;
                }
            } else {
                break;
            }
        } else {
            str = pos + 1;
        }
    }
}

int main() {
    char input[] = "Please use the road to get to the next road.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}