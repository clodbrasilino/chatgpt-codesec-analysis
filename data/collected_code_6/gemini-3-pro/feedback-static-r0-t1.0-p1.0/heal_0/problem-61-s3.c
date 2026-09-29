#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *str);

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
    const char *test_str1 = "1121";
    int result1 = count_substrings(test_str1);
    if (result1 >= 0) {
        printf("%d\n", result1);
    } else {
        fprintf(stderr, "Error processing string.\n");
    }

    const char *test_str2 = "123";
    int result2 = count_substrings(test_str2);
    if (result2 >= 0) {
        printf("%d\n", result2);
    } else {
        fprintf(stderr, "Error processing string.\n");
    }
    
    const char *test_str3 = NULL;
    int result3 = count_substrings(test_str3);
    if (result3 >= 0) {
        printf("%d\n", result3);
    } else {
        fprintf(stderr, "Error processing string.\n");
    }

    return 0;
}