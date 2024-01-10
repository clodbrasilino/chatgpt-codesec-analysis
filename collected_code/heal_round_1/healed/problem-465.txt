#include <stdio.h>
#include <string.h>

void dropEmptyItems(char* dict[]) {
    int i, j;

    for(i = 0; dict[i] != NULL; i++) {
        if(dict[i][0] == '\0') {
            for(j = i; dict[j] != NULL; j++) {
                dict[j] = dict[j+1];
            }
            i--; 
        }
    }
}

int main() {
    char* dict[] = {"apple", "", "banana", "carrot", "", "date", NULL};
    int i;
    
    printf("Before dropping empty items:\n");
    for(i = 0; dict[i] != NULL; i++) {
        printf("%s\n", dict[i]);
    }
    
    dropEmptyItems(dict);
    
    printf("\nAfter dropping empty items:\n");
    for(i = 0; dict[i] != NULL; i++) {
        printf("%s\n", dict[i]);
    }
    
    return 0;
}