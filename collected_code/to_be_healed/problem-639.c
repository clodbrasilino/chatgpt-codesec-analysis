#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumNameLength(char *names[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'names[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (islower(names[i][0])) {
            continue;
        }
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         *  Cannot determine that 'names[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += strlen(names[i]);
    }
    return sum;
}

int main() {
    char *names[] = {"John", "Doe", "Jane", "Smith", "amy", "michael"};
    int size = sizeof(names) / sizeof(names[0]);
    int totalLength = sumNameLength(names, size);
    printf("Total length of names: %d\n", totalLength);
    return 0;
}