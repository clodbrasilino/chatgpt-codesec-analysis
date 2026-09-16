#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  */

size_t string_length(const char *str) {
    const char *s = str;
    if (str == NULL) {
        return 0;
    }
    while (*s != '\0') {
        s++;
    }
    return (size_t)(s - str);
}

int main(void) {
    const char *test_strings[] = {
        "hello",
        "",
        "a",
        "This is a longer string to test.",
        "1234567890"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        size_t len = string_length(test_strings[i]);
        printf("Length of \"%s\" is %zu\n", test_strings[i], len);
    }

    size_t null_len = string_length(NULL);
    printf("Length of NULL is %zu\n", null_len);

    return EXIT_SUCCESS;
}