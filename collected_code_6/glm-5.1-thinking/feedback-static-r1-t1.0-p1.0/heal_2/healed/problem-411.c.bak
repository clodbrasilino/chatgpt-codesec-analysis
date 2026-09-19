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

    size_t camel_idx = 0;
    const char *ptr = snake_str;
    regmatch_t pmatch[2];

    while (1) {
        ret = regexec(&regex, ptr, 2, pmatch, 0);
        if (ret == REG_NOMATCH) {
            strcpy(camel_str + camel_idx, ptr);
            camel_idx += strlen(ptr);
            break;
        }

        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t match_len = pmatch[0].rm_so;
        memcpy(camel_str + camel_idx, ptr, match_len);
        camel_idx += match_len;

        char upper_char = toupper((unsigned char)ptr[pmatch[1].rm_so]);
        camel_str[camel_idx++] = upper_char;

        ptr += pmatch[0].rm_eo;
    }

    camel_str[camel_idx] = '\0';
    regfree(&regex);
    return camel_str;
}

int main(int argc, const char * const argv[]) {
    if (argc < 2) {
        const char *test = "hello_world_example";
        char *result = snake_to_camel(test);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char *result = snake_to_camel(argv[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return 0;
}