#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t capacity;
    size_t length;
    char *result;
    const char *cursor;
    size_t result_len = 0;

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    if (input == NULL) {
        regfree(&regex);
        return NULL;
    }

    length = strnlen(input, SIZE_MAX);
    if (length == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    capacity = length + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            const char *end = memchr(cursor, '\0', capacity - (cursor - input));
            size_t remaining = end ? (size_t)(end - cursor) : 0;
            if (remaining > 0) {
                size_t available = capacity - result_len;
                size_t copy_len = remaining < available ? remaining : available;
                if (copy_len > 0) {
                    memcpy(result + result_len, cursor, copy_len);
                }
                result_len += copy_len;
            }
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            size_t available = capacity - result_len;
            copy_len = copy_len < available ? copy_len : available;
            if (copy_len > 0) {
                memcpy(result + result_len, cursor, copy_len);
            }
            result_len += copy_len;
        }

        cursor += match.rm_eo;
    }

    if (result_len >= capacity) {
        result_len = capacity - 1;
    }
    result[result_len] = '\0';

    char *final_result = realloc(result, result_len + 1);
    if (final_result == NULL) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    regfree(&regex);
    return final_result;
}

int main(void) {
    char *result = remove_uppercase_substrings("abcHELLOdefWORLDghi");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("ALLCAPS");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("nocaps");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("MixedCASEstring");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}