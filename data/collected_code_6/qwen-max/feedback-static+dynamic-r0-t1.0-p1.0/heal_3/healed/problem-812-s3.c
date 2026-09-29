#include <stdio.h>
#include <string.h>

char* abbreviate_road(char *str) {
    char *pos;
    while ((pos = strstr(str, "road")) != NULL) {
        if (*(pos + 4) == ' ' || *(pos + 4) == ',' || *(pos + 4) == '.' || *(pos + 4) == '\0' || *(pos + 4) == ';' || *(pos + 4) == ':') {
            size_t len = strlen(pos + 4);
            memmove(pos + 3, pos + 4, len + 1);
            memcpy(pos, "rd", 2);
            str = pos + 2;
        } else {
            str = pos + 1;
        }
    }
    return str;
}

int main() {
    char str[] = "Welcome to the long road called life. Another road leads to success.";
    printf("Original: %s\n", str);
    abbreviate_road(str);
    printf("Abbreviated: %s\n", str);
    return 0;
}