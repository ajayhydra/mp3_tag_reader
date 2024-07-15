/*
Name:
Date:
Description:
Sample i/p:
Sample o/p:
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fun.h"
void help_menu()
{
    printf("-------------------------------------------------------HELP MENU-------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("         2.1. -t -> to edit song title\n");
    printf("         2.2. -a -> to edit artist name\n");
    printf("         2.3. -A -> to edit album name\n");
    printf("         2.4. -y -> to edit year\n");
    printf("         2.5. -m -> to edit content\n");
    printf("         2.6. -c -> to edit comment\n");
    printf("\n");
    printf("\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}
void display_error()
{
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
    printf("USAGE :\n");
    printf("To view please pass like: ./a.out -v mp3filename\n");
    printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
    printf("To get help pass like : ./a.out --help\n");
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}
int check_version(Tag *id,char *filename)
{
    id->fptr_mp3_file=fopen(filename, "r+");
    char buffer[4];
    char buffer2[4];
    fread(buffer,3,1,id->fptr_mp3_file);
    fseek(id->fptr_mp3_file,-128,SEEK_END);
    fread(buffer2,3,1,id->fptr_mp3_file);
    buffer[3]='\0';
    buffer2[3]='\0';
    if(strcmp(buffer,"ID3")==0)
    {
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,3,SEEK_CUR);
	unsigned int buffer1=0;
	fread(&buffer1,1,1,id->fptr_mp3_file);
	if(buffer1==0x03)
	{
	    return 2;
	}
	else
	    return 0;
    }
    else if(strcmp(buffer2,"TAG")==0)
    {
	return 1;
    }
    else
	return 0;
}

int main(int argc,char *argv[])
{
    char *filename;
    Tag id;
    char choice[5];
    char *temp;
    int ret=0;
    //FILE *fptr_mp3_file;
    if(argv[1]!=NULL)
    {
	if(strcmp(argv[1], "-v")==0)
	{
	    if(argv[2]!=NULL)
	    {
		if(strstr(argv[2], ".mp3") !=NULL)
		{
		    filename=argv[2];
		    ret=check_version(&id,filename);
		    if(ret==1 || ret==2)
		    {
			do_view_operation(&id,ret);
			//selected view details
			//function call
		    }
		    else
		    {
			printf("Unable to perform operation on this file\n");

			//display error message
			//display usage message
		    }
		}
		else
		{
		    display_error();
		    //display error message
		    //display usage message
		}
	    }
	    else
	    {
		display_error();
		//display error message
	    }
	}
	else if(strcmp(argv[1], "-e")==0)
	{
	    if(argv[2]!=NULL)
	    {
		if((strcmp(argv[2], "-t")==0) || (strcmp(argv[2], "-a")==0) || (strcmp(argv[2], "-A")==0) || (strcmp(argv[2], "-y")==0) || (strcmp(argv[2], "-m")==0) || (strcmp(argv[2], "-m")==0) || (strcmp(argv[2], "-c")==0))
		{
		    strcpy(choice,argv[2]);
		    printf("%s\n",choice);
		    if(argv[3]!=NULL)
		    {
			temp=argv[3];
			if(argv[4]!=NULL)
			{
			    if(strstr(argv[4], ".mp3")!=NULL)
			    {
				filename=argv[4];
				ret=check_version(&id,filename);
				printf("%d\n",ret);
				if(ret==2 || ret==1)
			        do_edit_operation(&id,ret,temp,choice);
				//print edit operation selected
				//function call
			    }
			    else
			    {
				display_error();
				//print failure message
				//print usage details
			    }

			}
			else
			{
			    display_error();
			    //print failure message
			    //print usage details
			}
		    }
		    else
		    {
			display_error();
			//print failure message
			//print usage details
		    }
		}
		else
		{
		    display_error();
		    //print failure message
		    //print usage details
		}
	    }
	    else
	    {
		display_error();
		//print failure message
		//print usage details
	    }
	}
	else if(strcmp(argv[1], "--help")==0)
	{
	    help_menu();

	    //display usage details
	}
	else
	{
	    display_error();
	    //print error message
	    //display usage details
	}
    }
    else
    {
	display_error();
	//print error message
	//display usage details
    }
}




