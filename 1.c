#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}node;

node *root=NULL;
int height(node *node)
{
    int lheight;
    int rheight;
    if(node ==NULL)
    {
        return 0;
    }
    else
    {
        lheight=height(node->left);
        rheight=height(node->right);

        if(lheight>rheight)
        {
            return (lheight + 1);
        }
        else
        {
            return (rheight + 1);
        }
    }
}
node *AddNode(int i,node *root)
{
    if(root==NULL)
    {
        node *temp=(node*)malloc(sizeof(node));
        temp->data=i;
        temp->left=temp->right=NULL;
        return temp;
    }
    else if(i < root->data)
    {
        root->left = AddNode(i,root->left);
    }
    else
    {
        root->right = AddNode(i,root->right);
    }
    return root;
}
void main()
{
    root=AddNode(13,root);
    root->left=AddNode(24,root->left);
    root->right=AddNode(6,root->right);
    root->left->left=AddNode(17,root->left->left);
    root->left->right=AddNode(12,root->left->right);


    printf("The height of the tree is %d\n",height(root));

}

