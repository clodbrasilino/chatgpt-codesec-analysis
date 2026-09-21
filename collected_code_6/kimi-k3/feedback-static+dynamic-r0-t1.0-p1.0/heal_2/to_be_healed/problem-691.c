#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 50
#define MAX_VALUES_PER_GROUP 100
#define MAX_GROUPS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[MAX_STRING_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[MAX_STRING_LEN];
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_STRING_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char values[MAX_VALUES_PER_GROUP][MAX_STRING_LEN];
    int value_count;
} Group;

static int safe_copy_string(char *dest, size_t dest_size, const char *src) {
    size_t src_len;
    
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    src_len = strlen(src);
    if (src_len >= dest_size) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len + 1);
    return 0;
}

int find_group_index(Group groups[], int group_count, const char *key) {
    if (groups == NULL || key == NULL || group_count < 0) {
        return -1;
    }
    
    for (int i = 0; i < group_count; i++) {
        if (strcmp(groups[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int group_tuples(Tuple tuples[], int tuple_count, Group groups[], int max_groups) {
    int group_count = 0;
    
    if (tuples == NULL || groups == NULL || tuple_count < 0 || max_groups <= 0) {
        return -1;
    }
    
    for (int i = 0; i < tuple_count; i++) {
        int idx = find_group_index(groups, group_count, tuples[i].second);
        
        if (idx == -1) {
            if (group_count >= max_groups) {
                return -1;
            }
            
            if (safe_copy_string(groups[group_count].key, MAX_STRING_LEN, tuples[i].second) != 0) {
                return -1;
            }
            
            groups[group_count].value_count = 0;
            idx = group_count;
            group_count++;
        }
        
        if (groups[idx].value_count >= MAX_VALUES_PER_GROUP) {
            return -1;
        }
        
        if (safe_copy_string(groups[idx].values[groups[idx].value_count], MAX_STRING_LEN, tuples[i].first) != 0) {
            return -1;
        }
        
        groups[idx].value_count++;
    }
    
    return group_count;
}

int main(void) {
    Tuple tuples[] = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"banana", "fruit"},
        {"broccoli", "vegetable"},
        {"cherry", "fruit"},
        {"spinach", "vegetable"}
    };
    
    int tuple_count = (int)(sizeof(tuples) / sizeof(tuples[0]));
    Group groups[MAX_GROUPS];
    int group_count;
    
    group_count = group_tuples(tuples, tuple_count, groups, MAX_GROUPS);
    
    if (group_count < 0) {
        fprintf(stderr, "Error: Failed to group tuples\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < group_count; i++) {
        printf("%s: [", groups[i].key);
        for (int j = 0; j < groups[i].value_count; j++) {
            printf("%s", groups[i].values[j]);
            if (j < groups[i].value_count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    
    return EXIT_SUCCESS;
}