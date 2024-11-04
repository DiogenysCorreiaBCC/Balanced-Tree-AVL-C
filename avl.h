#ifndef BST_H
#define BST_H

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    int bf;
} Node;

typedef Node *Tree;

Tree insert(Tree root, int value, int *grew);
Tree rotation(Tree root);
Tree leftRotation(Tree root);
Tree rightRotation(Tree root);
Tree doubleLeftRotation(Tree root);
Tree doubleRightRotation(Tree root);
void inOrder(Tree root);
Tree remov(Tree root, int value, int *decreased);
Tree biggest(Tree root);
void preOrder(Tree root);
void posOrder(Tree root);

#endif

























































































