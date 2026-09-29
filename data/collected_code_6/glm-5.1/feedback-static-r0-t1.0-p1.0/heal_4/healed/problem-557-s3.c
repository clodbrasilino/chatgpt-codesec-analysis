#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void toggle_case(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
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
            read = (ssize_t)newline_pos;
        }
        
        size_t buffer_size = len;
        if ((size_t)read < buffer_size) {
            toggle_case(buffer, (size_t)read);
            printf("%s\n", buffer);
        }
    }
    free(buffer);
    return 0;
}