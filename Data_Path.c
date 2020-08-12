#include "Shell.h"

char *
Data_Path(char **Temp_Environ)
{
	char *temp;
	int counter = 1;   /*
			    * Para incluir el caracter '\0'.
			    */
	int index = 0;

	while((*Temp_Environ)[index] != ':' && (*Temp_Environ)[index])
		counter++, index++;
	if((temp = (char *)malloc(sizeof(char) * counter)) == NULL)
		return NULL;
	else
	{
		index = 0;
		while(*(*Temp_Environ) != ':' && **(Temp_Environ))
			temp[index++] = *(*Temp_Environ)++;
		if (**Temp_Environ == ':')
			(*Temp_Environ)++;
		temp[index] = '\0';
		return (temp);
	}
}
