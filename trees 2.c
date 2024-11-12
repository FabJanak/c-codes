//11-20

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

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Flatten BST to Sorted Linked List
void flattenBST(struct node* root, struct node** prev) {
    if (root == NULL) return;
    flattenBST(root->left, prev);
    root->left = NULL;
    if (*prev != NULL) {
        (*prev)->right = root;
    }
    *prev = root;
    flattenBST(root->right, prev);
}

void printFlattenedList(struct node* root) {
    struct node* curr = root;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

// Mirror of BST
struct node* mirrorBST(struct node* root) {
    if (root == NULL) return NULL;

    struct node* mirrored = createnode(root->data);
    mirrored->left = mirrorBST(root->right);
    mirrored->right = mirrorBST(root->left);
    return mirrored;
}

// Merge Two BSTs
void storeInorder(struct node* root, int* arr, int* index) {
    if (root == NULL) return;
    storeInorder(root->left, arr, index);
    arr[(*index)++] = root->data;
    storeInorder(root->right, arr, index);
}

void mergeArrays(int* arr1, int n1, int* arr2, int n2, int* mergedArr) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            mergedArr[k++] = arr1[i++];
        } else {
            mergedArr[k++] = arr2[j++];
        }
    }
    while (i < n1) {
        mergedArr[k++] = arr1[i++];
    }
    while (j < n2) {
        mergedArr[k++] = arr2[j++];
    }
}

struct node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct node* root = createnode(arr[mid]);
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);
    return root;
}

struct node* mergeBSTs(struct node* root1, struct node* root2) {
    int arr1[100], arr2[100], mergedArr[200];
    int n1 = 0, n2 = 0;
    storeInorder(root1, arr1, &n1);
    storeInorder(root2, arr2, &n2);
    mergeArrays(arr1, n1, arr2, n2, mergedArr);
    return sortedArrayToBST(mergedArr, 0, n1 + n2 - 1);
}

// Find Successor and Predecessor
void findPredecessor(struct node* root, struct node** predecessor, int key) {
    if (root == NULL) return;

    if (root->data < key) {
        *predecessor = root;
        findPredecessor(root->right, predecessor, key);
    } else {
        findPredecessor(root->left, predecessor, key);
    }
}

void findSuccessor(struct node* root, struct node** successor, int key) {
    if (root == NULL) return;

    if (root->data > key) {
        *successor = root;
        findSuccessor(root->left, successor, key);
    } else {
        findSuccessor(root->right, successor, key);
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

    printf("Inorder traversal of the original tree: ");
    inorder(root);
    printf("\n");

    struct node* prev = NULL;
    flattenBST(root, &prev);
    printf("Flattened BST to linked list: ");
    printFlattenedList(root);
    printf("\n");

    struct node* mirrored = mirrorBST(root);
    printf("Inorder traversal of the mirrored tree: ");
    inorder(mirrored);
    printf("\n");

    struct node* root2 = NULL;
    root2 = insert(root2, 25);
    root2 = insert(root2, 15);
    root2 = insert(root2, 35);
    root2 = insert(root2, 5);

    struct node* mergedBST = mergeBSTs(root, root2);
    printf("Inorder traversal of the merged BST: ");
    inorder(mergedBST);
    printf("\n");

    struct node* predecessor = NULL;
    struct node* successor = NULL;
    int key = 40;

    findPredecessor(root, &predecessor, key);
    findSuccessor(root, &successor, key);

    if (predecessor != NULL)
        printf("Predecessor of %d: %d\n", key, predecessor->data);
    else
        printf("No predecessor for %d\n", key);

    if (successor != NULL)
        printf("Successor of %d: %d\n", key, successor->data);
    else
        printf("No successor for %d\n", key);

    return 0;
}