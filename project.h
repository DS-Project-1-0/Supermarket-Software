#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

typedef struct node{
int id;
char category[500000];
char name[500000];
int qty;
int price;      //unit price of the item
struct node *next;
}item;

void setColor(int);
int correctpass();
void inventory();
int screen1(char);



#endif // PROJECT_H_INCLUDED
