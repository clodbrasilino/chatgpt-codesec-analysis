#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t len = strnlen(str, size);
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
    size_t size = 0;
    if (getline(&buffer, &size, stdin) == -1) {
        free(buffer);
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    
    toggle_case(buffer, size);
    
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}