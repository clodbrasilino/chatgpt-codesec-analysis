#include <stdio.h>
#include <string.h>

char* date_format(char* date) {

    static char new_date[11];

    if(date==NULL || strlen(date)<10) {
        return NULL;
    }

    strncpy(new_date, &date[8], 2);
    new_date[2] = '-';
    strncpy(&new_date[3], &date[5], 2);
    new_date[5] = '-';
    strncpy(&new_date[6], &date[0], 4);
    new_date[10] = '\0';

    return new_date;
}

int main() {
    
    char *date = "2022-12-31";
    char *new_date;

    new_date = date_format(date);

    if(new_date == NULL) {
        printf("Invalid date format\n");
        return 1;
    }

    printf("New date: %s\n", new_date);

    return 0;
}