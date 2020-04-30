#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#define size 5   //size of the password
#include"project.h"

item *head1=NULL;//head1 for inventory and head1 for checkLocation
customer *head2=NULL;
bill_det *head3=NULL;
bill *head4=NULL;
int counter=0;
FILE *fp1=NULL;//file pointer used in details()
FILE *fp=NULL;//file pointer used in inventory()
FILE *fp2=NULL;
FILE *fp3=NULL;
int we=0,wp=0,wf=0,wd=0;

//function to change the color
void setColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

//login
void screen1(char ch)
{
	char c;//gets the password
	int ctr=0;//counter
	int i,k,l;//loop counter variables
	int t;//gets choice
	char password[10];//array for getting the password
	int g=1;//for do while

	if(we==0)//For Inventory File
    {
        fp=fopen("Inventory.csv","r");

        if(fp==NULL)
        {
            setColor(12);
            printf("File did not open successfully");
            setColor(15);
            exit(0);
        }

        rewind(fp);//moves the files to the beginning

        char Line[sizeof(item)];//contains a single line of file
        fgets(Line,sizeof(item),fp);
        char* delimiter=",";//to separate data by commas
        item *ptr=head1;

        while(fgets(Line,sizeof(item),(FILE *)fp)!=NULL)
        {
            item *temp=(item *)malloc(sizeof(item));    //allocating memory
            temp->id=atoi(strtok(Line,delimiter)); //storing the item id
            strcpy(temp->category,strtok(NULL,delimiter));//storing the category
            strcpy(temp->name,strtok(NULL,delimiter));//storing the name
            strcpy(temp->location,strtok(NULL,delimiter));//storing the location
            temp->qty=atoi(strtok(NULL,delimiter));//storing the qty
            temp->price=atoi(strtok(NULL,delimiter));//storing the price
            temp->next=NULL;//next pointer

            if(head1==NULL)         //checking if the list is empty and first node has to be inserted
            {
                head1=temp;
            }
            else
            {
                ptr=head1;
                while(ptr->next!=NULL)
                {

                    ptr=ptr->next;      //reaching the end of the list
                }
                ptr->next=temp;
            }

        }

        fclose(fp);     //closing the file
        we=1;
    }

    if(wp==0)
    {
        fp1=fopen("Customer_details.csv", "r");

        if(fp1==NULL)
        {
            setColor(12);
            printf("File did not open successfully");
            setColor(15);
            exit(0);
        }

        rewind(fp1);//takes the file pointer back to the starting of the file

        char Line[sizeof(customer)];//one line of file containing a customer's details
        fgets(Line,sizeof(customer),fp1);
        char* delimiter=",";//separates the data in a line

        customer *ptr=head2;
        //transferring the data from the file to the linked list

        while(fgets(Line,sizeof(customer),(FILE *)fp1)!=NULL)
        {
            customer *temp=(customer *)malloc(sizeof(customer));
            temp->id=atoi(strtok(Line,delimiter));
            strcpy(temp->name,strtok(NULL,delimiter));
            temp->bday.dd=atoi(strtok(NULL,delimiter));
            temp->bday.mm=atoi(strtok(NULL,delimiter));
            temp->bday.yy=atoi(strtok(NULL,delimiter));
            strcpy(temp->phoneno,strtok(NULL,delimiter));
            temp->entry.dd=atoi(strtok(NULL,delimiter));
            temp->entry.mm=atoi(strtok(NULL,delimiter));
            temp->entry.yy=atoi(strtok(NULL,delimiter));
            strcpy(temp->membership,strtok(NULL,delimiter));
            temp->points=atoi(strtok(NULL,delimiter));
            temp->rate=atoi(strtok(NULL,delimiter));
            temp->next=NULL;

            if(head2==NULL)//For entering first node
            {
                head2=temp;
            }
            else  // for adding new nodes
            {
                ptr=head2;
                while(ptr->next!=NULL)
                {
                    ptr=ptr->next;
                }
                ptr->next=temp;
            }
        }

        fclose(fp1);
        wp=1;
    }

    if(wf==0)
    {
        fp2=fopen("Bill_details.csv", "r");

        if(fp2==NULL)
        {
            setColor(12);
            printf("File did not open successfully");
            setColor(15);
            exit(0);
        }

        rewind(fp2);//takes the file pointer back to the starting of the file

        char Line[sizeof(bill_det)];//one line of file containing a customer's details
        fgets(Line,sizeof(bill_det),fp2);
        char* delimiter=",";//separates the data in a line

        bill_det *ptr=head3;

        while(fgets(Line,sizeof(bill_det),(FILE *)fp2)!=NULL)
        {
            bill_det *temp=(bill_det *)malloc(sizeof(bill_det));
            temp->customerno=atoi(strtok(Line,delimiter));
            temp->billno=atoi(strtok(NULL,delimiter));
            strcpy(temp->itemname,strtok(NULL,delimiter));
            temp->qty=atoi(strtok(NULL,delimiter));
            temp->t_price=atoi(strtok(NULL,delimiter));
            temp->cur_date.dd=atoi(strtok(NULL,delimiter));
            temp->cur_date.mm=atoi(strtok(NULL,delimiter));
            temp->cur_date.yy=atoi(strtok(NULL,delimiter));
            temp->next=NULL;

            if(head3==NULL)//For entering first node
            {
                head3=temp;
            }
            else  // for adding new nodes
            {
                ptr=head3;
                while(ptr->next!=NULL)
                {
                    ptr=ptr->next;
                }
                ptr->next=temp;
            }

        }

        fclose(fp2);
        wf=1;
    }

  /*if(wd==0)//For Inventory File
    {
        fp3=fopen("Bill.csv","r");

        if(fp3==NULL)
        {
            setColor(12);
            printf("File did not open successfully");
            setColor(15);
            exit(0);
        }

        rewind(fp3);//moves the files to the beginning

        char Line[sizeof(bill)];//contains a single line of file
        fgets(Line,sizeof(bill),fp3);
        char* delimiter=",";//to separate data by commas
        //bill *ptr=head4;

        while(fgets(Line,sizeof(bill),(FILE *)fp3)!=NULL)
        {
            bill *temp=(bill *)malloc(sizeof(bill));
            temp->customerno=atoi(strtok(Line,delimiter));
            temp->billno=atoi(strtok(NULL,delimiter));
            temp->total_price=atoi(strtok(NULL,delimiter));
            temp->cur_date.dd=atoi(strtok(NULL,delimiter));
            temp->cur_date.mm=atoi(strtok(NULL,delimiter));
            temp->cur_date.yy=atoi(strtok(NULL,delimiter));
            temp->next=NULL;

            if(head4==NULL)//For entering first node
            {
                head4=temp;
            }
            else  // for adding new nodes
            {
                ptr=head4;
                while(ptr->next!=NULL)
                {
                    ptr=ptr->next;
                }
                ptr->next=temp;
            }

        }

        fclose(fp3);
        wd=1;
        bill *mtr=head4;
        while(mtr!=NULL)
          printf("%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);

    }*/

        //checking if the user is the ADMIN
    if(ch=='a' || ch=='A')
	{
		for(k=0;k<3;k++)
		{
			printf("\n Enter the password\t"); //asking him to enter the password

			for( i = 0;;)
			{
			    c = getch();

			    if((c>='A' && c<='Z') ||(c>='a' && c<='z'))
                {
                    password[i] = c;
                    i++;
                    printf("*");            //the password is printed as astricks
                }

                if(c=='\b' && i>=1)
                {
                    printf("\b \b");        //in case the user wishes to erase a character he entered
                    --i;
                }

                if(c=='\r')
                {
                    password[i]='\0';       // the password is submitted once carriage return is encountered
                    break;
                }

			}

			if(!strcmp(password,"ADMIN"))       //the correct password is ADMIN
			{
                setColor(98);//changes the color of following text to green
                printf("\n\n\n ACCESS GRANTED");
                setColor(15);//sets the color of text to white again
                correctpass();
                break;
			}
			else
            {
                setColor(12);//Sets the color of following text to red
                printf("\n ACCESS DENIED");
                setColor(15);//Sets the color of following text to white again
                ctr++;

                if(ctr==3)      // when the user enters the password incorrect 3 times
                {
                    setColor(12);
                    printf("\n\n\n ACCESS LOCKED!! CONTACT SERVER"); //
                    setColor(15);
                }
                else
                {   //upon entering the  password incorrect three times he can retry or see the entered password
                    do
                    {
                        g=0;
                        printf("\n 1.Try Again.\n 2.Show password");
                        printf("\n Enter your choice:	");
                        scanf(" %d",&t);

                        if(t==1)
                        {
                            continue;
                        }
                        else if(t==2)
                        {
                            printf(" ");
                            for(l = 0;l<size;l++)
                                printf("%c", password[l]);
                            printf("\n");
                        }
                        else
                        {
                           setColor(12);
                           printf("\n\n INVALID SELECTION!\n\n");
                           setColor(15);
                           g=1;
                        }

                    }while(g==1);
                }

            }
        }
    }
    //if the user is a customer a different interface is there
	else if(ch=='c' || ch=='C')
    {
        customer_entry();  //customer interface
    }
    else
    {
        setColor(12);
        printf("\n\n INVALID SELECTION!\n\n");
        setColor(15);
        printf("\n Are you admin(a) or customer(c) \n ");
        printf("\n Enter your choice:	");
        scanf(" %c",&ch);
        screen1(ch);
    }

}

