#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }

    int len = snprintf(NULL, 0, "%d", num);
    if (len < 0) {
        return 0;
    }

    char *num_str = (char *)malloc((size_t)len + 1);
    if (num_str == NULL) {
        return 0;
    }

    snprintf(num_str, (size_t)len + 1, "%d", num);

    int result = (strncmp(str, num_str, (size_t)len) == 0);

    free(num_str);

    return result;
}

int main(void) {
    const char *test_str1 = "42 is the answer";
    const char *test_str2 = "420 is not 42";
    const char *test_str3 = "Hello 42";
    const char *test_str4 = NULL;

    int num1 = 42;
    int num2 = 42;
    int num3 = 123;
    int num4 = 42;

    printf("Result 1: %d\n", starts_with_number(test_str1, num1));
    printf("Result 2: %d\n", starts_with_number(test_str2, num2));
    printf("Result 3: %d\n", starts_with_number(test_str3, num3));
    printf("Result 4: %d\n", starts_with_number(test_str4, num4));

    return 0;
}