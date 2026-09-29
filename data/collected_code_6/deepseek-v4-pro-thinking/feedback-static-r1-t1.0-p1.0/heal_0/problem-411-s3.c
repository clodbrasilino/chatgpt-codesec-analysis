#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake);

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    regex_t regex;
    int comp_ret = regcomp(&regex, "_+([[:alnum:]]?)", REG_EXTENDED);
    if (comp_ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(snake);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *current = snake;
    size_t dest = 0;
    regmatch_t matches[2];
    int exec_ret;

    while ((exec_ret = regexec(&regex, current, 2, matches, 0)) == 0) {
        size_t prefix_len = (size_t)matches[0].rm_so;
        if (prefix_len > 0) {
            memcpy(result + dest, current, prefix_len);
            dest += prefix_len;
        }

        if (matches[1].rm_so != -1 && matches[1].rm_eo > matches[1].rm_so) {
            result[dest] = (char)toupper((unsigned char)current[matches[1].rm_so]);
            dest++;
        }

        current += matches[0].rm_eo;
    }

    if (exec_ret != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    size_t suffix_len = strlen(current);
    if (suffix_len > 0) {
        memcpy(result + dest, current, suffix_len);
        dest += suffix_len;
    }

    result[dest] = '\0';
    regfree(&regex);
    return result;
}

int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "snake_case_string";
    char *camel = snake_to_camel(input);

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", camel);
    free(camel);
    return EXIT_SUCCESS;
}