//admin home page
void correctpass()
{
	int c;//for choice by the user
	char d;//takes input from user whether to log out or not
	int ch=1;//for the do while function
	int w=0;


	do
    {
        setColor(45);
        printf("\n\n\n\n WELCOME ADMIN");
        setColor(15);
        //offered choices
        printf("\n\n Do you want to :\n 1. View inventory and stock\n 2. View Customer details\n 3. Statistics\n 4. Show Bill Details\n 5. Logout\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&c);

        switch(c)
        {
            case 1:
                inventory();        //shows the current inventory stocks
                break;
            case 2:
                customerDetails();  //shows the details of all the customers
                break;
            case 3:
                statistics();       //shows the stats about total sales ,rating,stock etc
                break;
            case 4:
                billDetails();       //shows details about the items sold
                break;
            case 5:
                do
                {
                    w=0;
                    printf("\n\n Do you want to Log Out?(y/n)\n");
                    printf("\n Enter your choice:	");
                    scanf(" %c",&d);

                    if((d==121)||(d==89))
                    {
                        setColor(98);
                        printf("\n\n You have been logged out successfully.\n");
                        setColor(15);
                        exit(0);
                    }
                    else if((d==78)||(d==110))
                    {
                        break;
                    }
                    else
                    {
                        w=1;
                    }

                }while(w==1);
                break;
            default:
                setColor(12);
                printf("\n\n INVALID SELECTION!\n\n");
                setColor(15);
        }

    }while(ch==1);
}

//inventory page
void inventory()
{

    int choice;//choice taken by the user
    int z=1;//for the do while function

    setColor(46);
    printf("\t\t\t\t\t\t INVENTORY	\n");
    setColor(1);
    do
    {
        setColor(22);
        printf("\n\n CATEGORIES \n\n");
        setColor(15);
        //shows the different categories of items in the shop
        printf(" 1. Food\n 2. Clothes\n 3. Essentials\n 4. Stationery\n 5. Kitchen Utensils\n 6. All \n 7. Go to Home Page\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&choice);


        if(choice>=1&&choice<=7)
        {
            int e=1;//maintains serial number
            int w;//for getting the maximum character length
            int max=0;//hold the maximum character length in name
            int q=0;//for checking the length of current item name
            item *ctr=head1->next;//to point to next node
            item *ltr=head1;//to traverse through the list

            if(choice!=7) //except when he doesn't wish to go to home page
            {
                setColor(11);
                printf("\n S.No\tName\t");
                max=strlen(head1->name);

                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max<w)
                        max=w;      //counting the length of the longest item name
                    ctr=ctr->next;
                }

                for(int t=0;t<=(max-4);t++) //for appropriate spacing in printing the names of items in an aligned manner
                {
                    printf(" ");
                }

                printf("Quantity\tUnit_Price\tLocation\n");
                setColor(15);
            }

            if(choice <=5) //displays the items category wise
            {
                while(ltr!=NULL)
                {

                    if((ltr->id)==choice)
                    {
                        printf(" %d\t%s",e,ltr->name);
                        q=strlen(ltr->name);
                        for(int t=0;t<=(max-q);t++)
                        {
                            printf(" ");
                        }
                        printf("\t%d\t\t%d\t\t%s\n",ltr->qty,ltr->price,ltr->location);
                        e++;
                    }

                    ltr=ltr->next;
                }
            }
            else if(choice==6) //displays items of all the categories
            {
                while(ltr!=NULL)
                {
                    printf(" %d\t%s",e,ltr->name);
                    q=strlen(ltr->name);

                    for(int t=0;t<=(max-q);t++)
                    {
                        printf(" ");
                    }

                    printf("\t%d\t\t%d\t\t%s\n",ltr->qty,ltr->price,ltr->location);
                    e++;
                    ltr=ltr->next;
                }
            }
            else if(choice==7)
            {
               break;       //return back to home page
            }
        }
        else
        {
           setColor(12);
           printf("\n\n INVALID SELECTION!\n\n");
           setColor(15);
        }

    }while(z==1);
}

void customerDetails()
{

    int choice;//user's choice
    int z=1;//do while loop variable

    setColor(22);
    printf("\t\t\t\t\t\t   CUSTOMER DETAILS  \n");
    setColor(43);
    do
    {
        setColor(22);
        printf("\n OPTIONS\n");
        setColor(15);
        printf("\n\n 1. View Members\n 2. View All Customers\n 3. Go to Home Page\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&choice);

        if(choice>=1 && choice<=3)
        {
            int e=1;//to maintain serial no.
            int w;//to get the maximum character length
            int max=0;//hold the maximum character length in name
            int q=0;//checks the length of current customer name in name
            customer *ctr=head2->next;//points to next node
            customer *ltr=head2;//for traversing the list
            char membership_check[500000]="N";

            if(choice==1)
            {
                setColor(11);
                printf("\n SNo.\tName\t");
                max=strlen(head2->name);

                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max < w)
                        max=w;  //counting the length of the longest customer name
                    ctr=ctr->next;
                }

                for(int t=0;t<=(max-4);t++)
                {
                    printf(" "); //for appropriate spacing in printing the names of items in an aligned manner
                }

                printf("\tDOB\t\t\tPhone no.\tDate\t\tMembership\tPoints\tRating\n");
                setColor(15);
                while(ltr!=NULL)
                {

                    if(strcmp(ltr->membership,membership_check))        //if the customer is a member
                    {
                        printf(" %d\t%s",e,ltr->name);
                        q=strlen(ltr->name);

                        for(int t=0;t<=(max-q);t++)
                        {
                            printf(" "); //for appropriate spacing in printing the names of items in an aligned manner
                        }

                        if(ltr->bday.dd<10)     //if the birth date is less than 10
                            printf("\t0%d",ltr->bday.dd);
                        else
                            printf("\t%d",ltr->bday.dd);

                        if(ltr->bday.mm<10)     //if the birth month is less than 10
                            printf("/0%d",ltr->bday.mm);
                        else
                            printf("/%d",ltr->bday.mm);

                        if(ltr->bday.yy<10)     //if the birth year is less than 10
                            printf("/0%d",ltr->bday.yy);
                        else
                            printf("/%d",ltr->bday.yy);

                        printf("\t\t%s",ltr->phoneno);      //prints the phone no

                        if(ltr->entry.dd<10)
                            printf("\t0%d",ltr->entry.dd);  //if the date of entry is less than 10
                        else
                            printf("\t%d",ltr->entry.dd);

                        if(ltr->entry.mm<10)
                            printf("/0%d",ltr->entry.mm);   // if the month of entry is less than 10
                        else
                            printf("/%d",ltr->entry.mm);

                        if(ltr->entry.yy<10)
                            printf("/0%d",ltr->entry.yy);     // if the year of entry is less than 10
                        else
                            printf("/%d",ltr->entry.yy);

                        printf("\t%s\t\t",ltr->membership);     //prints if the customer is the member (and the type of membership if yes)
                        printf("%d\t",ltr->points);             //prints the points in account of the member
                        printf("%d\n",ltr->rate);               //prints the ratings given by the user
                        e++;
                    }

                    ltr=ltr->next;      //moves to next customer node
                }
            }
            else if(choice==2)          //displays only the members
            {
                setColor(11);
                printf("\n SNo.\tName\t");
                max=strlen(head2->name);

                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max < w)
                        max=w;      //  for the counting the length of the maximum name of the members
                    ctr=ctr->next;
                }

                for(int t=0;t<=(max-4);t++)
                {
                    printf(" ");        //for appropriate spacing in the names coloumn
                }

                printf("\tDOB\t\t\tPhone no.\tDate\t\tMembership\tPoints\tRating\n");
                setColor(15);
                while(ltr!=NULL)
                {
                    printf(" %d\t%s",e,ltr->name);
                    q=strlen(ltr->name);

                    for(int t=0;t<=(max-q);t++)
                    {
                        printf(" ");  //  for the counting the length of the maximum name of the members
                    }

                    if(ltr->bday.dd<10)
                        printf("\t0%d",ltr->bday.dd);
                    else
                        printf("\t%d",ltr->bday.dd);

                    if(ltr->bday.mm<10)
                        printf("/0%d",ltr->bday.mm);
                    else
                        printf("/%d",ltr->bday.mm);

                    if(ltr->bday.yy<10)
                        printf("/0%d",ltr->bday.yy);
                    else
                        printf("/%d",ltr->bday.yy);

                    printf("\t\t%s",ltr->phoneno);

                    if(ltr->entry.dd<10)
                        printf("\t0%d",ltr->entry.dd);
                    else
                        printf("\t%d",ltr->entry.dd);

                    if(ltr->entry.mm<10)
                        printf("/0%d",ltr->entry.mm);
                    else
                        printf("/%d",ltr->entry.mm);

                    if(ltr->entry.yy<10)
                        printf("/0%d",ltr->entry.yy);
                    else
                        printf("/%d",ltr->entry.yy);

                    printf("\t%s\t\t%d\t%d\n",ltr->membership,ltr->points,ltr->rate);
                    e++;
                    ltr=ltr->next;
                }
            }
            else if(choice==3)
            {
                break;
            }

        }
        else
        {
           setColor(12);
           printf("\n\n INVALID SELECTION!\n\n");
           setColor(15);
        }

    }while(z==1);
}

