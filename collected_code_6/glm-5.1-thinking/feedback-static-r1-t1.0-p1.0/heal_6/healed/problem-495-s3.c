#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *str) {
    if (!str) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[[:lower:]]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *p = str;
    size_t out_idx = 0;
    regmatch_t match;

    while (*p) {
        if (regexec(&regex, p, 1, &match, 0) == REG_NOMATCH) {
            size_t remaining = len - (p - str);
            if (out_idx + remaining <= len) {
                memcpy(result + out_idx, p, remaining);
                out_idx += remaining;
            }
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (out_idx + copy_len <= len) {
                memcpy(result + out_idx, p, copy_len);
                out_idx += copy_len;
            }
        }

        p += match.rm_eo;
    }

    result[out_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, out_idx + 1);
    return shrunk != NULL ? shrunk : result;
}

int main(void) {
    const char *input = "HelloWorldABCdefGHI";
    char *output = remove_lowercase_substrings(input);
    
    if (output != NULL) {
        printf("Original: %s\nResult: %s\n", input, output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation or regex compilation failed\n");
        return 1;
    }
    
    return 0;
}