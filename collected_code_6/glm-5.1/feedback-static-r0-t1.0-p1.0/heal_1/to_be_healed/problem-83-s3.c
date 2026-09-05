#include <stdio.h>
#include <stdlib.h>

char find_char(const char *str) {
    unsigned int sum = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str) {
        sum += (unsigned char)*str;
        str++;
    }
    return (char)(sum % 256);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char result = find_char(argv[1]);
    printf("%c\n", result);
    return EXIT_SUCCESS;
}