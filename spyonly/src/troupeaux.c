#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "troupeaux.h"
#include <gtk/gtk.h>
enum 
{
    EREF ,
    EREF_MERE,
    EDATE,
    EGENRE ,
    EPOIDS ,
    EROBE;
    ELOT , 
    COLUMNS , 
    
};


int RefExiste (char ch[])
{
    animal a;
    int p=-1,test=0;
     
    FILE* f = fopen ("animal.bin","rb");

    while (fread (&a,sizeof (animal),1,f) != 0 && p==-1){
       
        if (strcmp (a.ref,ch) == 0) 
             p=test;
else test++;
    }
    fclose (f);
    return p;

}

void AjoutAnimal (animal a){
		FILE *f;
		animal a;
		
		f = fopen ("animal.bin","a+b");
		if (f!=NULL)
{           
                fprintf(f,"%s %s %s %s %s %s %s \n", a.ref,a.ref_mere,a.date_de_naissance,a.genre,a.poids,a.robe,a.lot) ;
		fclose (f);
			
			
		}
}
////////////////////////////////////////////////
void AffichListeAnimal(Gtkwidget *liste) 
{ animal a ;
    GtkcellRenderer *renderer ; 
    GtkTreeviewColumn *column ; 
    GtkTreeIter iter ; 
    GtkListStore *store ; 
        char ref[20];
	char gender[10] ;
	char poids[10] ;
	char ref_mere[20];
	char robe[20];
	char lot[100];
	char date_de_naissance[25]; 
        store=NULL ; 
if (store==NULL) 
{
renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Identifiant", renderer,"text",ETYPE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;

renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer,"text",EID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;

renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Date de naissance", renderer,"text",EMARQUE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;

renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Gender", renderer,"text",EVALEUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;


renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Poids", renderer,"text",EVALEUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;

renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Robe", renderer,"text",EDATE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;
renderer=gtk_cell_rennderer_text_new () ; 
column= gtk_tree_view_column_new_with_attributes("Lot", renderer,"text",EDATE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste, column ) ;
}
store=gtk_list_store_new (COLUMNS, G_TYPE_STRING , G_TYPE_STRING , G_TYPE_STRING ,G_TYPE_STRING ) ; 
f=fopen("animal.bin","r+b"); 
if (f==NULL) 
{
 return ; 
}
else 
{
f=fopen("animal.bin","a+b"); 
while (fscanf(f,"%s %s %s %s %s %s %s \n",ref,ref_mere,date_de_naissance,genre,poids,robe,lot);
{
	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,EREF,ref,EREF_MERE,ref_mere,EDATE,date,EGENDER ,gender,EPOIDS,poids ,EROBE,robe,ELOT,lot,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
//////////////////////////////////////////////////
void suppAnimal  (animal a) 
{
animal a2 ;
FILE *f,*g ;
      f=fopen("animal.bin","r+b");
      g=gopen("animal.bin","w+b");

   if (f==NULL || g=NULL)
      return ;
   else
{
   while (fscanf(f,"%s %s %s %s %s %s %s \n", a2.ref,a2.ref_mere,a2.date_de_naissance,a2.genre,a2.poids,a2.robe,a2.lot)!=E0F)
{
    if (strcmp(a.ref,a2.ref)!=0 || strcmp(a.ref_mere,a2.ref_mere)!=0 || strcmp(a.date,a2.date)!=0 ||
      strcmp(a.gender,a2.gender)!=0 || strcmp(a.Poids,a2.Poids)!=0  || strcmp(a.robe,a2.robe)!=0 || strcmp(a.lot,a2.lot)!=0 )
  fprintf (g,"%s %s %s %s %s %s %s \n" , a2.ref,a2.ref_mere,a2.date_de_naissance,a2.genre,a2.poids,a2.robe,a2.lot) ;
}
fclose(f);
fclose(g) ;
}
 remove ("animal.bin") ;
 rename ("animal2.bin","animal.bin");
}
