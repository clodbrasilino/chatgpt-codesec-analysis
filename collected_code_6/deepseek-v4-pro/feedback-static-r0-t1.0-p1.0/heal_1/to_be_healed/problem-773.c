#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_substrings(const char *str, const char *sub, int **positions) {
    if (str == NULL || sub == NULL || positions == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sub_len = strlen(sub);
    
    if (sub_len == 0 || str_len < sub_len) {
        *positions = NULL;
        return 0;
    }
    
    int capacity = 10;
    int count = 0;
    *positions = (int *)malloc(capacity * sizeof(int));
    if (*positions == NULL) {
        return -1;
    }
    
    const char *current = str;
    
    while (*current != '\0' && (size_t)(current - str) <= str_len - sub_len) {
        if (strncmp(current, sub, sub_len) == 0) {
            if (count >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(*positions, capacity * sizeof(int));
                if (temp == NULL) {
                    free(*positions);
                    *positions = NULL;
                    return -1;
                }
                *positions = temp;
            }
            (*positions)[count++] = (int)(current - str);
            current += sub_len;
        } else {
            current++;
        }
    }
    
    return count;
}

int main(void) {
    const char *text = "This is a test. This test is only a test.";
    const char *substring = "test";
    int *positions = NULL;
    
    int count = find_substrings(text, substring, &positions);
    
    if (count < 0) {
        printf("Error occurred during search.\n");
        return 1;
    }
    
    printf("Found %d occurrence(s) of '%s' in '%s'\n", count, substring, text);
    
    for (int i = 0; i < count; i++) {
        printf("Occurrence %d at position: %d\n", i + 1, positions[i]);
    }
    
    free(positions);
    positions = NULL;
    
    count = find_substrings(text, "xyz", &positions);
    printf("\nFound %d occurrence(s) of 'xyz'\n", count);
    free(positions);
    positions = NULL;
    
    count = find_substrings(text, "", &positions);
    printf("Found %d occurrence(s) of empty string\n", count);
    free(positions);
    positions = NULL;
    
    return 0;
}