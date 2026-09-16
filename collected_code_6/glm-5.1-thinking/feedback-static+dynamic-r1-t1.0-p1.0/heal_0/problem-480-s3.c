#include <stdio.h>

char find_max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int count[256] = {0};
    int max = 0;
    char max_char = '\0';

    for (size_t i = 0; str[i] != '\0'; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > max) {
            max = count[i];
            max_char = (char)i;
        }
    }

    return max_char;
}

int main(void) {
    const char *str = "experienced developer";
    char result = find_max_occurring_char(str);

    if (result != '\0') {
        printf("Maximum occurring character: %c\n", result);
    } else {
        printf("String is empty or NULL\n");
    }

    return 0;
}