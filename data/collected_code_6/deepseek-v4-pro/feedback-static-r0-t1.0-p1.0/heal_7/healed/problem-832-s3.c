#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

long long extract_max_numeric_value(const char *str) {
    const char *cursor = str;
    long long max_value = 0;
    int has_value = 0;
    
    while (*cursor != '\0') {
        while (*cursor != '\0' && *cursor != '-' && (*cursor < '0' || *cursor > '9')) {
            cursor++;
        }
        
        if (*cursor == '\0') {
            break;
        }
        
        int is_negative = 0;
        if (*cursor == '-') {
            const char *next = cursor + 1;
            if (*next >= '0' && *next <= '9') {
                is_negative = 1;
                cursor++;
            } else {
                cursor++;
                continue;
            }
        }
        
        const char *start = cursor;
        while (*cursor >= '0' && *cursor <= '9') {
            cursor++;
        }
        
        int length = (int)(cursor - start);
        if (length <= 0 || length >= 1024) {
            continue;
        }
        
        char *num_str = (char *)malloc(length + 2);
        if (num_str == NULL) {
            return has_value ? max_value : 0;
        }
        
        if (is_negative) {
            num_str[0] = '-';
            memcpy(num_str + 1, start, length);
            num_str[length + 1] = '\0';
        } else {
            memcpy(num_str, start, length);
            num_str[length] = '\0';
        }
        
        errno = 0;
        long long current = strtoll(num_str, NULL, 10);
        
        free(num_str);
        
        if (errno == ERANGE) {
            continue;
        }
        
        if (!has_value || current > max_value) {
            max_value = current;
            has_value = 1;
        }
    }
    
    return max_value;
}

int main(void) {
    const char *test_strings[] = {
        "abc123def456",
        "negative-42 and 100",
        "no numbers here",
        "-500 -100 -50",
        "mixed-10text20-30",
        "12345678901234567890",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        long long result = extract_max_numeric_value(test_strings[i]);
        printf("String: %s\n", test_strings[i]);
        printf("Max numeric value: %lld\n\n", result);
    }
    
    return 0;
}