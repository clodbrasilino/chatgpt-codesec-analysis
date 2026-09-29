#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
char* extractSizeStrings(char* str[], int n, int size) {
    char* extractedStrings[MAX_STRINGS];
    int j = 0;
    for(int i = 0; i < n; i++) {
        if(strlen(str[i]) == size) {
            extractedStrings[j] = malloc(strlen(str[i])+1);
            if (extractedStrings[j] == NULL) {
                printf("Memory allocation failed");
                exit(-1);
            }
            strcpy(extractedStrings[j], str[i]);
            j++;
        }
    }
    return *extractedStrings;
}

int main() {
    int i, n, size;
    char* str[MAX_STRINGS];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter the strings:\n");
    for (i = 0; i < n; i++) {
        str[i] = (char *) malloc(256);
        if (str[i] == NULL) {
            printf("Memory allocation failed");
            exit(-1);
        }
        scanf("%s", str[i]);
    }

    printf("Enter the size to filter: ");
    scanf("%d", &size);

    char* extractedStrings = extractSizeStrings(str, n, size);

    printf("Extracted strings of size %d are:\n", size);
    for(i = 0; i < n; i++) {
        if(strlen(extractedStrings+i) == size) {
            printf("%s\n", (extractedStrings+i));
        }
    }

    for(i = 0; i < n; i++) {
        free(str[i]);
    }

    return 0;
}