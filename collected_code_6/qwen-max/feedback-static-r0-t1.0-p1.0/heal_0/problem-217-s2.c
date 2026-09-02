#include <stdio.h>
#include <stdbool.h>

char find_first_repeated_char(const char *str) {
    bool visited[256] = {false};
    for (int i = 0; str[i] != '\0'; ++i) {
        if (visited[(unsigned char)str[i]]) {
            return str[i];
        }
        visited[(unsigned char)str[i]] = true;
    }
    return '\0';
}

int main() {
    const char *input = "programming";
    char result = find_first_repeated_char(input);
    if (result == '\0') {
        printf("No repeated characters found.\n");
    } else {
        printf("First repeated character: %c\n", result);
    }
    return 0;
}