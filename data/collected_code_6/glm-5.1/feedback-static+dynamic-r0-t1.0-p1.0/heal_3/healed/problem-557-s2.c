#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void toggle_case(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, stdin) == -1) {
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    toggle_case(buffer, len);
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}