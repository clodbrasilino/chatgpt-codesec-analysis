#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
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

    size_t src_idx = 0;
    size_t dest_idx = 0;

    while (src_idx < len) {
        if (regexec(&regex, snake_str + src_idx, 2, matches, 0) == 0 && matches[0].rm_so == 0) {
            if (matches[1].rm_so != -1) {
                camel_str[dest_idx++] = snake_str[src_idx + matches[1].rm_so] - 32;
            }
            src_idx += matches[0].rm_eo;
        } else {
            camel_str[dest_idx++] = snake_str[src_idx++];
        }
    }

    camel_str[dest_idx] = '\0';
    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}