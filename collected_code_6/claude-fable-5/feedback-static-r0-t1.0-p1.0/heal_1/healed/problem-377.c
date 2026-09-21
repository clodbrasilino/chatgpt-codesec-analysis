#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char ch)
{
    size_t i;
    size_t j;

    if (str == NULL) {
        return;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ch) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char target;
    int input;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    } else {
        buffer[sizeof(buffer) - 1] = '\0';
    }

    if (strchr(buffer, '\n') == NULL && len == strlen(buffer)) {
        int discard;
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
    }

    printf("Enter the character to remove: ");
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error reading character input\n");
        return EXIT_FAILURE;
    }
    target = (char)input;

    remove_char(buffer, target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}