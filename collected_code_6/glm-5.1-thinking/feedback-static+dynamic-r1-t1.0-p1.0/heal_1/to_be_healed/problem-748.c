#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *split_camel_case(const char *input) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = malloc(len * 2 + 2);
    if (!result) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])|([A-Z]+)([A-Z][a-z])", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    regmatch_t matches[5];
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        int exec_ret = regexec(&regex, input + src_offset, 5, matches, 0);
        if (exec_ret != 0) {
            break;
        }

        size_t insert_pos;
        if (matches[1].rm_so != -1) {
            insert_pos = src_offset + matches[1].rm_eo;
        } else if (matches[3].rm_so != -1) {
            insert_pos = src_offset + matches[3].rm_eo;
        } else {
            insert_pos = src_offset + matches[0].rm_eo;
        }

        for (size_t i = src_offset; i < insert_pos; i++) {
            result[dest_offset++] = input[i];
        }
        result[dest_offset++] = ' ';
        for (size_t i = insert_pos; i < src_offset + matches[0].rm_eo; i++) {
            result[dest_offset++] = input[i];
        }

        src_offset = src_offset + matches[0].rm_eo;
    }

    for (size_t i = src_offset; i < len; i++) {
        result[dest_offset++] = input[i];
    }
    result[dest_offset] = '\0';

    regfree(&regex);

    char *shrunk = realloc(result, dest_offset + 1);
    if (shrunk) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "HelloWorld",
        "ThisIsATest",
        "XMLParser",
        "JSONData",
        "simple",
        "Already Spaced",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        char *res = split_camel_case(tests[i]);
        if (res) {
            printf("Input: '%s' -> Output: '%s'\n", tests[i], res);
            free(res);
        } else {
            printf("Allocation or regex error for '%s'\n", tests[i]);
        }
    }

    return 0;
}