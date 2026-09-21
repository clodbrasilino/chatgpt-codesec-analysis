#include <ctype.h>
#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str, size_t str_len) {
    char *pos = memmem(str, str_len, "road", 4);
    while (pos != NULL && pos - str < str_len - 4) {
        if ((pos == str || !isalpha(*(pos - 1))) && 
            (pos[4] == '\0' || !isalpha(pos[4]))) {
            size_t len = str_len - (pos - str + 4);
            memmove(pos + 3, pos + 4, len + 1);
            strncpy(pos, "rd.", 3);
            str_len -= 2;
        }
        pos = memmem(pos + 1, str_len - (pos - str), "road", 4);
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    abbreviate_road(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}