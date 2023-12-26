#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom tuple structure
typedef struct Tuple {
    char* str;
    int* list;
    int list_size;
} Tuple;

// Function to create a new tuple from the given string and list
Tuple* createNewTuple(char* str, int* list, int list_size) {
    // Allocate memory for the tuple
    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));

    // Copy the string into the tuple
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int str_size = strlen(str);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_tuple->str = (char*)malloc((str_size + 1) * sizeof(char));
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(new_tuple->str, str);

    // Copy the list into the tuple
    new_tuple->list_size = list_size;
    new_tuple->list = (int*)malloc(list_size * sizeof(int));
    /* Possible weaknesses found:
     *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(new_tuple->list, list, list_size * sizeof(int));

    return new_tuple;
}

int main() {
    // Example usage
    char* str = "example";
    int list[3] = {1, 2, 3};
    int list_size = sizeof(list) / sizeof(int);

    Tuple* my_tuple = createNewTuple(str, list, list_size);

    // Print the tuple elements
    printf("String: %s\n", my_tuple->str);
    printf("List: ");
    for (int i = 0; i < my_tuple->list_size; i++) {
        printf("%d ", my_tuple->list[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(my_tuple->str);
    free(my_tuple->list);
    free(my_tuple);

    return 0;
}