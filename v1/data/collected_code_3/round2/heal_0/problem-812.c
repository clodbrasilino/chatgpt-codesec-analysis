#include <stdio.h>
#include <string.h>

void abbreviate(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        strncpy(pos, "rd.", 3);
        memmove(pos + 3, pos + 4, strlen(pos + 4) + 1);
    }
}

int main() {
    char str[] = "The road to success is always under construction.";
    printf("Original string: %s\n", str);
    abbreviate(str);
    printf("Modified string: %s\n", str);
    return 0;
}