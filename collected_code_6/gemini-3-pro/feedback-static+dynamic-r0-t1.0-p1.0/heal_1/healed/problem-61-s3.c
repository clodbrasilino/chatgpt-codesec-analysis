#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *str);

int count_substrings(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        if (!isdigit((unsigned char)str[len])) {
            return -1;
        }
        len++;
    }

    int count = 0;
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
    const char *tests[] = {"1121", "123", NULL};
    
    for (int i = 0; i < 3; ++i) {
        int result = count_substrings(tests[i]);
        if (result >= 0) {
            printf("%d\n", result);
        } else {
            fprintf(stderr, "Error processing string.\n");
        }
    }

    return 0;
}