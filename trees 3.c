//21-24

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* createnode(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return createnode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Define custom min and max values
#define MIN_VAL -100000
#define MAX_VAL 100000

// Check if a tree is a valid BST
int isBSTUtil(struct node* node, int min, int max) {
    if (node == NULL) return 1;
    if (node->data < min || node->data > max) return 0;
    return isBSTUtil(node->left, min, node->data - 1) && isBSTUtil(node->right, node->data + 1, max);
}

int isBST(struct node* root) {
    return isBSTUtil(root, MIN_VAL, MAX_VAL);
}

// Find the height of a BST
int findHeight(struct node* root) {
    if (root == NULL) return -1;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Check if a BST is balanced
int isBalanced(struct node* root) {
    if (root == NULL) return 1;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }
    return 0;
}

// Find the Lowest Common Ancestor (LCA)
struct node* findLCA(struct node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (root->data > n1 && root->data > n2) return findLCA(root->left, n1, n2);
    if (root->data < n1 && root->data < n2) return findLCA(root->right, n1, n2);
    return root;
}

// Convert a sorted array to a balanced BST
struct node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct node* root = createnode(arr[mid]);
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);
    return root;
}

// Convert a sorted linked list to a balanced BST
struct ListNode {
    int data;
    struct ListNode* next;
};

struct node* sortedListToBST(struct ListNode** head_ref, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct node* leftChild = sortedListToBST(head_ref, start, mid - 1);
    struct node* root = createnode((*head_ref)->data);
    root->left = leftChild;
    *head_ref = (*head_ref)->next;
    root->right = sortedListToBST(head_ref, mid + 1, end);
    return root;
}

// Find the k-th smallest element in a BST
int count = 0;
void kthSmallestUtil(struct node* root, int k, int* result) {
    if (root == NULL) return;
    kthSmallestUtil(root->left, k, result);
    count++;
    if (count == k) {
        *result = root->data;
        return;
    }
    kthSmallestUtil(root->right, k, result);
}

int kthSmallest(struct node* root, int k) {
    int result = -1;
    count = 0;
    kthSmallestUtil(root, k, &result);
    return result;
}

// Find the k-th largest element in a BST
void kthLargestUtil(struct node* root, int k, int* result) {
    if (root == NULL) return;
    kthLargestUtil(root->right, k, result);
    count++;
    if (count == k) {
        *result = root->data;
        return;
    }
    kthLargestUtil(root->left, k, result);
}

int kthLargest(struct node* root, int k) {
    int result = -1;
    count = 0;
    kthLargestUtil(root, k, &result);
    return result;
}

// Print nodes at a distance 'k' from a given node
void printKDistance(struct node* root, int k) {
    if (root == NULL) return;
    if (k == 0) {
        printf("%d ", root->data);
        return;
    }
    printKDistance(root->left, k - 1);
    printKDistance(root->right, k - 1);
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    if (isBST(root)) {
        printf("The tree is a valid BST\n");
    } else {
        printf("The tree is not a valid BST\n");
    }

    printf("Height of the tree: %d\n", findHeight(root));

    if (isBalanced(root)) {
        printf("The tree is balanced\n");
    } else {
        printf("The tree is not balanced\n");
    }

    struct node* lca = findLCA(root, 20, 40);
    if (lca) {
        printf("LCA of 20 and 40: %d\n", lca->data);
    } else {
        printf("LCA not found\n");
    }

    int k = 2;  // Change k to a valid value based on the height
    printf("The %d-th smallest element: %d\n", k, kthSmallest(root, k));

    printf("The %d-th largest element: %d\n", k, kthLargest(root, k));

    printf("Nodes at distance %d: ", k);
    printKDistance(root, k);
    printf("\n");

    return 0;
}