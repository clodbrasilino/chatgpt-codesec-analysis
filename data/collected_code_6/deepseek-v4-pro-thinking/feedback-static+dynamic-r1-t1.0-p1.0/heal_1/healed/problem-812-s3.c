#include <stdio.h>
#include <string.h>

char *abbreviate_road(char *str) {
    char *read;
    char *write;

    if (str == NULL) {
        return NULL;
    }

    read = str;
    write = str;

    while (*read != '\0') {
        if (read[0] != '\0' && read[1] != '\0' && read[2] != '\0' && read[3] != '\0' &&
            memcmp(read, "road", 4) == 0) {
            *write++ = 'r';
            *write++ = 'd';
            *write++ = '.';
            read += 4;
        } else {
            *write++ = *read++;
        }
    }

    *write = '\0';
    return str;
}

int main(void) {
    char input[] = "123 main road and broadway road";

    printf("%s\n", input);
    abbreviate_road(input);
    printf("%s\n", input);

    return 0;
}