#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *str)
{
    size_t freq[256] = {0};
    size_t i;
    size_t len;
    size_t max_freq = 0;
    unsigned char max_char = 0;
    char *result;
    size_t j = 0;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);

    if (len == 0) {
        result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    for (i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    for (i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (unsigned char)i;
        }
    }

    result = (char *)malloc(len - max_freq + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if ((unsigned char)str[i] != max_char) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "aabbbcc",
        "hello world",
        "mississippi",
        "",
        "xyz",
        "aaaa"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *minimized = minimize_string(test_strings[i]);
        if (minimized == NULL) {
            fprintf(stderr, "Error: failed to minimize string\n");
            return EXIT_FAILURE;
        }
        printf("Original : \"%s\" (length %zu)\n", test_strings[i], strlen(test_strings[i]));
        printf("Minimized: \"%s\" (length %zu)\n\n", minimized, strlen(minimized));
        free(minimized);
    }

    return EXIT_SUCCESS;
}