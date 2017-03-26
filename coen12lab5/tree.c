#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
};

void detach(struct tree *root)/* if the root is connected to a parent, detach it*/
{

    if(root->parent!=NULL)
    {
        if(root->parent->left==root)
        {
            root->parent->left=NULL;

        }
        else if(root->parent->right==root)
        {
            root->parent->right=NULL;

            
        }
    }
    
}

struct tree *createTree(int data, struct tree *left, struct tree *right)
{
    struct tree *tp;
    tp=malloc(sizeof(struct tree));
    
    if(left!=NULL)
    {
    detach(left);
    left->parent=tp;
    }
    tp->left=left;
    
    if(right!=NULL)
    {
    detach(right);
    right->parent=tp;
    }
    tp->right=right;
    tp->parent=NULL;
    tp->data=data;
    return tp;
    
}

void destroyTree(struct tree *root)
{
    if(root!=NULL)
    {

            destroyTree(root->left);
            destroyTree(root->right);
    }
    
    free(root);
}

int getData(struct tree *root)
{
    return root->data;
}

struct tree *getLeft(struct tree *root)
{
    return root->left;
}

struct tree *getRight(struct tree *root)
{
    return root->right;
}

struct tree *getParent(struct tree *root)
{
    return root->parent;
}

void setLeft(struct tree *root, struct tree *left)
{
    if(left!=NULL)
    {
        detach(left);
        left->parent=root;
    }

    root->left = left;
}

void setRight(struct tree *root, struct tree *right)
{
    if(right!=NULL)
    {
        detach(right);
        right->parent=root;
    }

    root->right = right;
}

