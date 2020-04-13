#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct bstnode{
int data;
struct  bstnode *left;
struct  bstnode *right;
}node;

node *root=NULL;

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

void printLeafNodes(node *root)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        printf("%d ",root->data);
        return;
    }

    if (root->left)
       printLeafNodes(root->left);

    if (root->right)
       printLeafNodes(root->right);
}

void maxDiffUtil(node *ptr, int k, int min_diff, int min_diff_key)
{
    if (ptr == NULL)
        return ;

    if (ptr->data == k)
    {
        min_diff_key = k;
        return;
    }

    if (min_diff > abs(ptr->data - k))
    {
        min_diff = abs(ptr->data - k);
        min_diff_key = ptr->data;
    }

    if (k < ptr->data)
        maxDiffUtil(ptr->left, k, min_diff, min_diff_key);
    else
        maxDiffUtil(ptr->right, k, min_diff, min_diff_key);
}

int maxDiff(node *root, int k)
{

    int min_diff = INT_MAX, min_diff_key = -1;
    maxDiffUtil(root, k, min_diff, min_diff_key);
    return min_diff_key;
}
void main()
{
    int ch,element,k;

while(1){
printf("\n1. To insert element in BST\n");
printf("2. To print from left to right node.\n");
printf("3. to search for the closest node for a given value\n4. Exit\n");
printf("Enter your choice\n");
scanf("%d", &ch);
switch(ch){

case 1: printf("Enter an element to insert\n");
        scanf("%d",&element);
        root=insert(root,element);
        break;
case 2: printLeafNodes(root);
        break;
case 3: printf("Enter an element to insert\n");
        scanf("%d",&k);
        printf("Closest Node is %d",maxDiff(root,k));
        break;
case 4: exit(0);
default:  printf("You have entered wrong choice");
          break;
}
}
}
