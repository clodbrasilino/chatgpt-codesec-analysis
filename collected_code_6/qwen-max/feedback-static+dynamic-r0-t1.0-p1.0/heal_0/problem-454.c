#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool contains_z(const char *str) {
    if (str == NULL) {
        return false;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'z') {
            return true;
        }
    }
    return false;
}

int main() {
    const char *words[] = {"zebra", "elephant", "lazy", "jazz", "python"};
    for (int i = 0; i < 5; i++) {
        if (contains_z(words[i])) {
            printf("%s\n", words[i]);
        }
    }
    return 0;
}