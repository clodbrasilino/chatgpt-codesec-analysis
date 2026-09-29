#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumNameLength(const char *names[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (names[i] != NULL && islower(names[i][0])) {
            continue;
        }
        if (names[i] != NULL) {
            sum += strlen(names[i]);
        }
    }
    return sum;
}

int main() {
    const char *names[] = {"John", "Doe", "Jane", "Smith", "amy", "michael"};
    int size = sizeof(names) / sizeof(names[0]);
    int totalLength = sumNameLength(names, size);
    printf("Total length of names: %d\n", totalLength);
    return 0;
}