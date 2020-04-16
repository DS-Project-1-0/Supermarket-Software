#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define size 5   //size of the password
#include"project.h"


int main()
{
	char ch;
	setColor(43);//sets the text color to blue
	printf("\t\t\t\t\t\t WELCOME TO SHOPIFY PLAZA	\n	");
	setColor(15);//again sets the text color to white
	printf("\n Are you admin(a) or customer(c) \n ");
	scanf("%c",&ch);
	screen1(ch);
	return 0;
}


