#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        return -1;
    }

    size_t len = strlen(str);
    char *new_str = malloc(len * 2 + 1);
    if (new_str == NULL) {
        regfree(&regex);
        return -1;
    }

    size_t new_len = 0;
    char *original_str = str;
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        size_t offset = pmatch[0].rm_so;
        if (str[pmatch[0].rm_so] >= 'A' && str[pmatch[0].rm_so] <= 'Z') {
            size_t remaining = original_str + len - str;
            memmove(new_str + new_len + 1, new_str + new_len, remaining);
            new_str[new_len] = ' ';
            new_len++;
        }
        new_str[new_len++] = str[pmatch[0].rm_so];
        str += offset + 1;
    }

    size_t remaining = original_str + len - str;
    if (remaining > 0) {
        memcpy(new_str + new_len, str, remaining);
        new_len += remaining;
    }
    new_str[new_len] = '\0';

    free(original_str);
    *original_str = *new_str;

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}