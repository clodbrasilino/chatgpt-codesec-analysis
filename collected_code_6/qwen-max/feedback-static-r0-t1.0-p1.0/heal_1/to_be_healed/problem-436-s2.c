#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
void print_negative_numbers(int *numbers, int length) {
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int list[] = {4, -1, -3, 12, -5, 6, -7};
    int length = sizeof(list) / sizeof(list[0]);
    print_negative_numbers(list, length);
    return 0;
}