#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char find_first_repeated(const char *str) {
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
    const char *test_str = "programming";
    char result = find_first_repeated(test_str);
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated characters found.\n");
    }
    return 0;
}