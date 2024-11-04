#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


Tree insert(Tree root, int value, int *grew){
    if(root == NULL){
        Tree newNode = (Tree) malloc(sizeof(Node));
        newNode->key = value;
        newNode->bf = 0;
        newNode->left = NULL;
        newNode->right = NULL;
        *grew = 1;

        return newNode;
    }else{
        if(value < root->key){
            *grew = 0;
            root->left = insert(root->left, value, grew);

            if(*grew){
                switch(root->bf){
                    case 1:
                        root->bf = 0;
                        *grew = 0;
                        break;
                    case 0:
                        root->bf = -1;
                        *grew = 1;
                        //printf("\nEsquerda do %d cresceu!", root->key);
                        break;
                    case -1:
                        *grew = 0;
                        return rotation(root);
                }
            }
        }else{
            *grew = 0;
            root->right = insert(root->right, value, grew);
                
            if(*grew){
                switch(root->bf){
                    case 1:
                        *grew = 0;
                        return rotation(root);
                        break;
                    case 0:
                        root->bf = 1;
                        *grew = 1;
                        //printf("\nDireita do %d cresceu!", root->key);
                        break;
                    case -1:
                        root->bf = 0;
                        *grew = 0;
                        break;
                }
            }
        }

        return root;
    }
    
    return root;    
}

Tree rotation(Tree root){
    Tree p = root;
    Tree u, v;

    if(p->bf > 0){
        u = p->right;
        if(u->bf >= 0){
            //RSE
            if(u->bf == 1){   
                u->bf = 0;
                p->bf = 0;
            }else{
                u->bf = -1;
                p->bf = 1;
            }

            return leftRotation(root);
        }else{
            //RDE
            v = u->left;
            switch(v->bf){
                case -1:
                    p->bf = 0;
                    u->bf = 1;
                    v->bf = 0;
                    break;
                case 0:
                    p->bf = 0;
                    u->bf = 0;
                    v->bf = 0;
                    break;
                case 1:
                    p->bf = -1;
                    u->bf = 0;
                    v->bf = 0;
                    break;
            }
            
            return doubleLeftRotation(root);
        }
        
    }else{
        u = p->left;
        if(u->bf <= 0){
            //RSD
            if(u->bf == -1){
                p->bf = 0;
                u->bf = 0;
            }else{
                p->bf = -1;
                u->bf = 1;
            }

            return rightRotation(root);
        }else{
            //RDD
            v = u->right;
            switch(v->bf){
                case -1:
                    p->bf = 1;
                    u->bf = 0;
                    v->bf = 0;
                    break;
                case 0:
                    p->bf = 0;
                    u->bf = 0;
                    v->bf = 0;
                    break;
                case 1:
                    p->bf = 0;
                    u->bf = -1;
                    v->bf = 0;
                    break;
            }
    
            return doubleRightRotation(root);
        }
    }
}

Tree leftRotation(Tree root){
    Tree p = root;
    Tree u = p->right;
    Tree t2 = u->left;
    
    //printf("\nRSE-%d", root->key);

    u->left = p;
    p->right = t2;

    return u;
}

Tree rightRotation(Tree root){
    Tree p = root;
    Tree u = p->left;
    Tree t2 = u->right;

    //printf("\nRSD-%d", root->key);

    u->right = p;
    p->left = t2;

    return u;
}

Tree doubleLeftRotation(Tree root){
    Tree p = root;
    Tree u = p->right;
    Tree v = u->left;
    Tree t2 = v->left;
    Tree t3 = v->right;

    //printf("\nRDE-%d", root->key);

    v->left = p;
    v->right = u;
    p->right = t2;
    u->left = t3;
    
    return v;
}

Tree doubleRightRotation(Tree root){
    Tree p = root;
    Tree u = p->left;
    Tree v = u->right;
    Tree t2 = v->left;
    Tree t3 = v->right;

    //printf("\nRDD-%d", root->key);

    v->left = u;
    v->right = p;
    u->right = t2;
    p->left = t3;

    return v;
}

void inOrder(Tree root){
    if(root){
        inOrder(root->left);
        printf("[%d]", root->key);
        inOrder(root->right);
    }
}

void preOrder(Tree root){
    if(root){
        printf("[%d %d]", root->key, root->bf);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void posOrder(Tree root){
    if(root){
        posOrder(root->left);
        posOrder(root->right);
        printf("[%d]", root->key);
    }
}

Tree remov(Tree root, int value, int *decreased){
    if(root == NULL){
        return NULL;
    }

    if(root->key == value){
        //Programação do ogro:
        if(root->left == root->right){
            free(root);
            *decreased = 1;
            return NULL;
        }

        if(root->left != NULL && root->right == NULL){
            Tree temp = root->left;
            free(root);
            *decreased = 1;
            return temp;
        }

        if(root->left == NULL && root->right == NULL){
            Tree temp = root->right;
            free(root);
            *decreased = 1;
            return temp;
        }

        if(root->left != NULL && root->right != NULL){
            Tree bigger = biggest(root->left);
            root->key = bigger->key;
            root->left = remov(root->left, bigger->key, decreased);
            return root;
        }
    }

    if(value < root->key){
        root->left = remov(root->left, value, decreased);

        if(*decreased){
            switch(root->bf){
                case -1:
                    root->bf = 0;
                    *decreased = 1;
                    //printf("\nEsquerda do %d Diminuiu!", root->key);
                    break;
                case 0:
                    root->bf = 1;
                    *decreased = 0;
                    break;
                case 1:
                    root->bf = 2;
                    return rotation(root);
            }
        }
    }else{
        root->right = remov(root->right, value, decreased);
        
        if(*decreased){
            switch(root->bf){
                case -1:
                    root->bf = -2;
                    return rotation(root);
                case 0:
                    root->bf = -1;
                    *decreased = 0;
                    break;
                case 1:
                    root->bf = 0;
                    *decreased = 1;
                    //printf("\nDireita do %d Diminuiu!", root->key);
                    break;
            }
        }
    }

    return root;
}

Tree biggest(Tree root){
    Tree temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }

    return temp;
}















