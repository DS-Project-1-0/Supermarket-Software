#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
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
			SetColor(98);//changes the color of following text to green
			printf("\n ACCESS GRANTED");
			SetColor(15);//sets the color of text to white again
			correctpass();
			break;
			}
			else
				{   SetColor(12);//Sets the color of following text to red
					printf("\n ACCESS DENIED");
					SetColor(15);//Sets the color of following text to white again
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
	SetColor(43);//sets the text color to blue
	printf("\t\t\t\t\t\t WELCOME TO SHOPIFY PLAZA	\n	");
	SetColor(15);//again sets the text color to white
	printf("\n Are you admin(a) or customer(c) \n");
	scanf("%c",&ch);
	screen1(ch);
	return 0;

}
//function to change the color
void SetColor(int ForgC)
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

