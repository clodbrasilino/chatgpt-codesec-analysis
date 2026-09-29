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

    while (*ptr != '\0') {
        if (len >= MAX_INPUT_LENGTH) {
            errno = EINVAL;
            return NULL;
        }
        freq[(unsigned char)*ptr]++;
        ptr++;
        len++;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[MAX_INPUT_LENGTH + 2];

    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else if (len == sizeof(str) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }

    if (len > MAX_INPUT_LENGTH) {
        return 1;
    }

    char* minimized = minimize_length(str);
    if (minimized == NULL) {
        return 1;
    }

    printf("%s\n", minimized);
    free(minimized);

    return 0;
}