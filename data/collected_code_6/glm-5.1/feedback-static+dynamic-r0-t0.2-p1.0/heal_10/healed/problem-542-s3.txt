#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    size_t max_replacements = len;
    size_t result_size = len + max_replacements + 1;
    if (result_size <= len) {
        return NULL;
    }

    char* result = (char*)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    regmatch_t match;

    while (i < len) {
        ret = regexec(&regex, str + i, 1, &match, 0);
        if (ret == 0) {
            size_t start = i + match.rm_so;
            size_t end = i + match.rm_eo;
            size_t copy_len = start - i;

            if (copy_len > 0) {
                size_t required = j + copy_len;
                if (required < result_size) {
                    memcpy(result + j, str + i, copy_len);
                    j = required;
                } else {
                    break;
                }
            }

            if (j + 1 < result_size) {
                result[j++] = ':';
            } else {
                break;
            }

            i = end;
        } else {
            size_t copy_len = len - i;

            if (copy_len > 0) {
                size_t required = j + copy_len;
                if (required < result_size) {
                    memcpy(result + j, str + i, copy_len);
                    j = required;
                } else {
                    break;
                }
            }
            i = len;
        }
    }

    if (j < result_size) {
        result[j] = '\0';
    } else {
        result[result_size - 1] = '\0';
        j = result_size - 1;
    }

    regfree(&regex);

    char* trimmed_result = (char*)realloc(result, j + 1);
    if (trimmed_result != NULL) {
        return trimmed_result;
    }
    
    return result;
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* res = replace_with_colon(argv[1]);
    if (res == NULL) {
        fprintf(stderr, "Error: Memory allocation or regex compilation failed\n");
        return 1;
    }

    printf("%s\n", res);
    free(res);

    return 0;
}