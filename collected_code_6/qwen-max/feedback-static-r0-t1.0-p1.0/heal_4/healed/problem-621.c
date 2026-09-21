#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increment_string_num(char *str, size_t len, int k) {
    for (size_t i = 0; i < len; i++) {
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

    str1[strcspn(str1, "\n")] = 0;
    size_t len = strlen(str1);

    if (len == 0 || len >= sizeof(str1) - 1) {
        fprintf(stderr, "Invalid input length\n");
        return EXIT_FAILURE;
    }

    printf("Enter an integer k: ");
    if (scanf("%d", &k) != 1) {
        return EXIT_FAILURE;
    }

    while ((getchar()) != '\n'); 

    increment_string_num(str1, len, k);

    printf("Updated string: %s\n", str1);
    return EXIT_SUCCESS;
}