/*
Name:
Date:
Description:
Sample i/p:
Sample o/p:
 */
#include<stdio.h>
#include<string.h>
#include"fun.h"
void change_buffer(char *ptr)
{
    for(int i=0;i<2;i++)
    {
	char temp=ptr[i];
	ptr[i]=ptr[3-i];
	ptr[3-i]=temp;
    }
}
int check_choice(Tag *id,int size,char *opt,char *temp)
{
    static int flag=0;
    char buffer[5];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,opt)==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_buffer(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	int len=strlen(temp);
	fwrite(temp,len,1,id->fptr_mp3_file);
	char ch='\0';
	for(int i=0;i<(buffer1-len);i++)
	{
	    fwrite(&ch,1,1,id->fptr_mp3_file);
	}
	flag=1;
	return flag;
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_buffer(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    flag=check_choice(id,id->size,opt,temp);
	}
    }
    return flag;
}
void do_edit_operation(Tag *id,int ret,char *temp,char *choice)
{
    if(ret==2)
    {
	rewind(id->fptr_mp3_file);
	id->size=0;
	fseek(id->fptr_mp3_file,6,SEEK_CUR);
	int size1;
	int count=0;
	fread(&size1,4,1,id->fptr_mp3_file);
	change_buffer(&size1);
	for(int i=0;i<32;i++)
	{
	    int var;
	    if(size1 & (1<<i))
	    {
		var=1;
	    }
	    else
		var=0;
	    if((i%8)==7)
	    {
		continue;
	    }
	    else
	    {
		id->size=id->size | (var<<count);
		count++;
	    }
	}
	if(strcmp(choice,"-t")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"TIT2",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE TITLE--------------------------------------------\n");
		printf("TITLE              :  %s\n",temp);
		printf("-----------------------------------TITLE CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else if(strcmp(choice,"-a")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"TPE1",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE ARTIST--------------------------------------------\n");
		printf("ARTIST              :  %s\n",temp);
		printf("-----------------------------------ARTIST NAME CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else if(strcmp(choice,"-A")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"TALB",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE ALBUM--------------------------------------------\n");
		printf("ALBUM              :  %s\n",temp);
		printf("-----------------------------------ALBUM NAME CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else if(strcmp(choice,"-y")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"TYER",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE YEAR--------------------------------------------\n");
		printf("YEAR              :  %s\n",temp);
		printf("-----------------------------------YEAR CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else if(strcmp(choice,"-m")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"TCON",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE CONTENT--------------------------------------------\n");
		printf("MUSIC              :  %s\n",temp);
		printf("-----------------------------------CONTENT CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else if(strcmp(choice,"-c")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,10,SEEK_SET);
	    int res=check_choice(id,id->size,"COMM",temp);
	    printf("------------------------------SELECTED EDIT DETAILS---------------------------------------\n");
	    if(res==1)
	    {
		printf("----------------------------------CHANGE THE COMMENT--------------------------------------------\n");
		printf("COMMENT              :  %s\n",temp);
		printf("-----------------------------------COMMENT CHANGED SUCCESSFULLY----------------------------------\n");
	    }
	    else
	    {
		printf("------------------------------------INFORMATION NOT PRESENT IN FILE-----------------------------\n");
	    }
	}
	else
	{
	    puts("None");
	}
    }
    else if(ret==1)
    {
	if(strcmp(choice,"-t")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,3,SEEK_SET);
	    fwrite(temp,30,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE TITLE-------------------------------------\n");
	    printf("TITLE                     :  %s\n",temp);
	    printf("---------------------------------------------------TITLE CHANGED SUCCESSFULLY----------------------------\n");

	}
	else if(strcmp(choice,"-a")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,33,SEEK_SET);
	    fwrite(temp,30,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE ARTIST NAME-------------------------------------\n");
	    printf("ARTIST                     :  %s\n",temp);
	    printf("---------------------------------------------------ARTIST NAME CHANGED SUCCESSFULLY----------------------------\n");
	}
	else if(strcmp(choice,"-A")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,63,SEEK_SET);
	    fwrite(temp,30,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE ALBUM-------------------------------------\n");
	    printf("ALBUM                     :  %s\n",temp);
	    printf("---------------------------------------------------ALBUM CHANGED SUCCESSFULLY----------------------------\n");
	}
	else if(strcmp(choice,"-y")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,93,SEEK_SET);
	    fwrite(temp,4,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE YEAR-------------------------------------\n");
	    printf("YEAR                     :  %s\n",temp);
	    printf("---------------------------------------------------YEAR CHANGED SUCCESSFULLY----------------------------\n");
	}
	else if(strcmp(choice,"-c")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,97,SEEK_SET);
	    fwrite(temp,30,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE COMMENT-------------------------------------\n");
	    printf("COMMENT                     :  %s\n",temp);
	    printf("---------------------------------------------------COMMENT CHANGED SUCCESSFULLY----------------------------\n");
	}
	else if(strcmp(choice,"-m")==0)
	{
	    rewind(id->fptr_mp3_file);
	    fseek(id->fptr_mp3_file,127,SEEK_SET);
	    fwrite(temp,1,1,id->fptr_mp3_file);
	    printf("--------------------------------------------------SELECTED EDIT DETAILS--------------------------------\n");
	    printf("--------------------------------------------------CHANGE THE GENRE-------------------------------------\n");
	    printf("GENRE                     :  %s\n",temp);
	    printf("---------------------------------------------------GENRE CHANGED SUCCESSFULLY----------------------------\n");
	}
    }
}








