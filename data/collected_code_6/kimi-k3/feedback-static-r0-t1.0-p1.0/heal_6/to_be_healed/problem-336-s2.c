#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MONTH_LENGTH 32

static void to_lowercase(char *dest, const char *src, size_t dest_size)
{
    size_t i;
    
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

static bool has_28_days(const char *month_name)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_MONTH_LENGTH];
    
    if (month_name == NULL) {
        return false;
    }
    
    if (strnlen(month_name, MAX_MONTH_LENGTH) >= MAX_MONTH_LENGTH) {
        return false;
    }
    
    to_lowercase(normalized, month_name, sizeof(normalized));
    
    return strcmp(normalized, "february") == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_MONTH_LENGTH];
    int result;
    
    printf("Enter month name: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    result = has_28_days(input) ? 1 : 0;
    printf("%d\n", result);
    
    return 0;
}