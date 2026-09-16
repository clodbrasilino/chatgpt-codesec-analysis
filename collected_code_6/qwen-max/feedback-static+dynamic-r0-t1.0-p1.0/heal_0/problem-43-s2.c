#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>

bool check_sequence(const char *str) {
    regex_t re;
    int ret;
    ret = regcomp(&re, "^[a-z]+(_[a-z]+)*$", 0);
    if (ret) {
        return false;
    }

    ret = regexec(&re, str, 0, NULL, 0);
    regfree(&re);
    return !ret;
}

int main() {
    const char *test_str[] = {
        "hello",
        "hello_world",
        "hello_world_test",
        "Hello_World",
        "hello_world123",
        ""
    };

    for (size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); ++i) {
        printf("%s: %s\n", test_str[i], check_sequence(test_str[i]) ? "Match" : "No Match");
    }

    return 0;
}