#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int **list, int rows, int cols, int pos){
    if(pos >= cols){
        printf("Position out of range!\n");
        return NULL;
    }

    int* extracted_elements = (int*)malloc(rows * sizeof(int));
    if(extracted_elements == NULL){
        printf("Malloc failed!\n");
        return NULL;
    }

    for(int i = 0; i < rows; i++){
        /* Possible weaknesses found:
         *  use of uninitialized value '*list_26(D) + _4' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        extracted_elements[i] = list[i][pos];
    }

    return extracted_elements;
}

int main(){
    int rows, cols, pos;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    int** list = (int**)malloc(rows * sizeof(int*));
    if(list == NULL){
        printf("Malloc failed!\n");
        return -1;
    }

    for(int i = 0; i < rows; i++){
        list[i] = (int*)malloc(cols * sizeof(int));
        if(list[i] == NULL){
            printf("Malloc failed!\n");
            return -1;
        }
    }

    printf("Enter the elements of the list:\n");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            scanf("%d", &list[i][j]);
        }
    }

    printf("Enter the position to extract: ");
    scanf("%d", &pos);

    int* extracted_elements = extract_elements(list, rows, cols, pos);
    if(extracted_elements != NULL){
        printf("Extracted elements:\n");
        for(int i = 0; i < rows; i++){
            printf("%d ", extracted_elements[i]);
        }
        printf("\n");
        free(extracted_elements);
    }

    for(int i = 0; i < rows; i++){
        /* Possible weaknesses found:
         *  use of uninitialized value '*list_57 + _34' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        free(list[i]);
    }
    free(list);

    return 0;
}