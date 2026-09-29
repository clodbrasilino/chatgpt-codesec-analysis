#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char first_repeated_char(const char *str)
{
    int count[UCHAR_MAX + 1] = {0};

    if (str == NULL) {
        return '\0';
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (count[c] == 2) {
            return str[i];
        }
    }

    return '\0';
}

int main(void)
{
    char *str = NULL;
    size_t buffer_size = 256;
    size_t len;
    char result;

    str = malloc(buffer_size);
    if (str == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(str, (int)buffer_size, stdin) == NULL) {
        free(str);
        return 1;
    }

    len = strnlen(str, buffer_size);
    while (len == buffer_size - 1 && str[len - 1] != '\n') {
        char *new_str;
        size_t new_size = buffer_size * 2;

        new_str = realloc(str, new_size);
        if (new_str == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            free(str);
            return 1;
        }
        str = new_str;

        if (fgets(str + len, (int)(new_size - len), stdin) == NULL) {
            free(str);
            return 1;
        }
        buffer_size = new_size;
        len = strnlen(str, buffer_size);
    }

    len = strnlen(str, buffer_size);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    result = first_repeated_char(str);
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    free(str);
    return 0;
}