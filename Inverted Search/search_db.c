#include "inverted.h"
/*
 * Function defination of search the database
 */
int search_DB(main_node_t *head, char *word, int index)
{
	//Declare the temparary main node
	main_node_t *temp = head;

	//Loop for cheching main node 
	while (temp)
	{
		//word compairing 
		if (strcmp(temp->word, word))
			temp = temp -> link;
		else
		{
			//print the content
			printf("Word %s found in the Database and it present in %d file(s)\n", word, temp -> f_count);
			
			//declare a temparary sub node
			sub_node_t *temp1 = temp->sub_link;

			//Loop to check sub node
			while (temp1)
			{
				//print the content
				printf("In file %s %d time(s)\n", temp1 -> f_name, temp1 -> w_count);
				//replace the temp1 
				temp1 = temp1 -> link;
			}
			return SUCCESS;
		}
	}
	//print the error message
	printf("Error : Word %s not found in the Database\n", word);
	return FAILURE;
}