void statistics()
{
    int choice;//to get choice from user
    //int x=0;//for do while loop
    int qty=0,e=1/*for serial number*/,t=0,i;
    int q=0,w=0,max;//to store length of strings
    int p=0,g=0,s=0;//to store members category wise
    item *ctr=head1->next,*ptr=head1;//pointers to inventory file
    customer *ltr=head2;//pointer to customer file
    int one=0,two=0,three=0,four=0,five=0;//types of rating  given
    bill *tra=head4;
    float total_sales=0.0;      //total sales made by the shop so far

    do
    {
        setColor(22);
        printf("\n\n\nOPTIONS");
        setColor(15);
        printf("\n\n 1. Stock Status\n 2. Total Sales\n 3. Total Members\n 4. Total Rating\n 5. Go to Home Page\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&choice);
        if(choice==1)//for status of stock
        {
            setColor(11);
            printf("\n S.No\tName\t");
            max=strlen(head1->name);//store maximum length

            while(ctr!=NULL)
            {
                w=strlen(ctr->name);
                if(max<w)
                    max=w;
                ctr=ctr->next;
            }

            for(int t=0;t<=(max-4);t++)//to get uniform alignment
            {
                printf(" ");
            }

            printf("\t\tQuantity\n");
            setColor(15);
            while(ptr!=NULL)
            {
                printf(" %d\t%s",e,ptr->name);
                q=strlen(ptr->name);

                for(int t=0;t<=(max-q);t++)
                {
                    printf(" ");
                }

                if(ptr->qty<=3)//case of urgent refill
                {
                    setColor(12);
                    printf("\t\t\t%d  URGENT REFILL\n",ptr->qty);
                    setColor(15);
                }
                else
                {
                    setColor(15);
                    printf("\t\t\t%d\n",ptr->qty);
                }

                e++;
                ptr=ptr->next;      //moves to the next node
            }
        }
        else if(choice==3)//to check total members category wise
        {
           setColor(11);
           printf("\n\n S.No\tCategory");
           max=strlen("Platinum");      //stores the length of platinum

           for(i=0;i<=(max-4);i++)
               printf(" ");     //to get uniform alignment

           printf("Members\n");

           while(ltr!=NULL)
           {
               if(!strcmp(ltr->membership,"P"))//to store platinum members
                ++p;
               else if(!strcmp(ltr->membership,"G"))//to store gold members
                ++g;
               else if(!strcmp(ltr->membership,"S"))//to store silver members
                ++s;

               ltr=ltr->next;       //moves to the next node
           }

           setColor(15);
           printf(" 1.\t");
           printf("PLATINUM");

           printf("     %d\n",p);       //prints the no of platinum members
           printf(" 2.\t");
           printf("GOLD");
           for(i=0;i<=(max);i++)
                printf(" ");            //to get proper alignments
           printf("%d\n",g);            //prints the number of gold members
           printf(" 3.\t");
           printf("SILVER");
           for(i=0;i<=(max-2);i++)      //since the length of silver=length of platinum
                printf(" ");
           printf("%d\n",s);            //prints the no of silver members
        }
        else if(choice==4)
        {
          ltr=head2;

          while(ltr!=NULL)   //traversing through customer file
          {
              if(ltr->rate==5)
                ++five;     //people who gave 5 rating
              else if(ltr->rate==4)
                ++four;     //people who gave 4 rating
              else if(ltr->rate==3)
                ++three;    //people who gave 3 rating
              else if(ltr->rate==2)
                ++two;      //people who gave 2 rating
              else if(ltr->rate==1)
                ++one;      //people who gave 1 rating

              ltr=ltr->next; //moves to the next node
          }
          setColor(11);
          printf("\n\n\t Ratings\t\t\tMembers\n");
          setColor(15);
          printf("\t 5-STARS\t\t\t");
          printf("%d\n",five);      //prints people who gave 5 star rating
          printf("\t 4-STARS\t\t\t");
          printf("%d\n",four);      //prints people who gave 4 star rating
          printf("\t 3-STARS\t\t\t");
          printf("%d\n",three);     //prints people who gave 3 star rating
          printf("\t 2-STARS\t\t\t");
          printf("%d\n",two);       //prints people who gave 2 star rating
          printf("\t 1-STARS\t\t\t");
          printf("%d\n",one);       //prints people who gave 1 star rating
        }
        else if(choice==2)
        {
          printf("\n");
          setColor(11);
          printf("\t\t\tTOTAL SALES\n\n");
          setColor(15);
          tra=head4;
          while(tra!=NULL)
          {
              total_sales+=tra->total_price;        //adds the bill amounts of all the bills generated so far
              tra=tra->next;
          }

         setColor(15);
         printf("\t\t\t%.2f (INR)\n\n",total_sales);    //prints the total sales
        }
        else if(choice==5)
            break;           //returns to homepage
        else                //for wrong choice of input
        {
           setColor(12);
           printf("\n\n INVALID SELECTION!\n\n");
           setColor(15);
        }
    }while(1);

}

void billDetails()
{
    char phoneno[500000];//for storing the phone no
    customer *atr=head2;    //pointer to customer linked list
    bill_det *ptr=head3,*ltr=head3,*trav=head3; //pointer to bill details linked list
    int ch;     //checks for a new customer
    int max_new;    //stores length of item name by head3
    int h;      //stores length of item name by trav
    int q;      //stores length of item name by ptr
    int sno=1;  //for serial no
    date dt;       //date type for storing current date
    getchar();
    do
    {
        ch=0;
        printf("\n Enter the Phone Number:	");
        gets(phoneno); //takes the phone no as a string
        atr=head2;  //head of customer list
        while(atr!=NULL)
        {
            if(!strcmp(phoneno,atr->phoneno)) //compares the entered phone no with that in the records to find the bill details of the customer
                break; //breaks upon encountering a match
            atr=atr->next; //points to the next node
        }

        if(atr==NULL)//reaches to the end of the list without any match
        {
            setColor(12);
            printf("\n\n NO CUSTOMER FOUND!\n\n");
            setColor(15);
            ch=1;
        }
        else
        {
            while(ptr!=NULL)
            {
                sno=1;
                if(ptr->customerno==atr->id) //checks for the id
                {
                    dt.dd=ptr->cur_date.dd;//stores the current date
                    dt.mm=ptr->cur_date.mm;//stores the current month
                    dt.yy=ptr->cur_date.yy;//stores the current year
                    setColor(45);
                    printf("\n\n\t\t\tDate: %d/%d/%d\n\n",dt.dd,dt.mm,dt.yy);
                    setColor(22);
                    printf(" S.no\tName");
                    max_new=strlen(head3->itemname);
                    trav=head3->next;//points to the second node in bill_det

                    while(trav!=NULL)
                    {
                        h=strlen(trav->itemname);
                        if(max_new<h)
                            max_new=h;      //stores the length of the longest item name
                        trav=trav->next;     //points to the next node
                    }

                    for(int t=0;t<=(max_new-4);t++)
                    {
                        printf(" "); //spacing for proper alignment
                    }

                    printf("\tQuantity\t\tTotal Price\n");
                    setColor(15);

                    printf(" %d\t%s",sno,ptr->itemname);
                    q=strlen(ptr->itemname);        //stores the length of longest item name

                    for(int t=0;t<=(max_new-q);t++)
                    {
                        printf(" ");        //spacing for proper alignment
                    }

                    printf("\t%d\t\t\t%d\n",ptr->qty,ptr->t_price);
                    sno++;          //incrementing the serial no

                    ltr=ptr->next;       // next record of ptr
                    while(ltr!=NULL)
                    {
                        if(ptr->customerno==ltr->customerno&&dt.dd==ltr->cur_date.dd&&dt.mm==ltr->cur_date.mm&&dt.yy==ltr->cur_date.yy)
                        {
                            printf(" %d\t%s",sno,ltr->itemname);
                            q=strlen(ltr->itemname);    // storing the item name

                            for(int t=0;t<=(max_new-q);t++)
                            {
                                printf(" ");        // proper alignment
                            }

                            printf("\t%d\t\t\t%d\n",ltr->qty,ltr->t_price);
                            sno++;                  // incrementing the serial no
                        }
                        // to check for records on the same date
                        if(dt.dd!=ltr->cur_date.dd||dt.mm!=ltr->cur_date.mm||dt.yy!=ltr->cur_date.yy)
                        {
                            ptr=ltr;
                            break;
                        }

                        ltr=ltr->next; // moves to the next node
                    }
                    if(ltr==NULL)
                    {
                        // if all records are traversed
                        ptr=NULL;
                    }
                }
                else
                {
                    ptr=ptr->next; // moves to the next node
                }
            }
        }
    }while(ch==1);
}
//customer home page
void customer_entry()
{

	int c;//for choice by the user
	char d;//takes input from user whether to log out or not
	int ch=1;//for the do while function
	int w=0;//  do-while loop counter

	setColor(45);
    printf("\n\n\n\n WELCOME CUSTOMER");
	setColor(15);
	do
    {
        //choices available to the customer
        printf("\n\n Do you want to :\n 1. Check Location\n 2. Generate Bill\n 3. Logout\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&c);

        switch(c)
        {
            case 1:
                checkLocation();//prints the location of any product entered
                break;
            case 2:
                generateBill();//generates the bill
                break;
            case 3:
                do
                {
                    w=0;
                    printf("\n\n Do you want to Log Out?(y/n)\n");
                    printf("\n Enter your choice:	");
                    scanf(" %c",&d);

                    if((d==121)||(d==89))//comparing the ASCII codes of y
                    {
                        setColor(98);
                        printf("\n\n You have been logged out successfully.\n");
                        setColor(15);
                        exit(0);
                    }
                    else if((d==78)||(d==110)) //comparing the ASCII code of n
                    {
                        break;
                    }
                    else
                    {
                        w=1;            //checking for invalid input
                    }

                }while(w==1);
                break;
            default:
               setColor(12);
               printf("\n\n INVALID SELECTION!\n\n");
               setColor(15);
        }

    }while(ch==1);
}

//check Location
void checkLocation()
{
    char choice[500000];
    int dh=0;//for do while
    int de=0;
    int cho=0;
    int e=1;//for serial number
    int w;//for getting the maximum character length
    int max=0;//hold the maximum character length in name
    int q=0;//for checking the length of current item name
    item *ctr=head1->next;//to point to next node
    item *ltr=head1;//to traverse through the list

    do
    {
        dh=0;
        printf("\n\n What item do you need to search for:\t ");
        getchar();
        gets(choice);//takes the name of the item as a string

        e=1;//for serial number
        max=0;//hold the maximum character length in name
        q=0;//for checking the length of current item name
        ctr=head1->next;//to point to next node
        ltr=head1;//to traverse through the list
        //for printing the table with headings
        while(ltr!=NULL)
        {
            if(!strcmp(ltr->name,choice)) //when a match is found within the records
            {
                setColor(46);
                printf("\n\n\t\t LOCATION OF PRODUCT	\n");//prints the location of the item
                setColor(1);
                setColor(3);
                printf("\n S.No\tName");
                max=strlen(head1->name);        //stores the length of the first item name

                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max<w)
                        max=w;      //finds the longest item name length
                    ctr=ctr->next;
                }

                for(int t=0;t<=(max-4);t++)
                {
                    printf(" ");        //for alignment
                }

                printf("Location\n");
                setColor(15);
            }
            ltr=ltr->next;          //prints the next node
        }

        int c=0;
        ltr=head1;
        //printing the contents under the headings
        while(ltr!=NULL)
        {
            if(!strcmp(ltr->name,choice))
            {
                printf(" %d\t%s",e,ltr->name);      //printing the item name
                q=strlen(ltr->name);

                for(int t=0;t<=(max-q);t++)
                {
                    printf(" ");                    //for proper alignment
                }

                printf("%s\n\n",ltr->location);     //prints the location of the item
                e++;        //serial number type counter
                c=1;        //to indicate that item is found
            }

            ltr=ltr->next;
        }

        if(c==0)    //when item is not found
        {
            setColor(12);
            printf("\n\n ITEM NOT FOUND!\n\n");
            setColor(15);
        }

        do
        {
            de=0;//do-while counter
            printf("\n 1. Do you want to find another product\n 2. Go to home page\n\n");
            printf("\n Enter your choice:	");
            scanf("%d",&cho);

            switch(cho)
            {
                case 1:
                    dh=1;   //outer do-while counter to find more items
                    break;
                case 2:
                    break;  //return back to home page
                default:
                    setColor(12);
                    printf("\n\n INVALID SELECTION!\n\n");
                    setColor(15);
                    de=1; // to indicate that the loop has to run again to take a valid input
            }

        }while(de==1);

    }while(dh==1);
}


