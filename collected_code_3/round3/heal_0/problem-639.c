#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumNameLength(char *names[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        if(isupper(names[i][0])) {
            sum += strlen(names[i]);
        }
    }
    return sum;
}

int main() {
    char *names[] = {"John", "jane", "Doe", "doe", "Alice", "bob"};
    int size = sizeof(names) / sizeof(names[0]);
    int sum = sumNameLength(names, size);
    printf("Sum of the length of the names: %d\n", sum);
    return 0;
}