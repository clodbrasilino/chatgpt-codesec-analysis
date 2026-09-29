#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

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

    size_t camel_idx = 0;
    const char *cursor = snake_str;

    while (1) {
        ret = regexec(&regex, cursor, 2, matches, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        memcpy(camel_str + camel_idx, cursor, prefix_len);
        camel_idx += prefix_len;

        char lower_char = cursor[matches[1].rm_so];
        camel_str[camel_idx++] = toupper((unsigned char)lower_char);

        cursor += matches[0].rm_eo;
    }

    strcpy(camel_str + camel_idx, cursor);

    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char *inputs[] = {"android_tv", "google_pixel", "apple_watch"};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < num_inputs; i++) {
        char *output = snake_to_camel(inputs[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    return 0;
}