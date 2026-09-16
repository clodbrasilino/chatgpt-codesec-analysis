#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'PRIu32' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    return value | (value + UINT32_C(1));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint32_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-32-bit-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 0);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid 32-bit unsigned integer\n");
        return EXIT_FAILURE;
    }

    result = set_rightmost_unset_bit((uint32_t)input);
    /* Possible weaknesses found:
     *  expected ')'
     *  expected ')' before 'PRIu32'
     *  to match this '('
     */
    printf("%" PRIu32 "\n", result);

    return EXIT_SUCCESS;
}