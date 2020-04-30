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
    int rate;
    struct customer *next;
}customer;

typedef struct bill_det{
int customerno;
int billno;
char itemname[500000];
int qty;
int t_price;
date cur_date;
struct bill_det *next;
}bill_det;

typedef struct bill{
int customerno;
int billno;
int total_price;
date cur_date;
struct bill *next;
}bill;


void setColor(int);
void screen1(char);
void correctpass();
void inventory();
void customerDetails();
void statistics();
void billDetails();
void customer_entry();
void checkLocation();
void generateBill();
void update_details();
void offerzone();
void invoice(int,int);



#endif // PROJECT_H_INCLUDED

