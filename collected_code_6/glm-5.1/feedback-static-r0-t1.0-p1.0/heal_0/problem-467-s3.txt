#include <stdio.h>
#include <stdlib.h>

char *decimal_to_octal(int num) {
    if (num == 0) {
        char *str = malloc(2);
        if (str == NULL) {
            return NULL;
        }
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int is_negative = 0;
    unsigned int n;
    if (num < 0) {
        is_negative = 1;
        n = (unsigned int)(-(num + 1)) + 1;
    } else {
        n = (unsigned int)num;
    }

    char buffer[12];
    int i = 0;

    while (n > 0) {
        buffer[i++] = (n % 8) + '0';
        n /= 8;
    }

    int len = i + is_negative;
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    int j = 0;
    if (is_negative) {
        result[j++] = '-';
    }

    while (i > 0) {
        result[j++] = buffer[--i];
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    int input;
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }

    char *octal_str = decimal_to_octal(input);
    if (octal_str == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", octal_str);
    free(octal_str);
    octal_str = NULL;

    return EXIT_SUCCESS;
}