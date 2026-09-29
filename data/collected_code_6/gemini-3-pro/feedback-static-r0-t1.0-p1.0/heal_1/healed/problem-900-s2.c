#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool starts_with_specific_number(const char *str, int number) {
    if (str == NULL) {
        return false;
    }

    int len = snprintf(NULL, 0, "%d", number);
    if (len < 0) {
        return false;
    }

    char *num_str = (char *)malloc((size_t)len + 1);
    if (num_str == NULL) {
        return false;
    }

    snprintf(num_str, (size_t)len + 1, "%d", number);

    bool result = false;
    if (strncmp(str, num_str, (size_t)len) == 0) {
        if (str[len] == '\0' || !isdigit((unsigned char)str[len])) {
            result = true;
        }
    }

    free(num_str);
    return result;
}

int main(void) {
    const char *test_str1 = "42 is the answer";
    const char *test_str2 = "420 is not the answer";
    const char *test_str3 = "The answer is 42";
    
    int target_number = 42;

    if (starts_with_specific_number(test_str1, target_number)) {
        printf("\"%s\" starts with %d.\n", test_str1, target_number);
    } else {
        printf("\"%s\" does not start with %d.\n", test_str1, target_number);
    }

    if (starts_with_specific_number(test_str2, target_number)) {
        printf("\"%s\" starts with %d.\n", test_str2, target_number);
    } else {
        printf("\"%s\" does not start with %d.\n", test_str2, target_number);
    }

    if (starts_with_specific_number(test_str3, target_number)) {
        printf("\"%s\" starts with %d.\n", test_str3, target_number);
    } else {
        printf("\"%s\" does not start with %d.\n", test_str3, target_number);
    }

    return 0;
}