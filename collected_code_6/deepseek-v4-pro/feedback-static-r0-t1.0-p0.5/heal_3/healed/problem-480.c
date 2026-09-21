#include <stdio.h>
#include <string.h>
#include <limits.h>

char max_occurring_char(const char *str) {
    int count[UCHAR_MAX + 1] = {0};
    int max_count = 0;
    char max_char = '\0';
    const unsigned char *s;

    if (str == NULL || *str == '\0') {
        return '\0';
    }

    s = (const unsigned char *)str;
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
    size_t len;
    char *ret;

    printf("Enter a string: ");
    ret = fgets(str, sizeof(str), stdin);
    if (ret == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    str[sizeof(str) - 1] = '\0';
    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (ch == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }

    if (len == 0) {
        printf("Empty string\n");
        return 0;
    }

    char result = max_occurring_char(str);
    printf("Maximum occurring character: %c\n", result);

    return 0;
}