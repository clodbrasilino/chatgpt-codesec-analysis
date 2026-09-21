#include <stdio.h>
#include <limits.h>
#include <string.h>

char max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    unsigned long count[UCHAR_MAX + 1] = {0};
    const unsigned char *s = (const unsigned char *)str;
    size_t max_count = 0;
    char max_char = '\0';

    while (*s != '\0') {
        unsigned char uc = *s;
        count[uc]++;

        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = (char)uc;
        }

        s++;
    }

    return max_char;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    char result = max_occurring_char(input);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No character found\n");
    }

    return 0;
}