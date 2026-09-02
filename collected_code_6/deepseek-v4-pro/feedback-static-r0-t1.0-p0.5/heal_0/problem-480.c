#include <stdio.h>
#include <string.h>
#include <limits.h>

char max_occurring_char(const char *str) {
    int count[UCHAR_MAX + 1] = {0};
    int max_count = 0;
    char max_char = '\0';
    const unsigned char *s = (const unsigned char *)str;

    if (str == NULL || *str == '\0') {
        return '\0';
    }

    while (*s) {
        count[*s]++;
        s++;
    }

    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }

    return max_char;
}

int main(void) {
    char str[1000];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    if (str[0] == '\0') {
        printf("Empty string\n");
        return 0;
    }

    char result = max_occurring_char(str);
    printf("Maximum occurring character: %c\n", result);

    return 0;
}