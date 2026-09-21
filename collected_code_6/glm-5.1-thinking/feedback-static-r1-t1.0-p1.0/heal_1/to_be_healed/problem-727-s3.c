#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *str) {
    regex_t regex;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    regoff_t i;
    
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }
    
    if (regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }
    
    size_t result_idx = 0;
    const char *p = str;
    
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }
        for (i = match.rm_so; i < match.rm_eo; i++) {
            result[result_idx++] = p[i];
        }
        p += match.rm_eo;
    }
    
    result[result_idx] = '\0';
    regfree(&regex);
    
    return result;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$%";
    char *output = remove_non_alnum(input);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}