#include <stdio.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }

    char *r = str;
    char *w = str;

    while (*r) {
        if (*r == 'r' && *(r + 1) == 'o' && *(r + 2) == 'a' && *(r + 3) == 'd') {
            *w++ = 'r';
            *w++ = 'd';
            *w++ = '.';
            r += 4;
        } else {
            *w++ = *r++;
        }
    }
    *w = '\0';
}

int main(void) {
    char s1[] = "123 road street";
    char s2[] = "road road";
    char s3[] = "no match";

    abbreviate_road(s1);
    abbreviate_road(s2);
    abbreviate_road(s3);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);

    return 0;
}