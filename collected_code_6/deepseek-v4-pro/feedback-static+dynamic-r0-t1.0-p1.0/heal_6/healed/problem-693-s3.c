#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char *resize_buffer(char *buffer, size_t *capacity, size_t required) {
    size_t new_capacity = *capacity;
    while (new_capacity <= required) {
        new_capacity *= 2;
    }
    char *new_buffer = (char *)realloc(buffer, new_capacity);
    if (new_buffer == NULL) {
        free(buffer);
        return NULL;
    }
    *capacity = new_capacity;
    return new_buffer;
}

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]{2,}", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t capacity = input_len + 1;
    if (capacity < 256) {
        capacity = 256;
    }
    char *result = (char *)malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len) {
        int match_result = regexec(&regex, input + src_pos, 1, &match, 0);
        
        if (match_result == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                if (dst_pos + copy_len + 1 > capacity) {
                    char *new_result = resize_buffer(result, &capacity, dst_pos + copy_len + 1);
                    if (new_result == NULL) {
                        regfree(&regex);
                        return NULL;
                    }
                    result = new_result;
                }
                memcpy(result + dst_pos, input + src_pos, copy_len);
                dst_pos += copy_len;
            }
            if (dst_pos + 2 > capacity) {
                char *new_result = resize_buffer(result, &capacity, dst_pos + 2);
                if (new_result == NULL) {
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
            }
            result[dst_pos++] = ' ';
            src_pos += match.rm_eo;
        } else if (match_result == REG_NOMATCH) {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining + 1 > capacity) {
                char *new_result = resize_buffer(result, &capacity, dst_pos + remaining + 1);
                if (new_result == NULL) {
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
            }
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
            src_pos = input_len;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (dst_pos + 1 > capacity) {
        char *new_result = resize_buffer(result, &capacity, dst_pos + 1);
        if (new_result == NULL) {
            regfree(&regex);
            return NULL;
        }
        result = new_result;
    }
    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "Hello   World",
        "  Multiple   spaces   here  ",
        "NoSpaces",
        "",
        "   ",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *cleaned = remove_multiple_spaces(test_strings[i]);
        if (cleaned != NULL && cleaned[0] != '\0') {
            printf("Original: \"%s\"\n", test_strings[i]);
            printf("Cleaned:  \"%s\"\n\n", cleaned);
            free(cleaned);
        } else if (cleaned != NULL && cleaned[0] == '\0') {
            printf("Original: \"%s\"\n", test_strings[i]);
            printf("Cleaned:  \"\"\n\n");
            free(cleaned);
        } else {
            printf("Error processing string %d\n", i);
        }
    }

    return 0;
}