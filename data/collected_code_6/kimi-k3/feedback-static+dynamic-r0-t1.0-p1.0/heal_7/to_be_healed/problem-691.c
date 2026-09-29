#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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
    
    src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        return -1;
    }
    
    if (dest_size < src_len + 1) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    
    return 0;
}

static int find_group_index(const Group groups[], int group_count, const char *key) {
    if (groups == NULL || key == NULL || group_count < 0 || group_count > MAX_GROUPS) {
        return -1;
    }
    
    for (int i = 0; i < group_count; i++) {
        if (strncmp(groups[i].key, key, MAX_STRING_LEN - 1) == 0 && 
            groups[i].key[MAX_STRING_LEN - 1] == '\0') {
            return i;
        }
    }
    return -1;
}

static int validate_tuple(const Tuple *t) {
    if (t == NULL) {
        return -1;
    }
    
    if (strnlen(t->first, MAX_STRING_LEN) >= MAX_STRING_LEN ||
        strnlen(t->second, MAX_STRING_LEN) >= MAX_STRING_LEN) {
        return -1;
    }
    
    return 0;
}

int group_tuples(const Tuple tuples[], int tuple_count, Group groups[], int max_groups) {
    int group_count = 0;
    
    if (tuples == NULL || groups == NULL || tuple_count < 0 || 
        max_groups <= 0 || max_groups > MAX_GROUPS) {
        return -1;
    }
    
    memset(groups, 0, sizeof(Group) * max_groups);
    
    for (int i = 0; i < tuple_count; i++) {
        if (validate_tuple(&tuples[i]) != 0) {
            return -1;
        }
        
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
        
        if (idx < 0 || idx >= max_groups) {
            return -1;
        }
        
        if (groups[idx].value_count >= MAX_VALUES_PER_GROUP) {
            return -1;
        }
        
        if (safe_copy_string(groups[idx].values[groups[idx].value_count], 
                            MAX_STRING_LEN, tuples[i].first) != 0) {
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
        if (printf("%s: [", groups[i].key) < 0) {
            return EXIT_FAILURE;
        }
        
        for (int j = 0; j < groups[i].value_count; j++) {
            if (printf("%s", groups[i].values[j]) < 0) {
                return EXIT_FAILURE;
            }
            if (j < groups[i].value_count - 1) {
                if (printf(", ") < 0) {
                    return EXIT_FAILURE;
                }
            }
        }
        
        if (printf("]\n") < 0) {
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}