#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool ends_with_number(const char *str)
{
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strlen(str);
    if (len == 0) {
        return false;
    }

    return isdigit((unsigned char)str[len - 1]) != 0;
}

int main(void)
{
    const char *tests[] = {
        "hello123",
        "hello",
        "42",
        "",
        "abc9",
        "number one"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (ends_with_number(tests[i])) {
            if (printf("\"%s\" ends with a number\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\" does not end with a number\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}