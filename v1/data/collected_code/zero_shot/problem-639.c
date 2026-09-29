#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumNameLength(char *names[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (islower(names[i][0])) {
            continue;
        }
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