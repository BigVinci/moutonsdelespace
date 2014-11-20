Informations relatives au projet MIPS réalisé par DELON Camille & FERRE Nicolas. 



pour exécuter

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



Voici le détail des fichiers présents et leur description (si non présent initialement) : 
 
- bits.c/.h 

 
- cmd_gestion.c/.h : contient toutes les fonctions à exécuter suite à la reconnaissance d'une ligne entrée par l'utilisateur. 

 
- elf.c/.h 

 
- emulMips.c : contient le main 

 
- fonct_gestion.c/.h : contient toutes les fonctions permettant de lire la ligne écrite par l'utilisateur et de vérifier si elle est correcte (i.e. si elle correspond à une fonction existante). Renvoie une erreur/warning en cas d'erreur. 

 
- formats.h

 
- interpreteur.c/.h : contient les fonctions relatives à l'interpréteur (initialisation, acquérrir une ligne, ...)

 
- load.c/.h : permet d'initialiser la mémoire en mode SCRIPT à l'aide d'un fichier elf

 
- mem.c/.h : décrit la mémoire et les fonctions relatives à la mémoire

 
- notify.h 

 
- reg.c/.h : décrit les registres et les fonctions relatives aux registres

 
- section.c/.h 

 
- syms.c/.h 

- types.h

 
- disasm.c/.h : contient l'ensemble des fonctions relatives à la lecture des instructions en assembleur & initialise le dictionnaire contenant l'ensemble des instructions
