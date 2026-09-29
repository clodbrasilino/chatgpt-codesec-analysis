#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (len - i >= 4 && strncmp(str + i, "road", 4) == 0) {
            str[j++] = 'r';
            str[j++] = 'd';
            str[j++] = '.';
            i += 4;
        } else {
            str[j++] = str[i++];
        }
    }

    str[j] = '\0';
}

int main(void) {
    char text[] = "main road and broadway road";
    abbreviate_road(text);
    puts(text);
    return 0;
}