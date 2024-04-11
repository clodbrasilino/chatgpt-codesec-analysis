#include <stdio.h>
#include <string.h>

void abbreviateRoad(char* str) {
    char* occurrence = strstr(str, "road");
    while (occurrence != NULL) {
        occurrence[1] = 'd';
        occurrence[2] = '.';
        memmove(&occurrence[3], &occurrence[4], strlen(occurrence) - 3);
        occurrence = strstr(str, "road");
    }
}

int main() {
    char str[] = "The road is long and the road is winding.";
    printf("Original string: %s\n", str);
    abbreviateRoad(str);
    printf("Modified string: %s\n", str);
    return 0;
}