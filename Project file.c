#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define size 5   //size of the password
#include"project.h" // includes the header file


int main()
{
	char ch;// takes the choice from the user if he is customer or admin
	setColor(43);
	printf("\t\t\t\t\t\t WELCOME TO SHOPIFY PLAZA	\n	");
	setColor(15);
    	printf("\n Are you admin(a) or customer(c) \n ");
	printf(" Enter your choice:   ");
	scanf("%c",&ch);
	screen1(ch); // calls the login page
	return 0;
}


