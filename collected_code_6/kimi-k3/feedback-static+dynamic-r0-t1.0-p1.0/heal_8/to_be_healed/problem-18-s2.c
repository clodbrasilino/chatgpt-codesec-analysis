#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_chars(char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        return;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    
    while (str1[read_idx] != '\0') {
        if (strchr(str2, str1[read_idx]) == NULL) {
            str1[write_idx] = str1[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str1[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer1[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer2[BUFFER_SIZE];
    
    printf("Enter first string: ");
    if (fgets(buffer1, sizeof(buffer1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer1, '\n') == NULL && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    printf("Enter second string: ");
    if (fgets(buffer2, sizeof(buffer2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer2, '\n') == NULL && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    buffer1[strcspn(buffer1, "\n")] = '\0';
    buffer2[strcspn(buffer2, "\n")] = '\0';
    
    remove_chars(buffer1, buffer2);
    
    printf("Result: %s\n", buffer1);
    
    return EXIT_SUCCESS;
}