#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static size_t safe_strlen(const char *s, size_t maxlen)
{
    size_t i;

    if (s == NULL) {
        return 0;
    }

    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }

    return maxlen;
}

char *minimizeString(const char *str, size_t max_len)
{
    size_t len;
    size_t freq[256] = {0};
    size_t max_freq = 0;
    unsigned char max_char = 0;
    size_t new_len;
    char *result;
    size_t j = 0;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = safe_strlen(str, max_len);
    if (len == max_len && str[len - 1] != '\0') {
        return NULL;
    }

    if (len == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (unsigned char)i;
        }
    }

    if (max_freq > len) {
        return NULL;
    }

    new_len = len - max_freq;
    if (new_len == SIZE_MAX) {
        return NULL;
    }

    result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)str[i] != max_char) {
            if (j >= new_len) {
                free(result);
                return NULL;
            }
            result[j++] = str[i];
        }
    }

    if (j != new_len) {
        free(result);
        return NULL;
    }

    result[j] = '\0';
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t input_len = safe_strlen(input, sizeof(input));

        if (input_len == sizeof(input) && input[input_len - 1] != '\0') {
            return 1;
        }

        if (input_len > 0 && input[input_len - 1] == '\n') {
            input[input_len - 1] = '\0';
        }

        char *result = minimizeString(input, sizeof(input));
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    return 0;
}