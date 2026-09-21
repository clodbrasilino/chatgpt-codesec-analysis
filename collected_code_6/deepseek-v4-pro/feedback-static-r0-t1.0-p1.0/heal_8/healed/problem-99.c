#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define BINARY_BUFFER_SIZE (sizeof(unsigned int) * CHAR_BIT + 1)
#define INPUT_BUFFER_SIZE 64

void decimalToBinary(unsigned int n) {
    char binary[BINARY_BUFFER_SIZE];
    int index = 0;

    if (n == 0) {
        printf("0");
        return;
    }

    while (n > 0 && index < BINARY_BUFFER_SIZE - 1) {
        binary[index] = (n % 2) + '0';
        n = n / 2;
        index++;
    }
    binary[index] = '\0';

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", binary[i]);
    }
}

int main(void) {
    char buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    long long input;

    printf("Enter a decimal number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    input = strtoll(buffer, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return 1;
    }

    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (input < 0 || input > UINT_MAX) {
        fprintf(stderr, "Please enter a non-negative integer within valid range\n");
        return 1;
    }

    printf("Binary equivalent: ");
    decimalToBinary((unsigned int)input);
    printf("\n");

    return 0;
}