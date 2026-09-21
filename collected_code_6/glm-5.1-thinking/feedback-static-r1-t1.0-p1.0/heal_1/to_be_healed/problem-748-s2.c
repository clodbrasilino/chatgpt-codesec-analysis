#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len * 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    size_t curr_offset = 0;
    size_t dst_idx = 0;
    regmatch_t match;

    while (regexec(&regex, str + curr_offset, 1, &match, 0) == 0) {
        size_t match_start = curr_offset + match.rm_so;
        size_t match_end = curr_offset + match.rm_eo;

        for (size_t i = curr_offset; i < match_start; i++) {
            result[dst_idx++] = str[i];
        }

        if (match_start > 0 && str[match_start - 1] != ' ') {
            result[dst_idx++] = ' ';
        }

        result[dst_idx++] = str[match_start];
        curr_offset = match_end;
    }

    for (size_t i = curr_offset; i <= len; i++) {
        result[dst_idx++] = str[i];
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *tests[] = {
        "HelloWorld",
        "ThisIsATest",
        "Already Spaced",
        "NoSpacesHere",
        "ABC",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        char *res = add_spaces_capitals(tests[i]);
        if (res != NULL) {
            printf("Input: %s\nOutput: %s\n\n", tests[i], res);
            free(res);
        }
    }

    return 0;
}