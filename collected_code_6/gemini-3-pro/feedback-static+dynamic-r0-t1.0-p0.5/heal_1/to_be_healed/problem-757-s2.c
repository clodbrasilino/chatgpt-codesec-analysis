#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int count_reverse_pairs(const char **str_list, size_t list_size) {
    if (str_list == NULL || list_size == 0) {
        return 0;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < list_size; i++) {
        if (str_list[i] == NULL) {
            continue;
        }
        for (size_t j = i + 1; j < list_size; j++) {
            if (str_list[j] == NULL) {
                continue;
            }
            if (is_reverse(str_list[i], str_list[j])) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    const char *strings[] = {
        "hello",
        "world",
        "olleh",
        "dlrow",
        "test",
        "tset",
        "abc",
        "cba",
        NULL
    };
    
    size_t size = 8; 
    
    int pairs = count_reverse_pairs(strings, size);
    
    printf("Number of reverse pairs: %d\n", pairs);
    
    return 0;
}