#include <stdio.h>
#include <string.h>

int isMatched(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == 'a') {
            break;
        }
        i++;
    }

    if (str[i] == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        if (str[i] == 'b' && str[i + 1] == '\0') {
            return 1;
        }
        i++;
    }

    return 0;
}

int main() {
    const char *str = "Hello, world!ab";
    if (isMatched(str)) {
        printf("The string matches the pattern.\n");
    } else {
        printf("The string does not match the pattern.\n");
    }
    return 0;
}