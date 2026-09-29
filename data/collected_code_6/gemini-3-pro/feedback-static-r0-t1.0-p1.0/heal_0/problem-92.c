#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    char str[15];
    if (snprintf(str, sizeof(str), "%d", num) < 0) {
        return false;
    }

    size_t len = strlen(str);
    
    if (str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2; i < len; ++i) {
        if (str[i - 2] != str[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int input;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }

    if (isUndulating(input)) {
        printf("The number is undulating.\n");
    } else {
        printf("The number is not undulating.\n");
    }

    return EXIT_SUCCESS;
}