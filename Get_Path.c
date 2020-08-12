#include "Shell.h"

void
Get_Path(List *list)
{
	char **Temp_Environ = environ;
	Posicionar_Path(Temp_Environ);
	Posicionar_Environ(Temp_Environ);
	while(**Temp_Environ)
		Ins_Next_Element(list, NULL,Data_Path(Temp_Environ));
}
