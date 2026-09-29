#include <stdio.h>
#include <string.h>

int has28Days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    if (strcmp(month, "February") == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    char month[32];
    
    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strcspn(month, "\n");
        month[len] = '\0';
        
        if (has28Days(month)) {
            printf("%s has 28 days.\n", month);
        } else {
            printf("%s does not have 28 days.\n", month);
        }
    }
    
    return 0;
}