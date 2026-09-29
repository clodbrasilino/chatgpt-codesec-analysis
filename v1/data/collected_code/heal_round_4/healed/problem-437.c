#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LENGTH 101

bool isStringValid(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '\0') {
            return true;
        }
    }
    return false;
}

void removeOddCharacters(char *str, size_t len) {
    if (!isStringValid(str, len)) {
        return;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH] = {0};

    printf("Enter a string: ");
    fgets(str, MAX_LENGTH, stdin);

    size_t inputLength = strlen(str);
    if (inputLength+2 > MAX_LENGTH) {
        fprintf(stderr, "Input too long, please limit your input to %d characters.\n", MAX_LENGTH - 2);
        return 1;
    }

    if (inputLength > 0 && str[inputLength - 1] == '\n') {
        inputLength--;
        str[inputLength] = '\0';
    }

    removeOddCharacters(str, inputLength);

    printf("Modified string: %s\n", str);

    return 0;
}