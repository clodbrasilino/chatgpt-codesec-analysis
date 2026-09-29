#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t match[2];
    char *camel_str, *p, *result;
    int len, match_len, i;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    len = strlen(snake_str);
    camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }
    strcpy(camel_str, snake_str);

    p = camel_str;
    while (regexec(&regex, p, 2, match, 0) == 0) {
        match_len = match[1].rm_eo - match[1].rm_so;
        for (i = 0; i < match_len; i++) {
            p[match[1].rm_so + i] = toupper(p[match[1].rm_so + i]);
        }
        p += match[0].rm_eo;
    }

    regfree(&regex);
    result = realloc(camel_str, strlen(camel_str) + 1);
    if (result == NULL) {
        free(camel_str);
        return NULL;
    }
    return result;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);

    if (camel_str != NULL) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}