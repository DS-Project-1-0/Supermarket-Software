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


typedef struct date//to take date as input
{
    int dd;
    int mm;
    int yy;
}date;

typedef struct customer
{
    char name[500000];//name of the customer
    date bday;//DOB of type date
    char phoneno[11];
    date entry;//current date
    int points;//member's points
    int membership;//1-yes and 0-no
    struct node *next;
}customer;

void setColor(int);
int correctpass();
void inventory();
int screen1(char);


#endif // PROJECT_H_INCLUDED
