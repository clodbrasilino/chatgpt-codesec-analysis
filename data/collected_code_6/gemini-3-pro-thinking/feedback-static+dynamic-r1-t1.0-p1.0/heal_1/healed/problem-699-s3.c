#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

int64_t min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    int64_t mismatch_01 = 0;
    int64_t mismatch_10 = 0;
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        
        if (s1[i] == '0' && s2[i] == '1') {
            mismatch_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            mismatch_10++;
        }
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0') {
        return -1;
    }

    if (mismatch_01 != mismatch_10) {
        return -1;
    }

    return mismatch_01;
}

int main(void) {
    const char *s1 = "110100";
    const char *s2 = "001110";

    int64_t swaps = min_swaps(s1, s2);
    
    if (swaps != -1) {
        printf("%" PRId64 "\n", swaps);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}