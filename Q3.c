#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}node;

node *root=NULL;

bool ifleaf(node *node)
{
    if(node==NULL)
    {
        return 0;
    }
    else if(node->left==NULL && node->right==NULL)
    {
        return 1;
    }
    return 0;
}

node *insert(node *root,int element)
{
    if(root==NULL)
    {
        node *temp=(node *)malloc(sizeof(node));
        temp->data=element;
        temp->left=temp->right=NULL;
        return temp;
    }
    else if(element<root->data)
        root->left=insert(root->left,element);
    else
        root->right=insert(root->right,element);
    return root;
}

int leftsum(node *root)
{
    int sum=0;

    if(root!=NULL)
    {
        if(ifleaf(root->left))
        {
            sum += root->left->data;
        }
        else
        {
            sum += leftsum(root->left);
        }
        sum += leftsum(root->right);
    }

    return sum;
}
void main()
{
    int ch,element;

while(1){
printf("\n1. To insert element in BST\n");
printf("2. To find the sum\n");
printf("3. Exit\n");
printf("Enter your choice\n");
scanf("%d", &ch);
switch(ch){

case 1: printf("Enter an element to insert\n");
        scanf("%d",&element);
        root=insert(root,element);
        break;
case 2: printf(" The sum of the leftmost elements is: \t%d",leftsum(root));
        break;
case 3: exit(0);
default:  printf("You have entered wrong choice");
          break;
}
}
}
