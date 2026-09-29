#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHAR_RANGE 256
#define INPUT_SIZE 1024

char find_first_non_repeated(const char *str, size_t max_len) {
    int count[CHAR_RANGE] = {0};
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return '\0';
    }

    len = strnlen(str, max_len);

    if (len == 0) {
        return '\0';
    }

    for (i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

int main(void) {
    char input[INPUT_SIZE];
    char result;
    size_t len;

    printf("Enter a string: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strnlen(input, sizeof(input));
    if (len >= sizeof(input)) {
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    result = find_first_non_repeated(input, sizeof(input));

    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }

    return 0;
}