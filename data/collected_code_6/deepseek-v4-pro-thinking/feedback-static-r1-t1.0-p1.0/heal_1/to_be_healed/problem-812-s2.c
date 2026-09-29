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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(p + 3, p + 4, strlen(p + 4) + 1);
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