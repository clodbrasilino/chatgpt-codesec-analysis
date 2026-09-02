#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increment_string_num(char *str, int k) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            str[i] = (str[i] - '0' + k) % 10 + '0';
        }
    }
    return 0;
}

int main() {
    char str1[1024];
    int k;

    printf("Enter a string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    str1[strcspn(str1, "\n")] = 0; // Remove newline character

    printf("Enter an integer k: ");
    if (scanf("%d", &k) != 1) {
        return EXIT_FAILURE;
    }

    increment_string_num(str1, k);

    printf("Updated string: %s\n", str1);
    return EXIT_SUCCESS;
}