#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int min_flips_to_alternate(const char *s, size_t *result) {
    size_t len;
    size_t flips_start_0 = 0;
    size_t flips_start_1 = 0;
    size_t i;
    
    if (s == NULL || result == NULL) {
        return -1;
    }
    
    len = strnlen(s, 1024);
    if (len == 1024) {
        return -1;
    }
    
    for (i = 0; i < len; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return -1;
        }
        
        if (i % 2 == 0) {
            if (s[i] != '0') {
                flips_start_0++;
            }
            if (s[i] != '1') {
                flips_start_1++;
            }
        } else {
            if (s[i] != '1') {
                flips_start_0++;
            }
            if (s[i] != '0') {
                flips_start_1++;
            }
        }
    }
    
    *result = (flips_start_0 < flips_start_1) ? flips_start_0 : flips_start_1;
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1025];
    size_t result;
    int status;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    status = min_flips_to_alternate(buffer, &result);
    if (status != 0) {
        return EXIT_FAILURE;
    }
    
    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}