#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_non_alnum(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t dest_idx = 0;
    size_t result_capacity = len + 1;
    const char *current_ptr = str;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, current_ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t copy_len = match.rm_so;
        if (copy_len > 0) {
            if (dest_idx + copy_len <= result_capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dest_idx, current_ptr, copy_len);
            } else {
                copy_len = result_capacity > dest_idx ? result_capacity - dest_idx - 1 : 0;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dest_idx, current_ptr, copy_len);
            }
            dest_idx += copy_len;
        }

        current_ptr += match.rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(current_ptr);
    if (remaining_len > 0) {
        size_t safe_remaining = (dest_idx + remaining_len < result_capacity) ? remaining_len : (result_capacity > dest_idx + 1 ? result_capacity - dest_idx - 1 : 0);
        if (safe_remaining > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dest_idx, current_ptr, safe_remaining);
            dest_idx += safe_remaining;
        }
    }

    if (dest_idx < result_capacity) {
        result[dest_idx] = '\0';
    } else {
        result[result_capacity - 1] = '\0';
    }

    regfree(&regex);

    char *shrunk_result = realloc(result, dest_idx + 1);
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *filtered = remove_non_alnum(argv[1]);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation or regex error\n");
        return 1;
    }

    printf("%s\n", filtered);
    free(filtered);

    return 0;
}