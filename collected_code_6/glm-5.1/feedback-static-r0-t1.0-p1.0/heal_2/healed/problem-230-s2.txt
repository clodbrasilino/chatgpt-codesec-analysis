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

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    } else {
        buffer[sizeof(buffer) - 1] = '\0';
    }

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}