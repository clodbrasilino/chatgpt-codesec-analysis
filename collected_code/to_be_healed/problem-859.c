#include <stdio.h>

void generateSublists(int list[], int size) {
    // Number of sublists is 2^n where n is the size of the list
    int numSublists = 1 << size;

    for (int i = 0; i < numSublists; i++) {
        printf("{");
        for (int j = 0; j < size; j++) {
            if ((i & (1 << j)) != 0) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                printf("%d ", list[j]);
            }
        }
        printf("}\n");
    }
}

int main() {
    int list[] = {1, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);

    generateSublists(list, size);

    return 0;
}