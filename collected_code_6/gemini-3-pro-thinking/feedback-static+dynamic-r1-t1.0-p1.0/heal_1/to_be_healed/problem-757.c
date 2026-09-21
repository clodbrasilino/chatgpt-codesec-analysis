#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool is_reverse(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    if (len1 != len2) {
        return false;
    }
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[len1 - 1 - i]) {
            return false;
        }
    }
    return true;
}

size_t count_reverse_pairs(const char *const *strings, size_t count) {
    if (strings == NULL || count == 0) {
        return 0;
    }
    size_t pair_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (size_t j = i + 1; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse(strings[i], strings[j])) {
                pair_count++;
            }
        }
    }
    return pair_count;
}

int main(void) {
    const char *const string_list[] = {
        "hello",
        "world",
        "olleh",
        "abc",
        "cba",
        "dlrow",
        "test"
    };
    size_t list_size = sizeof(string_list) / sizeof(string_list[0]);
    size_t result = count_reverse_pairs(string_list, list_size);
    if (printf("%zu\n", result) < 0) {
        return 1;
    }
    return 0;
}