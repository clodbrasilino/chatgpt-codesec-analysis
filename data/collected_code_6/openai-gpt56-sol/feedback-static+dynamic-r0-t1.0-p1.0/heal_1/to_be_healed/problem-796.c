#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    long long value;
} DictionaryEntry;

static int sum_dictionary(const DictionaryEntry *dictionary,
                          size_t count,
                          long long *sum)
{
    size_t i;
    long long total = 0;

    if (sum == NULL || (dictionary == NULL && count != 0)) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'LLONG_MAX'
         *  'LLONG_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if ((dictionary[i].value > 0 && total > LLONG_MAX - dictionary[i].value) ||
            /* Possible weaknesses found:
             *  'LLONG_MIN' undeclared (first use in this function)
             *  use of undeclared identifier 'LLONG_MIN'
             *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             */
            (dictionary[i].value < 0 && total < LLONG_MIN - dictionary[i].value)) {
            return 0;
        }
        total += dictionary[i].value;
    }

    *sum = total;
    return 1;
}

int main(void)
{
    const DictionaryEntry dictionary[] = {
        {"apple", 10},
        {"banana", 20},
        {"orange", 30}
    };
    long long sum;

    if (!sum_dictionary(dictionary,
                        sizeof(dictionary) / sizeof(dictionary[0]),
                        &sum)) {
        fputs("Unable to calculate sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}