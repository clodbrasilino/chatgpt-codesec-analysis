#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_z_not_at_edges(const char *word, size_t len) {
    if (word == NULL || len < 3) {
        return false;
    }
    
    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[257];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (contains_z_not_at_edges(buffer, len)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }
    
    return 0;
}