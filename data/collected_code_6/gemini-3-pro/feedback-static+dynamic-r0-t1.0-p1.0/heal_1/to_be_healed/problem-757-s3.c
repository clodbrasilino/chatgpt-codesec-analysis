#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_reverse(const char *str1, const char *str2) {
    if (!str1 || !str2) return false;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    if (len1 != len2) return false;
    
    for (size_t i = 0; i < len1; ++i) {
        if (str1[i] != str2[len1 - 1 - i]) {
            return false;
        }
    }
    
    return true;
}

int count_reverse_pairs(const char **string_list, size_t count) {
    if (!string_list || count == 0) return 0;
    
    int pairs_count = 0;
    
    for (size_t i = 0; i < count; ++i) {
        if (!string_list[i]) continue;
        for (size_t j = i + 1; j < count; ++j) {
            if (!string_list[j]) continue;
            if (is_reverse(string_list[i], string_list[j])) {
                pairs_count++;
            }
        }
    }
    
    return pairs_count;
}

int main(void) {
    const char *strings[] = {
        "hello",
        "world",
        "olleh",
        "dlrow",
        "test",
        "tset",
        "nothing"
    };
    
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    int pairs = count_reverse_pairs(strings, count);
    
    printf("%d\n", pairs);
    
    return 0;
}