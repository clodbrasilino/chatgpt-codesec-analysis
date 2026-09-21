#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_number_at_end(const char *str, size_t len) {
    if (str == NULL || len == 0) return 0;
    const char *ptr = str + len - 1;
    while (ptr >= str && isdigit((unsigned char)*ptr)) {
        ptr--;
    }
    return ptr < str || !isdigit((unsigned char)*(ptr + 1));
}

int main() {
    const char *test_strings[] = {
        "hello123",
        "123hello456",
        "noNumberHere",
        "",
        "endswith100"
    };
    /* Possible weaknesses found:
     *  Variable 'test_lens' can be declared as const array [constVariable]
     */
    size_t test_lens[] = {
        11,
        14,
        11,
        0,
        11
    };

    for (int i = 0; i < 5; i++) {
        printf("'%s' ends with a number: %s\n", test_strings[i], is_number_at_end(test_strings[i], test_lens[i]) ? "true" : "false");
    }

    return 0;
}