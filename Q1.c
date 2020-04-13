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
    int lh;
    int rh;
    if(node ==NULL)
    {
        return 0;
    }
    else
    {
        lh=height(node->left);
        rh=height(node->right);

        if(lh>rh)
        {
            return (lh + 1);
        }
        else
        {
            return (rh + 1);
        }
    }
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
void main()
{
    int ch,element;

while(1){
printf("\n1. To insert element in BST\n");
printf("2. To find the height\n");
printf("3. Exit\n");
printf("Enter your choice\n");
scanf("%d", &ch);
switch(ch){

case 1: printf("Enter an element to insert\n");
        scanf("%d",&element);
        root=insert(root,element);
        break;
case 2: printf("The height of the tree is %d\n",height(root));
        break;
case 3: exit(0);
default:  printf("You have entered wrong choice");
          break;
}
}
}



