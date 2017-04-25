/*******************************************************************************
 *
 * File Name:  	myLs.h
 *
 * Description: This is header file for a program to implement custom "ls" command utility
 *
 * History:
 *		MARCH/29/2012, CDA, modified the header file, added some #defines for file types
 *							and for filetype colours, (as suggeseted by alien.... :P)
 *      MARCH/16/2012, CDA, Created file to implement custom "ls" command utility
 *
 ******************************************************************************/

#ifndef MYLS__H__
#define MYLS__H__

/****************
 * Include Files
 ****************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <dirent.h>
#include <time.h>

/************************
 * typedefs and #defines
 ************************/
#define		BUFF_CD				3
#define		BUFF_FP				9
#define 	BUFF_DT				32
#define		MAX_FILE_PATH		4096
#define 	HELP_MSG			"-help"
#define 	r 					'r'
#define 	w 					'w'
#define 	x 					'x'
#define 	n 					'-'

#define 	BLACK 				"\033[22;30m"
#define 	GRAY 				"\033[01;30m"
#define 	RED 				"\033[22;31m"
#define 	LRED 				"\033[01;31m"
#define 	GREEN 				"\033[22;32m"
#define 	LGREEN 				"\033[01;32m"
#define 	BLUE 				"\033[22;34m"
#define 	LBLUE 				"\033[01;34m"
#define 	BROWN 				"\033[22;33m"
#define 	YELLOW 				"\033[01;33m"
#define 	CYAN 				"\033[22;36m"
#define 	LCYAN 				"\033[01;36m"
#define 	MAGENTA 			"\033[22;35m"
#define 	LMAGENTA 			"\033[01;35m"
#define 	WHITE 				"\033[01;37m"
#define 	RESET 				"\033[0m"
#define 	BOLD 				"\033[1m"
#define 	ULINE 				"\033[4m" 	//underline
#define 	BLINK 				"\033[5m"
#define 	INVERT 				"\033[7m"

#define 	GREENBG 			"\033[22;42m"

#define __CHECK_ERR(retVal, val)	do{\
										if(retVal < 0)\
										{\
											perror("error");\
											exit(val);\
										}\
									  }while(0)

#endif

