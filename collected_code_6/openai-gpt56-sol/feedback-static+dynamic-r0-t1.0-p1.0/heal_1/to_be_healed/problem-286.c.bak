#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t max_contiguous_sum_repeated(const int64_t *array, size_t length, uint64_t repetitions)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t max_prefix = array[0];
    int64_t suffix = 0;
    int64_t max_suffix = array[length - 1];
    int64_t current = array[0];
    int64_t best = array[0];

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2042 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000014,time:52304,execs:16974,op:havoc,rep:1)
         * UBSan: signed integer overflow: -33 + -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000017,time:55544,execs:18038,op:havoc,rep:5)
         * UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:45444,execs:15263,op:havoc,rep:8)
         */
        total += array[i];
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2042 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000014,time:52304,execs:16974,op:havoc,rep:1)
         * UBSan: signed integer overflow: -33 + -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000017,time:55544,execs:18038,op:havoc,rep:5)
         * UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:45444,execs:15263,op:havoc,rep:8)
         */
        prefix += array[i];

        if (prefix > max_prefix) {
            max_prefix = prefix;
        }

        if (i > 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2046 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000014,time:52304,execs:16974,op:havoc,rep:1)
             * UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:45444,execs:15263,op:havoc,rep:8)
             */
            current = current > 0 ? current + array[i] : array[i];
            if (current > best) {
                best = current;
            }
        }

        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 43 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:45444,execs:15263,op:havoc,rep:8)
         * UBSan: signed integer overflow: 3 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000014,time:52304,execs:16974,op:havoc,rep:1)
         */
        suffix += array[length - 1 - i];
        if (suffix > max_suffix) {
            max_suffix = suffix;
        }
    }

    if (repetitions == 1) {
        return best;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 43 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:45444,execs:15263,op:havoc,rep:8)
     * UBSan: signed integer overflow: 333333333335 + 9223372036854775775 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000017,time:55544,execs:18038,op:havoc,rep:5)
     */
    int64_t combined = max_suffix + max_prefix;

    if (total > 0 && repetitions > 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 311 * 133333333333333331 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:22784,execs:11373,op:havoc,rep:10)
         */
        combined += total * (int64_t)(repetitions - 2);
    }

    return combined > best ? combined : best;
}

int main(void)
{
    size_t length;
    uint64_t repetitions;

    if (scanf("%zu %" SCNu64, &length, &repetitions) != 2 ||
        length == 0 ||
        repetitions == 0 ||
        repetitions > (uint64_t)INT64_MAX) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = max_contiguous_sum_repeated(array, length, repetitions);

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}