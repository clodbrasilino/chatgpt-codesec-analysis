#include <stdio.h>

int count_lowercase_letters(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *test_string = "Hello World! This is a Test String 123.";
    int result = count_lowercase_letters(test_string);

    if (result != -1) {
        printf("Number of lowercase letters: %d\n", result);
    } else {
        printf("Error: Null pointer provided.\n");
    }

    return 0;
}