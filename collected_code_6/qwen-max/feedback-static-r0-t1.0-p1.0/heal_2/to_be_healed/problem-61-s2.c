#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstringsWithSum(const int *digits, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        int sum = 0;
        for (int j = i; j < len; j++) {
            sum += digits[j];
            if (sum == (j - i + 1)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    char input[1024];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int len = strlen(input);
    const int *digits = malloc(len * sizeof(int));
    if (digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  read-only variable is not assignable
         *  assignment of read-only location '*(digits + (sizetype)((long unsigned int)i * 4))'
         */
        digits[i] = input[i] - '0';
    }

    int result = countSubstringsWithSum(digits, len);
    printf("%d\n", result);

    free((void *)digits);
    return 0;
}