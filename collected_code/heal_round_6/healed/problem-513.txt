#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, size_t size_list) {
    if (tuple == NULL || string == NULL || list == NULL || size_list <= 0) {
        return;
    }

    size_t len_tuple = strlen(tuple);
    size_t len_string = strlen(string);

    if((len_tuple + len_string) < size_list) {
        strncpy(list, tuple, len_tuple);
        list[len_tuple] = '\0';
        strncat(list, string, len_string);
    } else {
        printf("Buffer not large enough to store concatenated string\n");
    }
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-";
    char list[MAX_SIZE] = "";

    tupleToList(tuple, string, list, sizeof(list)/sizeof(char));

    printf("%s\n", list);

    return 0;
}