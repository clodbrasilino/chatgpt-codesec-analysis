#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PATTERNS 10
#define MAX_PATTERN_LEN 20

bool check_sequence(const char *input, const char patterns[][MAX_PATTERN_LEN], int pattern_count) {
    if (input == NULL || patterns == NULL || pattern_count <= 0) {
        return false;
    }

    size_t input_len = strlen(input);
    size_t pos = 0;

    while (pos < input_len) {
        bool matched = false;

        for (int i = 0; i < pattern_count; i++) {
            size_t pat_len = strlen(patterns[i]);
            if (pat_len == 0) {
                continue;
            }

            if (pos + pat_len <= input_len &&
                strncmp(input + pos, patterns[i], pat_len) == 0) {
                pos += pat_len;
                matched = true;
                break;
            }
        }

        if (!matched) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char patterns[][MAX_PATTERN_LEN] = {
        "ab", "cd", "ef"
    };
    int pattern_count = 3;

    const char *test1 = "abcdef";
    const char *test2 = "abefcd";
    const char *test3 = "abc";
    const char *test4 = "";
    const char *test5 = "abxyz";

    printf("Test 1: %s -> %s\n", test1, check_sequence(test1, patterns, pattern_count) ? "true" : "false");
    printf("Test 2: %s -> %s\n", test2, check_sequence(test2, patterns, pattern_count) ? "true" : "false");
    printf("Test 3: %s -> %s\n", test3, check_sequence(test3, patterns, pattern_count) ? "true" : "false");
    printf("Test 4: %s -> %s\n", test4, check_sequence(test4, patterns, pattern_count) ? "true" : "false");
    printf("Test 5: %s -> %s\n", test5, check_sequence(test5, patterns, pattern_count) ? "true" : "false");

    return 0;
}