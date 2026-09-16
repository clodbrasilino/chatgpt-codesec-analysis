#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int get_nth_item(int *list, int size, int n, int *result) {
    if (n < 0 || n >= size) return -1;
    *result = list[n];
    return 0;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);
    int n = 5;
    int result;

    if (get_nth_item(list, size, n, &result) == 0) {
        printf("The %dth item is: %d\n", n + 1, result);
    } else {
        printf("Invalid index\n");
    }

    return 0;
}