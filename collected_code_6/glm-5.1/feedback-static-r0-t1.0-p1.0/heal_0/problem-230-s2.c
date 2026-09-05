#include <stdio.h>
#include <stdlib.h>

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
    int read_result;

    read_result = scanf("%255s", buffer);
    if (read_result != 1) {
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}