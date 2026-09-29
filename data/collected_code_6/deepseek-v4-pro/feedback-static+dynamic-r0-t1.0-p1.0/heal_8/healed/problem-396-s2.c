#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int starts_ends_same(const char *str) {
    regex_t regex;
    int ret;
    char pattern[] = "^(.).*\\1$";

    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 256);
    if (len == 0 || len >= 256) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(void) {
    size_t buffer_size = 257;
    char *input = calloc(buffer_size, sizeof(char));

    if (input == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(input, buffer_size, stdin) == NULL) {
        free(input);
        return 1;
    }

    size_t len = strnlen(input, buffer_size);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }

    if (len >= buffer_size) {
        input[buffer_size - 1] = '\0';
        len = buffer_size - 1;
    }

    if (starts_ends_same(input)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }

    free(input);
    return 0;
}