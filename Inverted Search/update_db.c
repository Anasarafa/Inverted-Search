#include "inverted.h"
/*
 * Function defination update the database
 */
int update_DB(main_node_t **main_head, file_node_t *file_head, char *f_name)
{
	/*
	 * function call of validation of file 
	 * and store in the database
	 * checking the status of the function 
	 * if success then call the read datafile function 
	 */
	if (validation_store_filenames(&file_head, f_name) == SUCCESS)
		read_datafile(main_head, f_name);
	return SUCCESS;
}
