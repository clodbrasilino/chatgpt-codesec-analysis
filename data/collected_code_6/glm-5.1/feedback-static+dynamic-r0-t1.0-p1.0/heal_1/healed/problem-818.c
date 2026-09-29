#include <stdio.h>
#include <ctype.h>

size_t count_lower_case(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    for (; *str != '\0'; str++) {
        if (islower((unsigned char)*str)) {
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