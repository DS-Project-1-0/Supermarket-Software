#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define size 5   //size of the password
#include"project.h"

item *head1=NULL;
customer *head2=NULL;
FILE *fp1=NULL,*fp=NULL;//file pointer
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

//admin home page
int correctpass()
{
	int c;//for choice by the user
	char d;//takes input from user whether to log out or not
	int ch=1;//for the do while function
	int w=0;
	printf("\n\n\n\n WELCOME ADMIN");
	do{
    printf("\n\n Do you want to :\n 1. View inventory and stock.\n 2. View Customer details.\n 3. Statistics\n 4. Logout\n\n");
	printf("\n Enter you choice\n");
	scanf("%d",&c);
	switch(c)
	{
		case 1:
			inventory();
			break;
		case 2:
			details();
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

    fp=fopen("Inventory.csv","r");

    if(fp==NULL)
    {
    printf("File did not open successfully");
    }

    rewind(fp);//moves the files to the beginning

    char Line[sizeof(item)];//contains a single line of file
    fgets(Line,sizeof(item),fp);
    char* delimiter=",";//to separate data by commas

    int i=0;//for entering data in the array
    int j=0;//contains the number of records in file

    rewind(fp);

    item *ptr=head1;
    while(fgets(Line,sizeof(item),(FILE *)fp)!=NULL)
    {
    item *temp=(item *)malloc(sizeof(item));
    temp->id=atoi(strtok(Line,delimiter));
    strcpy(temp->category,strtok(NULL,delimiter));
    strcpy(temp->name,strtok(NULL,delimiter));
    temp->qty=atoi(strtok(NULL,delimiter));
    temp->price=atoi(strtok(NULL,delimiter));
    temp->next==NULL;


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

    item *ytr=head1;
    head1=head1->next;
    free(ytr);

    setColor(46);
    printf("\t\t\t\t\t\t INVENTORY	\n");
    setColor(1);
    do{
    setColor(1);
    printf("\n\n CATEGORIES \n\n");
    setColor(15);
    printf(" 1. Food\n 2. Clothes\n 3. Essentials\n 4. Stationary\n 5. Kitchen Utensils\n 6. All \n 7. Go to Home Page\n\n");
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
    printf("Quantity\tUnit_Price\n");
    setColor(15);
    }
    if(choice <=5)
    {
        while(ltr!=NULL)
    {
            if((ltr->id)==choice&&i!=6)
            {
                printf("%d\t%s",e,ltr->name);
                q=strlen(ltr->name);
                for(int t=0;t<=(max-q);t++)
                {
                    printf(" ");
                }
                printf("\t%d\t\t%d\n",ltr->qty,ltr->price);
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
                printf("\t%d\t\t%d\n",ltr->qty,ltr->price);
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

void details()
{

    int choice;//user's choice
    int z=1;//do while loop variable

    fp1=fopen("Customer_details.csv", "r");

    if(fp1==NULL)
    {
        printf("The file did not open successfully");
    }

    rewind(fp1);//takes the file pointer back to the starting of the file

    char Line[sizeof(customer)];//one line of file containing a customer's details
    fgets(Line,sizeof(customer),fp1);
    char* delimiter=",";//separates the data in a line

    int i=0;//for entering data in file
    int j=0;//counts the no of lines in file

    rewind(fp1);

    date *entry;//current date
    date *bday;//birthday of the person

    customer *ptr=head2;
    while(fgets(Line,sizeof(customer),(FILE *)fp1)!=NULL)
    {
        customer *temp=(customer *)malloc(sizeof(customer));
        strcpy(temp->name,strtok(Line,delimiter));
        temp->bday.dd=atoi(strtok(NULL,delimiter));
        temp->bday.mm=atoi(strtok(NULL,delimiter));
        temp->bday.yy=atoi(strtok(NULL,delimiter));
        strcpy(temp->phoneno,strtok(NULL,delimiter));
        temp->entry.dd=atoi(strtok(NULL,delimiter));
        temp->entry.mm=atoi(strtok(NULL,delimiter));
        temp->entry.yy=atoi(strtok(NULL,delimiter));
        temp->points=atoi(strtok(NULL,delimiter));
        temp->membership=atoi(strtok(NULL,delimiter));
        temp->next==NULL;

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

    customer *p=head2;
    head2=head2->next;//to remove the Headings name,phoneno etc...so that they aren't printed
    free(p);

    setColor(22);
    printf("\t\t\t\t\t\t   CUSTOMER DETAILS  \n");
    setColor(43);
    do{
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
            if(choice!=3)
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
                printf("\tDOB\t\t\tPhone no.\t\tDate\t\tPoints\t\tMembership\n");
                setColor(15);
            }
            if(choice==1)
            {
                while(ltr!=NULL)
                {
                    if(ltr->membership==1)
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
                        printf("%/0d",ltr->bday.yy);
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
                        printf("\t%d\t\t%d\n",ltr->points,ltr->membership);
                        e++;
                    }
                        ltr=ltr->next;

                }
            }
            else if(choice==2)
            {
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
                        printf("%/0d",ltr->bday.yy);
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
                        printf("\t%d\t\t%d\n",ltr->points,ltr->membership);

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

//login
int screen1(char ch)
{
	char c;//gets the passsword
	int ctr=0;//counter
	int i,k,l;//loop counter variables
	int t;//gets choice
	char password[10];//array for getting the password
	int g=1;//for do while
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
                printf("\n ACCESS GRANTED");
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
							else{
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
  //to enter customer details
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


