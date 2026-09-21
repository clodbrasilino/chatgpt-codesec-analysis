#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void toggle_case(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters = getline(&buffer, &bufsize, stdin);
    if (characters == -1) {
        free(buffer);
        return 1;
    }
    size_t len = strnlen(buffer, (size_t)characters);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    toggle_case(buffer, len);
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}