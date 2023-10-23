#include "inverted.h"
/*
 *Function to create the database
 *create the data base for each and every file by calling the function read_datafile
 */
int create_DB(file_node_t *file_head, main_node_t **HT_head)
{
	while (file_head)
	{
		read_datafile(HT_head, file_head -> f_name);
		file_head = file_head -> link;
	}
	return SUCCESS;
}

/*
 *Function to read the data from the file
 *open the file
 *read the file until the EOF
 *identify the index
 *check the particular index is NULL or not
 *if NULL perform insert last operation
 *if particular index is not NULL 
 *transverse through all the nodes in particular index
 *check the word is same or not
 *if not same transverse through the next node
 *if the words are same update the word count
 */
void read_datafile(main_node_t **HT_head, char *f_name)
{
	FILE *fptr = fopen(f_name, "r");
	char word[BUFF_SIZE];
	short index, flag = 0;
	while (fscanf(fptr, "%s", word) != EOF)
	{
		index = tolower(word[0]) % 97;	
		if (index > 25 || index < 0)
			index = 26;
		
		if (HT_head[index] == NULL)
			insert_at_last_main( &HT_head[index], word, f_name);
		else
		{
			main_node_t *temp = HT_head[index];
			while(temp)
			{
				if (strcmp(temp->word, word))
					temp = temp->link;
				else
				{
					update_word_count(&HT_head[index], f_name);
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				insert_at_last_main(&HT_head[index], word, f_name);
		}
	}
	printf("Successfull: Creation of database for file %s\n", f_name);
}

/*
 *Function to perform insert at last operation
 *create a node
 *check the node is created or not
 *update the data
 *check the head is NULL or not 
 *if NULL update head with the new node adress
 *else transverse through all the nodes
 *at the last insert the node
 */
int insert_at_last_main(main_node_t **head, char *word, char *f_name)
{
	main_node_t *new_main = malloc(sizeof(main_node_t));
	if (new_main ==NULL)
		return FAILURE;

	new_main -> f_count = 1;
	strcpy(new_main -> word, word);
	new_main -> link = NULL;
	update_subnode(&new_main, f_name);

	if (*head == NULL)
		*head = new_main;
	else
	{
		main_node_t *temp = *head;
		while (temp->link)
			temp = temp->link;
		temp -> link = new_main;
	}
	return SUCCESS;
}

/*
 *Function to create the subnode
 *create the subnode
 *check the subnode is created or not
 *update the wordcount , file name and link in the subnode
 *in the main node sublink update the subnode adress
 */
int update_subnode(main_node_t **main_node, char *f_name)
{
	sub_node_t *new_sub = malloc(sizeof(sub_node_t));
	if (new_sub == NULL)
		return FAILURE;

	new_sub -> w_count = 1;
	strcpy(new_sub -> f_name, f_name);
	new_sub -> link = NULL;

	(*main_node)->sub_link = new_sub;

	return SUCCESS;
}

/*
 *Function to update the word count
 *take a temp pointer to store the sublink adress
 *transverse through all the particular subnode
 *compare with the file name
 *if the file name is same increment the word count
 *else move the next subnode
 *if the filename is not same create the subnode
 *update the subnode with word count, file name and its link part
 *and establish the link with the previous node
 */
int update_word_count(main_node_t **head, char *f_name)
{
	sub_node_t *temp = (*head) -> sub_link, *prev = NULL;

	while(temp)
	{
		if (!strcmp(f_name, temp -> f_name))
		{
			temp -> w_count += 1;
			return SUCCESS;
		}
		else
		{
			prev = temp;
			temp = temp -> link;
		}
	}
	(*head)->f_count += 1; 
	sub_node_t *new_sub = malloc(sizeof(sub_node_t));
	if (new_sub == NULL)
		return FAILURE;

	new_sub -> w_count = 1;
	strcpy(new_sub -> f_name, f_name);
	new_sub -> link = NULL;

	prev -> link = new_sub;
	return SUCCESS;
}
