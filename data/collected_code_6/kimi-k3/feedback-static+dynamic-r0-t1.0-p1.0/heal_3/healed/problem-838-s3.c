#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1001

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
    if (buffer_size == 0 || buffer == NULL || out_length == NULL) {
        return false;
    }
    
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strcspn(buffer, "\n");
    
    if (buffer[len] == '\0' && len == buffer_size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                break;
            }
        }
        return false;
    }
    
    buffer[len] = '\0';
    *out_length = len;
    return true;
}

bool validate_binary(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main(void) {
    char *s1 = NULL;
    char *s2 = NULL;
    size_t len1 = 0;
    size_t len2 = 0;
    int result = -1;
    
    s1 = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (s1 == NULL) {
        return EXIT_FAILURE;
    }
    
    s2 = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (s2 == NULL) {
        free(s1);
        return EXIT_FAILURE;
    }
    
    if (!read_line(s1, MAX_LINE_LENGTH, &len1)) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    if (!read_line(s2, MAX_LINE_LENGTH, &len2)) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    if (!validate_binary(s1, len1)) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    if (!validate_binary(s2, len2)) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    result = min_swaps_to_equal(s1, len1, s2, len2);
    
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    free(s1);
    free(s2);
    
    return EXIT_SUCCESS;
}