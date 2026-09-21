#include <stdio.h>
#include <stdlib.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int current_length = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\n' && s[i] != '\r') {
            current_length++;
            length = current_length;
        } else if (s[i] == ' ') {
            current_length = 0;
        }
    }

    return length;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    while (getline(&buffer, &bufsize, stdin) != -1) {
        printf("%d\n", lengthOfLastWord(buffer));
    }

    free(buffer);
    return 0;
}