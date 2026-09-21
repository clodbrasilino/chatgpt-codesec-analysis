#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str, size_t len) {
    char *pos = str;
    while ((pos = strstr(pos, "road")) != NULL && (pos - str + 4) <= len) {
        if (pos[4] == ' ' || pos[4] == '\0' || pos[4] == ',' || pos[4] == '.' || (pos - str + 4 == len)) {
            size_t remaining_len = len - (pos - str + 4);
            memmove(pos + 2, pos + 4, remaining_len);
            pos[2] = '.';
        }
        pos += 1;
    }
}

int main() {
    char input[] = "Please use the road or take the second road.";
    size_t input_len = sizeof(input) - 1;
    abbreviate_road(input, input_len);
    printf("%s\n", input);
    return 0;
}