#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
int id;
char category[500000];
char name[500000];
int qty;
int price;      //unit price of the item
struct node *next;
}item;

item *head=NULL;//creates head for the linked list

void file()//this function reads the file and stores it in the linked list
{
    FILE *fp;//file pointer

    fp=fopen("Inventory_dummy.csv","r");//fopen opens the file :- 1st parameter tells the file name and 2nd tells what to do with the file r means reading

    if(fp==NULL)//checks whether code find the file
    {
    printf("File did not open successfully");
    }

    rewind(fp);//moves the files to the beginning

    char Line[sizeof(item)];//contains a single line of file
    fgets(Line,sizeof(item),fp);//gets the 1st row of the file
    char* delimiter=",";//to separate data by commas

    int i=0;//for entering data in the array
    int j=0;//contains the number of records in file

    rewind(fp);//moves the files to the beginning

    item *ptr=head;

// READING
//reading of the file
    while(fgets(Line,sizeof(item),(FILE *)fp)!=NULL)//gets rows from the file
    {
    item *temp=(item *)malloc(sizeof(item));//create a new node
    temp->id=atoi(strtok(Line,delimiter));//to enter an integer value
    strcpy(temp->category,strtok(NULL,delimiter));//to enter a string value
    strcpy(temp->name,strtok(NULL,delimiter));
    temp->qty=atoi(strtok(NULL,delimiter));
    temp->price=atoi(strtok(NULL,delimiter));
    temp->next==NULL;


    if(head==NULL)//for 1st Node
    {
        head=temp;
    }
    else//for all other nodes
    {
        ptr=head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=temp;
    }
    }
    head=head->next;//to remove the first line which contains the topics of each column they are not required
    fclose(fp);

//MAXIMUM LENGTH
//to find the maximum length for the character helps in equal spacing while showing the data in console
int max,w;
item *ctr=head;
max=strlen(head->name);
    while(ctr!=NULL)
    {
        w=strlen(ctr->name);
        if(max<w)
            max=w;
        ctr=ctr->next;
    }

//DISPLAY THE COMPLETE FILE
//display whole file
printf("\n\nDisplaying Data\n\n");
item *ltr=head;
int e=1,q=0;
while(ltr!=NULL)
    {
                printf("%d\t%s",e,ltr->name);//e is the serial number
                q=strlen(ltr->name);//checks the length of name
                for(int t=0;t<=(max-q);t++)//add spaces for the equal spacing between data
                {
                    printf(" ");
                }
                printf("\t%d\t\t%d\n",ltr->qty,ltr->price);
                e++;
            ltr=ltr->next;
    }

//SEARCHING
//searching a data from the file

printf("\n\nSearching Data\n\n");
int choice;
printf("\n\nSelect a choice to show from id:\n");
scanf("%d",&choice);//assuming we have to find id
ltr=head;
e=1;
q=0;
 while(ltr!=NULL)
    {
            if((ltr->id)==choice)//checks whether the id matches
            {
                printf("%d\t%s",e,ltr->name);//e is the serial number
                q=strlen(ltr->name);//checks the length of name
                for(int t=0;t<=(max-q);t++)//add spaces for the equal spacing between data
                {
                    printf(" ");
                }
                printf("\t%d\t\t%d\n",ltr->qty,ltr->price);
                e++;
            }
            ltr=ltr->next;
    }

//ADD
//add data to the file
printf("\n\nAdding Data\n\n");

fp=fopen("Inventory_dummy.csv","a");//opening file to append the new data

item *temp=(item *)malloc(sizeof(item));//creating a new node to enter the new data
printf("Enter the id: ");
scanf("%d",&temp->id);
printf("Enter the Category: ");
getchar();
gets(temp->category);
printf("Enter the Name: ");
gets(temp->name);
printf("Enter the quantity: ");
scanf("%d",&temp->qty);
printf("Enter the Unit Price: ");
scanf("%d",&temp->price);
temp->next=NULL;

item *mtr=head;

while(mtr->next!=NULL)
{
    mtr=mtr->next;

}
mtr->next=temp;

FILE *fp1,*fp2;//file pointer
int id;//stores the id of the product from file
int y=0;//checks that the product is entered only once
char string[sizeof(item)];//to hold the complete line from file

fp1=fopen("Inventory_dummy.csv","r");//reading the file
fp2=fopen("Dummy.csv","w");//writing the file

while (fgets(Line,sizeof(item),(FILE *)fp1)!=NULL)//takes data from the file
    {

    strcpy(string,Line);//copying the line from file into string variable
    id=atoi(strtok(Line,delimiter));//gets id
    if((id)<=(temp->id))
    {
    fputs(string,(FILE *)fp2);//insert data into the dummy file
    }
    else
    {
        if(y==0)
        {
            fprintf(fp2,"%d,%s,%s,%d,%d\n",temp->id,temp->category,temp->name,temp->qty,temp->price);//adding the data in the file
            fputs(string,(FILE *)fp2);
            y=1;
        }
        else
        {
        fputs(string,(FILE *)fp2);//insert data into the dummy file
        }
    }
    }
fclose(fp);//closing the file pointer
fclose(fp1);//closing the file pointer
fclose(fp2);//closing the file pointer

 fp1=fopen("Inventory_dummy.csv","w");//writing into the file
    fp2=fopen("Dummy.csv","r");//reading from the file


    while (fgets(Line,sizeof(item),(FILE *)fp2)!=NULL)//taking data from file
        fputs(Line,(FILE *)fp1);//inserting data into the file

    fclose(fp1);//closing file pointer
    fclose(fp2);//closing file pointer


//DELETE
//deleting a data from file

printf("\n\nDeleting Data\n\n");

char name[900],name1[900],category1[900];//name to hold the name entered by user,name1 to hold the name from file,category1 to hold the category from the file

fp1=fopen("Inventory_dummy.csv","r");//reading the file
fp2=fopen("Dummy.csv","w");//writing the file


printf("Enter the name of the product\n");
scanf("%s",&name);//getting the product name from user

while (fgets(Line,sizeof(item),(FILE *)fp1)!=NULL)//takes data from the file
    {

    strcpy(string,Line);//copying the line from file into string variable
    id=atoi(strtok(Line,delimiter));//gets id
    strcpy(category1,strtok(NULL,delimiter));//gets category
    strcpy(name1,strtok(NULL,delimiter));//gets name of the product

        if(strcmp(name,name1))//checks if the entered name and the name from file are same
        {
            fputs(string,(FILE *)fp2);//insert data into the dummy file
        }

    }

    fclose(fp1);//closing file pointer
    fclose(fp2);//closing file pointer

    fp1=fopen("Inventory_dummy.csv","w");//writing into the file
    fp2=fopen("Dummy.csv","r");//reading from the file


    while (fgets(Line,sizeof(item),(FILE *)fp2)!=NULL)//taking data from file
        fputs(Line,(FILE *)fp1);//inserting data into the file

    fclose(fp1);//closing file pointer
    fclose(fp2);//closing file pointer

//UPDATE
//for updating the file

printf("\n\nUpdating Data\n\n");

char name2[900];//folding holding the name of product to be updated
item *ftr=head;
int ch;//switch case
int lo=0;//do while

printf("Name of product you want to update: ");
scanf("%s",&name2);

fp1 = fopen("Inventory_dummy.csv","r");//reading the file
fp2 = fopen("Dummy.csv","w");//writing the file

while(ftr!=NULL&&strcmp(name2,ftr->name))//getting ftr to the node which contains product information
{
    ftr=ftr->next;
}
    if(ftr==NULL)//if product is not found
        {
        printf("Product Not Found");
        }

    else //if product is found we use
    {
while (fgets(Line,sizeof(item),(FILE *)fp1)!=NULL)//taking input from inventory
    {

    strcpy(string,Line);//copying the line from file into string variable
    id=atoi(strtok(Line,delimiter));//gets id
    strcpy(category1,strtok(NULL,delimiter));//gets category
    strcpy(name1,strtok(NULL,delimiter));//gets name of the product

        if(strcmp(name1,ftr->name))//checks if name of product entered by user is not same as that of ftr
            fputs(string,(FILE *)fp2);//insert the string into dummy file
        else
        {
           do{
            lo=0;
            printf("\n(1)\tUpdate ID %d",ftr->id);
            printf("\n(2)\tUpdate Category %s",ftr->category);
            printf("\n(3)\tUpdate Name of Product %s",ftr->name);
            printf("\n(4)\tUpdate Quantity %d",ftr->qty);
            printf("\n(5)\tUpdate Unit Price %d",ftr->price);
            printf("Enter Your Choice: ");
            scanf("%d",&ch);
            getchar();
            switch(ch)
            {
            case 1:
                printf("Enter ID: ");
                scanf("%d",&ftr->id);
                break;
            case 2:
                printf("Enter Category: ");
                gets(ftr->category);
                break;
            case 3:
                printf("Enter Name: ");
                gets(ftr->name);
                break;
            case 4:
                printf("Enter Quantity ");
                scanf("%d",&ftr->qty);
                break;
            case 5:
                 printf("Enter Unit Price ");
                scanf("%d",&ftr->price);
                break;
            default:
                printf("Invalid Selection");
                lo=1;
            }
            }while(lo==1);
           fprintf(fp2,"%d,%s,%s,%d,%d\n",ftr->id,ftr->category,ftr->name,ftr->qty,ftr->price);//inserts the updated data in the file
        }
    }
    fclose(fp1);//closing file pointer
    fclose(fp2);//closing file pointer
    fp1 = fopen("Inventory_dummy.csv","w");//writing the file
    fp2 = fopen("Dummy.csv","r");//reading the file
    while (fgets(Line,sizeof(item),(FILE *)fp2)!=NULL)//takes data from dummy
    {
    fputs(Line,(FILE *)fp1);
    }
    fclose(fp1);//closing file pointer
    fclose(fp2);//closing file pointer
    }
}

int main()
{
    file();
}
