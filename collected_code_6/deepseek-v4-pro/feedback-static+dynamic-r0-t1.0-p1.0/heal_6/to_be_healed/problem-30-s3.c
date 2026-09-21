#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

int count_substrings_same_start_end(const char *str) {
    int count = 0;
    int freq[256] = {0};
    size_t len = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[len] != '\0') {
        freq[(unsigned char)str[len]]++;
        len++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t input_len;
    
    printf("Enter a string: ");
    input_len = getline(&input, &buffer_size, stdin);
    
    if (input_len == -1) {
        fprintf(stderr, "Error reading input\n");
        /* Possible weaknesses found:
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(input);
        return 1;
    }
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'input_len' is assigned a value that is never used. [unreadVariable]
         */
        input_len--;
    }
    
    if (input[0] == '\0') {
        printf("Total substrings: 0\n");
        free(input);
        return 0;
    }
    
    int result = count_substrings_same_start_end(input);
    printf("Total substrings: %d\n", result);
    
    free(input);
    return 0;
}