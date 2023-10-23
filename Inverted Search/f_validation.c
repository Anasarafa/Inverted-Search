#include"inverted.h"
/*
 *check the file passed throgh CLA are repeated or not
 *transverse through all the node 
 *compare the given file name with all the file
 *if matched return success else move to the next node
 */
int check_repeate(char *f_name, file_node_t *head)
{
	while (head != NULL)
	{
		if (!strcmp(f_name, head->f_name))
			return SUCCESS;
		head = head->link;
	}
	return FAILURE;
}

/*
 *Function to check the file is valid or not
 *open the file in read read mode to check the file is exist or not
 *check the file is empty or not
 */
int IsFileValid(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if(fp == NULL)
		return NOT_PRESENT;
	else
	{
		fseek(fp,0L,SEEK_END);
		int cot = ftell(fp);
		if(cot == 0)
			return FILE_EMPTY;
		else
			return SUCCESS;
	}
}

/*
 *Function to store the file names to the list
 *create a node
 *if head is NULL update head with new node adress
 *else check the file name is repeated or not using the check_repeate function
 *if it is not repeated transverse through all the node and update the new adress at the last node
 */
int store_filenames_to_list(char *f_name, file_node_t **head)
{
	file_node_t *new = malloc(sizeof(file_node_t));
	//string copy
	strcpy(new->f_name, f_name);
	new->link = NULL;
	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	else
	{
		if (check_repeate(f_name, *head) == SUCCESS)
			return REPEATED;
		else
		{
			file_node_t *temp = *head;

			while (temp->link != NULL)
				temp = temp->link;

			temp->link = new;
			return SUCCESS;
		}
	}
}

/*
 *Function to validate and store the filename
 */
void validate_n_store_filenames(file_node_t **file_head, char *filenames[])
{
	int i = 1;
	while(filenames[i] != NULL)
	{
		//Function call
		validation_store_filenames(file_head, filenames[i]);
		i++;
	}
}

/*
 *check the file is valid or not
 *check the file is empty or not
 *check the file is repeated or not
 */
int validation_store_filenames(file_node_t **file_head, char *filenames)
{
	int ret = IsFileValid(filenames);
	if(ret  == NOT_PRESENT)
	{
		printf("ERROR: %s is not present\n", filenames);
		printf("So we are not adding into the file\n");
		return FAILURE;
	}
	else if(ret == FILE_EMPTY)
	{
		printf("ERROR: %s is an empty file\n", filenames);
		printf("So we are not adding into the file\n");
		return FAILURE;
	}
	else
	{
		if(store_filenames_to_list(filenames, file_head) == REPEATED)
		{
			printf("Error : The file %s is repeated\n", filenames);
			printf("So we are not adding into the file\n");
			return FAILURE;
		}
		else
		{
			printf("Successfully : %s Added to the list\n", filenames);
			return SUCCESS;
		}
	}
}



