#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str) {
    size_t len = strlen(str);
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

char* minimize_string(const char *str) {
    size_t len = strlen(str);
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
        if (str[i] != target_char) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abracadabra";
    
    int min_len = calculate_min_length(input);
    printf("%d\n", min_len);

    char *output = minimize_string(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}