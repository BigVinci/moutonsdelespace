#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* macros de DEBUG_MSG fournies , etc */
#include "common/notify.h"

















int is_byte(char*chaine)
{   int l=0;
    int i=0;
    int k=0;
    l=strlen(chaine);
    for(i=0; i<l; i++)
    {
        if(chaine[i]=='0' || chaine[i]=='1')
        {
            k++;
        }
    }
    return(chaine!=NULL && k==l && l==8 && chaine[l]=='\0');
}







int is_word(char* chaine)
{ int i=0;
	int k=0;
	int l=0;
	l=strlen(chaine);				//Pour chaque bit vérifie qu'il est bien égal soit à 0 soit à 1
    for(i=0; i<32; i++)
	{
		if(chaine[i]=='0' || chaine[i]=='1')
		{
			k++;
		}
	}


 return (chaine!=NULL && k==l && strlen(chaine)=='32' && chaine[l]=='\0'); // Vérifie que tous les bits sont bien égaux à 1 ou à 0, et qu'il y en a bien 32
}





                                                                        /* testperso à finir !! - fonction incomplète */
int is_integer(char* chaine)
{   int i=0;
    int k=0;
    int l=0;
    l=strlen(chaine);
    for(i=0; i<l; i++)
    {
        if(   chaine[i]=='0'
           || chaine[i]=='1'
           || chaine[i]=='2'
           || chaine[i]=='3'
           || chaine[i]=='4'
           || chaine[i]=='5'
           || chaine[i]=='6'
           || chaine[i]=='7'
           || chaine[i]=='8'
           || chaine[i]=='9'
           || chaine[i]=='-') /*&& chaine[i]!='-'*/

            k++;

    }
    return (chaine!=NULL && k==l && chaine[l]=='\0');

   // int dec = chaine - '0'; /* transforme la chaine en int */

}





int is_octal(char* chaine)
{
    printf("Fonction non implémentée. \n");
}







int is_elf(char* chaine)
{	int l;
	l=strlen(chaine);

return ( chaine[l-4]=='.' && chaine[l-3]=='e' && chaine[l-2]=='l' && chaine[l-1]=='f' && chaine[l]=='\0');

}


/*

main()
{
    char chaine[256]; chaine[0]=0;
    int i,j;

    while(chaine[0]!='e')
        {
            printf("Quel test voulez-vous faire ? 1 : hexadecimal, 2 : byte, 3 : word, 4 : integer (decimal), 5 : octal. Tapez 0 pour exit.\n");
            scanf("%d", j);
            switch(j)
            {
                case 1 :
            printf("Entrer un nombre hexadécimal.\n");
            scanf("%s", chaine);
            i=is_hexa(chaine);
            if (i==0) printf("Ce n'est pas un hexadécimal !\n");
            else printf("C'est un hexadécimal.\n");
            break;

                case 2 :
            printf("Entrer un octet.\n");
            scanf("%s", chaine);
            i=is_byte(chaine);
            if (i==0) printf("Ce n'est pas un octet !\n");
            else printf("C'est un octet.\n");

                case 3 :
            printf("Entrer un word.\n");
            scanf("%s", chaine);
            i=is_word(chaine);
            if (i==0) printf("Ce n'est pas un uint32 !\n");
            else printf("C'est un uint32.\n");

                case 4 :
            printf("Entrer un integer.\n");
            scanf("%s", chaine);
            i=is_integer(chaine);
            if (i==0) printf("Ce n'est pas un integer !\n");
            else printf("C'est un integer.\n");

                case 5 :
            printf("Entrer un octal (puissance de 8).\n");
            scanf("%s", chaine);
            i=is_octal(chaine);
            if (i==0) printf("Ce n'est pas un octal !\n");
            else printf("C'est un octal.\n");

                case 0 :
            chaine[0]='e';
            break;
                default :
            chaine[0]=0;
            break;

            }
        }
}


*/
