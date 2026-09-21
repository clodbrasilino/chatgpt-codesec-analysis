#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int count_numeric_values(const char *str) {
    int count = 0;
    int in_number = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        str++;
    }

    return count;
}

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t len;

    printf("Enter a string: ");
    
    len = getline(&input, &size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    int result = count_numeric_values(input);
    printf("Number of numeric values: %d\n", result);

    free(input);
    return 0;
}