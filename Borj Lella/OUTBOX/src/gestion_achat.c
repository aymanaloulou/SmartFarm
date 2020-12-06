void ajouter_produit (produit P){
		FILE* f;
		
	
		
		f = fopen ("produit.bin","ab");
		          
		fwrite (&P,sizeof (produit),1,f);
		fclose (f);
}
////////////////////////////////////////////////////// modifier un produit ///////////////////////////////////////////////////////////////
int produitExiste (char ch[])
{
    produit c;
    int p=-1,ok=0;
     
    FILE* f = fopen ("produit.bin","rb");

    while (fread (&c,sizeof (produit),1,f) != 0 && p==-1){
       
        if (strcmp (c.Nom_du_produit,ch) == 0) 
             p=ok;
else ok++;
    }
    fclose (f);
    return p;

}
void modifier_produit (produit P1)
{


    FILE* f;
    produit t;
    

    f = fopen ("produit.bin","r+b");

    fseek (f,produitExiste (c.Nom_du_produit)*sizeof(produit),SEEK_SET);
     
       
   

    fseek (f,-sizeof(produit),SEEK_CUR);
    fwrite (&c,sizeof(produit),1,f);

    fclose (f);

}
/////////////////////////////////////////////////////////////// Affichage produit ///////////////////////////////////////////////////////////
enum {
NOM_DU_PRODUIT,
DDF_JOUR,DDF_MOIS,DDF_ANNEE,
DLC_JOUR,DLC_MOIS_DLC_ANNEE,
QUANTITE,
PRIX,
};
void  afficher_list_client(GtkWidget *liste)
{
	produit T;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	Client B;
store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom de produit",renderer, "text",NOM_DU_PRODUIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("ddf",renderer, "text",DDF_JOUR,DDF_MOIS,DDF_ANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("dlc",renderer, "text",DLC_JOUR,DLC_MOIS_DLC_ANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("quantite",renderer, "text",QUANTITE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("PRIX",renderer, "text",PRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
}
	

	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);

 f=fopen("produit.bin","r+b");
	while(fread(&B,sizeof(produit),1,f))
	{
	gtk_list_store_append (store,&iter);
	gtk_list_store_set(store,&iter,NOM_DU_PRODUIT,B.nom_du_produit,DDF_JOUR,B.ddf.jour,DDF_MOIS,B.ddf.mois,DDF_ANNE,B.ddf.annee,JOUR,B.jour,MOIS,B.mois,ANNEE,B.annee,DLC_JOUR,B.dlc.jour,DLC_MOIS,B.dlc.mois,DLC_ANNE,B.dlc.annee,QUANTITE,B.quantite,PRIX,B.PRIX-1);
	}
	fclose(f);

	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);

	

}
