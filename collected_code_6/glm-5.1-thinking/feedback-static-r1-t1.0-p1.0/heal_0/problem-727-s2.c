#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    size_t len = strlen(input);
    char *result = malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t result_idx = 0;
    const char *ptr = input;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            strcpy(result + result_idx, ptr);
            result_idx += strlen(ptr);
            break;
        }

        size_t copy_len = match.rm_so;
        if (copy_len > 0) {
            memcpy(result + result_idx, ptr, copy_len);
            result_idx += copy_len;
        }

        ptr += match.rm_eo;
    }

    result[result_idx] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test = "Hello, World! 123 @#$%";
    char *cleaned = remove_non_alnum(test);
    
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }
    
    return 0;
}