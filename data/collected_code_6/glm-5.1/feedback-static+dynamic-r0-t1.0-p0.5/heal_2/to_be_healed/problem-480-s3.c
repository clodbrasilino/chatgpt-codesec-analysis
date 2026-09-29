#include <stdio.h>
#include <string.h>

char find_max_occurring_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int count[256] = {0};
    int max_count = 0;
    char max_char = '\0';

    for (size_t i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = str[i];
        }
    }

    return max_char;
}

int main(int argc, char *argv[]) {
    const char *str = "experience";
    char result = find_max_occurring_char(str);

    if (result != '\0') {
        printf("Maximum occurring character: %c\n", result);
    } else {
        printf("String is empty or NULL\n");
    }

    return 0;
}