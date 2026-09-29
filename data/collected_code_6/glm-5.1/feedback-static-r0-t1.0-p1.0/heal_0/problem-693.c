#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_groups = 2;
    regmatch_t matches[max_groups];

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < len) {
        if (regexec(&regex, str + src_pos, max_groups, matches, 0) == 0 && matches[0].rm_so == 0) {
            result[dst_pos++] = ' ';
            src_pos += matches[0].rm_eo;
        } else {
            result[dst_pos++] = str[src_pos++];
        }
    }

    result[dst_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "This   is  a    test   string.";
    char *output = remove_multiple_spaces(input);

    if (output != NULL) {
        printf("Original: '%s'\n", input);
        printf("Modified: '%s'\n", output);
        free(output);
    }

    return 0;
}