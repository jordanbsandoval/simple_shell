#include "Shell.h"

void
Get_Path(List *list)
{
	char **Temp_Environ = environ;

	/*
	 *  Variable that restores the path environment variable to
	 *  its original position.
	 */

	char *Temp_Path;

	Posicionar_Path(Temp_Environ);

	/*
	 * We set Temp_path to point to the Path, where the paths
	 * are found.
	 */

	Temp_Path = *Temp_Environ;

	Posicionar_Environ(Temp_Environ);

	while (**Temp_Environ)
		Ins_Next_Element(list, NULL,Data_Path(Temp_Environ));

	/*
	 * We place the pointer is an original position.
	 */

	*Temp_Environ = Temp_Path;
}
