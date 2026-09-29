#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 100

char* minimize_length(const char* str) {
    if (str == NULL) {
        errno = EINVAL;
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
    const char* ptr = str;
    int len = 0;

    while (*ptr != '\0' && len < MAX_INPUT_LENGTH) {
        freq[(unsigned char)*ptr]++;
        ptr++;
        len++;
    }

    if (*ptr != '\0') {
        errno = EINVAL;
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

    char* result = (char*)malloc((size_t)len + 1);
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
    char* input = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;

    line_length = getline(&input, &buffer_size, stdin);
    if (line_length == -1) {
        free(input);
        return 1;
    }

    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
        line_length--;
    }

    if ((size_t)line_length > MAX_INPUT_LENGTH) {
        free(input);
        return 1;
    }

    char* minimized = minimize_length(input);
    if (minimized == NULL) {
        free(input);
        return 1;
    }

    printf("%s\n", minimized);
    free(minimized);
    free(input);

    return 0;
}