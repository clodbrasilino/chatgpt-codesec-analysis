#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    uint64_t right = number;
    uint64_t root = 0;

    while (left <= right) {
        uint64_t middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            root = middle;
            left = middle + 1;
        }
    }

    left = 0;
    right = root;

    while (left <= right) {
        uint64_t left_square = left * left;
        uint64_t right_square = right * right;
        uint64_t remainder = number - right_square;

        if (left_square == remainder) {
            return true;
        }

        if (left_square < remainder) {
            ++left;
        } else {
            if (right == 0) {
                break;
            }
            --right;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares((uint64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}