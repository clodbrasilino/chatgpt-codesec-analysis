#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *search_strings(const char *haystack, const char **needles, size_t needle_count) {
    if (haystack == NULL || needle_count == 0) {
        return NULL;
    }

    int *results = (int *)malloc(needle_count * sizeof(int));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < needle_count; i++) {
        if (needles[i] == NULL) {
            results[i] = 0;
            continue;
        }

        results[i] = strstr(haystack, needles[i]) != NULL;
    }

    return results;
}

int main(void) {
    const char *haystack = "The quick brown fox jumps over the lazy dog";
    const char *needles[] = {"quick", "lazy", "missing", NULL};
    /* Possible weaknesses found:
     *  Assignment 'needle_count=sizeof(needles)/sizeof(needles[0])-1', assigned value is 3
     */
    size_t needle_count = sizeof(needles) / sizeof(needles[0]) - 1;

    int *results = search_strings(haystack, needles, needle_count);
    if (results == NULL) {
        /* Possible weaknesses found:
         *  Condition 'needle_count>0' is always true [knownConditionTrueFalse]
         *  Condition 'needle_count>0' is always true
         */
        if (needle_count > 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < needle_count; i++) {
        printf("Needle '%s': %s\n", needles[i], results[i] ? "Found" : "Not Found");
    }

    free(results);

    return EXIT_SUCCESS;
}