#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *convert_date(const char *yyyy_mm_dd) {
    if (yyyy_mm_dd == NULL) {
        return NULL;
    }

    size_t len = strlen(yyyy_mm_dd);
    if (len != 10) {
        return NULL;
    }

    if (yyyy_mm_dd[4] != '-' || yyyy_mm_dd[7] != '-') {
        return NULL;
    }

    char *dd_mm_yyyy = malloc(11);
    if (dd_mm_yyyy == NULL) {
        return NULL;
    }

    memcpy(dd_mm_yyyy, yyyy_mm_dd + 8, 2);
    dd_mm_yyyy[2] = '-';
    memcpy(dd_mm_yyyy + 3, yyyy_mm_dd + 5, 2);
    dd_mm_yyyy[5] = '-';
    memcpy(dd_mm_yyyy + 6, yyyy_mm_dd, 4);
    dd_mm_yyyy[10] = '\0';

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

    const char * const *ptr_null = NULL;
    const char *converted3 = convert_date(ptr_null);
    if (converted3 == NULL) {
        printf("Invalid input handled.\n");
    }

    const char *date4 = "2023/10/25";
    char *converted4 = convert_date(date4);
    if (converted4 == NULL) {
        printf("Invalid format handled.\n");
    } else {
        free(converted4);
    }

    return 0;
}