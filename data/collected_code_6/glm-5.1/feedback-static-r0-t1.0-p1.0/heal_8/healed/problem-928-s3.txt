#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *convert_date(const char *yyyy_mm_dd) {
    if (yyyy_mm_dd == NULL) {
        return NULL;
    }

    if (strnlen(yyyy_mm_dd, 11) != 10) {
        return NULL;
    }

    if (yyyy_mm_dd[4] != '-' || yyyy_mm_dd[7] != '-') {
        return NULL;
    }

    char *dd_mm_yyyy = malloc(11);
    if (dd_mm_yyyy == NULL) {
        return NULL;
    }

    snprintf(dd_mm_yyyy, 11, "%.2s-%.2s-%.4s", yyyy_mm_dd + 8, yyyy_mm_dd + 5, yyyy_mm_dd);

    return dd_mm_yyyy;
}

int main(void) {
    const char *date1 = "2023-10-25";
    char *converted1 = convert_date(date1);
    if (converted1 != NULL) {
        printf("%s\n", converted1);
        free(converted1);
    }

    const char *date2 = "2023-05-01";
    char *converted2 = convert_date(date2);
    if (converted2 != NULL) {
        printf("%s\n", converted2);
        free(converted2);
    }

    const char *date3 = NULL;
    char *converted3 = convert_date(date3);
    if (converted3 == NULL) {
        printf("Invalid input handled.\n");
    }

    const char *date4 = "2023/10/25";
    char *converted4 = convert_date(date4);
    if (converted4 == NULL) {
        printf("Invalid format handled.\n");
    }

    return 0;
}