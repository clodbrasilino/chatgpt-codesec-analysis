#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool search_literal(const char *haystack, const char *needle)
{
    if (haystack == NULL || needle == NULL) {
        return false;
    }
    
    if (*needle == '\0') {
        return true;
    }
    
    return strstr(haystack, needle) != NULL;
}

size_t search_literals(const char *haystack, const char *needles[], size_t needle_count, size_t results[], size_t max_results)
{
    size_t found_count = 0;
    
    if (haystack == NULL || needles == NULL || (results == NULL && max_results > 0)) {
        return 0;
    }
    
    for (size_t i = 0; i < needle_count; i++) {
        if (needles[i] == NULL) {
            continue;
        }
        
        if (search_literal(haystack, needles[i])) {
            if (found_count < max_results) {
                results[found_count] = i;
            }
            found_count++;
        }
    }
    
    return found_count;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *search_terms[] = {"fox", "cat", "dog", "bird", "quick"};
    const size_t num_terms = sizeof(search_terms) / sizeof(search_terms[0]);
    size_t found_indices[5];
    
    size_t found = search_literals(text, search_terms, num_terms, found_indices, 5);
    
    printf("Text: %s\n\n", text);
    
    if (found == 0) {
        printf("No matches found.\n");
    } else {
        printf("Found %zu match(es):\n", found);
        for (size_t i = 0; i < found && i < 5; i++) {
            printf("- \"%s\" at index %zu\n", search_terms[found_indices[i]], found_indices[i]);
        }
    }
    
    return 0;
}