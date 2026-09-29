#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* minimize_length(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    if (*str == '\0') {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    int freq[256] = {0};
    const char* p = str;
    int len = 0;

    while (*p != '\0' && len < 1000) {
        freq[(unsigned char)*p]++;
        p++;
        len++;
    }

    if (*p != '\0') {
        return NULL;
    }

    int max_freq = -1;
    char max_char = '\0';

    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (char)i;
        }
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != max_char) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    char* buffer = NULL;
    size_t bufsize = 0;

    ssize_t nread = getline(&buffer, &bufsize, stdin);
    if (nread == -1) {
        free(buffer);
        return 1;
    }

    if (nread > 0 && buffer[nread - 1] == '\n') {
        buffer[nread - 1] = '\0';
    }

    char* minimized = minimize_length(buffer);
    free(buffer);

    if (minimized == NULL) {
        return 1;
    }

    printf("%s\n", minimized);
    free(minimized);

    return 0;
}