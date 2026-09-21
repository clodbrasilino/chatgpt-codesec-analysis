#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_upper(char *str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;
        to_upper(input, strlen(input));
        printf("Upper case: %s\n", input);
    } else {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }
    return 0;
}