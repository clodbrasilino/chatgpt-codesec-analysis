#include <stdio.h>

struct Node {
    struct Node* children[26];
};

int maxDepth(struct Node* node) {
    if (node == NULL)
        return 0;
    else {
        int max_depth = 0;
        for (int i = 0; i < 26; i++) {
            int child_depth = maxDepth(node->children[i]);
            if (child_depth > max_depth)
                max_depth = child_depth;
        }
        return max_depth + 1;
    }
}

int main() {
    struct Node* root = NULL;
    printf("Depth of tree is %d", maxDepth(root));
    return 0;
}