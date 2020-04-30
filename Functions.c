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
	else if(ch=='c' || ch=='C')
    {
        customer_entry();
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
        printf("\n\n Do you want to :\n 1. View inventory and stock\n 2. View Customer details\n 3. Statistics\n 4. Show Bill Details\n 5. Logout\n\n");
        printf("\n Enter your choice:	");
        scanf("%d",&c);

        switch(c)
        {
            case 1:
                inventory();
                break;
            case 2:
                customerDetails();
                break;
            case 3:
                statistics();
                break;
            case 4:
                billDetails();
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

            if(choice!=7)
            {
                setColor(11);
                printf("\n S.No\tName\t");
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
            else if(choice==6)
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
                        printf(" %d\t%s",e,ltr->name);
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

                        printf("\t%s\t\t",ltr->membership);
                        printf("%d\t",ltr->points);
                        printf("%d\n",ltr->rate);
                        e++;
                    }

                    ltr=ltr->next;
                }
            }
            else if(choice==2)
            {
                setColor(11);
                printf("\n SNo.\tName\t");
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
                    printf(" %d\t%s",e,ltr->name);
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
    int one=0,two=0,three=0,four=0,five=0;
    bill *tra=head4;
    float total_sales=0.0;

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

                if(ptr->qty<=3)//incase of urgent refill
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
                ptr=ptr->next;
            }
        }
        else if(choice==3)//to check total members category wise
        {
           setColor(11);
           printf("\n\n S.No\tCategory");
           max=strlen("Platinum");

           for(i=0;i<=(max-4);i++)
               printf(" ");

           printf("Members\n");

           while(ltr!=NULL)
           {
               if(!strcmp(ltr->membership,"P"))//to store platinum members
                ++p;
               else if(!strcmp(ltr->membership,"G"))//to store gold members
                ++g;
               else if(!strcmp(ltr->membership,"S"))//to store silver members
                ++s;

               ltr=ltr->next;
           }

           setColor(15);
           printf(" 1.\t");
           printf("PLATINUM");

           printf("     %d\n",p);
           printf(" 2.\t");
           printf("GOLD");
           for(i=0;i<=(max);i++)
                printf(" ");
           printf("%d\n",g);
           printf(" 3.\t");
           printf("SILVER");
           for(i=0;i<=(max-2);i++)
                printf(" ");
           printf("%d\n",s);
        }
        else if(choice==4)
        {
          ltr=head2;

          while(ltr!=NULL)//traversing through customer file
          {
              if(ltr->rate==5)
                ++five;
              else if(ltr->rate==4)
                ++four;
              else if(ltr->rate==3)
                ++three;
              else if(ltr->rate==2)
                ++two;
              else if(ltr->rate==1)
                ++one;

              ltr=ltr->next;
          }
          setColor(11);
          printf("\n\n\t Ratings\t\t\tMembers\n");
          setColor(15);
          printf("\t 5-STARS\t\t\t");
          printf("%d\n",five);
          printf("\t 4-STARS\t\t\t");
          printf("%d\n",four);
          printf("\t 3-STARS\t\t\t");
          printf("%d\n",three);
          printf("\t 2-STARS\t\t\t");
          printf("%d\n",two);
          printf("\t 1-STARS\t\t\t");
          printf("%d\n",one);
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
              total_sales+=tra->total_price;
              tra=tra->next;
          }

         setColor(15);
         printf("\t\t\t%.2f (INR)\n\n",total_sales);
        }
        else if(choice==5)
            break;
        else//for wrong choice of input
        {
           setColor(12);
           printf("\n\n INVALID SELECTION!\n\n");
           setColor(15);
        }
    }while(1);

}

