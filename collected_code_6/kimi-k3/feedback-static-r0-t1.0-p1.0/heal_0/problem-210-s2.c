#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_string(const char *str) {
    regex_t regex;
    int ret;
    bool result = false;

    if (str == NULL) {
        return false;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (ret != 0) {
        return false;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = true;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld123",
        "Hello_World",
        "abc123",
        "Hello World",
        "",
        NULL
    };
    int i;

    for (i = 0; test_strings[i] != NULL; i++) {
        if (is_valid_string(test_strings[i])) {
            printf("\"%s\": Valid\n", test_strings[i]);
        } else {
            printf("\"%s\": Invalid\n", test_strings[i]);
        }
    }

    return 0;
}