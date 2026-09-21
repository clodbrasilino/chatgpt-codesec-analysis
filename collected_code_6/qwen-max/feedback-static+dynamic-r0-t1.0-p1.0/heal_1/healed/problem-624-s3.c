#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin)) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        to_upper(input);
        printf("Upper case: %s\n", input);
    } else {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }
    return 0;
}