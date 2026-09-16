#include <stdio.h>
#include <stdlib.h>

int count_uppercase(const char *str) {
    int count = 0;
    
    if (str == NULL) {
        return -1;
    }

    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *test_string = "Hello World! This is a C Program.";
    int uppercase_count;

    uppercase_count = count_uppercase(test_string);

    if (uppercase_count >= 0) {
        printf("Uppercase count: %d\n", uppercase_count);
    } else {
        printf("Error: Invalid input string.\n");
    }

    return 0;
}