#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t max_groups = 1;
    regmatch_t matches[max_groups];

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