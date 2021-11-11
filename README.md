# <ins>**Supermarket-Software**</ins>
# Description
It is a shopping store management software.The software is made to be operated by both the customer and the administrator. The whole program has been modulated into a number of functions and dynamic memory allocation has been used to make it efficient and user friendly. <br/>
The .csv files are automatically updated to keep the stocks ,customer details and bill records up to date.

This software has been created through **C**.

## Structs Defined

### <ins>1. typedef struct node</ins>
This stores the item and contains attributes for the item.


### <ins>2. typedef struct date</ins>
This stores the date. Each structure contains date, month, year. 


### <ins>3. typedef struct customer</ins>
Customer struct stores the details of customer and the attributes for those customers.


### <ins>4. typedef struct bill_det</ins>
This stores information of each invoice generated.


### <ins> 5. typedef struct bill</ins>
Stores the details of the final bill of the current customer.



## Objective

### [Project](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Project.h)
----
This is a header file that contains the definition of each struct and declaration of every function used in the software.<br />

### [Project file](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Project%20file.c)
----
This initializes the software and presents the dashboard and asks whether the user is an admin or customer.

### [Functions](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Functions.c)
----
This class performs all the DS operation on the data, read and write Files. This acts as the backend of the software.

**<ins>Member Functions</ins>**

**1. void setColor(int);**<br />
This function has been used to change the font color on the console.<br /><br />
**2. void correctpass();**<br />
It displays the main menu to the admin when correct password is entered.<br /><br />
**3. void inventory();**<br />
It displays the Inventory/list of all items to the admin.<br /><br />
**4. void screen1(char);**<br />
(a)It takes a character input as argument which tells whether the user is a customer or admin.<br />
(b)This function reads all the files used in the program and also shows the respective opening screens for customer and admin.<br /><br />
**5. void customer_entry();**<br />
It displays the main menu to the customer and asks whether he wants to check item location or generate the bill.<br /><br />
**6. void checkLocation();**<br />
It shows the location of a particular item in the store to the customer.<br /><br />
**7. void customerDetails();**<br />
It displays the details of the customers to the admin.<br /><br />
**8. void generateBill();**<br />
It facilitates the user to choose the items to buy and then modify according to his needs and finally generate the total amount to be paid.<br /><br />
**9. void update_details(int);**<br />
This function updates all the values in the appropriate .csv files from the recent updates in the linked lists with the help of the parameter passed which tells which file has to be updated.<br /><br />
**10. void offerzone();**<br />
It displays the offerzone and all the discounts to the customer who is currently not a member.<br /><br />
**11. void invoice(int,int);**<br />
(a)It takes two integer arguments as input, it takes the total bill amount and Bill number from the generateBill() function .<br />
(b)This function generates the final invoice, it shows the bill summary the final amount to be paid after application of valid discounts.<br /><br />
**12.void billDetails();**<br />
This function generates prints the items bought by a customer by matching the records in the files using the phone number.<br /><br />
**13.void addItems();**<br />
This function allows the admin to insert a new item by creating a new category or inserting them in the already existing ones.<br /><br />
**14.void statistics();**<br />
This function allows the admin to view the statistics :total sales,inventory stock,ratings and total members of each type of membership.<br /><br />

## CSV Files

| CSV File | Link |
| :---: | :---: |
| Bill | [https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Bill.csv](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Bill.csv)
| Bill Details | [https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Bill_details.csv](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Bill_details.csv)
| Customer Details | [https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Customer_details.csv](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Customer_details.csv)
| Inventory | [https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Inventory.csv](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Inventory.csv)


# Local Setup

## Pre-Requisites
An IDE that supports C.
## Installation and Execution
1. Pull this code into any folder.<br />
2. Open this folder in your preferred IDE.<br />
3. Build the Project.<br />
4. Run the [Project file.c](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/Project%20file.c) file and your dashboard for the application will be displayed.<br />


# Screenshots
To check the outputs go to the [album](https://github.com/DS-Project-1-0/Supermarket-Software/blob/master/OUTPUT%20ALBUM.pptx).

# Contact
## [Aditya Srivastava](mailto:aditya26052002@gmail.com?subject=GitHub)<br/><br/>[Samriddhi Panwar](mailto:samriddhipanwaren@gmail.com?subject=GitHub)<br/><br/>Jayati Sharma<br/><br/>Ansh Gupta<br/><br/>
