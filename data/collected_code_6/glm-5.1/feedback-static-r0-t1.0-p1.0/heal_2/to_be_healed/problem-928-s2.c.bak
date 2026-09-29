#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *convert_date_format(const char *yyyy_mm_dd) {
    if (yyyy_mm_dd == NULL) {
        return NULL;
    }

    if (strlen(yyyy_mm_dd) != 10) {
        return NULL;
    }

    if (yyyy_mm_dd[4] != '-' || yyyy_mm_dd[7] != '-') {
        return NULL;
    }

    char *dd_mm_yyyy = malloc(11);
    if (dd_mm_yyyy == NULL) {
        return NULL;
    }

    dd_mm_yyyy[0] = yyyy_mm_dd[8];
    dd_mm_yyyy[1] = yyyy_mm_dd[9];
    dd_mm_yyyy[2] = '-';
    dd_mm_yyyy[3] = yyyy_mm_dd[5];
    dd_mm_yyyy[4] = yyyy_mm_dd[6];
    dd_mm_yyyy[5] = '-';
    dd_mm_yyyy[6] = yyyy_mm_dd[0];
    dd_mm_yyyy[7] = yyyy_mm_dd[1];
    dd_mm_yyyy[8] = yyyy_mm_dd[2];
    dd_mm_yyyy[9] = yyyy_mm_dd[3];
    dd_mm_yyyy[10] = '\0';

    return dd_mm_yyyy;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", argv[0]);
        return 1;
    }

    char *result = convert_date_format(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Invalid input format. Expected yyyy-mm-dd\n");
        return 1;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return 0;
}