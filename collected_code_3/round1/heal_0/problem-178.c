#include <stdio.h>
#include <string.h>

int search_string(char *str, char *search) {
    char *ptr = strstr(str, search);

    if(ptr != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    char search[50];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    printf("Enter a string to search: ");
    fgets(search, sizeof(search), stdin);

    search[strlen(search)-1] = '\0';

    if(search_string(str, search)) {
        printf("String found\n");
    } else {
        printf("String not found\n");
    }

    return 0;
}