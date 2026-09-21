#include <stdio.h>
#include <string.h>

int count_substrings(const char *str, size_t len) {
    int count = 0;
    size_t i, j;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '\0') {
            break;
        }
        for (j = i; j < len; j++) {
            if (str[j] == '\0') {
                break;
            }
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    const char *input = "abcab";
    size_t len = strnlen(input, 1024);
    int result = count_substrings(input, len);
    printf("%d\n", result);
    return 0;
}