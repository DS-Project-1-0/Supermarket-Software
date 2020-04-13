#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node* right;
}node;

//Function to Insert a Node
struct node* insert(node* newnode, int element)
{
    if(newnode==NULL)
    {
        struct node* temp = (node*)malloc(sizeof(struct node));
        temp->data = element;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else if(element < newnode->data)
        newnode->left = insert(newnode->left, element);
    else
        newnode->right = insert(newnode->right, element);
    return newnode;
}

//Function to find Maximum kills by Yatin
int max_kills(node* Node)
{
    if (Node == NULL)
        return 0;
    else
    {

        int lheight = max_kills(Node->left);
        int rheight = max_kills(Node->right);

        if (lheight > rheight)
            return(lheight + 1);
        else
            return(rheight + 1);
    }
}

//Function to find the nodes where Yatin killed the enemies
void Yatin_killed(node* root)
{
    int initial = 0;
    killed(root, &initial, 1);
}

void killed(node* root, int* initial, int max)
{
    if (root == NULL)
        return;

    if (*initial < max) {
        printf("%d\t", root->data);
        *initial = max;
    }

    killed(root->left, initial, max+1);
    killed(root->right, initial, max+1);
}

int main()
{
    int t, i, j, x;
    printf("Enter the Number of Test Cases: ");
    scanf("%d",&t);
    for(j=t; j>0; j--)
    {
    int n;
    printf("Enter Number of Nodes in the Tree: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter The values at each node respectively:\n");
    for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);

    struct node* root=(node*)malloc(sizeof(node));
    root->data = arr[0];
    root->left = NULL;
    root->right = NULL;

    for(i=1;i<n;i++)
        insert(root,arr[i]);

    x = max_kills(root);
    printf("Maximum Possible Kills: ");
    printf("%d\n",x);

    printf("Nodes where Yatin killed: ");
    Yatin_killed(root);
    }
    return 0;
}
