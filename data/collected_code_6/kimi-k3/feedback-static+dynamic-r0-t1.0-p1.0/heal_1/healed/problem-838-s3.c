#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int min_swaps_to_equal(const char *s1, size_t len1, const char *s2, size_t len2) {
    if (len1 != len2) {
        return -1;
    }
    
    int count_10 = 0;
    int count_01 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1' && s2[i] == '0') {
                count_10++;
            } else if (s1[i] == '0' && s2[i] == '1') {
                count_01++;
            }
        }
    }
    
    if (count_10 != count_01) {
        return -1;
    }
    
    return count_10;
}

bool read_line(char *buffer, size_t buffer_size, size_t *out_length) {
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strcspn(buffer, "\n");
    
    if (buffer[len] == '\0' && len == buffer_size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return false;
    }
    
    buffer[len] = '\0';
    *out_length = len;
    return true;
}

bool validate_binary(const char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main(void) {
    char s1[1001];
    char s2[1001];
    size_t len1 = 0;
    size_t len2 = 0;
    
    if (!read_line(s1, sizeof(s1), &len1)) {
        return EXIT_FAILURE;
    }
    
    if (!read_line(s2, sizeof(s2), &len2)) {
        return EXIT_FAILURE;
    }
    
    if (!validate_binary(s1, len1)) {
        return EXIT_FAILURE;
    }
    
    if (!validate_binary(s2, len2)) {
        return EXIT_FAILURE;
    }
    
    int result = min_swaps_to_equal(s1, len1, s2, len2);
    
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    return EXIT_SUCCESS;
}