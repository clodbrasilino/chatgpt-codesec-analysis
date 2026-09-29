#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }

    char *ptr = str;
    while ((ptr = strstr(ptr, "road")) != NULL) {
        ptr[0] = 'r';
        ptr[1] = 'd';
        ptr[2] = '.';
        
        size_t remaining_length = strlen(ptr + 4);
        memmove(ptr + 3, ptr + 4, remaining_length + 1);
        
        ptr += 3;
    }
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