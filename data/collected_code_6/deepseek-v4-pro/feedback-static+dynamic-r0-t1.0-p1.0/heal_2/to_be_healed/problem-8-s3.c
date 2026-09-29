#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void square_elements(int64_t *list, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6666666666606 * 6666666666606 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000009,time:21231,execs:13504,op:havoc,rep:6)
         * UBSan: signed integer overflow: 22222222222222222 * 22222222222222222 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:27221,execs:17167,op:havoc,rep:2)
         * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000010,time:25171,execs:15873,op:havoc,rep:1)
         */
        list[i] = list[i] * list[i];
    }
}

int main(void) {
    int size;
    int64_t *list;

    printf("Enter number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    list = malloc((size_t)size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    square_elements(list, size);

    printf("Squared elements:\n");
    for (int i = 0; i < size; i++) {
        printf("%" PRId64 " ", list[i]);
    }
    printf("\n");

    free(list);
    return EXIT_SUCCESS;
}