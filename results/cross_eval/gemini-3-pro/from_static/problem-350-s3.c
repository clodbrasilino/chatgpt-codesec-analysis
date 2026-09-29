#include <stdio.h>
#include <stdlib.h>

void minimizeString(const char *str, size_t max_size, char *result) {
    if (str == NULL || result == NULL || max_size == 0) {
        if (result != NULL) {
            result[0] = '\0';
        }
        return;
    }

    size_t len = 0;
    while (len < max_size && str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        result[0] = '\0';
        return;
    }

    int maxCount = 0;
    char charToRemove = '\0';
    int counts[256] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > maxCount) {
            maxCount = counts[c];
            charToRemove = c;
        }
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != charToRemove) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
}

int main(void) {
    const char *original = "abracadabra";
    size_t max_size = 12; 

    size_t len = 0;
    while (len < max_size && original[len] != '\0') {
        len++;
    }
    
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return 1;
    }

    minimizeString(original, max_size, result);
    printf("%s\n", result);

    free(result);
    return 0;
}