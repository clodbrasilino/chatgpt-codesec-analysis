#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_([a-z0-9])", REG_EXTENDED);
    if (ret != 0) {
        free(camel_str);
        return NULL;
    }

    regmatch_t matches[2];
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
        if (camel_idx + prefix_len >= len + 1) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }
        if (prefix_len > 0) {
            memcpy(camel_str + camel_idx, cursor, prefix_len);
        }
        camel_idx += prefix_len;

        char next_char = cursor[matches[1].rm_so];
        camel_str[camel_idx++] = (char)((int)next_char - 32);

        cursor += matches[0].rm_eo;
    }

    const char *remaining_cursor = cursor;
    while (*remaining_cursor != '\0') {
        if (camel_idx >= len + 1) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }
        camel_str[camel_idx++] = *remaining_cursor++;
    }
    camel_str[camel_idx] = '\0';

    regfree(&regex);

    char *shrunk = realloc(camel_str, camel_idx + 1);
    if (shrunk != NULL) {
        camel_str = shrunk;
    }

    return camel_str;
}

int main(void) {
    const char *tests[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "this_is_a_snake_case_string_123",
        NULL
    };
    
    for (int i = 0; tests[i] != NULL; i++) {
        char *output = snake_to_camel(tests[i]);
        if (output == NULL) {
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }
    return 0;
}