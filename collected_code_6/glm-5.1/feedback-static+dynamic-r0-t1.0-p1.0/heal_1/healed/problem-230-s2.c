#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_spaces(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = ch;
        }
        i++;
    }
}

int main(void) {
    char buffer[256];
    char *read_result;

    read_result = fgets(buffer, sizeof(buffer), stdin);
    if (read_result == NULL) {
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}