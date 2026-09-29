#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }

    int count[256] = {0};
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
    }

    int min_count = len;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && count[i] < min_count) {
            min_count = count[i];
        }
    }

    return len - min_count;
}

char* minimize_string(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        char *empty = malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    int count[256] = {0};
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
    }

    int min_count = len;
    int target_char = -1;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && count[i] < min_count) {
            min_count = count[i];
            target_char = i;
        }
    }

    char *result = malloc(len - min_count + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)str[i] != target_char) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    size_t max_len = strnlen(input, 4096);
    if (max_len == 4096) {
        fprintf(stderr, "Invalid input string\n");
        return 1;
    }
    
    char *minimized = minimize_string(input, max_len + 1);
    if (!minimized) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Minimized: %s\n", minimized);
    printf("Min Length: %d\n", calculate_min_length(input, max_len + 1));

    free(minimized);
    return 0;
}