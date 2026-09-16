#include <stdio.h>
#include <stdlib.h>

int can_be_difference_of_squares(int n) {
    if (n < 0) {
        return 0;
    }
    if (n % 4 == 0) {
        return 1;
    }
    if (n % 2 != 0) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int num;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (can_be_difference_of_squares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return EXIT_SUCCESS;
}