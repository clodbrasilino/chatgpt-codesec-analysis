#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'PositiveNumbers'
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 *  expected ';' after top level declarator
 *  variable has incomplete type 'void'
 */
void print PositiveNumbers(int *numbers, int size) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] > 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = {3, -1, 4, -1, 5, 9, 2, -6, 5, 3, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     *  call to undeclared function 'printPositiveNumbers'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'printPositiveNumbers' [-Wimplicit-function-declaration]
     */
    printPositiveNumbers(numbers, size);
    return 0;
}