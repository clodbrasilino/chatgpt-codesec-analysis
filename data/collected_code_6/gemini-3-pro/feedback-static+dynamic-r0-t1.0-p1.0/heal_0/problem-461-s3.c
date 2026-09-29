#include <stdio.h>
#include <ctype.h>

size_t count_uppercase(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            count++;
        }
    }
    return count;
}

int main(void) {
    const char *test_str1 = "Hello World!";
    const char *test_str2 = "no uppercase here.";
    const char *test_str3 = "ALL UPPERCASE";
    const char *test_str4 = NULL;

    printf("Count 1: %zu\n", count_uppercase(test_str1));
    printf("Count 2: %zu\n", count_uppercase(test_str2));
    printf("Count 3: %zu\n", count_uppercase(test_str3));
    printf("Count 4: %zu\n", count_uppercase(test_str4));

    return 0;
}