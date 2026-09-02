#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < len) {
        ret = regexec(&regex, input + src_pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            strcpy(result + dst_pos, input + src_pos);
            dst_pos += len - src_pos;
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            memcpy(result + dst_pos, input + src_pos, match_start - src_pos);
            dst_pos += match_start - src_pos;
        }

        src_pos = match_end;
    }

    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello WORLD this IS a Test STRING";
    char *cleaned = remove_uppercase_substrings(test_str);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_str);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}