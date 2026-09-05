#include <stdio.h>

int count_lower_case(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            count++;
        }
    }
    return count;
}

int main(void) {
    const char *text = "Hello World!";
    int result = count_lower_case(text);
    printf("%d\n", result);
    return 0;
}