#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t count_lower_case(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    const char *text = "Hello World!";
    size_t result = count_lower_case(text);
    printf("%zu\n", result);
    return 0;
}