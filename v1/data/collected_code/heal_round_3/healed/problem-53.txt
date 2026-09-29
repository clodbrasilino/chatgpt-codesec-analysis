#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_first_last_equal(const char *str, size_t len) {
    if(str == NULL || len == 0) {
        return false;
    }

    if (len == 1) {
        return true;
    }

    return (str[0] == str[len - 1]);
}

int main() {
    const char str[] = "hello";
    size_t len = sizeof(str) - 1;
    bool result = is_first_last_equal(str, len);

    printf("%s\n", result ? "true" : "false");

    return 0;
}