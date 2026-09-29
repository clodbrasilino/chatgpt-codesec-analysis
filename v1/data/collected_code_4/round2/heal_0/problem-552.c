#include <stdio.h>
#include <stdlib.h>

int isSequenceLinear(int *seq, int size) {
    if (seq == NULL || size <= 2) {
        return -1;
    }

    int diff = seq[1] - seq[0];
    for(int i = 2; i < size; i++) {
        if ((seq[i] - seq[i-1]) != diff) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    int size;
    printf("Enter size of sequence: ");
    scanf("%d", &size);

    if (size <= 0) {
	    printf("Size must be greater than 0. Exiting...\n");
	    return -1;
    }
    
    int *seq = (int*) malloc(size * sizeof(int));
    if (seq == NULL) {
	    printf("Memory allocation for the sequence failed. Exiting...\n");
	    return -1;
    }
    
    for (int i = 0; i < size; i++) {
	    printf("Enter element %d: ", i + 1);
	    scanf("%d", &seq[i]);
    }

    int result = isSequenceLinear(seq, size);

    if(result == -1) {
	    printf("The sequence is too short or invalid. Exiting...\n");
    } else if (result == 0) {
	    printf("The sequence is not linear.\n");
    } else {
	    printf("The sequence is linear.\n");
    }

    free(seq);
    
    return 0;
}