#include <stdio.h>

void convert_date_format(char* date, char* new_date) {
    int yyyy, mm, dd;
    sscanf(date, "%d-%d-%d", &yyyy, &mm, &dd);
    sprintf(new_date, "%02d-%02d-%04d", dd, mm, yyyy);
}

int main() {
    char date[] = "2022-03-01";
    char new_date[11];
    convert_date_format(date, new_date);
    printf("New date format: %s\n", new_date);
    return 0;
}