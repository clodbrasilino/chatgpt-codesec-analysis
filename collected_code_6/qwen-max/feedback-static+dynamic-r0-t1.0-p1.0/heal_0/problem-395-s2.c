#include <stdio.h>
#include <string.h>

char find_first_non_repeated(const char *str) {
    int count[256] = {0};
    for (int i = 0; str[i]; i++) {
        count[str[i]]++;
    }
    for (int i = 0; str[i]; i++) {
        if (count[str[i]] == 1) {
            return str[i];
        }
    }
    return '\0';
}

int main() {
    const char *str = "programming";
    char result = find_first_non_repeated(str);
    if (result != '\0') {
        printf("The first non-repeated character is: %c\n", result);
    } else {
        printf("There is no non-repeated character in the string.\n");
    }
    return 0;
}