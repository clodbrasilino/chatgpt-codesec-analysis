#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH (1024 * 1024)

static size_t safe_strlen(const char* str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == max_len && str[len] != '\0') {
        return max_len + 1;
    }
    return len;
}

static void* safe_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    return malloc(size);
}

char* minimize_by_removing_one_char(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, MAX_STRING_LENGTH + 1);
    if (len > MAX_STRING_LENGTH) {
        return NULL;
    }

    if (len == 0) {
        char* empty = (char*)safe_malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    int max_freq = -1;
    char char_to_remove = '\0';
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            char_to_remove = (char)i;
        }
    }

    if (max_freq <= 0) {
        size_t copy_size = len + 1;
        char* copy = (char*)safe_malloc(copy_size);
        if (copy == NULL) {
            return NULL;
        }
        memcpy(copy, str, len);
        copy[len] = '\0';
        return copy;
    }

    size_t remaining = len - max_freq;
    size_t result_size = remaining + 1;
    char* result = (char*)safe_malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != char_to_remove) {
            if (j < remaining) {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* test_cases[] = {
        "aabbbcc",
        "abcd",
        "aaabbb",
        "abcabcabc",
        "",
        "aaaa"
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char* minimized = minimize_by_removing_one_char(test_cases[i]);
        if (minimized == NULL) {
            printf("Input: \"%s\", Result: (allocation failed or null input)\n",
                   test_cases[i] ? test_cases[i] : "NULL");
            continue;
        }
        size_t min_len = strlen(minimized);
        printf("Input: \"%s\", Minimized: \"%s\", Length: %zu\n",
               test_cases[i], minimized, min_len);
        free(minimized);
    }

    const char* null_input = NULL;
    char* null_result = minimize_by_removing_one_char(null_input);
    if (null_result == NULL) {
        printf("Input: NULL, Result: NULL (handled)\n");
    } else {
        printf("Input: NULL, Result: \"%s\"\n", null_result);
        free(null_result);
    }

    return 0;
}