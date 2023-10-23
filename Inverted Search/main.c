/* Name : MUHAMMED ANAS K
*  Project : InvertedSearch
 * DESCRIPTION : An inverted index is a mapping of words to their location in a set of documents. Most modern search engines utilize 
 some form of an inverted index to process user-submitted queries. In its most basic form, an inverted index is a simple hash table 
 which maps words in the documents to some sort of document identifier. 
 
 * SAMPLE OUTPUT:- 
[index_no]	[word]	[file_count]	[filename]	[word_count]
--------------------------------------------------------------------------
[0]		are	     2		file(s) : file1.txt: 1 : file2.txt: 1 : -> NULL
[7]		Hi	     1		file(s) : file1.txt: 1 : -> NULL
		hello	     1		file(s) : file1.txt: 1 : -> NULL
		hi	     2		file(s) : file1.txt: 2 : file2.txt: 1 : -> NULL
		how	     1		file(s) : file1.txt: 1 : -> NULL
[24]		you	     2		file(s) : file1.txt: 1 : file2.txt: 1 : -> NULL

 */


#include "inverted.h"
int main(int argc, char *argv[])
{
	//check whether there is only one CLA
	if(argc == 1)
	{
		//printing the error message
		printf("Error : Invalid number of arguments\nUsage: ./invertedIndex <file1> <file2> ...\n");
		return FAILURE;
	}
	else
	{
		//create a file structure
		file_node_t *file_head = NULL;

		//validate all the files
		validate_n_store_filenames(&file_head, argv);

		//logic to check wheteher the files are valid or not
		if(file_head == NULL)
		{
			printf("There is no valid files\nPlease enter valid files\n");
			return FAILURE;
		}

		//create a main structure
		main_node_t *HT_head[SIZE] = {NULL};

		//Variable and array declaration
		char cont;
		int choice, flage = 0;
		char name[BUFF_SIZE], backup_f[BUFF_SIZE], upd_file[BUFF_SIZE];
	
		//Loop for continue the proccess 
		while(1)
		{
			//Print the content
			printf("1.create DB\n2.Display DB\n3.Search DB\n4.Update DB\n5.Save DB\nPlease Enter your choice : ");
			scanf("%d", &choice);
			//switch case to do different operations
			switch(choice)
			{
				//case 1 is for creating the database
				case 1:
					if (flage == 0)
					{
						//Function call of create database
						create_DB(file_head, HT_head);
						flage = 1;   //flage set as 1
					}
					else
						//Print the content
						printf("Files passed through commandline already added into the Database\n");
					break;

				//case 2 is for display the database	
				case 2:
					//function call of display database
					display_DB(HT_head);
					break;
				
				//case 3 is for search the database	
				case 3:
					printf("Enter the word to be searched in Database : ");
					scanf("%s", name);
					//Finding the index value
					int index = tolower(name[0]) % 97;
					if (index < 0 || index > 25)
						index = 26;
					//function call of search database
					search_DB(HT_head[index], name, index);
					break;

				//case 4 for update the database
				case 4:
					printf("Enter the filename : ");
					scanf("%s", upd_file);

					//function call of update database
					update_DB(HT_head, file_head, upd_file);
					break;

				//case 5 for save the database to backup file
				case 5:
					printf("Enter the backup filename : ");
					scanf("%s", backup_f);
					//function call to save the database 
					save_DB(HT_head, backup_f);
					break;

				//default massage	
				default :
					printf("Error : Invalid choice\n");
			}
			printf("Do you want to continue(y/Y) ? ");
			getchar();
			scanf("%c", &cont);
			//checking the cont value
			if (cont != 'y' && cont != 'Y')
				return SUCCESS;
		}
		
	}
}
