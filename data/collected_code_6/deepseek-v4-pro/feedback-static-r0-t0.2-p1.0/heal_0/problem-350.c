#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minimize_string_length(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    int len = strlen(str);
    if (len == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    int freq[256] = {0};
    for (int i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    char char_to_remove = str[0];
    int max_freq = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            char_to_remove = (char)i;
        }
    }

    int new_len = len - max_freq;
    char* result = (char*)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != char_to_remove) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* test_str = "aabbbcccc";
    char* minimized = minimize_string_length(test_str);
    
    if (minimized != NULL) {
        printf("Original: %s\n", test_str);
        printf("Minimized: %s\n", minimized);
        free(minimized);
    }

    return 0;
}