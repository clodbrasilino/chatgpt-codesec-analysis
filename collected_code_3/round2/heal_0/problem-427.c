#include <stdio.h>
#include <string.h>

void convert_date_format(char* date) {
    char new_date[11];
    strncpy(new_date, &date[8], 2);
    strncpy(&new_date[2], "-", 1);
    strncpy(&new_date[3], &date[5], 2);
    strncpy(&new_date[5], "-", 1);
    strncpy(&new_date[6], &date[0], 4);
    new_date[10] = '\0';
    printf("%s\n", new_date);
}

int main() {
    char date[] = "2022-09-23";
    convert_date_format(date);
    return 0;
}