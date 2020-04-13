#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
//screen2
int correctpass()
{
	int c;
	printf("\n\n\n\n WELCOME ADMIN");
	printf("\n\n Do you want to :\n1.View inventory and stock.\n2.View Customer details.\n3.Statistics	");
	printf("\n Enter you choice\n");
	scanf("%d",&c);
	/*
	switch(c)
	{
		case 1:
			inventory();
			break;
		case 2:
			details();
			break;
		case 3:
			statistics();
			break();
	}
	*/
}

//screen 1
int screen1(char ch)
{
	char c;
	int ctr=0;
	int d,i,j,k,l;
	char password[10];
	if(ch=='a' || ch=='A')
	{
		for(k=0;k<3;k++)
		{
			printf("\n Enter the password	");
			for( i = 0;i < 5;i++)
			{
				c = getch();
				password[i] = c;
				c = '*' ;
				printf("%c ", c);
			}
			password[i]='\0';
		
			if(!strcmp(password,"ADMIN"))
			{
			//colour
			printf("\n ACCESS GRANTED");
			correctpass();
			break;
			}
			else
				{
					printf("\n ACCESS DENIED");
					ctr++;
					if(ctr==3)
						printf("\n ACCESS LOCKED!! CONTACT SERVER");
						else
							{
							printf("\n 1.Try Again.\n 2.Show password");
							printf("\n Enter your choice	");
							scanf("%d",&d);
							if(d==1)
								continue;
							else
								for(l = 0;l< i-1;l++)
									printf("%c ", password[l]);
							}
				}
	}
	}
}

int main()
{
	char ch;
	printf("\t\t\t WELCOME TO SHOPIFY PLAZA	\n	");
	printf("\n Are you admin(a) or customer(c) \n");
	scanf("%c",&ch);
	screen1(ch);
	return 0;
	
}
