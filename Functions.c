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
int counter=0;
FILE *fp1=NULL;//file pointer used in details()
FILE *fp=NULL;//file pointer used in inventory()
FILE *fp2=NULL;
int we=0,wp=0,wf=0;

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
int screen1(char ch)
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
            printf("File did not open successfully");
            exit(0);
        }

        rewind(fp);//moves the files to the beginning

        char Line[sizeof(item)];//contains a single line of file
        fgets(Line,sizeof(item),fp);
        char* delimiter=",";//to separate data by commas


        item *ptr=head1;
        while(fgets(Line,sizeof(item),(FILE *)fp)!=NULL)
        {
            item *temp=(item *)malloc(sizeof(item));
            temp->id=atoi(strtok(Line,delimiter));
            strcpy(temp->category,strtok(NULL,delimiter));
            strcpy(temp->name,strtok(NULL,delimiter));
            strcpy(temp->location,strtok(NULL,delimiter));
            temp->qty=atoi(strtok(NULL,delimiter));
            temp->price=atoi(strtok(NULL,delimiter));
            temp->next=NULL;


            if(head1==NULL)
            {
                head1=temp;
            }
            else
            {
                ptr=head1;

                while(ptr->next!=NULL)
                {

                    ptr=ptr->next;
                }
                ptr->next=temp;
            }
        }

        fclose(fp);

        we=1;
    }

    if(wp==0)
    {
        fp1=fopen("Customer_details.csv", "r");

        if(fp1==NULL)
        {
            printf("The file did not open successfully");
            exit(0);
        }

        rewind(fp1);//takes the file pointer back to the starting of the file

        char Line[sizeof(customer)];//one line of file containing a customer's details
        fgets(Line,sizeof(customer),fp1);
        char* delimiter=",";//separates the data in a line


        customer *ptr=head2;

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
            printf("The file did not open successfully");
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

    if(ch=='a' || ch=='A')
	{
		for(k=0;k<3;k++)
		{
			printf("\n Enter the password\t");
			for( i = 0;;)
			{
			    c = getch();
			    if((c>='A' && c<='Z') ||(c>='a' && c<='z'))
                {
                    password[i] = c;
                    i++;
                    printf("*");
                }

                if(c=='\b' && i>=1)
                {
                    printf("\b \b");
                    --i;
                }
                if(c=='\r')
                {
                    password[i]='\0';
                    break;
                }

			}

			if(!strcmp(password,"ADMIN"))
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
                if(ctr==3)
                {
                    setColor(12);
                    printf("\n\n\n ACCESS LOCKED!! CONTACT SERVER");
                    setColor(15);
                }
                else
                {
                    do
                    {
                        g=0;
                        printf("\n 1.Try Again.\n 2.Show password");
                        printf("\n Enter your choice	");
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
                           printf("\n\nENTERED WRONG CHOICE\n\n");
                           setColor(15);
                            g=1;
                        }
                    }while(g==1);
                }
            }
        }
    }
	else if(ch=='c' || ch=='C')
    {
        customer_entry();
    }
    else
    {
        setColor(12);
        printf("\n\nENTERED WRONG CHOICE\n\n");
        setColor(15);
        printf("\n Are you admin(a) or customer(c) \n ");
        scanf(" %c",&ch);
        screen1(ch);
    }
}

