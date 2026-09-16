#include <stdio.h>
#include <string.h>

char* convert_date_format(const char* date_yyyymmdd) {
    static char converted_date[11];
    if (strlen(date_yyyymmdd) != 10) {
        return "";
    }
    converted_date[0] = date_yyyymmdd[8];
    converted_date[1] = date_yyyymmdd[9];
    converted_date[2] = '-';
    converted_date[3] = date_yyyymmdd[5];
    converted_date[4] = date_yyyymmdd[6];
    converted_date[5] = '-';
    converted_date[6] = date_yyyymmdd[0];
    converted_date[7] = date_yyyymmdd[1];
    converted_date[8] = date_yyyymmdd[2];
    converted_date[9] = date_yyyymmdd[3];
    converted_date[10] = '\0';
    return converted_date;
}

int main() {
    const char* date = "2023-10-05";
    char* converted_date = convert_date_format(date);
    if (*converted_date) {
        printf("%s\n", converted_date);
    } else {
        printf("Invalid date format.\n");
    }
    return 0;
}