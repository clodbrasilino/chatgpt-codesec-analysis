#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>

int has28Days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    if (strcasecmp(month, "February") == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    char month[64];
    
    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    month[sizeof(month) - 1] = '\0';
    
    size_t len = strnlen(month, sizeof(month));
    if (len > 0 && month[len - 1] == '\n') {
        month[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Error: empty input\n");
        return 1;
    }
    
    if (has28Days(month)) {
        printf("%s has 28 days\n", month);
    } else {
        printf("%s does not have 28 days\n", month);
    }
    
    return 0;
}