#include <stdio.h>
#include <string.h>

void remove_spaces(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        size_t len = strlen(input);
        if (len > 0 && len < sizeof(input)) {
            remove_spaces(input);
            printf("String after removing spaces: %s\n", input);
        } else {
            fprintf(stderr, "Input is too long or empty.\n");
        }
    } else {
        perror("Input error");
    }
    return 0;
}