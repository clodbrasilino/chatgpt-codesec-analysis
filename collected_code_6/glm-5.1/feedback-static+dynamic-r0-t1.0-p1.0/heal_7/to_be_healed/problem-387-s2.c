#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int is_hex_even(const char hex_str[static 1]) {
    size_t len = strnlen(hex_str, SIZE_MAX);
    if (len == 0) {
        return -1;
    }

    size_t start = 0;
    /* Possible weaknesses found:
     *  Array 'hex_str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     */
    if (len >= 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2;
    }

    if (start >= len) {
        return -1;
    }

    size_t last_idx = len - 1;
    char last_char = tolower((unsigned char)hex_str[last_idx]);

    if ((last_char >= '0' && last_char <= '9') || (last_char >= 'a' && last_char <= 'f')) {
        int val = (last_char >= 'a') ? (last_char - 'a' + 10) : (last_char - '0');
        return (val % 2 == 0) ? 1 : 0;
    }

    return -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hex_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = is_hex_even(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Invalid hexadecimal input\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return EXIT_SUCCESS;
}