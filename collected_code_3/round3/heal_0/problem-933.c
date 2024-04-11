#include <stdio.h>
#include <ctype.h>
#include <string.h>

void camel_to_snake(char *input, char *output) {
    while (*input) {
        if (isupper(*input)) {
            *output++ = '_';
            *output++ = tolower(*input);
        } else {
            *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

int main() {
    char input[100];
    char output[200];

    printf("Enter a camel case string: ");
    scanf("%s", input);

    camel_to_snake(input, output);

    printf("Snake case string: %s\n", output);

    return 0;
}