#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100000

int main(void) {
    char **seen = malloc(MAX_WORDS * sizeof(char*));
    if (seen == NULL) {
        return 1;
    }
    
    int count = 0;
    char word[2048];
    
    while (scanf("%2047s", word) == 1) {
        for (int i = 0; i < count; i++) {
            if (strcmp(seen[i], word) == 0) {
                printf("%s\n", word);
                for (int j = 0; j < count; j++) {
                    free(seen[j]);
                }
                free(seen);
                return 0;
            }
        }
        
        if (count < MAX_WORDS) {
            seen[count] = strdup(word);
            if (seen[count] != NULL) {
                count++;
            }
        }
    }
    
    printf("None\n");
    
    for (int i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(seen);
    
    return 0;
}