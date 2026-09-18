#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* extract_elements(int* source_array, int num_elements, int start_element, int source_length) {
    if(start_element < 0 || start_element >= source_length || 
       num_elements <= 0 || start_element+num_elements > source_length) {
        return NULL;
    }
    int* extracted_elements = malloc(num_elements*sizeof(int));

    if(extracted_elements == NULL) {
        return NULL;
    }

    memcpy(extracted_elements, source_array + start_element, num_elements*sizeof(int));
    return extracted_elements;
}

int main() {
    int num_elements = 3;
    int start_element = 2;
    int source_length = 6;

    int source_array[6] = {1, 2, 3, 4, 5, 6};

    int* extracted_elements = extract_elements(source_array, num_elements, 
                                               start_element, source_length);
    
    if(extracted_elements == NULL) {
        printf("Invalid input or memory allocation error.\n");
        return 1;
    }

    for(int i = 0; i < num_elements; i++) {
        printf("%d ", extracted_elements[i]);
    }

    free(extracted_elements);
    return 0;
}