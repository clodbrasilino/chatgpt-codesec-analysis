#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t capacity;
    size_t length;
    char *result;
    const char *cursor;

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    capacity = strlen(input) + 1;
    result = (char *)malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    length = 0;
    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            if (length + remaining + 1 > capacity) {
                char *temp = (char *)realloc(result, length + remaining + 1);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                /* Possible weaknesses found:
                 *  Value stored to 'capacity' is never read [deadcode.DeadStores]
                 *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
                 */
                capacity = length + remaining + 1;
            }
            memcpy(result + length, cursor, remaining);
            length += remaining;
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            if (length + copy_len + 1 > capacity) {
                char *temp = (char *)realloc(result, length + copy_len + 1);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                capacity = length + copy_len + 1;
            }
            memcpy(result + length, cursor, copy_len);
            length += copy_len;
        }

        cursor += match.rm_eo;
    }

    result[length] = '\0';

    char *final_result = (char *)realloc(result, length + 1);
    if (final_result == NULL) {
        regfree(&regex);
        return result;
    }

    regfree(&regex);
    return final_result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    result = remove_lowercase_substrings(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}