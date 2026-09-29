#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} Collection;

void collection_init(Collection *col, size_t initial_capacity) {
    col->items = (char **)malloc(initial_capacity * sizeof(char *));
    col->size = 0;
    col->capacity = initial_capacity;
}

bool collection_add(Collection *col, const char *item) {
    for (size_t i = 0; i < col->size; i++) {
        if (strcmp(col->items[i], item) == 0) {
            return false;
        }
    }
    if (col->size == col->capacity) {
        size_t new_capacity = col->capacity * 2;
        char **new_items = (char **)realloc(col->items, new_capacity * sizeof(char *));
        if (new_items == NULL) {
            return false;
        }
        col->items = new_items;
        col->capacity = new_capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    col->items[col->size] = (char *)malloc(strlen(item) + 1);
    if (col->items[col->size] == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(col->items[col->size], item);
    col->size++;
    return true;
}

void collection_free(Collection *col) {
    for (size_t i = 0; i < col->size; i++) {
        free(col->items[i]);
    }
    free(col->items);
    col->items = NULL;
    col->size = 0;
    col->capacity = 0;
}

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Collection col;
    collection_init(&col, 16);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        collection_free(&col);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);

    char *token = strtok(temp, " ");
    while (token != NULL) {
        collection_add(&col, token);
        token = strtok(NULL, " ");
    }

    size_t result_len = 0;
    for (size_t i = 0; i < col.size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result_len += strlen(col.items[i]) + 1;
    }

    if (result_len == 0) {
        free(temp);
        collection_free(&col);
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    char *result = (char *)malloc(result_len);
    if (result == NULL) {
        free(temp);
        collection_free(&col);
        return NULL;
    }

    result[0] = '\0';
    for (size_t i = 0; i < col.size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, col.items[i]);
        if (i < col.size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
    }

    free(temp);
    collection_free(&col);

    return result;
}

int main(void) {
    const char *input = "hello world hello universe world";
    char *output = remove_duplicate_words(input);

    if (output != NULL) {
        printf("Input: %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    }

    const char *input2 = "one two three";
    char *output2 = remove_duplicate_words(input2);

    if (output2 != NULL) {
        printf("Input: %s\n", input2);
        printf("Output: %s\n", output2);
        free(output2);
    }

    /* Possible weaknesses found:
     *  Assignment 'output3=remove_duplicate_words(NULL)', assigned value is 0
     *  Variable 'output3' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'remove_duplicate_words' returns 0
     */
    char *output3 = remove_duplicate_words(NULL);
    /* Possible weaknesses found:
     *  Condition 'output3==NULL' is always true
     *  Condition 'output3==NULL' is always true [knownConditionTrueFalse]
     */
    if (output3 == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}