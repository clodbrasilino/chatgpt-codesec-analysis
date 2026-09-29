#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL) {
        return -1;
    }

    char *endptr;
    long val;
    errno = 0;

    val = strtol(hex_str, &endptr, 16);

    if (errno == ERANGE || endptr == hex_str || *endptr != '\0') {
        return -1;
    }

    if ((val & 1) == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (buffer[strcspn(buffer, "\n")] != '\n') {
        return EXIT_FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    int result = is_hex_even(buffer);

    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}