//Generate bill
void generateBill()
{
    char name1[500000]; //stores the customer name
    date bday;          //stores the bday of the customer
    char phoneno[11];   //stores the phone no of the customer
    date cur_date;      //stores the date when the customer arrives (also printed on bill)
    int h=0;            //for traversing in array of units in bill
    int customerid;     //stores the customer id
    int billno;         //stores the bill no

    printf("\t\t\t\t\t\t CUSTOMER DETAILS	\n");
    printf(" Enter Name: ");
    getchar();
    gets(name1);    //takes the input of the customer name as a string

    printf(" Enter Birthdate(dd/mm/yyyy): ");
    scanf("%d/%d/%d",&bday.dd,&bday.mm,&bday.yy);   //takes the input of the customer's bday

    printf(" Enter Phone Number(10digit): ");
    getchar();
    gets(phoneno);  //stores the phoneno of the customer as an array

    time_t now;     //used for representing current date
    time(&now);     //returns the current date
    struct tm *local=localtime(&now); //storing the current date in form of a structure

    cur_date.dd=local->tm_mday; //current date
    cur_date.mm=local->tm_mon+1; //current month
    cur_date.yy=local->tm_year+1900;  //current year

    customer *ltr=head2; //points to the customer list
    customer *ztr=head2; //points to the customer list


    while(ltr!=NULL)
    {
        if(!strcmp(phoneno,ltr->phoneno)) //to see if the customer is an existing one
            break;

        ltr=ltr->next;
    }

    customer *ytr=head2;    //points to the customer list

    if(ltr==NULL)       //if the customer is new
    {
        while(ytr->next!=NULL)
        {
            ytr=ytr->next;  //reach the end of the list to add new customer
        }
        customerid=(ytr->id)+1; //id of new customer found by incrementation of last record id

        customer *new_cust = (customer *)malloc(sizeof(customer)); //dynamic memory allocation
        //copying the details in to the new customer node
        new_cust->bday.dd=bday.dd;
        new_cust->bday.mm=bday.mm;
        new_cust->bday.yy=bday.yy;
        new_cust->id=customerid;
        strcpy(new_cust->name,name1);
        strcpy(new_cust->phoneno,phoneno);
        new_cust->entry.dd=cur_date.dd;
        new_cust->entry.mm=cur_date.mm;
        new_cust->entry.yy=cur_date.yy;
        new_cust->points=0;
        strcpy(new_cust->membership,"N"); //by default no membership is assigned to the new node
        new_cust->next=NULL;        //the next pointer of new node points to NULL

        while(ztr->next!=NULL)
        {
            ztr=ztr->next;
        }
        ztr->next=new_cust; //stores the address of the new node

    }
    else if(ltr!=NULL)  //if existing customer
    {
        customerid=ltr->id;
    }

    bill_det *atr=head3;

    while(atr->next!=NULL)
    {
        atr=atr->next;  //to reach the last record
    }

    billno=((atr->billno)+1); //assigns a new bill no
    setColor(11);
    printf("\t\t\t\t\t\t      STOCKS	\n");
    setColor(15);

    item *ptr=head1,*ctr=head1->next; //pointers of item type
    int e=1;        //for serial number
    int w;          //for getting the maximum character length
    int max=0;      //hold the maximum character length in name
    int q=0;        //for checking the length of current item name

    max=strlen(head1->name);//stores length of item name
    while(ctr!=NULL)
    {
        w=strlen(ctr->name);
        if(max<w)
            max=w;  //to calculate the maximum length of the item name
        ctr=ctr->next;
    }
    //printing the item name,category,quantity
    char cat[500000];
    strcpy(cat,ptr->category);
    setColor(22);
    printf(" %s\n\n",ptr->category);
    setColor(3);
    printf(" S.no\tName");

    for(int t=0;t<=(max-4);t++)
    {
        printf(" ");    //for proper alignment
    }

    printf("Quantity\tPrice\n");
    setColor(15);

    while(ptr!=NULL)
    {
        if(strcmp(cat,ptr->category))   //comparing the category
        {
            setColor(22);
            printf("\n %s\n\n",ptr->category);
            e=1;        //serial no
            setColor(3);
            printf(" S.no\tName");

            for(int t=0;t<=(max-4);t++)
            {
                printf(" ");    //for proper alignment
            }

            printf("Quantity\tPrice\n");
            setColor(15);
        }

        printf(" %d.\t%s",e,ptr->name);     // printing the category name
        q=strlen(ptr->name);

        for(int t=0;t<=(max-q);t++)
        {
            printf(" ");        // for proper alignment
        }

        if((ptr->qty)<=2)
            setColor(12);       // if the stocks are about to run out:RED highlighting

        printf("%d\t\t",ptr->qty);
        setColor(15);
        printf("%d\n",ptr->price);
        strcpy(cat,ptr->category);
        e++;
        ptr=ptr->next;          //points to the next node
    }

    char item_name[100];        //take the name of the item to be bought
    int item_qty=0;             //takes the quantity of the item to be bought
    int ch=0;
    int y=0;
    int totalprice=0;           //bill amount

    bill_det *itr=head3;        // pointers of bill_det
    char n;                     //counter to modify quantity
    item *notfound=head1;       //pointers of item type
    item *htr=head1;            //pointers of item type
    int new_qty;                //modified quantity
    int check=0;                // to check if an item is already bought
    int x=1;
    int old_price;              //stores the price before the quantity is modified
    int z,re;                   //loop counter to take quantity again
    int cttr=1;
    int k;                      //takes choice to enter the name of the item again or quit
    int l;                      //loop counter to enter item name again
    int counter=0;

    /*bill *temp1=(bill*)malloc(sizeof(item));
    (temp1->customerno)=customerid;
    (temp1->billno)=billno;
    (temp1->total_price)=0;
    (temp1->cur_date.dd)=cur_date.dd;
    (temp1->cur_date.mm)=cur_date.mm;
    (temp1->cur_date.yy)=cur_date.yy;
    temp1->next=NULL;
    bill *lntr=head4;
    while(lntr->next!=NULL)
    {
        lntr=lntr->next;
    }
    lntr->next=temp1;*/

    do
    {
        y=0;
        check=0;

        bill_det *temp= (bill_det*)malloc(sizeof(bill_det));    // allocates dynamic memory in bill_det
        // the details are copied into the temp node
        temp->customerno=customerid;
        temp->billno=billno;
        temp->cur_date.dd=cur_date.dd;
        temp->cur_date.mm=cur_date.mm;
        temp->cur_date.yy=cur_date.yy;

        int ex=0;   // do while counter
        int zz=0;   //counter to quit
        do
        {
            l=0;
            printf("\n\n Enter Name of the Item you want to buy:   ");
            gets(item_name);        //takes the item name
            notfound=head1;

            //checks if the item entered is available in the stocks or not
            while(notfound!=NULL)
            {
                if(!(strcmp(item_name,notfound->name)))
                        break;
                notfound=notfound->next;
            }

            //if the item is not found
            if(notfound==NULL)
            {

                setColor(12);
                printf("\n\n ITEM NOT FOUND!\n\n");
                setColor(15);
                do
                {

                    ex=0;//do while counter
                    printf("\n 1.Do you want to enter again.\n 2.Quit\n");
                    printf("\n Enter your choice:	");
                    scanf("%d",&k);

                    if(k==1)
                    {
                        l=1;
                        getchar();
                    }
                    else if (k==2)
                    {
                           setColor(15);
                           zz=1;
                    }
                    else
                    {
                          setColor(12);
                          printf("\n\n INVALID SELECTION!\n\n");
                          setColor(15);
                          ex=1;
                    }

                }while(ex==1);
            }
        }while(l==1);

        if(zz!=1)
        {
            itr=head3;
            while(itr!=NULL)
            {
                // to match then node in th ebill_det list
                if((itr->billno)==(temp->billno))
                {
                    //in case the item is already bought
                    if(!strcmp(item_name,itr->itemname))
                    {
                        setColor(46);
                        printf(" YOU ALREADY BOUGHT THIS ITEM!\n Quantity is %d\n",itr->qty);
                        setColor(15);

                        do
                        {
                            w=0; //do -while counter
                            printf("\n\n Do you want to update?(y/n)\n");
                            printf("\n Enter your choice:	");
                            scanf("%c",&n);
                            if((n==121)||(n==89))   //comparing ASCII codes for yes
                            {
                                do
                                {
                                    x=1;
                                    printf("\n\n Enter the Quantity:\t");
                                    scanf("%d",&new_qty);
                                    old_price=itr->t_price; //storing old price
                                    htr=head1;
                                    while(htr!=NULL)
                                    {
                                        if(!strcmp(item_name,htr->name))    //reaching the node with the same item name
                                            break;
                                        htr=htr->next;                      //moving to the next node
                                    }

                                    itr->t_price=new_qty*(htr->price); //finding total price as per new quantity

                                    if(new_qty<(itr->qty))
                                    {
                                        //subtracting the quantity and reducing total price
                                        (htr->qty)+=(itr->qty)-new_qty;
                                        totalprice-=old_price-(itr->t_price);
                                    }
                                    else
                                    {
                                        //adding the quantity and increasing total price
                                        (htr->qty)-=new_qty-(itr->qty);
                                        totalprice+=(itr->t_price)-old_price;
                                    }

                                    if(htr->qty<0)
                                    {
                                        // incase the stocks are not sufficient
                                        setColor(12);
                                        printf(" NOT ENOUGH LEFT!\n ENTER AGAIN!\n\n");
                                        setColor(26);
                                        printf(" Quantity Available: %d\n\n",(htr->qty+(new_qty-(itr->qty)))); //displaying the current quantity
                                        setColor(15);
                                        x=0;        //for running loop again to take acceptable value of quantity
                                        //updating the qty and total price
                                       (htr->qty)+=new_qty-(itr->qty);
                                        totalprice-=(itr->t_price)-old_price;
                                    }

                                }while(x==0);
                                itr->qty=new_qty; // updating the quantity in the node
                                check=1;

                            }
                            else if((n==78)||(n==110))
                            {
                                check =1; // to run the loop again
                            }
                            else
                            {
                                w=1;   //do while counter
                            }
                        }while(w==1);
                    }
                }
                itr=itr->next; //moving to the next node
            }

           if(check==0) // if the item is not bought already
           {
                do
                {
                    ch=0;//initializing
                    printf(" Enter the Quantity:\t");
                    scanf("%d",&item_qty);

                    ptr=head1;
                    while(ptr!=NULL)
                    {
                        if(!strcmp(item_name,ptr->name))        //comparing with records to check stock
                        {
                            break;
                        }
                        ptr=ptr->next;                          //moves to the next node
                    }

                    if((item_qty)>(ptr->qty))           //if the entered qty is greater than the one available
                    {
                        ch=1;
                        setColor(12);

                        if(ptr->qty>0)
                        {

                            printf(" NOT ENOUGH LEFT!\n ENTER AGAIN!\n\n");
                            setColor(26);
                            printf(" Quantity Available: %d\n\n",ptr->qty);
                            setColor(15);
                        }
                        else
                        {
                            printf("\n\n STOCK FINISHED!\n\n");
                            setColor(15);
                            item_qty=0;
                            break;
                        }

                    }
                }while(ch==1);
                // the customer ends his visit
                if(item_qty==0 && counter==0)
                {
                    setColor(43);
                    printf("\n THANKS FOR VISITING\n");
                    setColor(15);
                }
                //if the item qty is not zero
                if(item_qty!=0)
                {
                    //copying the data into the temp node
                    (temp->t_price)=(item_qty)*(ptr->price);
                    (temp->qty)=item_qty;
                    strcpy(temp->itemname,item_name);
                    totalprice+=(temp->t_price);    //updating the totalprice
                    temp->next=NULL;                //moves to the next node

                    (ptr->qty)-=item_qty;           //updates the item quantity

                    bill_det *rtr = head3;          // pointer to bill_det

                    if(head3==NULL)
                    {
                        head3=temp;
                    }
                    else
                    {
                        while(rtr->next!=NULL)
                        {
                            rtr=rtr->next;              //points to the next node
                        }
                        rtr->next=temp;                 // points to the newnode
                    }

                }
                else
                {
                    free(temp);     // if the quantity entered is zero then the node is deleted
                }
           }

            int d;   //takes choice
            int z;  //do while counter

            do
            {
                z=0;
                counter++;
                printf("\n\n Do you want to enter more items?(y/n)\n");
                printf("\n Enter your choice:	");
                scanf(" %c",&d);
                if((d==121)||(d==89))       //compares ASCII codes of y
                {
                    y=1;
                    getchar();
                    h++;
                }
                else if((d==78)||(d==110)) // compares the ASCII codes of N
                {
                    printf("\n");
                    printf("\n");
                    printf(" Your Current Bill is ");  // displays the interim bill
                    setColor(60);
                    printf("%d",totalprice);
                    setColor(15);
                }
                else
                {
                    setColor(12);
                    printf("\n\n INVALID SELECTION!\n\n");
                    setColor(15);
                    z=1;    // to make the loop run again for a valid input
                }
            }while(z==1);
        }
        else
        {
            printf("\n");
            printf("\n");
            printf(" Your Current Bill is ");   // displays the interim bill
            setColor(60);
            printf("%d",totalprice);
            setColor(15);
        }

    }while(y==1);

    int choice2,choice3;//takes choices
    int j=0;
    bill_det *trav = head3;//bill_det pointer
    int max_new=0;// used for storing the length of the item name
    int sno=1;  //used for serial no
    int rw,ew,d,pq=0;
    item *dtr=head1; //item pointers
    bill_det *btr=head3;
    int new_qty1;


    do
    {
        pq=0;
        printf("\n\n 1. Do you want to modify your shopping list.\n 2. Generate bill\n");
        printf("\n Enter your choice:	");
        scanf("%d",&choice2);
        switch(choice2)
        {
            case 1:
                setColor(45);
                printf("\t\t\t Your Current Bill\n\n");// displays the interim bill
                setColor(22);
                printf(" S.no\tName");
                max_new=strlen(head3->itemname);
                trav=head3->next;

                while(trav!=NULL)
                {
                    h=strlen(trav->itemname);
                    if(max_new<h)
                        max_new=h;      // length of longest item name
                    trav=trav->next;    // moves to the next node
                }

                for(int t=0;t<=(max_new-4);t++)
                {
                    printf(" ");        // for alignment
                }

                printf("\tQuantity\t\tTotal Price\n");
                setColor(15);
                trav=head3;
                sno=1;

                while(trav!=NULL)
                {
                    // for matching the bill no and printing the quantity,price
                    if((trav->billno)==billno)
                    {
                        printf(" %d\t%s",sno,trav->itemname);
                        q=strlen(trav->itemname);
                        for(int t=0;t<=(max_new-q);t++)
                        {
                            printf(" ");
                        }
                        printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                        sno++;
                    }
                    trav=trav->next;        // moves to the next node
                }

                while(1)
                {
                    //options to modify the list

                    do
                    {
                        printf("\n\n 1. Do you want to delete a item\n 2. Do you want to modify the quantity\n 3. Finished\n\n");
                        printf("\n Enter your choice:	");
                        scanf("%d",&choice3);
                        trav=head3; //bill_det type pointer

                        j=1;

                        switch(choice3)
                        {
                            case 1:
                               do
                               {
                                   trav=head3;
                                   rw=0;

                                    while(trav!=NULL)
                                    {
                                        // matching the record to be deleted
                                        if((trav->billno)==billno)
                                            break;

                                        trav=trav->next;        //moving to the next node
                                    }

                                    if(trav!=NULL)
                                    {
                                        trav=head3;// bill_det type pointer
                                        dtr=head1; //item type pointer

                                        getchar();
                                        printf(" Enter the item you want to delete: ");
                                        gets(item_name);


                                        while(trav!=NULL)
                                        {
                                            if(trav->billno==billno)
                                            {
                                                if(!strcmp(trav->itemname,item_name))
                                                {
                                                    break;
                                                }
                                            }

                                            btr=trav; // storing the node address to be deleted
                                            trav=trav->next;
                                        }

                                        if(trav==NULL)
                                        {
                                            // if the end of the list is reached
                                            setColor(12);
                                            printf("\n\n ITEM NOT FOUND!\n\n");
                                            setColor(15);
                                        }
                                        else
                                        {
                                            btr->next=trav->next; // unlinking the node to be deleted
                                            dtr=head1;
                                            while(dtr!=NULL)
                                            {
                                                if(!strcmp(dtr->name,trav->itemname)) // comparing the item name
                                                    break;

                                                dtr=dtr->next;
                                            }
                                            // updating the quantity and item price
                                            (dtr->qty)+=(trav->qty);
                                            totalprice-=(trav->t_price);
                                         }
                                        free(trav); // freeing the node to be deleted

                                        trav=head3;
                                        while(trav!=NULL)
                                        {
                                            if(trav->billno==billno) // comparing the bill no
                                                break;

                                            trav=trav->next;        // moving to the next node
                                        }

                                        if(trav!=NULL)
                                        {
                                            // displaying the current bill after deletion
                                            setColor(45);
                                            printf("\t\t\tYour current bill is \n\n");
                                            setColor(22);
                                            printf(" S.no\tName");
                                            max_new=strlen(head3->itemname); // storing name of item name
                                            trav=head3->next;

                                            while(trav!=NULL)
                                            {
                                                h=strlen(trav->itemname);
                                                if(max_new<h)
                                                    max_new=h;      // storing the length of the largest item name
                                                trav=trav->next;
                                            }

                                            for(int t=0;t<=(max_new-4);t++)
                                            {
                                                printf(" ");    // for alignment
                                            }

                                            printf("\tQuantity\t\tTotal Price\n");
                                            setColor(15);

                                            trav=head3;     // fro traversal
                                            sno=1;          //serial no

                                            while(trav!=NULL)
                                            {
                                                // matching the bill nos
                                                if((trav->billno)==billno)
                                                {
                                                    printf(" %d\t%s",sno,trav->itemname);
                                                    q=strlen(trav->itemname);
                                                    for(int t=0;t<=(max_new-q);t++)
                                                    {
                                                        printf(" ");    // for alignment
                                                    }
                                                    printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                                                    sno++;              // incrementing sno
                                                }
                                                trav=trav->next;        // moving to the next node
                                            }

                                            do
                                            {
                                                ew=0;       // do -while counter
                                                    printf("\n\n Do you want to delete more items?(y/n)\n");
                                                    printf("\n Enter your choice:	");
                                                    scanf("%c",&d);

                                                    if((d==121)||(d==89))   //comparing ASCII values of Y
                                                    {
                                                        rw=1;

                                                    }
                                                    else if((d==78)||(d==110)) // comparing ASCII values of N
                                                    {
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        setColor(60);
                                                        printf("\n INVALID INPUT");
                                                        setColor(15);
                                                        ew=1;                   // incase of invalid input
                                                    }

                                            }while(ew==1);
                                        }
                                        else
                                        {
                                            // if all the items are deleted
                                            setColor(12);
                                            printf("\n\n BILL IS EMPTY!\n\n");
                                            setColor(15);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        setColor(12);
                                        printf("\n\n BILL IS EMPTY!\n\n");
                                        setColor(15);
                                        break;
                                    }
                               }while(rw==1);

                               break;

                            case 2:
                               do
                               {
                                    re=0;
                                    getchar();
                                    printf(" Enter the item you want to modify: ");
                                    gets(item_name);

                                    trav=head3; // used for traversal
                                    while(trav!=NULL)
                                    {
                                        if(trav->billno==billno) // comparing the bill no to find the item
                                        {
                                            if(!strcmp(trav->itemname,item_name)) // comparing the item names
                                            break;
                                        }
                                        trav=trav->next;        // moving to the next node
                                    }

                                    if(trav==NULL)
                                    {
                                        // reaches the end of list without any match
                                        setColor(12);
                                        printf("\n\n ITEM NOT FOUND!\n\n");
                                        setColor(15);
                                    }
                                    else
                                    {
                                        do
                                        {
                                            x=1;
                                            printf(" Enter the Quantity:\t");
                                            scanf("%d",&new_qty1);
                                            old_price=trav->t_price; // stores the current price
                                            htr=head1; // used for traversal
                                            while(htr!=NULL)
                                            {
                                                if(!strcmp(item_name,htr->name)) // compares the item name
                                                    break;

                                                htr=htr->next;      // moves to the next node
                                            }

                                            trav->t_price=new_qty1*htr->price;  // updating the price

                                            if(new_qty1<trav->qty)
                                            {
                                                // subtracting the quantity and reducing the totalprice
                                                htr->qty+=trav->qty-new_qty1;
                                                totalprice-=old_price-trav->t_price;
                                            }
                                            else
                                            {
                                                 // adding the quantity and increasing the totalprice
                                                htr->qty-=new_qty1-trav->qty;
                                                totalprice+=trav->t_price-old_price;
                                            }

                                            if(htr->qty<0)
                                            {
                                                // if the stocks are in sufficient
                                                setColor(12);
                                                printf("\n\n NOT ENOUGH LEFT! ENTER AGAIN!\n\n");
                                                setColor(26);
                                                printf(" Quantity Available: %d\n\n",(htr->qty+(new_qty1-trav->qty)));
                                                x=0;// to run the loop again to take a acceptable quantity as input
                                                setColor(15);
                                                //updating the quantity and total price
                                                htr->qty+=new_qty1-trav->qty;
                                                totalprice-=trav->t_price-old_price;

                                            }
                                        }while(x==0);

                                        trav->qty=new_qty1;
                                        setColor(45);
                                        printf("\t\t\tYour current bill is\n\n");
                                        setColor(22);
                                        printf(" S.no\tName");
                                        max_new=strlen(head3->itemname);    // storing the length of the item_name
                                        trav=head3->next;                   // to skip the headings node

                                        while(trav!=NULL)
                                        {
                                            h=strlen(trav->itemname);
                                            if(max_new<h)
                                                max_new=h;                   // storing the longest item name
                                            trav=trav->next;
                                        }

                                        for(int t=0;t<=(max_new-4);t++)
                                        {
                                            printf(" ");                    // for alignment
                                        }

                                        printf("\tQuantity\t\tTotal Price\n");
                                        setColor(15);

                                        trav=head3;  // used for traversal
                                        sno=1;      // serial no

                                        while(trav!=NULL)
                                        {
                                            if(trav->billno==billno)
                                            {
                                                printf(" %d\t%s",sno,trav->itemname);
                                                q=strlen(trav->itemname);        // storing the length of the item_name

                                                for(int t=0;t<=(max_new-q);t++)
                                                {
                                                    printf(" ");                // for alignment
                                                }

                                                printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                                                sno++;                          // incrementing serial no
                                            }
                                            trav=trav->next;                    // moving to the next node
                                        }
                                    }

                                    do
                                    {
                                        z=0;
                                        printf("\n\n Do you want to update more items?(y/n)\n");
                                        printf("\n Enter your choice:	");
                                        scanf(" %c",&d);
                                        if((d==121)||(d==89)) // comparing ASCII codes for Y
                                        {
                                            re=1;       // for updating more items
                                        }
                                        else if((d==78)||(d==110)) // comparing ASCII codes for N
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            setColor(12);
                                            printf("\n\n INVALID SELECTION!\n\n");
                                            setColor(15);
                                            z=1;    //making the do-while run again for a valid input
                                        }
                                    }while(z==1);
                               }while(re==1);
                               break;

                            case 3:
                                printf(" Your Current Bill is ");
                                setColor(60);
                                printf("%d ",totalprice);   //prints the current bill
                                setColor(15);
                                invoice(totalprice,billno);  // to print the summary
                                break;

                            default:
                                setColor(12);
                                printf("\n\n INVALID SELECTION!\n\n");
                                setColor(15);
                                j=0; // to make the do-while run again for a valid input
                        }

                    }while(j==0);
               }
               break;

            case 2:
                invoice(totalprice,billno); // for generating the bill
                setColor(15);
                break;

            default:
                setColor(12);
                printf("\n\n INVALID SELECTION!\n\n");
                setColor(15);
                pq=1;// to make the do-while run again for a valid input
                break;
        }
    }while(pq==1);

}

