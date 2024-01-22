#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LENGTH 102

bool isStringValid(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
    return strnlen(str, len + 1) <= len;
}

void removeOddCharacters(char *str, size_t len) {
    if (!isStringValid(str, len)) {
        return;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH] = {0};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    size_t inputLength = strnlen(str, sizeof(str));

    if (inputLength >= MAX_LENGTH || str[inputLength - 1] != '\n') {
        fprintf(stderr, "Input too long, please limit your input to %d characters or less.\n", MAX_LENGTH - 2);
        return 1;
    }

    str[inputLength - 1] = '\0';
    removeOddCharacters(str, inputLength - 1);
    printf("Modified string: %s\n", str);

    return 0;
}