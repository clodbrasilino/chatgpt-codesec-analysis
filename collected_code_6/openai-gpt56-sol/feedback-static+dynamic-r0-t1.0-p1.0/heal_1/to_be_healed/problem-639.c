#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

size_t sum_filtered_name_lengths(const char *const names[], size_t count)
{
    size_t total = 0U;

    if (names == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (names[i] == NULL) {
            continue;
        }

        const unsigned char first = (unsigned char)names[i][0];

        if (first == '\0' || islower(first) != 0) {
            continue;
        }

        const size_t length = strlen(names[i]);

        /* Possible weaknesses found:
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (SIZE_MAX - total < length) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'SIZE_MAX'
             */
            return SIZE_MAX;
        }

        total += length;
    }

    return total;
}

int main(void)
{
    const char *const names[] = {
        "Alice",
        "bob",
        "Charlie",
        "diana",
        "Eve"
    };
    const size_t count = sizeof(names) / sizeof(names[0]);
    const size_t total = sum_filtered_name_lengths(names, count);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
     */
    if (total == SIZE_MAX) {
        fputs("Length sum overflowed.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}