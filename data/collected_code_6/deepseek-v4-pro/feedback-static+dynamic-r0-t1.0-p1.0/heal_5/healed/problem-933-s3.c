#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool is_uppercase(char c) {
    return (c >= 'A' && c <= 'Z');
}

static char to_lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (char)(c + ('a' - 'A'));
    }
    return c;
}

static char *camel_to_snake(const char *input) {
    size_t input_len;
    size_t capacity;
    char *result;
    size_t length = 0;
    size_t pos = 0;
    size_t segment_start;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len == 0) {
        result = (char *)malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    capacity = input_len * 2 + 1;
    result = (char *)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    segment_start = 0;

    for (pos = 0; pos < input_len; pos++) {
        if (is_uppercase(input[pos])) {
            if (pos > segment_start) {
                size_t segment_len = pos - segment_start;
                if (length + segment_len >= capacity) {
                    size_t new_capacity = capacity * 2 + segment_len;
                    char *new_result = (char *)realloc(result, new_capacity);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }
                memcpy(result + length, input + segment_start, segment_len);
                length += segment_len;
            }

            if (length > 0 && result[length - 1] != '_') {
                if (length + 1 >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char *new_result = (char *)realloc(result, new_capacity);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }
                result[length] = '_';
                length++;
            }

            if (length >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                capacity = new_capacity;
            }
            result[length] = to_lowercase(input[pos]);
            length++;

            segment_start = pos + 1;
        }
    }

    if (segment_start < input_len) {
        size_t remaining = input_len - segment_start;
        if (length + remaining >= capacity) {
            size_t new_capacity = capacity + remaining + 1;
            char *new_result = (char *)realloc(result, new_capacity);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
            capacity = new_capacity;
        }
        memcpy(result + length, input + segment_start, remaining);
        length += remaining;
    }

    result[length] = '\0';
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCaseString",
        "thisIsATest",
        "single",
        "",
        "ALLCAPS",
        "mixedCASEString"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *converted = camel_to_snake(test_strings[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_strings[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_strings[i]);
        }
    }

    return 0;
}