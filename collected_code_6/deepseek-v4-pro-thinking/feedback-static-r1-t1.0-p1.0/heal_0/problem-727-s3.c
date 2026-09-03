#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    char *result;
    size_t len;
    size_t pos = 0;
    size_t out = 0;

    if (input == NULL)
        return NULL;

    if (regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED) != 0)
        return NULL;

    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (pos < len) {
        regmatch_t match;
        int ret = regexec(&regex, input + pos, 1, &match, 0);

        if (ret == 0) {
            if (match.rm_so > 0) {
                size_t n = (size_t)match.rm_so;
                memcpy(result + out, input + pos, n);
                out += n;
            }
            if (match.rm_eo <= match.rm_so) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            pos += (size_t)match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            size_t n = len - pos;
            memcpy(result + out, input + pos, n);
            out += n;
            pos = len;
        } else {
            regfree(&regex);
            free(result);
            return NULL;
        }
    }

    result[out] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    char *cleaned = remove_non_alphanumeric("Hello, World! 123");
    if (cleaned != NULL) {
        puts(cleaned);
        free(cleaned);
    }
    return 0;
}