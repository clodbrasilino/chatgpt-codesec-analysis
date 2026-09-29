#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_std_occurrence(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int count = 0;
    const char *ptr = str;
    while ((ptr = strstr(ptr, "std")) != NULL) {
        count++;
        ptr++;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int count = find_std_occurrence(argv[1]);
    printf("%d\n", count);
    return EXIT_SUCCESS;
}