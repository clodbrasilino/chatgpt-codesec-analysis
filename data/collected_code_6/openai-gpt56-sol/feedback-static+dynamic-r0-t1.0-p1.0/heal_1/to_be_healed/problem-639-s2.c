#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static int starts_with_lowercase(const char *name)
{
    if (name == NULL || name[0] == '\0') {
        return 0;
    }

    return islower((unsigned char)name[0]) != 0;
}

static size_t sum_filtered_name_lengths(const char *const names[], size_t count)
{
    size_t total = 0;

    if (names == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (names[i] == NULL || starts_with_lowercase(names[i])) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(names[i]);
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
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
    const char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "diana",
        "Eve"
    };
    size_t total = sum_filtered_name_lengths(
        names,
        sizeof(names) / sizeof(names[0])
    );

    /* Possible weaknesses found:
     *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
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