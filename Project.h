#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

typedef struct node
{
    int id;                  // stores the item id
    char category[500000];   // stores the category name
    char name[500000];       // stores the item name
    int qty;                 // stores the quantity of item
    int price;               // stores unit price of the item
    char location[10];       // stores the location of the item
    struct node *next;       // pointer to next node
}item;                       // typedef item

typedef struct date         //to take date as input
{
    int dd;                 // stores the date
    int mm;                 // stores the month
    int yy;                 // stores the year
}date;                      // typedef date

typedef struct customer
{
    int id;                 // stores the customer id
    char name[500000];      // stores the name of the customer
    date bday;              // stores the DOB of the customer of type date
    char phoneno[11];       // stores the phone no of the customer
    date entry;             // stores the date of customer entry
    int points;             // stores the member's points
    char membership[500000];// stores the type of membership
    int rate;               // stores the rating given by the user
    struct customer *next;  // pointer to next node
}customer;                  // typedef customer

typedef struct bill_det
{
    int customerno;         // stores the customer no
    int billno;             // stores the bill no
    char itemname[500000];  // stores the item name
    int qty;                // stores the quantity
    int t_price;            // stores the price
    date cur_date;          // store the bill generation date
    struct bill_det *next;  // pointer to the next node
}bill_det;                  // typedef bill_det

typedef struct bill
{
    int customerno;         // stores the customer no
    int billno;             // stores the bill no
    float total_price;      // stores the total_price paid by customer
    date cur_date;          // store the bill generation date
    struct bill *next;      // pointer to the next node
}bill;                      // typedef bill

void setColor(int);         // use to change colour of text
void screen1(char *);         // storing data in linked list
void correctpass();         // login page
void inventory();           // viewing inventory stocks
void customerDetails();     // related to customer details
void statistics();			// related to stats of the stocks and sales
void billDetails();			// shows items bought by the customer
void addItems();            // add more items to the inventory
void customer_entry();      // displays the options to customer to check location,generate bill or log out
void checkLocation();       // checking location of the items
void generateBill();        // bill related options of modify and delete quantities
void update_details(int);      // updating the details in the customer's account
void offerzone();           // displays the memberships and discounts
void invoice(int,int);      // generates invoice



#endif // PROJECT_H_INCLUDED
