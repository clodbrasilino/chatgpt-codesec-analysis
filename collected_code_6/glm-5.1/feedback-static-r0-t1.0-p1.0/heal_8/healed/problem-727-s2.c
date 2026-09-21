#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_non_alnum(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    size_t result_capacity = len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t dest_idx = 0;
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
            size_t available = result_capacity > dest_idx ? result_capacity - dest_idx - 1 : 0;
            if (copy_len > available) {
                copy_len = available;
            }
            memcpy(result + dest_idx, current_ptr, copy_len);
            dest_idx += copy_len;
        }

        current_ptr += match.rm_eo;
    }

    size_t remaining_len = strnlen(current_ptr, result_capacity);
    if (remaining_len > 0) {
        size_t available = result_capacity > dest_idx ? result_capacity - dest_idx - 1 : 0;
        if (remaining_len > available) {
            remaining_len = available;
        }
        memcpy(result + dest_idx, current_ptr, remaining_len);
        dest_idx += remaining_len;
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