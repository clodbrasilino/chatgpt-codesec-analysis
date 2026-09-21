#include <stdio.h>
#include <string.h>

char *abbreviate_road(char *str) {
    char *p;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    p = str;
    while ((p = strstr(p, "road")) != NULL) {
        size_t tail = len + 1 - (p + 4 - str);
        p[0] = 'r';
        p[1] = 'd';
        p[2] = '.';
        memmove(p + 3, p + 4, tail);
        len--;
        p += 3;
    }

    return str;
}

int main(void) {
    char text[] = "Main road and crossroad to road";

    printf("Before: %s\n", text);
    abbreviate_road(text);
    printf("After: %s\n", text);

    return 0;
}