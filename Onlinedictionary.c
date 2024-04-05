#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for Binary Search Tree node
struct BSTnode {
    char word[128];
    char meaning[256];
    struct BSTnode *left;
    struct BSTnode *right;
};

// Global root node
struct BSTnode *root = NULL;

// Function prototypes
struct BSTnode *createNode(char *word, char *meaning);
void insertWord(char *word, char *meaning);
void deleteWord(char *word);
void searchWord(char *word);
void traverseBST(struct BSTnode *root);
struct BSTnode *findMin(struct BSTnode *node);
struct BSTnode *deleteNode(struct BSTnode *root, char *word);

int main() {
    int choice;
    char word[128], meaning[256];

    // Menu-driven interface
    while (1) {
        printf("\n===== Dictionary Menu =====\n");
        printf("1. Insert Word\n");
        printf("2. Delete Word\n");
        printf("3. Search Word\n");
        printf("4. Display All Words\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the word to insert: ");
                scanf(" %[^\n]", word);
                printf("Enter the meaning: ");
                scanf(" %[^\n]", meaning);
                insertWord(word, meaning);
                break;
            case 2:
                printf("Enter the word to delete: ");
                scanf(" %[^\n]", word);
                deleteWord(word);
                break;
            case 3:
                printf("Enter the word to search: ");
                scanf(" %[^\n]", word);
                searchWord(word);
                break;
            case 4:
                printf("List of all words:\n");
                traverseBST(root);
                break;
            case 5:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}

// Function to create a new node
struct BSTnode *createNode(char *word, char *meaning) {
    struct BSTnode *newNode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a word into the dictionary
void insertWord(char *word, char *meaning) {
    struct BSTnode *parent = NULL, *current = NULL, *newNode = NULL;
    int comparison = 0;

    // If tree is empty, create root node
    if (!root) {
        root = createNode(word, meaning);
        return;
    }

    // Traverse the tree to find the appropriate position to insert the new word
    for (current = root; current != NULL; current = (comparison > 0) ? current->right : current->left) {
        comparison = strcasecmp(word, current->word);
        if (comparison == 0) {
            printf("Sorry, the word already exists in the dictionary.\n");
            return;
        }
        parent = current;
    }

    // Create the new node and attach it to the appropriate position
    newNode = createNode(word, meaning);
    if (comparison > 0) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
}

// Function to delete a word from the dictionary
void deleteWord(char *word) {
    root = deleteNode(root, word);
}

// Function to search for a word in the dictionary
void searchWord(char *word) {
    struct BSTnode *current = root;
    int comparison;

    while (current != NULL) {
        comparison = strcasecmp(word, current->word);
        if (comparison == 0) {
            printf("Word: %s\n", current->word);
            printf("Meaning: %s\n", current->meaning);
            return;
        } else if (comparison < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    printf("Word not found in the dictionary.\n");
}

// Function to traverse the BST in-order
void traverseBST(struct BSTnode *root) {
    if (root != NULL) {
        traverseBST(root->left);
        printf("Word: %s\n", root->word);
        printf("Meaning: %s\n", root->meaning);
        printf("\n");
        traverseBST(root->right);
    }
}

// Function to find the minimum node in a subtree
struct BSTnode *findMin(struct BSTnode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node from the BST
struct BSTnode *deleteNode(struct BSTnode *root, char *word) {
    if (root == NULL) {
        return root;
    }
    int comparison = strcasecmp(word, root->word);
    if (comparison < 0) {
        root->left = deleteNode(root->left, word);
    } else if (comparison > 0) {
        root->right = deleteNode(root->right, word);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct BSTnode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BSTnode *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct BSTnode *temp = findMin(root->right);
        // Copy the inorder successor's content to this node
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}
