#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void toggle_case(char *str) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read = getline(&buffer, &len, stdin);
    if (read == -1) {
        if (buffer) {
            free(buffer);
        }
        return 1;
    }
    if (read > 0) {
        size_t newline_pos = strcspn(buffer, "\n");
        if (newline_pos < (size_t)read) {
            buffer[newline_pos] = '\0';
        }
        
        toggle_case(buffer);
        
        printf("%s\n", buffer);
    }
    free(buffer);
    return 0;
}