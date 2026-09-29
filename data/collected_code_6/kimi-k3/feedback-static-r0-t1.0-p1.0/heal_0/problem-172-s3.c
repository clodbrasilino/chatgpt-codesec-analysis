#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    size_t len = strlen(str);

    if (len < 3) {
        return 0;
    }

    for (size_t i = 0; i <= len - 3; i++) {
        if (str[i] == 's' && str[i + 1] == 't' && str[i + 2] == 'd') {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *input = "std string with std occurrences std";
    int result = count_std_occurrences(input);

    if (result >= 0) {
        printf("Occurrences of 'std': %d\n", result);
    } else {
        printf("Invalid input string\n");
    }

    return 0;
}