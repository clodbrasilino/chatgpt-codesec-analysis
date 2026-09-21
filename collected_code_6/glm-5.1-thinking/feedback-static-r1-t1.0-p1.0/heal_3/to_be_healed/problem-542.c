#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_with_colon(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = str;
    char *dst = result;
    regmatch_t match;
    size_t remaining = len + 1;

    while (1) {
        ret = regexec(&regex, src, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            snprintf(dst, remaining, "%s", src);
            break;
        }
        
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if ((size_t)match.rm_so >= remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        int written = snprintf(dst, remaining, "%.*s", (int)match.rm_so, src);
        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        dst += written;
        remaining -= written;

        if (remaining < 2) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        *dst = ':';
        dst++;
        remaining--;

        src += match.rm_eo;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "Hello world, this.is a test.";
    char *output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}