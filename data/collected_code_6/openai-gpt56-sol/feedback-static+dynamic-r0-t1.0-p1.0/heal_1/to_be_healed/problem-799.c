#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static uint32_t rotate_left_u32(uint32_t value, unsigned int count)
{
    const unsigned int width = 32U;
    count %= width;

    if (count == 0U) {
        return value;
    }

    return (value << count) | (value >> (width - count));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;
    uintmax_t count;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <value> <rotation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 0);
    if (errno != 0 || end == argv[1] || *end != '\0' || value > UINT32_MAX) {
        (void)fprintf(stderr, "Invalid 32-bit unsigned value\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    count = strtoumax(argv[2], &end, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (errno != 0 || end == argv[2] || *end != '\0' || count > UINT_MAX) {
        (void)fprintf(stderr, "Invalid rotation count\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n",
               rotate_left_u32((uint32_t)value, (unsigned int)count)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}