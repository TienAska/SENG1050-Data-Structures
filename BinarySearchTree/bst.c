#include <stdio.h>
#include <stdlib.h>

typedef struct DataNode {
    int Element;
    struct DataNode* LeftChild;
    struct DataNode* RightChild;
} DataNode;

//prototypes
DataNode* InitializeDataNode(int element);
DataNode* InsertElementIntoBST(DataNode* root, int elementToInsert);
int SearchElementInBST(DataNode* root, int elementToSearch);
DataNode* DeleteLeftMostLeafNode(DataNode* root);
void printPreOrder(DataNode* root);



int main(int argc, const char* argv[]) {
    DataNode* root = NULL;
    root = InsertElementIntoBST(root, 50);
    InsertElementIntoBST(root, 70);
    InsertElementIntoBST(root, 30);
    InsertElementIntoBST(root, 40);
    InsertElementIntoBST(root, 20);
    printPreOrder(root);
    printf("\n");
    root = DeleteLeftMostLeafNode(root);
    int element = SearchElementInBST(root, 20);
    if (element < 0) {
        printf("Search Failure");
    }

    return 0;
}
/*
* Function: InitializeDataNode(int)
*/
DataNode* InitializeDataNode(int element) {
    DataNode* node = (DataNode*)malloc(sizeof(DataNode));
    if (node == NULL) {
        printf("EOM");
        exit(EXIT_FAILURE);
    }

    node->Element = element;
    node->LeftChild = NULL;
    node->RightChild = NULL;
    return node;
}

/*
* Function: InsertElementIntoBST(DataNode *, int)
*/
DataNode* InsertElementIntoBST(DataNode* parent, int elementToInsert) {
    if (parent == NULL) { // This means your tree is empty, create a new node and treat it as root
        return InitializeDataNode(elementToInsert);
    }

    //Check if you should insert the node to the left
    if (elementToInsert < parent->Element) {
        parent->LeftChild = InsertElementIntoBST(parent->LeftChild, elementToInsert);
    }
    else if (elementToInsert > parent->Element) {
        parent->RightChild = InsertElementIntoBST(parent->RightChild, elementToInsert);
    }

    return parent;
}
/*
* Function: SearchElementInBST(DataNode *, int)
*/
int SearchElementInBST(DataNode* root, int elementToSearch) {
    if (root == NULL) {
        printf("Tree is Empty. Cannot Perform Search!");
        return -1;
    }

    if (root->Element == elementToSearch) {
        return root->Element;
    }

    if (elementToSearch < root->Element) {
        return SearchElementInBST(root->LeftChild, elementToSearch);
    }
    else if (elementToSearch > root->Element) {
        return SearchElementInBST(root->RightChild, elementToSearch);
    }

    return -1;
}
/*
* Function: DeleteLeftMostLeafNode(DataNode *)
*/
DataNode* DeleteLeftMostLeafNode(DataNode* root) {
    if (root == NULL) {
        printf("Tree is Empty. Cannot Perform Delete!");
        return NULL;
    }

    if (root->LeftChild == NULL && root->RightChild == NULL) {
        free(root);
        return NULL;
    }

    if (root->LeftChild != NULL) {
        root->LeftChild = DeleteLeftMostLeafNode(root->LeftChild);
    }

    return root;
}

void printPreOrder(DataNode* root)
{
    if (root == NULL)
        return;

    // Visit Node

    printf("%d ", root->Element);

    // Traverse left subtree
    printPreOrder(root->LeftChild);

    // Traverse right subtree
    printPreOrder(root->RightChild);

    
}