void billDetails()
{
    char phoneno[500000];
    customer *atr=head2;
    bill_det *ptr=head3,*ltr=head3,*trav=head3;
    int ch,max_new,h,q,sno=1;
    date dt;
    getchar();
    do
    {
        ch=0;
        printf("\n Enter the Phone Number:	");
        gets(phoneno);
        atr=head2;
        while(atr!=NULL)
        {
            if(!strcmp(phoneno,atr->phoneno))
                break;
            atr=atr->next;
        }

        if(atr==NULL)
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
                if(ptr->customerno==atr->id)
                {
                    dt.dd=ptr->cur_date.dd;
                    dt.mm=ptr->cur_date.mm;
                    dt.yy=ptr->cur_date.yy;
                    setColor(45);
                    printf("\n\n\t\t\tDate: %d/%d/%d\n\n",dt.dd,dt.mm,dt.yy);
                    setColor(22);
                    printf(" S.no\tName");
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

                    printf(" %d\t%s",sno,ptr->itemname);
                    q=strlen(ptr->itemname);

                    for(int t=0;t<=(max_new-q);t++)
                    {
                        printf(" ");
                    }

                    printf("\t%d\t\t\t%d\n",ptr->qty,ptr->t_price);
                    sno++;

                    ltr=ptr->next;
                    while(ltr!=NULL)
                    {
                        if(ptr->customerno==ltr->customerno&&dt.dd==ltr->cur_date.dd&&dt.mm==ltr->cur_date.mm&&dt.yy==ltr->cur_date.yy)
                        {
                            printf(" %d\t%s",sno,ltr->itemname);
                            q=strlen(ltr->itemname);

                            for(int t=0;t<=(max_new-q);t++)
                            {
                                printf(" ");
                            }

                            printf("\t%d\t\t\t%d\n",ltr->qty,ltr->t_price);
                            sno++;
                        }

                        if(dt.dd!=ltr->cur_date.dd||dt.mm!=ltr->cur_date.mm||dt.yy!=ltr->cur_date.yy)
                        {
                            ptr=ltr;
                            break;
                        }

                        ltr=ltr->next;
                    }
                    if(ltr==NULL)
                    {
                        ptr=NULL;
                    }
                }
                else
                {
                    ptr=ptr->next;
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
	int w=0;

	setColor(45);
    printf("\n\n\n\n WELCOME CUSTOMER");
	setColor(15);
	do
    {
        printf("\n\n Do you want to :\n 1. Check Location\n 2. Generate Bill\n 3. Logout\n\n");
        printf("\n Enter your choice:	");
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
        gets(choice);

        e=1;//for serial number
        max=0;//hold the maximum character length in name
        q=0;//for checking the length of current item name
        ctr=head1->next;//to point to next node
        ltr=head1;//to traverse through the list

        while(ltr!=NULL)
        {
            if(!strcmp(ltr->name,choice))
            {
                setColor(46);
                printf("\n\n\t\t LOCATION OF PRODUCT	\n");
                setColor(1);
                setColor(3);
                printf("\n S.No\tName");
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
            }
            ltr=ltr->next;
        }

        int c=0;
        ltr=head1;

        while(ltr!=NULL)
        {
            if(!strcmp(ltr->name,choice))
            {
                printf(" %d\t%s",e,ltr->name);
                q=strlen(ltr->name);

                for(int t=0;t<=(max-q);t++)
                {
                    printf(" ");
                }

                printf("%s\n\n",ltr->location);
                e++;
                c=1;
            }

            ltr=ltr->next;
        }

        if(c==0)
        {
            setColor(12);
            printf("\n\n ITEM NOT FOUND!\n\n");
            setColor(15);
        }

        do
        {
            de=0;
            printf("\n 1. Do you want to find another product\n 2. Go to home page\n\n");
            printf("\n Enter your choice:	");
            scanf("%d",&cho);

            switch(cho)
            {
                case 1:
                    dh=1;
                    break;
                case 2:
                    break;
                default:
                    setColor(12);
                    printf("\n\n INVALID SELECTION!\n\n");
                    setColor(15);
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
    printf(" Enter Name: ");
    getchar();
    gets(name1);

    printf(" Enter Birthdate(dd/mm/yyyy): ");
    scanf("%d/%d/%d",&bday.dd,&bday.mm,&bday.yy);

    printf(" Enter Phone Number(10digit): ");
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

    customer *ytr=head2;

    if(ltr==NULL)
    {
        while(ytr->next!=NULL)
        {
            ytr=ytr->next;
        }
        customerid=(ytr->id)+1;

        customer *new_cust = (customer *)malloc(sizeof(customer));
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
    printf(" %s\n\n",ptr->category);
    setColor(3);
    printf(" S.no\tName");

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
            printf("\n %s\n\n",ptr->category);
            e=1;
            setColor(3);
            printf(" S.no\tName");

            for(int t=0;t<=(max-4);t++)
            {
                printf(" ");
            }

            printf("Quantity\tPrice\n");
            setColor(15);
        }

        printf(" %d.\t%s",e,ptr->name);
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
            printf("\n\n Enter Name of the Item you want to buy:   ");
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

                setColor(12);
                printf("\n\n ITEM NOT FOUND!\n\n");
                setColor(15);
                do
                {
                    ex=0;
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
                if((itr->billno)==(temp->billno))
                {
                    if(!strcmp(item_name,itr->itemname))
                    {
                        setColor(46);
                        printf(" YOU ALREADY BOUGHT THIS ITEM!\n Quantity is %d\n",itr->qty);
                        setColor(15);

                        do
                        {
                            w=0;
                            printf("\n\n Do you want to update?(y/n)\n");
                            printf("\n Enter your choice:	");
                            scanf("%c",&n);
                            if((n==121)||(n==89))
                            {
                                do
                                {
                                    x=1;
                                    printf("\n\n Enter the Quantity:\t");
                                    scanf("%d",&new_qty);
                                    old_price=itr->t_price;
                                    htr=head1;
                                    while(htr!=NULL)
                                    {
                                        if(!strcmp(item_name,htr->name))
                                            break;
                                        htr=htr->next;
                                    }

                                    itr->t_price=new_qty*(htr->price);

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
                                        printf(" NOT ENOUGH LEFT!\n ENTER AGAIN!\n\n");
                                        setColor(26);
                                        printf(" Quantity Available: %d\n\n",(htr->qty+(new_qty-(itr->qty))));
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
                    printf(" Enter the Quantity:\t");
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

                if(item_qty==0 && counter==0)
                {
                    setColor(43);
                    printf("\n THANKS FOR VISITING\n");
                    setColor(15);
                }

                if(item_qty!=0)
                {
                    (temp->t_price)=(item_qty)*(ptr->price);
                    (temp->qty)=item_qty;
                    strcpy(temp->itemname,item_name);
                    totalprice+=(temp->t_price);
                    temp->next=NULL;

                    (ptr->qty)-=item_qty;

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
                    free(temp);
                }
           }

            int d,z;

            do
            {
                z=0;
                counter++;
                printf("\n\n Do you want to enter more items?(y/n)\n");
                printf("\n Enter your choice:	");
                scanf(" %c",&d);
                if((d==121)||(d==89))
                {
                    y=1;
                    getchar();
                    h++;
                }
                else if((d==78)||(d==110))
                {
                    printf("\n");
                    printf("\n");
                    printf(" Your Current Bill is ");
                    setColor(60);
                    printf("%d",totalprice);
                    setColor(15);
                }
                else
                {
                    setColor(12);
                    printf("\n\n INVALID SELECTION!\n\n");
                    setColor(15);
                    z=1;
                }
            }while(z==1);
        }
        else
        {
            printf("\n");
            printf("\n");
            printf(" Your Current Bill is ");
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
    int rw,ew,d,pq=0;
    item *dtr=head1;
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
                printf("\t\t\t Your Current Bill\n\n");
                setColor(22);
                printf(" S.no\tName");
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
                        printf(" %d\t%s",sno,trav->itemname);
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

                    do
                    {
                        printf("\n\n 1. Do you want to delete a item\n 2. Do you want to modify the quantity\n 3. Finished\n\n");
                        printf("\n Enter your choice:	");
                        scanf("%d",&choice3);
                        trav=head3;

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
                                        dtr=head1;

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

                                            btr=trav;
                                            trav=trav->next;
                                        }

                                        if(trav==NULL)
                                        {
                                            setColor(12);
                                            printf("\n\n ITEM NOT FOUND!\n\n");
                                            setColor(15);
                                        }
                                        else
                                        {
                                            btr->next=trav->next;
                                            dtr=head1;
                                            while(dtr!=NULL)
                                            {
                                                if(!strcmp(dtr->name,trav->itemname))
                                                    break;

                                                dtr=dtr->next;
                                            }

                                            (dtr->qty)+=(trav->qty);
                                            totalprice-=(trav->t_price);
                                         }
                                        free(trav);

                                        trav=head3;
                                        while(trav!=NULL)
                                        {
                                            if(trav->billno==billno)
                                                break;

                                            trav=trav->next;
                                        }

                                        if(trav!=NULL)
                                        {
                                            setColor(45);
                                            printf("\t\t\tYOUR BILL\n\n");
                                            setColor(22);
                                            printf(" S.no\tName");
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
                                                    printf(" %d\t%s",sno,trav->itemname);
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
                                                    printf("\n\n Do you want to delete more items?(y/n)\n");
                                                    printf("\n Enter your choice:	");
                                                    scanf("%c",&d);

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

                                    trav=head3;
                                    while(trav!=NULL)
                                    {
                                        if(trav->billno==billno)
                                        {
                                            if(!strcmp(trav->itemname,item_name))
                                            break;
                                        }
                                        trav=trav->next;
                                    }

                                    if(trav==NULL)
                                    {
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
                                            old_price=trav->t_price;
                                            htr=head1;
                                            while(htr!=NULL)
                                            {
                                                if(!strcmp(item_name,htr->name))
                                                    break;

                                                htr=htr->next;
                                            }

                                            trav->t_price=new_qty1*htr->price;

                                            if(new_qty1<trav->qty)
                                            {
                                                htr->qty+=trav->qty-new_qty1;
                                                totalprice-=old_price-trav->t_price;
                                            }
                                            else
                                            {
                                                htr->qty-=new_qty1-trav->qty;
                                                totalprice+=trav->t_price-old_price;
                                            }

                                            if(htr->qty<0)
                                            {
                                                setColor(12);
                                                printf("\n\n NOT ENOUGH LEFT! ENTER AGAIN!\n\n");
                                                setColor(26);
                                                printf(" Quantity Available: %d\n\n",(htr->qty+(new_qty1-trav->qty)));
                                                setColor(15);
                                                x=0;
                                                htr->qty+=new_qty1-trav->qty;
                                                totalprice-=trav->t_price-old_price;

                                            }
                                        }while(x==0);

                                        trav->qty=new_qty1;
                                        setColor(45);
                                        printf("\t\t\tYOUR BILL\n\n");
                                        setColor(22);
                                        printf(" S.no\tName");
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
                                            if(trav->billno==billno)
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
                                            trav=trav->next;
                                        }
                                    }

                                    do
                                    {
                                        z=0;
                                        printf("\n\n Do you want to update more items?(y/n)\n");
                                        printf("\n Enter your choice:	");
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
                                            setColor(12);
                                            printf("\n\n INVALID SELECTION!\n\n");
                                            setColor(15);
                                            z=1;
                                        }
                                    }while(z==1);
                               }while(re==1);
                               break;

                            case 3:
                                printf(" Your Current Bill is ");
                                setColor(60);
                                printf("%d ",totalprice);
                                setColor(15);
                                invoice(totalprice,billno);
                                break;

                            default:
                                setColor(12);
                                printf("\n\n INVALID SELECTION!\n\n");
                                setColor(15);
                                j=0;
                        }

                    }while(j==0);
               }
               break;

            case 2:
                invoice(totalprice,billno);
                setColor(15);
                break;

            default:
                setColor(12);
                printf("\n\n INVALID SELECTION!\n\n");
                setColor(15);
                pq=1;
                break;
        }
    }while(pq==1);

}

void offerzone()
{
    setColor(98);
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
    int p=0;
    int cur_points=0;
    float finalpay=0.0;

    setColor(78);
	printf("\t\t\t\t\t\t\tINVOICE");
	printf("\n");
	setColor(15);

	bill_det *hd = head3;
	customer *h=head2;
	customer *h2=head2;

    while(hd->next!=NULL)
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

       h=h->next;
    }

	printf("\nBILL ID:\t");
	setColor(22);
	printf("%d",h->id);
	setColor(15);

	printf("\nDATE:\t");
	setColor(22);
	printf("%d/%d/%d",hd->cur_date.dd,hd->cur_date.mm,hd->cur_date.yy);
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
    printf(" S.no\tName");
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
            printf(" %d\t%s",sno,ftr->itemname);
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
    printf("\n TOTAL:\t%d (INR)",totalprice);

    setColor(60);//reddish
    float amount=0.0;
    amount=(0.05)*totalprice;
    printf("\n TAX (5%%) : %.2f (INR)",amount);

    float pay;
    pay=totalprice+amount;
    setColor(43);
    printf("\n GRAND TOTAL :\t%.2f (INR)\n\n\n\n",pay);

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


    if(cc!=0)
    {
        setColor(44);
        printf("\n AMOUNT PAYABLE AFTER APPLYING MEMBER DISCOUNT : %.2f (INR)",finalpay);
        setColor(15);

        if((h2->bday.dd == hd->cur_date.dd) && (h2->bday.mm == hd->cur_date.mm))
        {
            d=cc;
        }

        int pp=0;

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

        if(pp!=0)
        {
            printf("\n\n AHH ITS YOUR BIRTHDAY!!!\nCongrats on getting an additional discount of %d%%",pp);
            printf("\n AMOUNT PAYABLE AFTER APPLYING SPECIAL BDAY DISCOUNT ");
            setColor(44);
            printf("%.2f (INR)",finalpay);
            setColor(15);
        }

        int chh=0;
        int pts=0;
        int ou=0;

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

            printf("\n AMOUNT PAYABLE AFTER APPLYING GREATER THAN 500 POINTS DISCOUNT:  ");
            setColor(44);
            printf("%.2f (INR)",finalpay);
            setColor(15);

        }
        else
        {
            chh=0;
            if(h2->points!=0)
            {
                printf("\n 1. Do you wish to redeem your points now \n 2. Would like to add them to 500 to avail discounts in future\n");
                printf("\n Enter your choice:	");
                scanf("%d",&chh);
                if(chh==1)
                {
                    float p,g,s=0;
                    float point;
                    p=(finalpay/2)/1;

                    g=(finalpay/2)/0.5;

                    s=(finalpay/2)/0.25;


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
                        if(pts<=point)
                        {
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
                            printf("\n These many points can't be redeemed  ");
                            printf("\n AMOUNT PAYABLE :%.2f (INR)",finalpay);
                            ou=1;

                        }
                    }while(ou==1);
                }
                else
                {
                    printf("\n OK!!");
                }
            }
        }
    }
    else if(cc==0)
    {
        char ch2;
        char ch3;
        offerzone();
        printf("\n\n Do you want to take membership?(Y/N)\n\n");
        printf("\n Enter your choice:	");
        scanf(" %c",&ch2);

        if(ch2 == 'Y' || ch2=='y')
        {
            printf("\n What type of membership do you want to take?(P/G/S):\t");
            printf("\n Enter your choice:	");
            scanf(" %c",&ch3);

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

    int r=1;
    char stars[10];
    setColor(67);
    printf("\n\n THANK YOU!! VISIT AGAIN");
    setColor(15);
    printf(" \n\n Take a Minute to Rate Us     ");

    printf("\n\n How Many Stars Would You Give Us (***** means Best Services)?\n");
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

    if(cc!=0)
    {
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
        h2->points+=cur_points;
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
    exit(0);// because here the 3 options of checking loc etc look irrelevant
}



void update_details()
{
    fp=fopen("Inventory.csv","w");
    fp1=fopen("Customer_details.csv","w");
    fp2=fopen("Bill_details.csv","w");
   // fp3=fopen("Bill.csv","w");

    if(fp==NULL)
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }

    if(fp1==NULL)
    {
        setColor(12);
        printf("File did not open successfully");
        setColor(15);
        exit(0);
    }

    if(fp2==NULL)
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

  /*fprintf(fp3,"Customer Id,Bill No.,Total_Price,Date,Month,Year\n");
    while(mtr->next!=NULL)
    {
        printf("%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
        fprintf(fp3,"%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
        mtr=mtr->next;
    }
  //printf("%d,%d,%d,%d,%d,%d\n",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
    fprintf(fp3,"%d,%d,%d,%d,%d,%d",mtr->customerno,mtr->billno,mtr->total_price,mtr->cur_date.dd,mtr->cur_date.mm,mtr->cur_date.yy);
*/
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
 // fclose(fp3);

}



