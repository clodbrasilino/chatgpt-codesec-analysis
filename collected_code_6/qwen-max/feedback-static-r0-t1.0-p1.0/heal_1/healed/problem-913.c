#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_number_at_end(const char *str, size_t len) {
    if (str == NULL || len == 0) return 0;
    const char *ptr = str + len - 1;
    while (ptr >= str && isdigit(*ptr)) {
        ptr--;
    }
    return ptr < str || !isdigit(*(ptr + 1));
}

int main() {
    const char *test_strings[] = {
        "hello123",
        "123hello456",
        "noNumberHere",
        "",
        "endswith100"
    };

    for (int i = 0; i < 5; i++) {
        size_t len = strlen(test_strings[i]);
        printf("'%s' ends with a number: %s\n", test_strings[i], is_number_at_end(test_strings[i], len) ? "true" : "false");
    }

    return 0;
}