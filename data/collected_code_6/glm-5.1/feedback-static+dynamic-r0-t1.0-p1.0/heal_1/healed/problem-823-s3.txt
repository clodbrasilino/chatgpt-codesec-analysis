#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    size_t sub_len = strnlen(sub, SIZE_MAX);
    if (sub_len == 0) {
        return 1;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    if (str_len < sub_len) {
        return 0;
    }

    return strncmp(str, sub, sub_len) == 0 ? 1 : 0;
}

int main(void) {
    const char *text = "Hello, world!";
    const char *sub = "Hello";
    const char *fail_sub = "World";
    const char *null_str = NULL;

    printf("%d\n", starts_with_substring(text, sub));
    printf("%d\n", starts_with_substring(text, fail_sub));
    printf("%d\n", starts_with_substring(text, null_str));
    printf("%d\n", starts_with_substring(null_str, sub));

    return 0;
}