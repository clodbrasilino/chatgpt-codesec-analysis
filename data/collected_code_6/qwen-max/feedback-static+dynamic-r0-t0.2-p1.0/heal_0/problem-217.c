#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char findFirstRepeatedChar(const char *str) {
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
    const char *testStr = "programming";
    char result = findFirstRepeatedChar(testStr);
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated characters found.\n");
    }
    return 0;
}