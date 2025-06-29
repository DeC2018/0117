#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for a Node.
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct Node* connect(struct Node* root) {
    if (root == NULL)
        return NULL;

    struct Node *current = root;
    while (current) {
        struct Node *dummy = malloc(sizeof(struct Node));
        dummy->next = NULL; 
        struct Node *temp = dummy;

        while (current) {
            if (current->left) {
                temp->next = current->left;
                temp = temp->next;
            }
            if (current->right) {
                temp->next = current->right;
                temp = temp->next;
            }
            current = current->next;
        }

        current = dummy->next;
        free(dummy);
    }

    return root;
}

// Helper function to create a new node
struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

// Helper function to create a tree from an array
struct Node* createTree(int* nodes, int size, int index) {
    if (index >= size || nodes[index] == -1) {
        return NULL;
    }
    struct Node* root = newNode(nodes[index]);
    root->left = createTree(nodes, size, 2 * index + 1);
    root->right = createTree(nodes, size, 2 * index + 2);
    return root;
}

// Helper function to print the connected tree in the required format
void printConnectedTree(struct Node* root) {
    if (!root) {
        printf("[]\n");
        return;
    }
    
    printf("[");
    struct Node* levelStart = root;
    
    while (levelStart) {
        struct Node* current = levelStart;
        while (current) {
            printf("%d,", current->val);
            current = current->next;
        }
        printf("#,");
        
        // Find the first node of the next level
        struct Node* nextLevelStart = NULL;
        current = levelStart;
        while (current && !nextLevelStart) {
            if (current->left) nextLevelStart = current->left;
            else if (current->right) nextLevelStart = current->right;
            current = current->next;
        }
        levelStart = nextLevelStart;
    }
    
    // Remove trailing comma
    printf("\b \b"); // Backspace to remove last comma
    printf("]\n");
}

int main() {
    // Test case 1
    int nodes1[] = {1, 2, 3, 4, 5, -1, 7};
    int size1 = sizeof(nodes1) / sizeof(nodes1[0]);
    struct Node* root1 = createTree(nodes1, size1, 0);
    struct Node* connected1 = connect(root1);
    printf("Input: root = [1,2,3,4,5,null,7]\n");
    printf("Output: ");
    printConnectedTree(connected1);

    // Test case 2
    int* nodes2 = NULL;
    int size2 = 0;
    struct Node* root2 = createTree(nodes2, size2, 0);
    struct Node* connected2 = connect(root2);
    printf("Input: root = []\n");
    printf("Output: ");
    printConnectedTree(connected2);

    return 0;
}
