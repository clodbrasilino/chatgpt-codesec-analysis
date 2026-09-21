#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool starts_with_specific_number(const char *str, int number) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[32];
    int snprintf_result = snprintf(num_str, sizeof(num_str), "%d", number);

    if (snprintf_result < 0 || (size_t)snprintf_result >= sizeof(num_str)) {
        return false;
    }

    size_t i = 0;
    while (num_str[i] != '\0') {
        if (str[i] == '\0' || str[i] != num_str[i]) {
            return false;
        }
        i++;
    }

    if (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        return false;
    }

    return true;
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