void offerzone()
{
    setColor(98);
    //Different types of memberships and their associated benefits are displayed
    printf("\n\t\t\t\t******OFFER ZONE******");
    setColor(15);
    printf("\n Become a member of shopify plaza and avail exciting discounts        ");
    setColor(21);

    printf("\n\nTYPES OF MEMBERSHIP");
    setColor(98);

    printf("\n\n1.PLATINUM");
    setColor(15);
    printf("\nRs250=100 points");
    printf("\nDiscounts\n1. Get 10%% off on every shopping.\n2. Get 25%% off if your points are more than 500.\n3. Get a special 30%% off on your Birthday.\n4. Upon redemption 1 point=1 INR.\n5. Points earned on purchase =30%% of bill amount.");
    setColor(22);

    printf("\n\n2.GOLD");
    setColor(15);
    printf("\nRs200=100 points");
    printf("\nDiscounts\n1. Get 7%% off on every shopping.\n2. Get 20%% off if your points are more than 500.\n3. Get a special 25%% off on your Birthday.\n4. Upon redemption 1 point=0.5 INR.\n5. Points earned on purchase =20%% of bill amount.");
    setColor(88);

    printf("\n\n3.SILVER");
    setColor(15);
    printf("\nRs150=100 points");
    printf("\nDiscounts\n1. Get 5%% off on every shopping.\n2. Get 15%% off if your points are more than 500.\n3. Get a special 15%% off on your Birthday.\n4. Upon redemption 1 point=0.25 INR.\n5. Points earned on purchase =10%% of bill amount.");

    printf("\n");
}


