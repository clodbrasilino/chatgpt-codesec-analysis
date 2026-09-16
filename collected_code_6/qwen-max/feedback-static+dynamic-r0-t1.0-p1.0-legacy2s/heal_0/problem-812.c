#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    if (str == NULL) return;
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        memmove(pos + 2, pos + 4, strlen(pos + 4) + 1);
        *(pos + 2) = '.';
        pos += 2;
        pos = strstr(pos, "road");
    }
}

int main() {
    char input[] = "Please use the long road or side road for access.";
    abbreviate_road(input);
    printf("%s\n", input);
    return 0;
}