#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
long long findProductOfFirstEvenOdd(int *list, int size) {
    int found_even = 0, found_odd = 0;
    long long product = 1;

    for (int i = 0; i < size && (!found_even || !found_odd); i++) {
        if (!found_even && list[i] % 2 == 0) {
            product *= list[i];
            found_even = 1;
        } else if (!found_odd && list[i] % 2 != 0) {
            product *= list[i];
            found_odd = 1;
        }
    }

    return found_even && found_odd ? product : -1;
}

int main() {
    int list[] = {3, 5, 2, 8, 9};
    int size = sizeof(list) / sizeof(list[0]);

    long long result = findProductOfFirstEvenOdd(list, size);

    if (result != -1) {
        printf("The product of the first even and odd numbers is: %lld\n", result);
    } else {
        printf("The list does not contain both an even and an odd number.\n");
    }

    return 0;
}