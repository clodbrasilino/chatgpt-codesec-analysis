#include <stdio.h>
#include <stdlib.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date\n");
        return;
    }

    if ((month == 3 && day >= 20) || month == 4 || month == 5 || (month == 6 && day < 21)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || month == 7 || month == 8 || (month == 9 && day < 22)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 22) || month == 10 || month == 11 || (month == 12 && day < 21)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int month = 0;
    int day = 0;

    if (argc == 3) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        month = atoi(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        day = atoi(argv[2]);
    } else {
        printf("Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_season(month, day);

    return EXIT_SUCCESS;
}