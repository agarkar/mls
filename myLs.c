/*******************************************************************************
 *
 * File Name:  	myLs.c
 *
 * Description:	This is a program to implement custom "ls" command utility
 *
 * History:		
 *		MARCH/29/2012, CDA, modified the code for bugs, suggested by....
 * 							alien (ashish my friend), like the max path size,
 *							more file types, associated filetype colours, removed
 *							unnecessary variables etc.
 *		MARCH/08/2012, CDA,	Created file to implement custom "ls" command utility		
 *
 ******************************************************************************/

/****************
 * Include Files
 ****************/
#include "myLs.h"

/****************
 * main function
 ****************/
int main(int argc, char* argv[])
{
	int 	i;
	int 	retVal;
	int 	entryCount;
	
	char	*dirPath;
	char 	buff[BUFF_DT];
	char	currDir[BUFF_CD] 	= 	"./";
	char	filePerm[BUFF_FP];
	char	filePath[MAX_FILE_PATH];
		
	struct 	stat 	fileBuff;
	struct 	dirent 	**entries;

	if(argc == 1)
	{
		printf("Current Directory :: %s\n", currDir);
		entryCount = scandir(currDir, &entries, 0, alphasort);
		__CHECK_ERR(entryCount, 1);
		dirPath = currDir;
	}
	else if(argc == 2)
	{
		if(!strcmp(argv[1],HELP_MSG))
		{
			printf("usage :: \n%s \t\t== ls -la for current directory\n%s <Path> \t== ls -la for path specified\n", argv[0], argv[0]);
			exit(0);
		}
		dirPath = argv[1];
		printf("directory :: %s\n", dirPath);
		entryCount = scandir(dirPath, &entries, 0, alphasort);
		if(entryCount == -1)
		{
			printf("Wrong usage :: try %s -help for more details\n", argv[0]);
			exit(0);
		}
		__CHECK_ERR(entryCount, 1);
	}
	else
	{
		printf("Wrong usage :: try %s -help for more details\n", argv[0]);
		exit(0);
	}
	
	printf("No of Files :: %d\n", entryCount);
	printf("<filetype><permissions> <Inode No> <No of Hard Links> <Size in Bytes> <Date><Time> <Name>\n\n");
	
	for(i = 0; i < entryCount; i++)
	{
		char type = '\0';
		
		//preparing the file path
		sprintf(filePath, "%s%s", dirPath, entries[i]->d_name);
		//get the file status
		retVal = lstat(filePath, &fileBuff);
		__CHECK_ERR(retVal, 1);
		
		//clear the buffer
		bzero(filePerm, 9);
			
		//checking user permissions
		if(fileBuff.st_mode & S_IRUSR)
			filePerm[0] = r;
		else
			filePerm[0] = n;
		if(fileBuff.st_mode & S_IWUSR)
			filePerm[1] = w;
		else
			filePerm[1] = n;
		if(fileBuff.st_mode & S_IXUSR)
			filePerm[2] = x;
		else
			filePerm[2] = n;

		//checking group permissions
		if(fileBuff.st_mode & S_IRGRP)
			filePerm[3] = r;
		else
			filePerm[3] = n;
		if(fileBuff.st_mode & S_IWGRP)
			filePerm[4] = w;
		else
			filePerm[4] = n;
		if(fileBuff.st_mode & S_IXGRP)
			filePerm[5] = x;
		else
			filePerm[5] = n;
		
		//checking others permission
		if(fileBuff.st_mode & S_IROTH)
			filePerm[6] = r;
		else
			filePerm[6] = n;
		if(fileBuff.st_mode & S_IWOTH)
			filePerm[7] = w;
		else
			filePerm[7] = n;
		if(fileBuff.st_mode & S_IXOTH)
			filePerm[8] = x;
		else
			filePerm[8] = n;

		filePerm[9] = '\0';
		
		bzero(buff, BUFF_DT);
		//getting the time of last status changed
		sprintf( buff, "%s", ctime( &(fileBuff.st_mtime) ) );
		buff[strlen(buff)-1] = '\0';

		//file types and associated colur codes
		if(entries[i]->d_type == 1)			//pipe file
		{
			type = 'p';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			printf(BROWN "%s" RESET "\n", entries[i]->d_name); 		//brown
		}
		else if(entries[i]->d_type == 2)	//character file
		{
			type = 'c';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			printf(YELLOW "%s" RESET "\n", entries[i]->d_name); 	//yellow
		}
		else if(entries[i]->d_type == 4)	//directory
		{
			type = 'd';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			if( (filePerm[7] == w) & (filePerm[8] == x) )
			{
				printf(GREENBG "%s" RESET "\n", entries[i]->d_name); //green background
			}
			else
			{
				printf(CYAN "%s" RESET "\n", entries[i]->d_name); 	//cyan
			}
		}
		else if(entries[i]->d_type == 6)	//block file
		{
			type = 'b';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			printf(YELLOW "%s" RESET "\n", entries[i]->d_name); 	//yellow
		}
		else if(entries[i]->d_type == 8)	//regular file
		{
			type = '-';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			if( (filePerm[2] == x) | (filePerm[5] == x) | (filePerm[8] == x) )
			{
				printf(GREEN "%s" RESET "\n", entries[i]->d_name); 	//green
			}
			else
			{
				printf("%s\n", entries[i]->d_name);					//no colour
			}
		}
		else if(entries[i]->d_type == 10)	//Link file
		{
			type = 'l';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			printf(CYAN "%s" RESET "\n", entries[i]->d_name); 		//cyan
		}
		else if(entries[i]->d_type == 12)	//special file
		{
			type = 's';
			printf("%c%s %8lu %4u %10ld %s ", type,filePerm, entries[i]->d_ino, fileBuff.st_nlink, fileBuff.st_size, buff);
			printf(MAGENTA "%s" RESET "\n", entries[i]->d_name); 	//magenta
		}
		else
		{
		}
	}
	printf("\n");
	printf("\t\t\t\t\tcopy left @ Chandrakant Agarkar :P\n");
	exit(0);
}

