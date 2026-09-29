#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

char** remove_words(char** list, int count, const char* substr, int* out_count) {
    if (list == NULL || substr == NULL || out_count == NULL || count <= 0) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int res_idx = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t substr_len = strlen(substr);

    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }

        char *match = strstr(list[i], substr);
        if (match == NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t word_len = strlen(list[i]);
            result[res_idx] = (char*)malloc(word_len + 1);
            if (result[res_idx] == NULL) {
                for (int j = 0; j < res_idx; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[res_idx], list[i], word_len + 1);
            res_idx++;
        } else {
            /* Possible weaknesses found:
             *  Variable 'remove_start' can be declared as pointer to const [constVariablePointer]
             */
            char *remove_start = match;
            char *remove_end = match + substr_len;
            
            char *next_match = strstr(remove_end, substr);
            while (1) {
                size_t segment_len;
                if (next_match == NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    segment_len = strlen(remove_end);
                } else {
                    segment_len = next_match - remove_end;
                }
                
                if (segment_len > 0) {
                    char *old_result = result[res_idx];
                    size_t old_len = 0;
                    if (old_result != NULL) {
                        /* Possible weaknesses found:
                         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                         */
                        old_len = strlen(old_result);
                    }
                    
                    char *new_result = (char*)malloc(old_len + segment_len + 1);
                    if (new_result == NULL) {
                        if (old_result) free(old_result);
                        for (int j = 0; j < res_idx; j++) {
                            free(result[j]);
                        }
                        free(result);
                        *out_count = 0;
                        return NULL;
                    }
                    
                    if (old_result) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(new_result, old_result, old_len);
                        free(old_result);
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(new_result + old_len, remove_end, segment_len);
                    new_result[old_len + segment_len] = '\0';
                    result[res_idx] = new_result;
                }
                
                if (next_match == NULL) {
                    break;
                }
                remove_end = next_match + substr_len;
                next_match = strstr(remove_end, substr);
            }
            
            /* Possible weaknesses found:
             *  Assuming that condition 'result[res_idx]!=NULL' is not redundant
             */
            if (result[res_idx] != NULL || remove_start != list[i]) {
                if (result[res_idx] == NULL) {
                    result[res_idx] = (char*)malloc(1);
                    if (result[res_idx] == NULL) {
                        for (int j = 0; j < res_idx; j++) {
                            free(result[j]);
                        }
                        free(result);
                        *out_count = 0;
                        return NULL;
                    }
                    result[res_idx][0] = '\0';
                }
                res_idx++;
            } else {
                /* Possible weaknesses found:
                 *  Condition 'result[res_idx]!=NULL' is always false
                 *  Condition 'result[res_idx]!=NULL' is always false [knownConditionTrueFalse]
                 */
                if (result[res_idx] != NULL) {
                    free(result[res_idx]);
                    result[res_idx] = NULL;
                }
            }
        }
    }

    if (res_idx == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    char** shrunk_result = (char**)realloc(result, res_idx * sizeof(char*));
    if (shrunk_result == NULL) {
        *out_count = res_idx;
        return result;
    }

    *out_count = res_idx;
    return shrunk_result;
}

int main(void) {
    char* words[] = {"Red color", "Orange#", "Green", "Orange", "White"};
    int count = sizeof(words) / sizeof(words[0]);
    int out_count = 0;
    
    char** filtered = remove_words(words, count, "color", &out_count);
    
    if (filtered != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("No matching words found or allocation failed.\n");
    }

    return 0;
}