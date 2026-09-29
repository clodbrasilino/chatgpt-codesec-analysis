#include <stdio.h>
#include <ctype.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (islower((unsigned char)str[i])) {
            while (str[i] != '\0' && islower((unsigned char)str[i])) {
                i++;
            }
        } else {
            str[res_idx++] = str[i++];
        }
    }

    str[res_idx] = '\0';
}

int main(void) {
    char test_str1[] = "Hello world! THIS is A test.";
    char test_str2[] = "ALLCAPS";
    char test_str3[] = "alllower";
    char test_str4[] = "MixedCASE123";

    remove_lowercase_substrings(test_str1);
    printf("%s\n", test_str1);

    remove_lowercase_substrings(test_str2);
    printf("%s\n", test_str2);

    remove_lowercase_substrings(test_str3);
    printf("%s\n", test_str3);

    remove_lowercase_substrings(test_str4);
    printf("%s\n", test_str4);

    return 0;
}