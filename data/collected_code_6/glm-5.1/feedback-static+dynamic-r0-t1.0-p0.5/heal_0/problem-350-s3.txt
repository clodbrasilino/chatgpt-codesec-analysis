#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    int max_freq = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }

    return (int)len - max_freq;
}

char* minimize_string(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        char *empty = malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    int max_freq = 0;
    char target = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            target = (char)i;
        }
    }

    char *result = malloc(len - max_freq + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abracadabra";
    
    int min_len = calculate_min_length(input);
    char *minimized = minimize_string(input);

    if (minimized) {
        printf("Original: %s\n", input);
        printf("Minimized: %s\n", minimized);
        printf("Min Length: %d\n", min_len);
        free(minimized);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}