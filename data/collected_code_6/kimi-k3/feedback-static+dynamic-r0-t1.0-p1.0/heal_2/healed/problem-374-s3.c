#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, size_t left, size_t right) {
    if (left == right) {
        printf("%s\n", str);
    } else {
        for (size_t i = left; i <= right; i++) {
            swap((str + left), (str + i));
            permute(str, left + 1, right);
            swap((str + left), (str + i));
        }
    }
}

int main(void) {
    char *str = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    bool valid_input = false;
    
    printf("Enter a string: ");
    
    bytes_read = getline(&str, &buffer_size, stdin);
    
    if (bytes_read != -1) {
        size_t len = (size_t)bytes_read;
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        
        if (len > 0) {
            printf("All permutations:\n");
            permute(str, 0, len - 1);
            valid_input = true;
        } else {
            printf("Empty string provided.\n");
        }
        
        free(str);
    } else {
        fprintf(stderr, "Error reading input.\n");
        free(str);
        return EXIT_FAILURE;
    }
    
    return valid_input ? EXIT_SUCCESS : EXIT_FAILURE;
}