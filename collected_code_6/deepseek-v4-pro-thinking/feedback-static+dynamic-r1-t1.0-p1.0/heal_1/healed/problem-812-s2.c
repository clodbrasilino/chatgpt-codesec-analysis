#include <stdio.h>
#include <string.h>

char *abbreviate_road(char *str) {
    char *p;

    if (str == NULL) {
        return NULL;
    }

    p = str;
    while ((p = strstr(p, "road")) != NULL) {
        p[0] = 'r';
        p[1] = 'd';
        p[2] = '.';
        {
            char *dst = p + 3;
            char *src = p + 4;
            while ((*dst++ = *src++) != '\0')
                ;
        }
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