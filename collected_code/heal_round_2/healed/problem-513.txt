#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, int size_list) {
    int i;

    if (tuple == NULL || string == NULL || list == NULL || size_list <= 0) {
        return;
    }

    list[0] = '\0';

    for(i = 0; tuple[i] != '\0' && i < size_list; i++) {
        snprintf(list + strlen(list), size_list - strlen(list), "%c", tuple[i]);
        snprintf(list + strlen(list), size_list - strlen(list), "%s", string);
    }
    list[size_list - 1] = '\0';
}

int main() {
    char tuple[] = "12345";
    char string[] = "-";
    char list[MAX_SIZE];

    tupleToList(tuple, string, list, MAX_SIZE);

    printf("%s\n", list);

    return 0;
}