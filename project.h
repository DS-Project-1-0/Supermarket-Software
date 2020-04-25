#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

typedef struct node{
int id;
char category[500000];
char name[500000];
int qty;
int price;      //unit price of the item
char location[10];
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
    int id;
    char name[500000];//name of the customer
    date bday;//DOB of type date
    char phoneno[11];
    date entry;//current date
    int points;//member's points
    char membership[500000];
    struct customer *next;
}customer;

typedef struct bill{
int customerno;
int billno;
char itemname[500000];
int qty;
int t_price;
struct bill *next;
}bill_det;

void setColor(int);
int correctpass();
void inventory();
int screen1(char);
void customer_entry();
void checkLocation();
void customerDetails();
void generateBill();




#endif // PROJECT_H_INCLUDED
