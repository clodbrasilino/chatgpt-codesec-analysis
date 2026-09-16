#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sequence' can be declared as pointer to const [constParameterPointer]
 */
int is_linear(int *sequence, int n) {
    if (n <= 1) return 1;
    int diff = sequence[1] - sequence[0];
    for (int i = 2; i < n; i++) {
        if (sequence[i] - sequence[i-1] != diff) return 0;
    }
    return 1;
}

int main() {
    int sequence[] = {2, 4, 6, 8, 10};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    if (is_linear(sequence, n)) {
        printf("The sequence is linear.\n");
    } else {
        printf("The sequence is not linear.\n");
    }
    return 0;
}