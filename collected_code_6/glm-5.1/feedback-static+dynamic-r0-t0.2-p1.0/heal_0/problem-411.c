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

    char *out_ptr = camel_str;
    const char *in_ptr = snake_str;
    regmatch_t matches[2];

    while (1) {
        ret = regexec(&regex, in_ptr, 2, matches, 0);
        if (ret == REG_NOMATCH) {
            strcpy(out_ptr, in_ptr);
            break;
        }

        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        memcpy(out_ptr, in_ptr, prefix_len);
        out_ptr += prefix_len;

        char c = in_ptr[matches[1].rm_so];
        if (c >= 'a' && c <= 'z') {
            c -= 32;
        }
        *out_ptr = c;
        out_ptr += 1;

        in_ptr += matches[0].rm_eo;
    }

    regfree(&regex);
    return camel_str;
}

int main(int argc, char *argv[]) {
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