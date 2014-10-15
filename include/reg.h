#ifndef _REG_H_
#define _REG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <strings.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "common/types.h"
#include "common/bits.h"
#include "common/notify.h"

#ifndef _REG_
#define _REG_
/* définie la structure registre */
typedef struct registre
{
	char	*name;		/* nom du registre */ 
	char	*mnemo;		/* second nom du registre */ 
	vaddr32	address; 	/* adresse de destination sur 32 bits */  
	char	*data;		/* contenu du registre sur 32 bits */
}* reg; /* pointeur qui pointe sur un registre */ 

#endif /* _REG_ */

reg init_reg(char* namereg, char* mnemoreg);
void del_reg (reg vreg);
reg to_reg(char* registre);
reg* init_tab_reg(void);
void del_tab_reg(reg* tabreg);


#ifdef __cplusplus
}
#endif

#endif /* _REG_H_ */
