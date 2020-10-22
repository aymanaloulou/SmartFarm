#include <stdio.h>
#include "fonction.h"

void main() {
	int a;int b;
	printf ("Donner deux entier : ");
	scanf ("%d %d",&a,&b);
	printf ("%d + %d = %d\n",a,b,sommer (a,b));
	printf ("%d - %d = %d\n",a,b,soustraire (a,b));
	printf ("%d / %d = %f\n",a,b,diviser (a,b));
}