void invoice(int totalprice,int billno)
{
    int p=0;        //stores the percent of discount given as per the membership
    int cur_points=0;//stores the points earned on the current purchase
    float finalpay=0.0;//stores the amount to be paid after eligible discounts
    setColor(78);
	printf("\t\t\t\t\t\t\tINVOICE");
	printf("\n");
	setColor(15);

	bill_det *hd = head3; //points to bill_det linked list
	customer *h=head2;    //points to customer type linked list
	customer *h2=head2;   //points to customer type linked list

    while(hd->next!=NULL)
    {
        if(billno==hd->billno)
            break;      //if a match is found
        hd=hd->next;
    }

    int cid=hd->customerno;     //stores the matched record customer id

    while(h->next!=NULL)
    {
       if(h->id==cid)       //till the cid matches with that of records
            break;

       h=h->next;
    }

	printf("\nBILL ID:\t");
	setColor(22);
	printf("%d",h->id); //prints the bill id
	setColor(15);

	printf("\nDATE:\t");
	setColor(22);
	printf("%d/%d/%d",hd->cur_date.dd,hd->cur_date.mm,hd->cur_date.yy); //prints the current date
	setColor(15);

	printf("\n\nCUSTOMER NAME:\t");
	setColor(22);
	puts(h->name);                          //prints the customer name
	setColor(15);

    printf("\nPHONE NUMBER:\t");
    setColor(22);
    printf("%s",h->phoneno);                //prints the customer phoneno
    setColor(15);

    printf("\nMEMBER:\t");
    setColor(22);
    printf("%s",h->membership);             //prints the customer membership
    setColor(15);

    printf("\nPOINTS IN CARD:\t");
    setColor(22);
    printf("%d",h->points);                 //prints the customer points
    setColor(90);

    printf("\n\t\t\tPURCHASE SUMMARY\n\n\n");
    //table for s.no,item ,price;
    int name_item;
    bill_det *ftr=head3;        //pointer to bill_det linked list
    int sno=1,q;

    setColor(22);
    printf(" S.no\tName");
    name_item=strlen(head3->itemname);  //stores the length of the item name
    ftr=head3->next;        //stores the next node

    while(ftr!=NULL)
    {
        p=strlen(ftr->itemname);
        if(name_item<p)
            name_item=p;            //finds the longest item name
        ftr=ftr->next;              //points to the next node
    }

    for(int t=0;t<=(name_item-4);t++)
    {
        printf(" ");                // for proper alignment
    }

    printf("\tQuantity\t\tTotal Price\n");
    setColor(15);

    ftr=head3;

    while(ftr!=NULL)
    {
        if((ftr->billno)==billno)
        {
            printf(" %d\t%s",sno,ftr->itemname);
            q=strlen(ftr->itemname);
            for(int t=0;t<=(name_item-q);t++)
            {
                printf(" ");        //proper alignment
            }
            printf("\t%d\t\t\t%d\n",ftr->qty,ftr->t_price);
            sno++;              //serial no incrementation
        }
        ftr=ftr->next;      //points to the next node
    }


    setColor(74);
    printf("\n TOTAL:\t%d (INR)",totalprice);   //prints the total of items cost

    setColor(60);//reddish
    float amount=0.0;
    amount=(0.05)*totalprice;
    printf("\n TAX (5%%) : %.2f (INR)",amount); //tax applicable on purchase

    float pay;
    pay=totalprice+amount;      //sum of tax and the cost of items
    setColor(43);
    printf("\n GRAND TOTAL :\t%.2f (INR)\n\n\n\n",pay);

    setColor(15);
    char ch1; //whether a member or not
    hd=head3; // bill_det linked list pointer
    h2=head2; //customer linked list pointer

    while(hd->next!=NULL)   //to move to the end of the linked list
    {
        hd=hd->next;    //moves to the next node
    }

    while(h2->next!=NULL)
    {
        if(h2->id == hd->customerno)    //to match the customer ids
            break;

        h2=h2->next;    //moves to the next node
    }

    int cc=0;       //to identify different types of membership
    int d=0;        //to identify the type of membership bday discount

    //string comparisons to check the type of member and store the corresponding value in cc
    if(!(strcmp("P",h2->membership)))
    {
        cc=1;
        printf("\n Great !You are a platinum member\n");
    }

    if(!(strcmp("G",h2->membership)))
    {
        cc=2;
        printf("\n Great !You are a gold member\n");
    }

    if(!(strcmp("S",h2->membership)))
    {
        cc=3;
        printf("\n Great !You are a silver member\n");
    }
    // calculating the member discount as per the membership policies
    switch(cc)
    {
        case 1:
             finalpay=pay-(0.1*pay);
             break;
        case 2:
            finalpay=pay-(0.07*pay);
            break;
        case 3:
            finalpay=pay-(0.05*pay);
            break;
    }

    //only if the customer is a member
    if(cc!=0)
    {
        setColor(44);
        printf("\n AMOUNT PAYABLE AFTER APPLYING MEMBER DISCOUNT : %.2f (INR)",finalpay);
        setColor(15);

        //to check the eligibility of birthday discount
        if((h2->bday.dd == hd->cur_date.dd) && (h2->bday.mm == hd->cur_date.mm))
        {
            d=cc; //to store the type of membership
        }

        int pp=0;       //stores the percentage of discount

        // only if the bill generation date matches with the bday
        if(pp!=0)
        {
        switch(d)
        {
            case 1:
                  finalpay=finalpay-(0.30*finalpay);
                  pp=30;
                  break;
            case 2:
                  finalpay=finalpay-(0.25*finalpay);
                  pp=25;
                  break;
            case 3:
                  finalpay=finalpay-(0.20*finalpay);
                  pp=20;
                  break;
        }

            printf("\n\n AHH ITS YOUR BIRTHDAY!!!\nCongrats on getting an additional discount of %d%%",pp);
            printf("\n AMOUNT PAYABLE AFTER APPLYING SPECIAL BDAY DISCOUNT ");
            setColor(44);
            printf("%.2f (INR)",finalpay);
            setColor(15);
        }
        int chh=0;  //for storing the choice entered by user if he wishes to redeem points or not
        int pts=0;  // maximum points which can be redeemed on a particular purchase
        int ou=0;   //do -while loop counter
        //checks if eligible for greater than 500  points discount
        if(h2->points>500)
        {
            //finalpay updated as per membership policies
            switch(cc)
            {
                case 1:
                     finalpay-=0.25*finalpay;
                     break;
                case 2:
                    finalpay-=0.20*finalpay;
                    break;
                case 3:
                    finalpay-=0.15*finalpay;
                    break;
            }

            printf("\n AMOUNT PAYABLE AFTER APPLYING GREATER THAN 500 POINTS DISCOUNT:  ");
            setColor(44);
            printf("%.2f (INR)",finalpay);
            setColor(15);

        }
        else
        {
            chh=0;//initializes choice
            if(h2->points!=0)
            {
                printf("\n 1. Do you wish to redeem your points now \n 2. Would like to add them to 500 to avail discounts in future\n");
                printf("\n Enter your choice:	");
                scanf("%d",&chh);
                if(chh==1)
                {
                    float p,g,s=0;  //maximum points that can be redeemed per category on the current purchase
                    float point;
                    //finalpay divided by 2 so that the points are redeemed such that the final-pay is not negative or zero
                    p=(finalpay/2)/1;

                    g=(finalpay/2)/0.5;

                    s=(finalpay/2)/0.25;

                    //assigning the max redeemable points to point
                    switch(cc)
                    {
                        case 1:
                             point=p;
                             break;
                        case 2:
                             point=g;
                             break;
                        case 3:
                             point=s;
                             break;
                    }
                    //if the redeemable points exceed the available points then the available points are the max which can be redeemed
                    if(h2->points<point)
                        point=h2->points;

                    printf("\n On the current purchase you can redeem maximum points :");
                    printf("%.2f",point);

                    do
                    {
                        ou=0;
                        printf("\n Enter the points you wish to redeem  ");
                        printf("\n Enter your choice:	");
                        scanf("%d",&pts);
                        if(pts<=point) //the entered points are redeemable
                        {
                            //updating the final pay as per the membership policies by converting the points to INR
                            //updating the points in the customer's account after he has redeemed some/all points
                            switch(cc)
                            {

                                case 1:
                                     finalpay=finalpay-pts;
                                     h2->points-=pts;
                                     break;
                                case 2:
                                     finalpay=finalpay-(pts*0.5);
                                     h2->points-=pts;
                                    break;
                                case 3:
                                     finalpay=finalpay-(pts*0.25);
                                     h2->points-=pts;
                                    break;
                            }

                            printf("\n Points left after redemption:");
                            setColor(44);
                            printf("\t %d",h2->points);
                            setColor(15);
                            printf("\n AMOUNT PAYABLE AFTER POINTS REDEMPTION DISCOUNT :%.2f (INR)",finalpay);
                        }

                        else
                        {
                            //if the entered points are greater than the redeemable limit
                            printf("\n These many points can't be redeemed  ");
                            printf("\n AMOUNT PAYABLE :%.2f (INR)",finalpay);
                            ou=1; //updates ou to make the customer enter the points again or proceed without redemption

                        }
                    }while(ou==1);
                }
                else
                {
                    printf("\n OK!!");      // wishes to save points for future
                }
            }
        }
    }
    else if(cc==0)      //not an existing member
    {
        char ch2;
        char ch3;
        offerzone();    //displays the different memberships available and the associated policies
        printf("\n\n Do you want to take membership?(Y/N)\n\n");
        printf("\n Enter your choice:	");
        scanf(" %c",&ch2);

        if(ch2 == 'Y' || ch2=='y')  // wishes to be a member
        {
            printf("\n What type of membership do you want to take?(P/G/S):\t");
            printf("\n Enter your choice:	");
            scanf(" %c",&ch3);
            // type of membership taken and associated points updated in member's account as per membership policies
            if(ch3 == 'P' || ch3 == 'p')
            {
                strcpy(h2->membership,"P");
                h2->points=100;
                setColor(11);
                printf("\n\n Thanks for becoming our member!");
                printf("\n Membership:Platinum");
                printf("\n Initial Points:100");
                setColor(15);
            }
            else if(ch3 == 'G' || ch3 == 'g')
            {
                strcpy(h2->membership,"G");
                h2->points=100;
                setColor(11);
                printf("\n\n Thanks for becoming our member!");
                printf("\n Membership:Gold");
                printf("\n Initial Points:100");
                setColor(15);
            }
            else if(ch3 == 'S' || ch3 == 's')
            {
                strcpy(h2->membership,"S");
                h2->points=100;
                setColor(11);
                printf("\n\n Thanks for becoming our member!");
                printf("\n Membership:Silver");
                printf("\n Initial Points:100");
                setColor(15);
            }

        }

    }

    setColor(74);
    printf("\n\n\n\n");

    int r=1;    //stars counter
    char stars[10];
    setColor(67);
    printf("\n\n THANK YOU!! VISIT AGAIN");
    setColor(15);
    printf(" \n\n Take a Minute to Rate Us     ");

    printf("\n\n How Many Stars Would You Give Us (***** means Best Services)?\n"); //input of rating taken in terms of *
    int j=0;        //for traversing the string
    setColor(22);
    getchar();
    fgets(stars,10,stdin);  //takes the input as a string

    while(stars[j]!='\0')
    {
        r++;        //counts the no of stars
        j++;
    }

    setColor(15);
    r=r-2;
    h2->rate=r;     //updating the rating give by user

    if(cc!=0)       //only for members
    {
        //calculation of the points earned on this purchase as per membership policies
        switch(cc)
        {

        case 1:
             cur_points+=finalpay*0.3;
             break;
        case 2:
             cur_points+=finalpay*0.2;
            break;
        case 3:
             cur_points+=finalpay*0.1;
            break;
        }
        setColor(46);
        printf("\n Points Earned on this Purchase:\t%d",cur_points);
        setColor(67);
        h2->points+=cur_points; //adds this points into user's account
        printf("\n Total Points:\t%d",h2->points);
        setColor(42);
    }
    printf("\n\n\n HAVE A NICE DAY!");


    setColor(15);
    printf("\n ");

 /* bill *gtr=head4;
    while(gtr->next!=NULL)
        gtr=gtr->next;

    gtr->total_price=finalpay;*/

    update_details();
    exit(0);// because here the 3 options of checking location etc look irrelevant
}



