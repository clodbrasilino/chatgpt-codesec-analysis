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

    size_t str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
    }

    char *result = malloc(str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;

    while (read_pos < str_len) {
        if (regexec(&regex, str + read_pos, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = match.rm_so;
                if (write_pos + copy_len > str_len) {
                    copy_len = str_len - write_pos;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + write_pos, str + read_pos, copy_len);
                write_pos += copy_len;
            }
            if (write_pos < str_len) {
                result[write_pos++] = ' ';
            }
            read_pos += match.rm_eo;
        } else {
            size_t remaining = str_len - read_pos;
            size_t copy_len = remaining;
            if (write_pos + copy_len > str_len) {
                copy_len = str_len - write_pos;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + write_pos, str + read_pos, copy_len);
            write_pos += copy_len;
            break;
        }
    }

    result[write_pos] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *res = remove_multiple_spaces("Hello    world!  This   is a    test.");
    if (res != NULL) {
        printf("%s\n", res);
        free(res);
    }
    return 0;
}