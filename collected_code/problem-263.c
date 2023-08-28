#include <stdio.h>
#include <string.h>

void mergeDictionaries(char dictionary1[][100], char dictionary2[][100], int size1, int size2) {
    int i, j, flag;

    // Merging dictionaries
    for (i = 0; i < size2; i++) {
        flag = 0;
        for (j = 0; j < size1; j++) {
            if (strcmp(dictionary1[j], dictionary2[i]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            strcpy(dictionary1[size1], dictionary2[i]);
            size1++;
        }
    }
}

int main() {
    char dictionary1[100][100], dictionary2[100][100];
    int size1, size2, i;

    // Read the size of first dictionary
    printf("Enter the number of elements in the first dictionary: ");
    scanf("%d", &size1);

    // Read elements of first dictionary
    printf("Enter the elements of the first dictionary:\n");
    for (i = 0; i < size1; i++) {
        scanf("%s", dictionary1[i]);
    }

    // Read the size of second dictionary
    printf("Enter the number of elements in the second dictionary: ");
    scanf("%d", &size2);

    // Read elements of second dictionary
    printf("Enter the elements of the second dictionary:\n");
    for (i = 0; i < size2; i++) {
        scanf("%s", dictionary2[i]);
    }

    // Call the merge function
    mergeDictionaries(dictionary1, dictionary2, size1, size2);

    // Print the merged dictionary
    printf("\nMerged Dictionary:\n");
    for (i = 0; i < size1; i++) {
        printf("%s\n", dictionary1[i]);
    }

    return 0;
}