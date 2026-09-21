#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_STR_LEN 1048576

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    regex_t regex = {0};
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return NULL;
    }

    const char *p = camel;
    size_t match_count = 0;
    regmatch_t matches[3];

    while (regexec(&regex, p, 3, matches, 0) == 0) {
        match_count++;
        p += matches[0].rm_eo;
    }

    size_t camel_len = strnlen(camel, MAX_STR_LEN);
    if (camel_len == MAX_STR_LEN) {
        regfree(&regex);
        return NULL;
    }

    if (match_count > SIZE_MAX - camel_len) {
        regfree(&regex);
        return NULL;
    }

    size_t out_len = camel_len + match_count;
    if (out_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *out = malloc(out_len + 1);
    if (out == NULL) {
        regfree(&regex);
        return NULL;
    }

    p = camel;
    char *o = out;
    size_t out_written = 0;

    while (regexec(&regex, p, 3, matches, 0) == 0) {
        if (matches[1].rm_so < 0 || matches[2].rm_so < 0) {
            regfree(&regex);
            free(out);
            return NULL;
        }
        
        size_t copy_len = (size_t)matches[1].rm_so;
        size_t dest_remaining = out_len - out_written;
        
        if (copy_len > dest_remaining) {
            regfree(&regex);
            free(out);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(o, p, copy_len);
        o += copy_len;
        out_written += copy_len;

        dest_remaining = out_len - out_written;
        if (3 > dest_remaining) {
            regfree(&regex);
            free(out);
            return NULL;
        }

        *o++ = p[matches[1].rm_so];
        *o++ = '_';
        *o++ = p[matches[2].rm_so];
        out_written += 3;

        p += matches[0].rm_eo;
    }

    size_t remaining = out_len - out_written;
    snprintf(o, remaining + 1, "%s", p);

    for (size_t i = 0; i < out_len; i++) {
        out[i] = (char)tolower((unsigned char)out[i]);
    }

    regfree(&regex);
    return out;
}

int main(void) {
    const char *input = "helloWorldThisIsATest";
    char *output = camel_to_snake(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}