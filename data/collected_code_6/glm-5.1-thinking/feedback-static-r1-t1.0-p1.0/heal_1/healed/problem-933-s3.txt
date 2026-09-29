#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdint.h>

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

    size_t camel_len = 0;
    while (camel[camel_len] != '\0') {
        camel_len++;
    }

    const char *p = camel;
    size_t match_count = 0;
    regmatch_t matches[3];

    while (regexec(&regex, p, 3, matches, 0) == 0) {
        match_count++;
        p += matches[0].rm_eo;
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

    size_t alloc_size = out_len + 1;
    if (alloc_size == 0) {
        regfree(&regex);
        return NULL;
    }

    char *out = malloc(alloc_size);
    if (out == NULL) {
        regfree(&regex);
        return NULL;
    }

    p = camel;
    char *o = out;
    size_t remaining = alloc_size;

    while (regexec(&regex, p, 3, matches, 0) == 0) {
        size_t copy_len = matches[1].rm_so;
        if (copy_len > remaining) {
            free(out);
            regfree(&regex);
            return NULL;
        }
        memcpy(o, p, copy_len);
        o += copy_len;
        remaining -= copy_len;

        if (remaining < 3) {
            free(out);
            regfree(&regex);
            return NULL;
        }
        *o++ = p[matches[1].rm_so];
        *o++ = '_';
        *o++ = p[matches[2].rm_so];
        remaining -= 3;

        p += matches[0].rm_eo;
    }

    size_t final_len = 0;
    while (p[final_len] != '\0') {
        final_len++;
    }
    if (final_len >= remaining) {
        free(out);
        regfree(&regex);
        return NULL;
    }
    snprintf(o, remaining, "%s", p);

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