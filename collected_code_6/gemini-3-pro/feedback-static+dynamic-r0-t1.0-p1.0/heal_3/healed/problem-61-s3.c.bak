#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            return -1;
        }
    }

    for (size_t i = 0; i < len; ++i) {
        int current_sum = 0;
        for (size_t j = i; j < len; ++j) {
            current_sum += (str[j] - '0');
            if (current_sum == (int)(j - i + 1)) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *test_strings[] = {"1121", "123", NULL};
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        int result = count_substrings(test_strings[i]);
        if (result >= 0) {
            printf("%d\n", result);
        } else {
            fprintf(stderr, "Error processing string.\n");
        }
    }

    return 0;
}