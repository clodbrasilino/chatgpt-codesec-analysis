#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert_date_format(const char* date) {
    char* new_date = (char*) malloc(sizeof(char) * 11);
    if(!new_date) {
        printf("Error allocating memory.\n");
        exit(1);
    }
    
    strncpy(new_date, date + 8, 2);
    new_date[2] = '-';
    strncpy(new_date + 3, date + 5, 2);
    new_date[5] = '-';
    strncpy(new_date + 6, date, 4);
    new_date[10] = '\0';
    
    return new_date;
}

int main() {
    char* old_format = "2022-01-01";
    char* new_format = NULL;

    new_format = convert_date_format(old_format);
    
    if(new_format) {
        printf("The date in dd-mm-yyyy format is: %s\n", new_format);
        free(new_format);
    }
    
    return 0;
}