#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    return month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int month;
    if (argc != 2) {
        return 1;
    }
    if (sscanf(argv[1], "%d", &month) != 1) {
        return 1;
    }
    if (has_31_days(month)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}