#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t string_length(const char *str) {
    size_t length = 0;
    if (str == NULL) {
        return 0;
    }
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t nread;

    printf("Enter a string: ");
    nread = getline(&str, &size, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }

    if (nread > 0 && str[nread - 1] == '\n') {
        str[nread - 1] = '\0';
    }

    printf("Length of the string: %zu\n", string_length(str));

    free(str);
    return 0;
}