#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    int count_01 = 0;
    int count_10 = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != '0' && s1[i] != '1') return -1;
        if (s2[i] != '0' && s2[i] != '1') return -1;

        if (s1[i] == '0' && s2[i] == '1') {
            count_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count_10++;
        }
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0') {
        return -1;
    }

    if ((count_01 + count_10) % 2 != 0) {
        return -1;
    }

    int swaps = (count_01 / 2) + (count_10 / 2);

    if (count_01 % 2 != 0) {
        swaps += 2;
    }

    return swaps;
}

int main(void) {
    size_t max_size = 100005;
    char *s1 = (char *)malloc(max_size * sizeof(char));
    char *s2 = (char *)malloc(max_size * sizeof(char));
    
    if (s1 == NULL || s2 == NULL) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char format[64];
    snprintf(format, sizeof(format), "%%%zus %%%zus", max_size - 1, max_size - 1);
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf(format, s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        printf("%d\n", result);
    }
    
    free(s1);
    free(s2);
    
    return 0;
}