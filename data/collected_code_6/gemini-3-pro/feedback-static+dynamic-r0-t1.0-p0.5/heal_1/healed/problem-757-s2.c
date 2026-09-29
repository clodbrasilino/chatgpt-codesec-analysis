#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

bool is_reverse(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    size_t len1 = safe_strlen(str1, MAX_STR_LEN);
    size_t len2 = safe_strlen(str2, MAX_STR_LEN);
    
    if (len1 != len2 || len1 == MAX_STR_LEN || len2 == MAX_STR_LEN) {
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