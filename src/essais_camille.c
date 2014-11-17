



int execute_cmd(interpreteur inter) {
    DEBUG_MSG("input '%s'", inter->input);
    char cmdStr[MAX_STR];
    memset( cmdStr, '\0', MAX_STR );

    /* gestion des commandes vides, commentaires, etc*/
    if(strlen(inter->input) == 0
            || sscanf(inter->input, "%s", cmdStr) == 0
            || strlen(cmdStr) == 0
            || cmdStr[0] == '#') { /* ligne commence par # => commentaire*/
        return CMD_OK_RETURN_VALUE;
    }

    /*on identifie la commande avec un premier appel a get_next_token*/
    char * token = get_next_token(inter);

  switch (token)
{
	case  "exit": 

        return exitcmd(inter);
  
	case  "test":

        return testcmd(inter);
    
	case "load":

	return loadcmd(inter);

	case "disp":

	return dispcmd(inter);

	case "disasm":

	return disasm(inter);

	case "set":

	return sertcmd(inter);

	case "assert":

	return assertcmd(inter);

	case "debug":

	return debugcmd(inter);

	case "resume":

	return resumecmd(inter);

	case "run":

	return runcmd(inter);

	case "step":

	return stepcmd(inter);

	case "break":

	return breakcmd(inter);


    /* si aucune commande n'est reconnue */ 
	default:
	WARNING_MSG("Unknown Command : '%s'\n", cmdStr);
    return CMD_UNKOWN_RETURN_VALUE;
}












void loadcmd(interpreteur inter)
{




 while((token = get_next_token(inter))!=NULL && return_value==0)
{

DEBUG_MSG("Chaine : %s", inter->input);
    int return_value=0;































int  acquire_line(FILE *fp, interpreteur inter) {
    char* chunk =NULL;

    memset(inter->input, '\0', MAX_STR );
    inter->first_token =0;
    if (inter->mode==SCRIPT) {
        // mode fichier
        // acquisition d'une ligne dans le fichier
        chunk =calloc(MAX_STR, sizeof(*chunk));
        char * ret = fgets(chunk, MAX_STR, fp );
        if(ret == NULL) {
            free(chunk);
            return 1;
        }
        // si windows remplace le \r du '\r\n' (fin de ligne windows) par \0
        if(strlen(ret) >1 && ret[strlen(ret) -2] == '\r') {
            ret[strlen(ret)-2] = '\0';
        }
        // si unix remplace le \n par \0
        else if(strlen(ret) >0 && ret[strlen(ret) -1] == '\n') {
            ret[strlen(ret)-1] = '\0';
        }

    }
    else {
        /* mode shell interactif */
        /* on utilise la librarie libreadline pour disposer d'un historique */
        chunk = readline( PROMPT_STRING );
        if (chunk == NULL || strlen(chunk) == 0) {
            /* commande vide... */
            if (chunk != NULL) free(chunk);
            return 1;
        }
        /* ajout de la commande a l'historique, librairie readline */
        add_history( chunk );

    }
    // standardisation de la ligne d'entree (on met des espaces lÃ  ou il faut)
    string_standardise(chunk, inter->input);

    free( chunk ); // liberation de la memoire allouee par la fonction readline() ou par calloc()

    DEBUG_MSG("Ligne acquise '%s'\n", inter->input); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */
    return 0;
}
