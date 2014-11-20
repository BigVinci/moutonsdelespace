Informations relatives au projet MIPS r�alis� par DELON Camille & FERRE Nicolas. 



pour ex�cuter

 : 
emulMips script.txt   // en mode SCRIPT
 : 
emulMips              // en mode INTERACTIF




Les sources se trouvent dans 
./src/


Les includes dans 
./include/  ./include/common/  et ./include/elf/


Les fichiers de script de test se trouvent dans 
./tests/
script.txt



Voici le d�tail des fichiers pr�sents et leur description (si non pr�sent initialement) : 
 
- bits.c/.h 

 
- cmd_gestion.c/.h : contient toutes les fonctions � ex�cuter suite � la reconnaissance d'une ligne entr�e par l'utilisateur. 

 
- elf.c/.h 

 
- emulMips.c : contient le main 

 
- fonct_gestion.c/.h : contient toutes les fonctions permettant de lire la ligne �crite par l'utilisateur et de v�rifier si elle est correcte (i.e. si elle correspond � une fonction existante). Renvoie une erreur/warning en cas d'erreur. 

 
- formats.h

 
- interpreteur.c/.h : contient les fonctions relatives � l'interpr�teur (initialisation, acqu�rrir une ligne, ...)

 
- load.c/.h : permet d'initialiser la m�moire en mode SCRIPT � l'aide d'un fichier elf

 
- mem.c/.h : d�crit la m�moire et les fonctions relatives � la m�moire

 
- notify.h 

 
- reg.c/.h : d�crit les registres et les fonctions relatives aux registres

 
- section.c/.h 

 
- syms.c/.h 

- types.h

 
- disasm.c/.h : contient l'ensemble des fonctions relatives � la lecture des instructions en assembleur & initialise le dictionnaire contenant l'ensemble des instructions
