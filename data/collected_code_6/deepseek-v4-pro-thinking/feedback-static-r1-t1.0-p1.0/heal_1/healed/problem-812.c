#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }

    size_t i = 0, j = 0;

    while (str[i] != '\0') {
        if (strncmp(str + i, "road", 4) == 0) {
            str[j++] = 'r';
            str[j++] = 'd';
            str[j++] = '.';
            i += 4;
        } else {
            str[j++] = str[i++];
        }
    }

    str[j] = '\0';
}

int main(void) {
    char text[] = "main road and broadway road";
    abbreviate_road(text);
    puts(text);
    return 0;
}