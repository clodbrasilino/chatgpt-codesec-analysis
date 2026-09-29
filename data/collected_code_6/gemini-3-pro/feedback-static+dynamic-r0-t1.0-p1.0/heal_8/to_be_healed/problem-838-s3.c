#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100004

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
    size_t buffer_size = MAX_STR_LEN + 1;
    char *s1 = (char *)malloc(buffer_size * sizeof(char));
    char *s2 = (char *)malloc(buffer_size * sizeof(char));
    
    if (s1 == NULL || s2 == NULL) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100004s %100004s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        printf("%d\n", result);
    }
    
    free(s1);
    free(s2);
    
    return 0;
}