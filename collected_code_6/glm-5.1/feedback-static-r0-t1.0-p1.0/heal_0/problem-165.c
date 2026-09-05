#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_matching_chars(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t len = strlen(str);

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
    int result = count_matching_chars(input);
    printf("%d\n", result);
    return 0;
}