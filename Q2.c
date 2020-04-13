#include<stdio.h>
#include<stdlib.h>
#define bool int


struct tNode
{
int data;
struct tNode* left;
struct tNode* right;
};

struct tNode *root=NULL;

struct sNode
{
struct tNode *t;
struct sNode *next;
};


void push(struct sNode** top_ref, struct tNode *t);
struct tNode *pop(struct sNode** top_ref);
bool isEmpty(struct sNode *top);


void inOrder(struct tNode *root)
{

struct tNode *current = root;
struct sNode *s = NULL;
bool done = 0;

while (!done)
{

	if(current != NULL)
	{

	push(&s, current);
	current = current->left;
	}


	else
	{
	if (!isEmpty(s))
	{
		current = pop(&s);
		printf("%d ", current->data);


		current = current->right;
	}
	else
		done = 1;
	}
}
}


void push(struct sNode** top_ref, struct tNode *t)
{

struct sNode* new_tNode =
			(struct sNode*) malloc(sizeof(struct sNode));

if(new_tNode == NULL)
{
	printf("Stack Overflow \n");
	getchar();
	exit(0);
}


new_tNode->t = t;


new_tNode->next = (*top_ref);


(*top_ref) = new_tNode;
}


bool isEmpty(struct sNode *top)
{
return (top == NULL)? 1 : 0;
}


struct tNode *pop(struct sNode** top_ref)
{
struct tNode *res;
struct sNode *top;


if(isEmpty(*top_ref))
{
	printf("Stack Underflow \n");
	getchar();
	exit(0);
}
else
{
	top = *top_ref;
	res = top->t;
	*top_ref = top->next;
	free(top);
	return res;
}
}


struct tNode *insert(struct tNode *root,int element)
{
    if(root==NULL)
    {
        struct tNode *temp=(struct tNode *)malloc(sizeof(struct tNode));
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
printf("\n1. To Insert element in BST\n");
printf("2. For Inorder Tree Traversal\n");
printf("3. Exit\n");
printf("Enter your choice\n");
scanf("%d", &ch);
switch(ch){

case 1: printf("Enter an element to insert\n");
        scanf("%d",&element);
        root=insert(root,element);
        break;
case 2: inOrder(root);
        break;
case 3: exit(0);
default:  printf("You have entered wrong choice");
          break;
}
}
}
