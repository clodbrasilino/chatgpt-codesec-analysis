#include <stdio.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

int has_number_at_end(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < MAX_STR_LEN && str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return 0;
    }

    return isdigit((unsigned char)str[len - 1]) ? 1 : 0;
}

int main(void) {
    const char *test_strings[] = {
        "helloWorld123",
        "helloWorld",
        "test1",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            printf("String: '%s', Has number at end: %d\n", test_strings[i], has_number_at_end(test_strings[i]));
        } else {
            printf("String: NULL, Has number at end: %d\n", has_number_at_end(test_strings[i]));
        }
    }

    return 0;
}