#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_matching_chars(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t len = strnlen(str, max_len);

    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (islower((unsigned char)str[i])) {
                if (str[i] - 'a' == (int)i) {
                    count++;
                }
            } else if (isupper((unsigned char)str[i])) {
                if (str[i] - 'A' == (int)i) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main(void) {
    const char *input = "Aabdt";
    int result = count_matching_chars(input, 32);
    printf("%d\n", result);
    return 0;
}