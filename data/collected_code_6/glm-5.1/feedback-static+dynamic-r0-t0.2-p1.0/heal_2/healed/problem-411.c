#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        free(camel_str);
        return NULL;
    }

    char *out_ptr = camel_str;
    const char *in_ptr = snake_str;
    regmatch_t matches[2];

    while (1) {
        ret = regexec(&regex, in_ptr, 2, matches, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = strlen(in_ptr);
            if (remaining_len > 0) {
                memcpy(out_ptr, in_ptr, remaining_len);
                out_ptr += remaining_len;
            }
            break;
        }

        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        if (prefix_len > 0) {
            memcpy(out_ptr, in_ptr, prefix_len);
            out_ptr += prefix_len;
        }

        if (matches[1].rm_so != -1) {
            *out_ptr = toupper((unsigned char)in_ptr[matches[1].rm_so]);
            out_ptr += 1;
        }

        in_ptr += matches[0].rm_eo;
    }

    *out_ptr = '\0';
    regfree(&regex);
    return camel_str;
}

int main(int argc, char * const argv[]) {
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