void update_details()
{
    fp=fopen("Inventory.csv","w");// opening file to update inventory records
    fp1=fopen("Customer_details.csv","w");// opening file to update customer records
    fp2=fopen("Bill_details.csv","w");// opening file to update bill records
   // fp3=fopen("Bill.csv","w");

    if(fp==NULL)    //in case the file pointer returns zero
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }

    if(fp1==NULL)  //in case the file pointer returns zero
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }

    if(fp2==NULL)  //in case the file pointer returns zero
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }
   /* if(fp3=NULL)
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }*/

    item *ptr=head1;        //pointer to item linked list
    customer *ltr=head2;    // pointer to customer linked list
    bill_det *atr=head3;    //pointer to bill_det linked list

    //for writing the headings in the inventory file
    fprintf(fp,"Item ID,Category,Name,Location,Quantity,Unit Price\n");
    while(ptr->next!=NULL)
    {
        //writing each record line wise into the file
        fprintf(fp,"%d,%s,%s,%s,%d,%d\n",ptr->id,ptr->category,ptr->name,ptr->location,ptr->qty,ptr->price);
        //moving to the next node
        ptr=ptr->next;
    }
    //for writing the last record into the file
    fprintf(fp,"%d,%s,%s,%s,%d,%d",ptr->id,ptr->category,ptr->name,ptr->location,ptr->qty,ptr->price);

    //for writing the headings in the Customer_details file
    fprintf(fp1,"Customer_Id,Name,BirthDate,BirthMonth,BirthYear,Phone No.,Date added,Month added,Year added,Membership,Points,Rating\n");
    while(ltr->next!=NULL)
    {
        //writing each record line-wise into the file
        fprintf(fp1,"%d,%s,%d,%d,%d,%s,%d,%d,%d,%s,%d,%d\n",ltr->id,ltr->name,ltr->bday.dd,ltr->bday.mm,ltr->bday.yy,ltr->phoneno,ltr->entry.dd,ltr->entry.mm,ltr->entry.yy,ltr->membership,ltr->points,ltr->rate);
        //moving to the next node
        ltr=ltr->next;
    }
    //for writing the last record into the file
    fprintf(fp1,"%d,%s,%d,%d,%d,%s,%d,%d,%d,%s,%d,%d",ltr->id,ltr->name,ltr->bday.dd,ltr->bday.mm,ltr->bday.yy,ltr->phoneno,ltr->entry.dd,ltr->entry.mm,ltr->entry.yy,ltr->membership,ltr->points,ltr->rate);

    //writing the headings in the Bill_details file
    fprintf(fp2,"Customer Id,Bill No.,ItemName,Quantity,Total_Price,Date,Month,Year\n");
    while(atr->next!=NULL)
    {
        //writing each record line-wise into the file
        fprintf(fp2,"%d,%d,%s,%d,%d,%d,%d,%d\n",atr->customerno,atr->billno,atr->itemname,atr->qty,atr->t_price,atr->cur_date.dd,atr->cur_date.mm,atr->cur_date.yy);
        //moving to the next node
        atr=atr->next;
    }
    //for writing the last record into the file
    fprintf(fp2,"%d,%d,%s,%d,%d,%d,%d,%d",atr->customerno,atr->billno,atr->itemname,atr->qty,atr->t_price,atr->cur_date.dd,atr->cur_date.mm,atr->cur_date.yy);

  /*
    //for writing the headings in the Bill file
    fprintf(fp3,"Customer Id,Bill No.,Total_Price,Date,Month,Year\n");

    while(mtr->next!=NULL)
    {

        printf("%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
        //for writing each record line-wise
        fprintf(fp3,"%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
        // for moving to the next node
        mtr=mtr->next;
    }
  //printf("%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
    //for writing the last record into the file
    fprintf(fp3,"%d,%d,%d,%d,%d,%d",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
*/
    fclose(fp);     //closing the inventory file
    fclose(fp1);    //closing the customer details file
    fclose(fp2);    //closing the bill details file
 // fclose(fp3);    //closing the bill file

}



