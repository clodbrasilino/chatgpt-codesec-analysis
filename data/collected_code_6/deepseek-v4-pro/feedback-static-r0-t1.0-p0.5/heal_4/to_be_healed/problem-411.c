#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake);

    if (len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t result_size = len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "_([a-z])";

    int comp_result = regcomp(&regex, pattern, REG_EXTENDED);
    if (comp_result != 0) {
        free(result);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *cursor = snake;
    regmatch_t matches[2];
    int continue_matching = 1;

    while (src_pos < len && continue_matching) {
        int exec_result = regexec(&regex, cursor, 2, matches, 0);

        if (exec_result == 0) {
            size_t match_start = (size_t)matches[0].rm_so;
            size_t match_end = (size_t)matches[0].rm_eo;
            size_t letter_pos = (size_t)matches[1].rm_so;

            if (match_start > 0) {
                while (dst_pos + match_start >= result_size) {
                    size_t new_size = result_size * 2;
                    if (new_size < dst_pos + match_start + 1) {
                        new_size = dst_pos + match_start + 1;
                    }
                    char *new_result = realloc(result, new_size);
                    if (new_result == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = new_result;
                    result_size = new_size;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, cursor, match_start);
                dst_pos += match_start;
            }

            while (dst_pos >= result_size) {
                size_t new_size = result_size * 2;
                if (new_size < dst_pos + 1) {
                    new_size = dst_pos + 1;
                }
                char *new_result = realloc(result, new_size);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_size = new_size;
            }

            result[dst_pos] = (char)toupper((unsigned char)cursor[letter_pos]);
            dst_pos++;

            cursor += match_end;
            src_pos += match_end;
        } else {
            continue_matching = 0;
        }
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        while (dst_pos + remaining >= result_size) {
            size_t new_size = dst_pos + remaining + 1;
            char *new_result = realloc(result, new_size);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            result_size = new_size;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, cursor, remaining);
        dst_pos += remaining;
    }

    while (dst_pos >= result_size) {
        size_t new_size = dst_pos + 1;
        char *new_result = realloc(result, new_size);
        if (new_result == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
        result_size = new_size;
    }
    result[dst_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "already_camel",
        "multiple__underscores",
        "trailing_underscore_",
        "_leading_underscore",
        "single",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("%s -> %s\n", test_cases[i], camel);
            free(camel);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}