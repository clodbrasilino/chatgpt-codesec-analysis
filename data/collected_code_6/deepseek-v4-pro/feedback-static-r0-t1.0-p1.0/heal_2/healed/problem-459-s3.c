#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t result_size = len + 1;
    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            size_t copy_size = match_start - src_pos;
            if (dst_pos + copy_size >= result_size) {
                size_t new_size = dst_pos + copy_size + (len - match_start) + 1;
                if (new_size < result_size) {
                    new_size = result_size * 2;
                }
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_size = new_size;
            }
            if (dst_pos + copy_size <= result_size) {
                memcpy(result + dst_pos, input + src_pos, copy_size);
                dst_pos += copy_size;
            }
        }

        src_pos = match_end;

        if (match.rm_eo == match.rm_so) {
            if (src_pos < len && input[src_pos] != '\0') {
                if (dst_pos + 1 >= result_size) {
                    size_t new_size = result_size * 2;
                    char *temp = (char *)realloc(result, new_size);
                    if (temp == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    result_size = new_size;
                }
                if (dst_pos < result_size) {
                    result[dst_pos++] = input[src_pos++];
                }
            } else {
                break;
            }
        }
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        if (dst_pos + remaining >= result_size) {
            size_t new_size = dst_pos + remaining + 1;
            if (new_size < result_size) {
                new_size = result_size * 2;
            }
            char *temp = (char *)realloc(result, new_size);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            result_size = new_size;
        }
        if (dst_pos + remaining <= result_size) {
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
        }
    }

    if (dst_pos >= result_size) {
        size_t new_size = dst_pos + 1;
        char *temp = (char *)realloc(result, new_size);
        if (temp == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
        result_size = new_size;
    }

    if (dst_pos < result_size) {
        result[dst_pos] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "HelloWORLDexampleTESTstring";
    char *cleaned = remove_uppercase_substrings(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}