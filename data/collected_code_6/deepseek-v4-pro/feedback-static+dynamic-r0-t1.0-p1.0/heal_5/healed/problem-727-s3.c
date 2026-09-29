#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char *append_chars(char *dest, size_t *dest_len, size_t *dest_cap,
                          const char *src, size_t src_len) {
    if (src_len == 0) {
        return dest;
    }

    if (src_len > (size_t)-1 - *dest_len) {
        free(dest);
        return NULL;
    }

    size_t needed = *dest_len + src_len + 1;
    if (needed > *dest_cap) {
        size_t new_cap = needed;
        char *new_dest = (char *)realloc(dest, new_cap);
        if (new_dest == NULL) {
            free(dest);
            return NULL;
        }
        dest = new_dest;
        *dest_cap = new_cap;
    }

    if (*dest_len + src_len >= *dest_cap) {
        free(dest);
        return NULL;
    }

    memcpy(dest + *dest_len, src, src_len);
    *dest_len += src_len;
    dest[*dest_len] = '\0';
    return dest;
}

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    char *result = NULL;
    size_t input_len = strnlen(input, 65536);
    size_t result_len = 0;

    if (input_len >= (size_t)-1) {
        return NULL;
    }

    size_t result_capacity = input_len + 1;

    result = (char *)malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    const char *cursor = input;
    regmatch_t match;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            if ((size_t)match.rm_so > 65536 - (size_t)(cursor - input)) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result = append_chars(result, &result_len, &result_capacity,
                                  cursor, (size_t)match.rm_so);
            if (result == NULL) {
                regfree(&regex);
                return NULL;
            }
        }
        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
        if (cursor - input > 65536) {
            regfree(&regex);
            free(result);
            return NULL;
        }
    }

    if (*cursor != '\0') {
        size_t offset = (size_t)(cursor - input);
        if (offset > 65536) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        size_t remaining_len = strnlen(cursor, 65536 - offset);
        result = append_chars(result, &result_len, &result_capacity,
                              cursor, remaining_len);
        if (result == NULL) {
            regfree(&regex);
            return NULL;
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "Hello, World! 123",
        "Test@#$%^&*()String",
        "abc123XYZ",
        "   spaces   and---symbols!!!",
        "",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *cleaned = remove_non_alphanumeric(test_strings[i]);
        if (cleaned != NULL) {
            printf("Original: %s\n", test_strings[i]);
            printf("Cleaned:  %s\n\n", cleaned);
            free(cleaned);
        } else {
            printf("Failed to process string: %s\n\n", test_strings[i]);
        }
    }

    return 0;
}