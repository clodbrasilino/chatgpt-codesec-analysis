#include <ctype.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    char *out = malloc(len * 2 + 1);
    if (out == NULL) {
        return NULL;
    }

    if (len == 0) {
        out[0] = '\0';
        return out;
    }

    regex_t regex;
    int reg_error = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (reg_error != 0) {
        free(out);
        return NULL;
    }

    size_t in_pos = 0;
    size_t out_pos = 0;
    regmatch_t match;
    int ret;

    while ((ret = regexec(&regex, str + in_pos, 1, &match, 0)) == 0) {
        size_t match_pos = in_pos + (size_t)match.rm_so;

        size_t seg_len = match_pos - in_pos;
        memcpy(out + out_pos, str + in_pos, seg_len);
        out_pos += seg_len;

        unsigned char prev = match_pos > 0 ? (unsigned char)str[match_pos - 1] : 0;
        unsigned char next = (unsigned char)str[match_pos + 1];

        int insert_underscore = 0;
        if ((prev >= 'a' && prev <= 'z') || (prev >= '0' && prev <= '9')) {
            insert_underscore = 1;
        } else if ((prev >= 'A' && prev <= 'Z') && (next >= 'a' && next <= 'z')) {
            insert_underscore = 1;
        }

        if (insert_underscore) {
            out[out_pos++] = '_';
        }

        out[out_pos++] = (char)tolower((unsigned char)str[match_pos]);
        in_pos = match_pos + 1;
    }

    if (ret != REG_NOMATCH) {
        regfree(&regex);
        free(out);
        return NULL;
    }

    size_t rem_len = len - in_pos;
    memcpy(out + out_pos, str + in_pos, rem_len);
    out_pos += rem_len;
    out[out_pos] = '\0';

    regfree(&regex);
    return out;
}

int main(void) {
    const char *tests[] = {
        "camelCaseString",
        "HTTPServer",
        "getHTTPResponse",
        "fooBARBaz",
        "CamelCase",
        "hello",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; ++i) {
        char *result = camel_to_snake(tests[i]);
        if (result != NULL) {
            printf("%s -> %s\n", tests[i], result);
            free(result);
        } else {
            printf("%s -> (null)\n", tests[i]);
        }
    }

    return 0;
}