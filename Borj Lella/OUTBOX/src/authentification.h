#include<gtk/gtk.h>

typedef struct
	{
	char username[50];
	char mdp[50];
	char email[100];	
	}admin;

int CINExiste_emp (char ch[]);
void mail_mdp_oub(char TO[],char *pass);
void get_mail( char id[], char mail[]);
void get_pass( char id[], char pass[]);
