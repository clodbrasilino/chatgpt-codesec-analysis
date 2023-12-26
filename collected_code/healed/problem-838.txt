#include <stdio.h>

int minSwaps(const char* s1, const char* s2) {
    int n = 0; 
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            n++;
            i++;
        }
    }
    return n;
}

int main() {
    const char s1[] = "1001";
    const char s2[] = "0110";

    int swaps = minSwaps(s1, s2);

    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}