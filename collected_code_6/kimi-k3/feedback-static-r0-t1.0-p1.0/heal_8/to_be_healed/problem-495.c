#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

int remove_lowercase_substrings(const char *input, size_t input_len, char **output)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *end;
    char *result;
    size_t result_len;
    size_t remaining;
    size_t copy_len;
    int ret;

    if (input == NULL || output == NULL) {
        errno = EINVAL;
        return -1;
    }

    *output = NULL;
    end = input + input_len;

    result = malloc(input_len + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        errno = EINVAL;
        return -1;
    }

    cursor = input;
    result_len = 0;

    while (cursor < end && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            remaining = (size_t)(end - cursor);
            copy_len = strnlen(cursor, remaining);

            if (copy_len > input_len - result_len) {
                regfree(&regex);
                free(result);
                errno = EOVERFLOW;
                return -1;
            }

            if (copy_len > 0) {
                if (result_len + copy_len > input_len) {
                    regfree(&regex);
                    free(result);
                    errno = EOVERFLOW;
                    return -1;
                }
                if (result_len + copy_len + 1 > input_len + 1) {
                    regfree(&regex);
                    free(result);
                    errno = EOVERFLOW;
                    return -1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
            }
            break;
        }

        if (ret != 0) {
            regfree(&regex);
            free(result);
            errno = EINVAL;
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo < match.rm_so ||
            (size_t)match.rm_eo > (size_t)(end - cursor)) {
            regfree(&regex);
            free(result);
            errno = EINVAL;
            return -1;
        }

        copy_len = (size_t)match.rm_so;

        if (copy_len > input_len - result_len) {
            regfree(&regex);
            free(result);
            errno = EOVERFLOW;
            return -1;
        }

        if (copy_len > 0) {
            if (result_len + copy_len > input_len) {
                regfree(&regex);
                free(result);
                errno = EOVERFLOW;
                return -1;
            }
            if (result_len + copy_len + 1 > input_len + 1) {
                regfree(&regex);
                free(result);
                errno = EOVERFLOW;
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }

        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

int main(void)
{
    const char *input = "HelloWorldABCdefGHIjklMNOP";
    size_t input_len;
    char *output = NULL;

    input_len = strnlen(input, 256);
    if (input_len == 256) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    if (remove_lowercase_substrings(input, input_len, &output) != 0) {
        fprintf(stderr, "Error processing string: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);

    return EXIT_SUCCESS;
}