//admin home page
int correctpass()
{
	int c;//for choice by the user
	char d;//takes input from user whether to log out or not
	int ch=1;//for the do while function
	int w=0;
	setColor(45);
	printf("\n\n\n\n WELCOME ADMIN");
	setColor(15);
	do
    {
        printf("\n\n Do you want to :\n 1. View inventory and stock\n 2. View Customer details\n 3. Statistics\n 4. Logout\n\n");
        printf("\n Enter you choice\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                inventory();
                break;
            case 2:
                customerDetails();
                break;
                /*
            case 3:
                statistics();
                break();*/
            case 4:
                do
                {
                    w=0;
                    printf("\n\nDo you want to Log Out?(y/n)\n");
                    scanf(" %c",&d);
                    if((d==121)||(d==89))
                    {
                        setColor(98);
                        printf("\n\nYou have been logged out successfully.\n");
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
                    printf("\n\nENTERED WRONG CHOICE\n");
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
        setColor(1);
        printf("\n\n CATEGORIES \n\n");
        setColor(15);
        printf(" 1. Food\n 2. Clothes\n 3. Essentials\n 4. Stationery\n 5. Kitchen Utensils\n 6. All \n 7. Go to Home Page\n\n");
        printf("Enter the Category to View:\t\n");
        scanf("%d",&choice);


        if(choice>=1&&choice<=7)
        {
            int e=1;//maintains serial number
            int w;//for getting the maximum character length
            int max=0;//hold the maximum character length in name
            int q=0;//for checking the length of current item name
            item *ctr=head1->next;//to point to next node
            item *ltr=head1;//to traverse through the list

            if(choice!=7)
            {
                setColor(3);
                printf("\nS.No\tName\t");
                max=strlen(head1->name);

                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max<w)
                        max=w;
                    ctr=ctr->next;
                }

                for(int t=0;t<=(max-4);t++)
                {
                    printf(" ");
                }

                printf("Quantity\tUnit_Price\tLocation\n");
                setColor(15);
            }
            if(choice <=5)
            {
                while(ltr!=NULL)
                {

                    if((ltr->id)==choice)
                    {
                        printf("%d\t%s",e,ltr->name);
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
            else if(choice==6)
            {
                while(ltr!=NULL)
                {
                    printf("%d\t%s",e,ltr->name);
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
                correctpass();
            }
        }
        else
        {
            setColor(12);
            printf("\n\nENTERED WRONG CHOICE");
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

            printf("\nOPTIONS\n");
        setColor(15);
        printf("\n\n1.View Members\n2.View all customers\n3.Go to Home Page\n\n");
        printf("Enter your choice :\t\n");
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
                printf("\nSNo.\tName\t");
                max=strlen(head2->name);
                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max < w)
                        max=w;
                    ctr=ctr->next;
                }
                for(int t=0;t<=(max-4);t++)
                {
                    printf(" ");
                }
                printf("\tDOB\t\t\tPhone no.\tDate\t\tMembership\tPoints\tRating\n");
                setColor(15);
                while(ltr!=NULL)
                {
                    if(strcmp(ltr->membership,membership_check))
                    {
                        printf("%d\t%s",e,ltr->name);
                        q=strlen(ltr->name);
                        for(int t=0;t<=(max-q);t++)
                        {
                            printf(" ");
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

                        printf("\t\t%s\t",ltr->phoneno);

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
                            printf("\t%s\n",ltr->membership);
                        printf("\t\t%s\t",ltr->membership);
                        printf("\t\t%d\t",ltr->points);
                        printf("\t\t%d\t",ltr->rate);
                        e++;
                    }
                        ltr=ltr->next;
                }
            }
            else if(choice==2)
            {
                setColor(11);
                printf("\nSNo.\tName\t");
                max=strlen(head2->name);
                while(ctr!=NULL)
                {
                    w=strlen(ctr->name);
                    if(max < w)
                        max=w;
                    ctr=ctr->next;
                }
                for(int t=0;t<=(max-4);t++)
                {
                    printf(" ");
                }
                printf("\tDOB\t\t\tPhone no.\tDate\t\tMembership\tPoints\tRating\n");
                setColor(15);
                while(ltr!=NULL)
                {
                    printf("%d\t%s",e,ltr->name);
                    q=strlen(ltr->name);
                    for(int t=0;t<=(max-q);t++)
                    {
                        printf(" ");
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
                correctpass();
            }
        }
        else
        {
           setColor(12);
           printf("ENTERED WRONG CHOICE ");
           setColor(15);
        }
    }while(z==1);
}

//customer home page
void customer_entry()
{

	int c;//for choice by the user
	char d;//takes input from user whether to log out or not
	int ch=1;//for the do while function
	int w=0;
	setColor(45);
        printf("\n\n\n\n WELCOME CUSTOMER");
	setColor(15);
	do{
        printf("\n\n Do you want to :\n 1. Check Location\n 2. Generate Bill\n 3. Logout\n\n");
        printf("\n Enter you choice\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                checkLocation();
                break;
            case 2:
                generateBill();

                break;
            case 3:
                do
                {
                    w=0;
                        printf("\n\nDo you want to Log Out?(y/n)\n");
                        scanf(" %c",&d);
                        if((d==121)||(d==89))
                        {
                            setColor(98);
                            printf("\n\nYou have been logged out successfully.\n");
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
                    printf("\n\nENTERED WRONG CHOICE\n");
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

            printf("\n\nWhat item do you need to search for:\t ");
            getchar();
            gets(choice);


            setColor(46);
            printf("\n\n\t\tLOCATION OF PRODUCT	\n");
            setColor(1);

            e=1;//for serial number
            max=0;//hold the maximum character length in name
            q=0;//for checking the length of current item name
            ctr=head1->next;//to point to next node
            ltr=head1;//to traverse through the list

            setColor(3);
            //incorrect name
            printf("\nS.No\tName");
            max=strlen(head1->name);
            while(ctr!=NULL)
            {
                w=strlen(ctr->name);
                if(max<w)
                    max=w;
                ctr=ctr->next;
            }
            for(int t=0;t<=(max-4);t++)
            {
                printf(" ");
            }

            printf("Location\n");
            setColor(15);
            int c=0;
            while(ltr!=NULL)
            {
                if(!strcmp(ltr->name,choice))
                {
                    printf("%d\t%s",e,ltr->name);
                    q=strlen(ltr->name);
                        for(int t=0;t<=(max-q);t++)
                        {
                            printf(" ");
                        }
                    printf("%s",ltr->location);
                    e++;
                    c=1;
                }
                ltr=ltr->next;
            }
            if(c==0)
            {
                setColor(60);
                printf("NULL \tNULL \t\t\t      NULL");
                printf("\n\nITEM NOT FOUND");
                setColor(15);
            }



            do
            {
                de=0;
                printf("\n1. Do you want to find another product\n2. Go to home page\n\n");
                scanf("%d",&cho);
                switch(cho)
                {
                    case 1:
                        dh=1;
                        break;
                    case 2:
                        break;
                    default:
                        printf("Entered Wrong Choice");
                        de=1;
                }

            }while(de==1);
        }while(dh==1);
}


//Generate bill
void generateBill()
{
    char name1[500000];
    date bday;
    char phoneno[11];
    date cur_date;
    int h=0;//for traversing in array of units in bill

    int customerid,billno;

    printf("\t\t\t\t\t\t CUSTOMER DETAILS	\n");
    printf("Enter Name: ");
    getchar();
    gets(name1);

    printf("Enter Birthdate(dd/mm/yyyy): ");
    scanf("%d/%d/%d",&bday.dd,&bday.mm,&bday.yy);

    printf("Enter Phone Number(10digit): ");
    getchar();
    gets(phoneno);

    time_t now;
    time(&now);
    struct tm *local=localtime(&now);

    cur_date.dd=local->tm_mday;
    cur_date.mm=local->tm_mon+1;
    cur_date.yy=local->tm_year+1900;

     customer *ltr=head2;
     customer *ztr=head2;

    while(ltr!=NULL)
    {
        if(!strcmp(phoneno,ltr->phoneno))//new node when match
            break;
        ltr=ltr->next;
    }
    customer *new_cust = (customer *)malloc(sizeof(customer));

    customer *ytr=head2;

    if(ltr==NULL)
    {
        while(ytr->next!=NULL)
        {
            ytr=ytr->next;
        }
        customerid=(ytr->id)+1;
        //addCustomer()

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
            strcpy(new_cust->membership,"N");
            new_cust->next=NULL;

              while(ztr->next!=NULL)
            {
                ztr=ztr->next;
            }
            ztr->next=new_cust;

    }
    else if(ltr!=NULL)
    {
        customerid=ltr->id;
    }



   bill_det *atr=head3;
  while(atr->next!=NULL)
  {
     atr=atr->next;
  }
  billno=((atr->billno)+1);

    setColor(11);
    printf("\t\t\t\t\t\t      STOCKS	\n");
    setColor(15);

  item *ptr=head1,*ctr=head1->next;
    int e=1;//for serial number
    int w;//for getting the maximum character length
    int max=0;//hold the maximum character length in name
    int q=0;//for checking the length of current item name

    max=strlen(head1->name);
    while(ctr!=NULL)
    {
        w=strlen(ctr->name);
        if(max<w)
            max=w;
        ctr=ctr->next;
    }

    char cat[500000];
    strcpy(cat,ptr->category);
    setColor(22);
    printf("%s\n\n",ptr->category);
    setColor(3);
    printf("S.no\tName");
    for(int t=0;t<=(max-4);t++)
    {
        printf(" ");
    }
    printf("Quantity\tPrice\n");
    setColor(15);
    while(ptr!=NULL)
    {
        if(strcmp(cat,ptr->category))
        {
            setColor(22);
            printf("\n%s\n\n",ptr->category);
            e=1;
            setColor(3);
            printf("S.no\tName");
            for(int t=0;t<=(max-4);t++)
            {
                printf(" ");
            }
            printf("Quantity\tPrice\n");
            setColor(15);
        }
        printf("%d.\t%s",e,ptr->name);
        q=strlen(ptr->name);
        for(int t=0;t<=(max-q);t++)
        {
            printf(" ");
        }
        if((ptr->qty)<=2)
            setColor(12);
        printf("%d\t\t",ptr->qty);
        setColor(15);
        printf("%d\n",ptr->price);
        strcpy(cat,ptr->category);
        e++;
        ptr=ptr->next;
    }

    char item_name[100];
    int item_qty=0;
    int ch=0;
    int y=0;
    int totalprice=0;

    bill_det *itr=head3;
    char n;
    item *notfound=head1;
    item *htr=head1;
    int new_qty;
    int check=0;
    int x=1;
    int old_price;
    int z,re;
    int cttr=1;
    int k;
    int l;

    do
    {
        y=0;
        check=0;
        bill_det *temp= (bill_det*)malloc(sizeof(bill_det));
        temp->customerno=customerid;
        temp->billno=billno;
        temp->cur_date.dd=cur_date.dd;
        temp->cur_date.mm=cur_date.mm;
        temp->cur_date.yy=cur_date.yy;
        int ex=0;
        int zz=0;
        do
        {
            l=0;
            printf("\n\nEnter Name of the Item you want to buy:");
            printf("\n ");
            gets(item_name);
            notfound=head1;

                while(notfound!=NULL)
                {
                    if(!(strcmp(item_name,notfound->name)))
                            break;
                    notfound=notfound->next;
                }
                if(notfound==NULL)
                {

                    setColor(60);
                    printf("\n Ooops!Item not found....");
                    setColor(15);
                    do
                    {
                    ex=0;
                    printf("\n1.Do you want to enter again.\n2.Quit");
                    printf("\n");
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
                          setColor(60);
                          printf("\n Incorrect input!!!\n");
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
                if((itr->billno)==(temp->billno))
                {
                    if(!strcmp(item_name,itr->itemname))
                    {
                        setColor(46);
                        printf("You have already bought this item!\nQuantity is %d\n",itr->qty);
                        setColor(15);

                        do
                        {
                            w=0;
                                printf("\n\nDo you want to update?(y/n)\n");
                                scanf("%c",&n);
                                if(((n==121)||(n==89))&& l!=0)
                                {
                                    do
                                    {
                                    x=1;

                                    printf("Enter the Quantity:\t");
                                    scanf("%d",&new_qty);
                                    old_price=itr->t_price;
                                    while(htr!=NULL)
                                    {
                                        if(!strcmp(item_name,htr->name))
                                            break;
                                        htr=htr->next;
                                    }
                                    (itr->t_price)=new_qty*(htr->price);
                                    if(new_qty<(itr->qty))
                                    {
                                        (htr->qty)+=(itr->qty)-new_qty;
                                        totalprice-=old_price-(itr->t_price);
                                    }
                                    else
                                    {
                                        (htr->qty)-=new_qty-(itr->qty);
                                        totalprice+=(itr->t_price)-old_price;
                                    }

                                    if(htr->qty<0)
                                    {
                                        setColor(12);
                                        printf("Not enough left!\nEnter Again!\n\n");
                                        setColor(26);
                                        printf("Quantity Available: %d\n\n",(htr->qty+(new_qty-(itr->qty))));
                                        setColor(15);
                                        x=0;
                                       (htr->qty)+=new_qty-(itr->qty);
                                        totalprice-=(itr->t_price)-old_price;

                                    }
                                    }while(x==0);
                                    itr->qty=new_qty;
                                    check=1;

                                }
                                else if((n==78)||(n==110))
                                {
                                    check =1;
                                }
                                else
                                {
                                    w=1;
                                }
                        }while(w==1);
                    }
                }
                itr=itr->next;
            }

       if(check==0)
       {
           do
            {
                ch=0;
                printf("Enter the Quantity:\t");
                scanf("%d",&item_qty);

                ptr=head1;
                while(ptr!=NULL)
                {
                    if(!strcmp(item_name,ptr->name))
                    {
                        break;
                    }
                    ptr=ptr->next;
                }
                if((item_qty)>(ptr->qty))
                {
                    ch=1;
                    setColor(12);
                    if(ptr->qty>0)
                    {
                        printf("Not enough left!\nEnter Again!\n\n");
                        setColor(26);
                        printf("Quantity Available: %d\n\n",ptr->qty);
                          setColor(15);
                    }
                    else
                    {
                        printf("Stock Finished\n\n");
                        setColor(15);
                        item_qty=0;
                        break;

                    }

                }
            }while(ch==1);
            if(item_qty==0 && counter==0)
            {
                setColor(43);
                printf("\n THANKS FOR VISITING");
                setColor(15);

            }
            if(item_qty!=0)
            {

            (temp->t_price)=(item_qty)*(ptr->price);
            (temp->qty)=item_qty;
            strcpy(temp->itemname,item_name);
            totalprice+=(temp->t_price);
            temp->next=NULL;
            (ptr->qty)=(ptr->qty)-item_qty;


            bill_det *rtr = head3;

            if(head3==NULL)
            {
                head3=temp;
            }
            else
            {
                while(rtr->next!=NULL)
                {
                    rtr=rtr->next;
                }
                rtr->next=temp;
            }
            }
            else
            {

                free (temp);
            }
       }

        int d,z;

        do
        {
            counter++;
            z=0;
                printf("\n\nDo you want to enter more items?(y/n)\n");
                scanf(" %c",&d);
                if((d==121)||(d==89))
                {
                    (ptr->qty)-=item_qty;
                    y=1;
                    getchar();
                    h++;
                }
                else if((d==78)||(d==110))
                {
                    printf("\n");
                    printf("\n");
                    printf("Your current bill is ");
                    setColor(60);
                    printf("%d",totalprice);
                    setColor(15);
                }
                else
                {
                    printf("INVALID SELECTION");
                    z=1;
                }
        }while(z==1);
        }
            else
            {
                printf("\n");
                    printf("\n");
                    printf("Your current bill is ");
                    setColor(60);
                    printf("%d",totalprice);
                    setColor(15);

            }

    }while(y==1);


     int choice2,choice3;
    int j=0;
    bill_det *trav = head3;
    int max_new=0;
    int sno=1;
    int rw,ew,d;
    item *dtr=head1;
    printf("\n\n1.Do you want to modify your shopping list.\n2.Generate bill\n");
    scanf("%d",&choice2);
    do
    {
        y=0;
        switch(choice2)
        {
        case 1:
                setColor(45);
                printf("\t\t\tYour current bill\n\n");
                setColor(22);
                printf("S.no\tName");
                max_new=strlen(head3->itemname);
                trav=head3->next;
                while(trav!=NULL)
                {
                    h=strlen(trav->itemname);
                    if(max_new<h)
                        max_new=h;
                    trav=trav->next;
                }
                for(int t=0;t<=(max_new-4);t++)
                {
                    printf(" ");
                }
                printf("\tQuantity\t\tTotal Price\n");
                setColor(15);

                trav=head3;
                sno=1;
                while(trav!=NULL)
                {
                    if((trav->billno)==billno)
                    {
                        printf("%d\t%s",sno,trav->itemname);
                         q=strlen(trav->itemname);
                            for(int t=0;t<=(max_new-q);t++)
                            {
                                printf(" ");
                            }
                        printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                        sno++;
                    }
                    trav=trav->next;
                }

               while(1)
               {
                printf("\n\n1. Do you want to delete a item\n2. Do you want to modify the quantity\n3. Finished\n\n");
                scanf("%d",&choice3);
                trav=head3;
                do
                {
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
                                    if((trav->billno)==billno)
                                        break;
                                    trav=trav->next;
                                }
                                if(trav!=NULL)
                                {
                                trav=head3;
                                printf("Enter the item you want to delete: ");
                                getchar();
                                gets(item_name);
                                while(trav!=NULL&&(strcmp(trav->next->itemname,item_name)))
                                    trav=trav->next;
                                if(trav==NULL)
                                    {
                                        setColor(12);
                                        printf("\nItem Not Found!\n");
                                        setColor(15);
                                    }
                                else
                                    {
                                        bill_det *p=trav->next;
                                        trav->next=trav->next->next;
                                        while(dtr!=NULL)
                                        {
                                            if(!strcmp(dtr->name,p->itemname))
                                                break;
                                            dtr=dtr->next;
                                        }
                                        (dtr->qty)+=(p->qty);
                                        totalprice-=(p->t_price);
                                        free(p);

                                    }
                                   setColor(45);
                printf("\t\t\tYour current bill is \n\n");
                setColor(22);
                printf("S.no\tName");
                max_new=strlen(head3->itemname);
                trav=head3->next;
                while(trav!=NULL)
                {
                    h=strlen(trav->itemname);
                    if(max_new<h)
                        max_new=h;
                    trav=trav->next;
                }
                for(int t=0;t<=(max_new-4);t++)
                {
                    printf(" ");
                }
                printf("\tQuantity\t\tTotal Price\n");
                setColor(15);

                trav=head3;
                sno=1;
                while(trav!=NULL)
                {
                    if((trav->billno)==billno)
                    {
                        printf("%d\t%s",sno,trav->itemname);
                         q=strlen(trav->itemname);
                            for(int t=0;t<=(max_new-q);t++)
                            {
                                printf(" ");
                            }
                        printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                        sno++;
                    }
                    trav=trav->next;
                }

                                do
                                {
                                    ew=0;
                                        printf("\n\nDo you want to delete more items?(y/n)\n");
                                        scanf(" %c",&d);
                                        if((d==121)||(d==89))
                                        {
                                            rw=1;
                                        }
                                        else if((d==78)||(d==110))
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            ew=1;
                                        }
                                }while(ew==1);
                           }
                           else
                           {
                               printf("Bill is Empty");
                               break;
                           }
                           }while(rw==1);

                            break;
                        case 2:
                            htr=head1;
                            trav=head3;
                            int d=0;
                           do
                           {
                                trav=head3;
                               re=0;

                     //not working//
                            printf("Enter the item you want to modify: ");
                            getchar();
                            gets(item_name);

                            while(trav->next!=NULL)
                            {
                                if(!strcmp(trav->itemname,item_name))
                                {
                                    d=0;
                                      break;
                                }
                                else
                                {
                                      trav=trav->next;
                                      d=1;
                                }


                            }
                            if(d==1)
                            {
                                setColor(60);
                                printf("\n You have not bought this item!!!");
                                setColor(15);
                            }
                            else
                            {
                            do
                            {
                            x=1;
                            printf("Enter the Quantity:\t");
                            scanf("%d",&new_qty);
                            old_price=trav->t_price;
                            while(htr!=NULL)
                            {
                                if(!strcmp(item_name,htr->name))
                                    break;
                                htr=htr->next;
                            }
                            (trav->t_price)=new_qty*(htr->price);
                            if(new_qty<(trav->qty))
                            {
                                (htr->qty)+=(trav->qty)-new_qty;
                                totalprice-=old_price-(trav->t_price);
                            }
                            else
                            {
                                (htr->qty)-=new_qty-(trav->qty);
                                totalprice+=(trav->t_price)-old_price;
                            }

                            if((htr->qty)<0)
                            {
                                setColor(12);
                                printf("Not enough left!\nEnter Again!\n\n");
                                setColor(26);
                                printf("Quantity Available: %d\n\n",(htr->qty+(new_qty-(trav->qty))));
                                setColor(15);
                                x=0;
                               (htr->qty)+=new_qty-(trav->qty);
                                totalprice-=(trav->t_price)-old_price;

                            }
                            }while(x==0);
                            }
                            trav->qty=new_qty;
                               setColor(45);
                printf("\t\t\tYour bill\n\n");
                setColor(22);
                printf("S.no\tName");
                max_new=strlen(head3->itemname);
                trav=head3->next;
                while(trav!=NULL)
                {
                    h=strlen(trav->itemname);
                        max_new=h;
                    if(max_new<h)
                    trav=trav->next;
                }
                for(int t=0;t<=(max_new-4);t++)
                {
                    printf(" ");
                }
                printf("\tQuantity\t\tTotal Price\n");
                setColor(15);

                trav=head3;
                sno=1;
                while(trav!=NULL)
                {
                    if((trav->billno)==billno)
                    {
                        printf("%d\t%s",sno,trav->itemname);
                         q=strlen(trav->itemname);
                            for(int t=0;t<=(max_new-q);t++)
                            {
                                printf(" ");
                            }
                        printf("\t%d\t\t\t%d\n",trav->qty,trav->t_price);
                        sno++;
                    }
                    trav=trav->next;
                }

                            do
                            {
                                z=0;
                                    printf("\n\nDo you want to update more items?(y/n)\n");
                                    scanf(" %c",&d);
                                    if((d==121)||(d==89))
                                    {
                                        re=1;
                                    }
                                    else if((d==78)||(d==110))
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        printf("INVALID SELECTION");
                                        z=1;
                                    }
                            }while(z==1);
                           }while(re==1);


                            break;
                        case 3:
                            printf("Your current bill is ");
                            setColor(60);
                            printf("%d",totalprice);
                            setColor(15);
                            update_details();
                            invoice(totalprice,billno);
                            break;
                        default:
                            printf("INVALID SELECTION!");
                            j=0;
                    }
                }while(j==0);
               }
                break;
        case 2:

                invoice(totalprice,billno);
                setColor(15);
            break;
        default:("INVALID SELECTION");
        y=1;
        }
        }while(y==1);


}

void offerzone()
{   setColor(98);
    printf("\n\t\t\t\t******OFFER ZONE******");
    setColor(15);
    printf("\n Become a member of shopify plaza and avail exciting discounts        ");
    setColor(21);
    printf("\n\nTYPES OF MEMBERSHIP");
    setColor(98);
    printf("\n\n1.PLATINUM");
    setColor(15);
    printf("\nRs250=100 points");
    printf("\nDiscounts\n1. Get 10%% off on every shopping.\n2. Get 25%% off if your points are more than 500.\n3. Get a special 30%% off on your Birthday.\n4. Upon redemption 1 point=1 INR");
    setColor(22);
    printf("\n\n2.GOLD");
    setColor(15);
    printf("\nRs200=100 points");
    printf("\nDiscounts\n1. Get 10%% off on every shopping.\n2. Get 20%% off if your points are more than 500.\n3. Get a special 25%% off on your Birthday.\n4. Upon redemption 1 point=0.5 INR");
    setColor(88);
    printf("\n\n3.SILVER");
    setColor(15);
    printf("\nRs150=100 points");
    printf("\nDiscounts\n1. Get 7%% off on every shopping.\n2. Get 15%% off if your points are more than 500.\n3. Get a special 15%% off on your Birthday.\n4. Upon redemption 1 point=0.25 INR");
    printf("\n");
}


void invoice(int totalprice,int billno)
{   int p=0;
    setColor(78);
	printf("\t\t\t\t\t\t\tINVOICE");
	printf("\n");
	setColor(15);

	bill_det *hd = head3;
	customer *h=head2;
	customer *h2=head2;
        while(hd->next!=NULL )
        {
            if(billno==hd->billno)
                break;
            hd=hd->next;
        }
    int cid=hd->customerno;
       while(h->next!=NULL)
       {
           if(h->id==cid)
                break;
            else
                h=h->next;
       }
	printf("\nBILL ID:\t");
	setColor(22);
	printf("%d",h->id);
	setColor(15);
	printf("\nDATE:\t");
	setColor(22);
	printf("%d/%d/%d",h->entry.dd,h->entry.mm,h->entry.yy);
	setColor(15);
	printf("\n\nCUSTOMER NAME:\t");
	setColor(22);
	puts(h->name);
	setColor(15);
    printf("\nPHONE NUMBER:\t");
    setColor(22);
    printf("%s",h->phoneno);
    setColor(15);
    printf("\nMEMBER:\t");
    setColor(22);
    printf("%s",h->membership);
    setColor(15);
    printf("\nPOINTS IN CARD:\t");
    setColor(22);
    printf("%d",h->points);
    setColor(90);
    printf("\n\t\t\tPURCHASE SUMMARY\n\n\n");
    //table for s.no,item ,price;
    int name_item;
    bill_det *ftr=head3;
    int sno=1,q;

    setColor(22);
    printf("S.no\tName");
                name_item=strlen(head3->itemname);
                ftr=head3->next;
                while(ftr!=NULL)
                {
                    p=strlen(ftr->itemname);
                    if(name_item<p)
                        name_item=p;
                    ftr=ftr->next;
                }
                for(int t=0;t<=(name_item-4);t++)
                {
                    printf(" ");
                }
                printf("\tQuantity\t\tTotal Price\n");
                setColor(15);

                ftr=head3;
                while(ftr!=NULL)
                {
                    if((ftr->billno)==billno)
                    {
                        printf("%d\t%s",sno,ftr->itemname);
                         q=strlen(ftr->itemname);
                            for(int t=0;t<=(name_item-q);t++)
                            {
                                printf(" ");
                            }
                        printf("\t%d\t\t\t%d\n",ftr->qty,ftr->t_price);
                        sno++;
                    }
                    ftr=ftr->next;
                }


    setColor(74);
    printf("\n TOTAL:\t%d",totalprice);

    setColor(60);//reddish
    float amount=0.0;
    amount=(0.05)*totalprice;
    printf("\n TAX (5%%) : %.2f",amount);
    float pay;
    pay=totalprice+amount;
    setColor(43);
    printf("\n GRAND TOTAL :\t%.2f\n\n\n\n",pay);
    setColor(15);
    char ch1;
    //whether a member or not
    hd=head3;
    h2=head2;

    while(hd->next!=NULL)
    {
        hd=hd->next;
    }

    while(h2->next!=NULL)
    {
        if(h2->id == hd->customerno)
            break;
        h2=h2->next;
    }

    int cc=0;
    int d=0;

    if(!(strcmp("P",h2->membership)))
    {
        cc=1;
        printf("\n Great !You are a platinum member");

    }
    if(!(strcmp("G",h2->membership)))
    {
        cc=2;
        printf("\n Great !You are a gold member");

    }
    if(!(strcmp("S",h2->membership)))
    {
        cc=3;
        printf("\n Great !You are a silver member");

    }



    float finalpay=0.0;

        switch(cc)
        {

        case 1:
             finalpay=pay-(0.1*pay);
             break;
        case 2:
            finalpay=pay-(0.1*pay);
            break;
        case 3:
            finalpay=pay-(0.07*pay);
            break;
        }


    if(cc!=0)
    {
    setColor(44);
    printf("\nAMOUNT PAYABLE AFTER APPLYING MEMBER DISCOUNT : %.2f",finalpay);
    setColor(15);
    if((h2->bday.dd == h->entry.dd) && (h2->bday.mm == h->entry.mm))
    {
        d=cc;
    }

    int pp=0;

            switch(d)
            {
                    case 1:
                          finalpay=finalpay-(0.30*pay);
                          pp=25;
                          break;
                    case 2:
                          finalpay=finalpay-(0.25*pay);
                          pp=20;
                           break;
                    case 3:
                           finalpay=finalpay-(0.20*pay);
                           pp=15;
                            break;
            }
    if(pp!=0)
    {
    printf("\n\nAHH ITS YOUR BIRTHDAY!!!\n Congrats on getting an additional discount of ");
    printf("\nAMOUNT PAYABLE AFTER APPLYING SPECIAL BDAY DISCOUNT ");
    setColor(48);
    printf("%.2f",finalpay);
    setColor(15);
    }
    int chh=0;
    int pts=0;
        if(h2->points>500)
        {
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

                 printf("\nAMOUNT PAYABLE AFTER APPLYING GREATER THAN 500 POINTS DISCOUNT:  ");
                 setColor(44);
                printf("%.2f",finalpay);
                setColor(15);


        }
        else
        {
                if(h2->points!=0)
                {
                      printf("\n1.Do you wish to redeem your points now \n2. Would like to add them to 500 to avail discounts in future\n");
                      getchar();
                      scanf("%d",&chh);
                }

        }

        if(chh==1)
        {
            printf("\n Enter the points you wish to redeem  ");
            scanf("%d",&pts);

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
        if(finalpay>=0)
        printf("\nAMOUNT PAYABLE AFTER POINTS REDEMPTION DISCOUNT :%.2f",finalpay);
        else
        printf("\nAMOUNT PAYABLE AFTER POINTS REDEMPTION DISCOUNT :0");
  //    setColor(48);
   //   printf("%.2f",finalpay);//not showing output
        setColor(15);
       }
        else
        {
            printf("\n Ok!!");

        }
    }

    if(cc==0)
    {
        char ch2;
        char ch3;
        offerzone();
        printf("\n\nDo you want to take membership?(Y/N)\n\n");
        scanf(" %c",&ch2);
        if(ch2 == 'Y' || ch2=='y')
        {
            printf("\nWhat type of membership do you want to take?(P/G/S):\t");
            scanf(" %c",&ch3);
            if(ch3 == 'P' || ch3 == 'p')
            {
                strcpy(h2->membership,"P");
                h2->points=100;
                setColor(11);
                printf("\n\nThanks for becoming our member!");
                printf("\n Membership:Platinum");
                printf("\n Initial Points:100");
                setColor(15);
            }
            else if(ch3 == 'G' || ch3 == 'g')
            {
                strcpy(h2->membership,"G");
                h2->points=100;
                setColor(11);
                printf("\n\nThanks for becoming our member!");
                printf("\n Membership:Gold");
                printf("\n Initial Points:100");
                setColor(15);
            }
            else if(ch3 == 'S' || ch3 == 's')
            {
                strcpy(h2->membership,"S");
                h2->points=100;
                setColor(11);
                printf("\n\nThanks for becoming our member!");
                printf("\n Membership:Silver");
                printf("\n Initial Points:100");
                setColor(15);
            }
        }
    }

     setColor(74);
    printf("\n\n\n\n");

    int r=1;
    char stars[10];
    setColor(67);
    printf("\n\n THANK YOU!! VISIT AGAIN");
    setColor(15);
    printf(" \n\nTake a minute to rate us     ");

    printf("\n\nHow many stars would u give us(***** means best services)?\n");
    int j=0;
     setColor(22);
     getchar();
     fgets(stars,10,stdin);

        while(stars[j]!='\0')
        {
            r++;
            j++;

        }
    setColor(15);
    r=r-2;
    h2->rate=r;
    setColor(42);
    printf("\n\n\nHAVE A NICE DAY!");
    setColor(15);
    printf("\n");
    update_details();
   exit(0);// because here the 3 options of checking loc etc look irrelevant
}


void update_details()
{
     fp=fopen("Inventory.csv","w");
    fp1=fopen("Customer_details.csv","w");
    fp2=fopen("Bill_details.csv","w");

    if(fp==NULL)
    {
        printf("File did not open successfully 1");
        exit(0);
    }
     if(fp1==NULL)
    {
        printf("File did not open successfully 2");
        exit(0);
    } if(fp2==NULL)
    {
        printf("File did not open successfully 3");
        exit(0);
    }

    item *ptr=head1;
    customer *ltr=head2;
    bill_det *atr=head3;

    fprintf(fp,"Item ID,Category,Name,Location,Quantity,Unit Price\n");
    while(ptr->next!=NULL)
    {
        fprintf(fp,"%d,%s,%s,%s,%d,%d\n",ptr->id,ptr->category,ptr->name,ptr->location,ptr->qty,ptr->price);
        ptr=ptr->next;
    }
   fprintf(fp,"%d,%s,%s,%s,%d,%d",ptr->id,ptr->category,ptr->name,ptr->location,ptr->qty,ptr->price);


    fprintf(fp1,"Customer_Id,Name,BirthDate,BirthMonth,BirthYear,Phone No.,Date added,Month added,Year added,Membership,Points,Rating\n");
    while(ltr->next!=NULL)
    {
        fprintf(fp1,"%d,%s,%d,%d,%d,%s,%d,%d,%d,%s,%d,%d\n",ltr->id,ltr->name,ltr->bday.dd,ltr->bday.mm,ltr->bday.yy,ltr->phoneno,ltr->entry.dd,ltr->entry.mm,ltr->entry.yy,ltr->membership,ltr->points,ltr->rate);
        ltr=ltr->next;
    }
    fprintf(fp1,"%d,%s,%d,%d,%d,%s,%d,%d,%d,%s,%d,%d",ltr->id,ltr->name,ltr->bday.dd,ltr->bday.mm,ltr->bday.yy,ltr->phoneno,ltr->entry.dd,ltr->entry.mm,ltr->entry.yy,ltr->membership,ltr->points,ltr->rate);


    fprintf(fp2,"Customer Id,Bill No.,ItemName,Quantity,Total_Price,Date,Month,Year\n");
    while(atr->next!=NULL)
    {
        fprintf(fp2,"%d,%d,%s,%d,%d,%d,%d,%d\n",atr->customerno,atr->billno,atr->itemname,atr->qty,atr->t_price,atr->cur_date.dd,atr->cur_date.mm,atr->cur_date.yy);
        atr=atr->next;
    }
    fprintf(fp2,"%d,%d,%s,%d,%d,%d,%d,%d",atr->customerno,atr->billno,atr->itemname,atr->qty,atr->t_price,atr->cur_date.dd,atr->cur_date.mm,atr->cur_date.yy);

    fclose(fp);
    fclose(fp1);
    fclose(fp2);

}



