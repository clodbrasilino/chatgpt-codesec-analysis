#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t matches[2];
    size_t read_idx = 0;
    size_t write_idx = 0;

    if (snake_str[0] >= 'a' && snake_str[0] <= 'z') {
        camel_str[write_idx++] = snake_str[0] - 32;
        read_idx = 1;
    }

    while (read_idx < len) {
        if (regexec(&regex, snake_str + read_idx, 2, matches, 0) == 0) {
            size_t match_start = read_idx + matches[0].rm_so;
            size_t match_end = read_idx + matches[0].rm_eo;

            for (size_t i = read_idx; i < match_start; i++) {
                camel_str[write_idx++] = snake_str[i];
            }

            char c = snake_str[read_idx + matches[1].rm_so];
            if (c >= 'a' && c <= 'z') {
                c -= 32;
            }
            camel_str[write_idx++] = c;

            read_idx = match_end;
        } else {
            for (size_t i = read_idx; i < len; i++) {
                camel_str[write_idx++] = snake_str[i];
            }
            break;
        }
    }

    camel_str[write_idx] = '\0';
    regfree(&regex);

    char *final_str = realloc(camel_str, write_idx + 1);
    if (final_str == NULL) {
        free(camel_str);
        return NULL;
    }

    return final_str;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return 1;
    }

    char *result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}