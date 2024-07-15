/*
Name:
Date:
Description:
Sample i/p:
Sample o/p:
 */
#include<stdio.h>
#include"fun.h"
#include<string.h>
#include<ctype.h>
void do_view_operation(Tag *id,int ret)
{
    if(ret==2)
    {
	decode_size(id);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_title(id,id->size);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_artist(id,id->size);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_album(id,id->size);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_year(id,id->size);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_music(id,id->size);
	rewind(id->fptr_mp3_file);
	fseek(id->fptr_mp3_file,10,SEEK_SET);
	decode_comment(id,id->size);
	print_details(id,ret);
    }
    else if(ret==1)
    {
	rewind(id->fptr_mp3_file);
	decode_title1(id);
	decode_artist1(id);
	decode_album1(id);
	decode_year1(id);
	decode_comment1(id);
	decode_genre1(id);
	print_details(id,ret);
    }


}
void printable_character(char *data,int size)
{
    int count=0;
    char buffer[size];
    for(int i=0;i<size;i++)
    {
	if(isprint(data[i]))
	{
	    buffer[count]=data[i];
	    count++;
	}
    }
    buffer[count]='\0';
    strcpy(data,buffer);
}

void decode_size(Tag *id)
{
    id->size=0;
    rewind(id->fptr_mp3_file);
    fseek(id->fptr_mp3_file,6,SEEK_SET);
    int size1;
    int count=0;
    fread(&size1,4,1,id->fptr_mp3_file);
    change_size(&size1);
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
    printf("%d ",id->size);
}

void decode_title(Tag *id,int size)
{
    id->title[0]='\0';
    char buffer[100];
    buffer[4]='\0';
    fread(buffer,4,1,id->fptr_mp3_file);
    int buffer1;
    if(strcmp(buffer,"TIT2")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->title,buffer1,1,id->fptr_mp3_file);
        //strcpy(id->title,buffer);
	id->title[buffer1]='\0';
	printable_character(id->title,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_title(id,id->size);
	}
    }
}
void decode_artist(Tag *id,int size)
{
    id->artist[0]='\0';
    char buffer[100];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,"TPE1")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->artist,buffer1,1,id->fptr_mp3_file);
	//strcpy(id->artist,buffer);
	id->artist[buffer1]='\0';
	printable_character(id->artist,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_artist(id,id->size);
	}
    }
}

void decode_album(Tag *id,int size)
{
    id->album[0]='\0';
    char buffer[100];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,"TALB")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->album,buffer1,1,id->fptr_mp3_file);
	//strcpy(id->album,buffer);
	id->album[buffer1]='\0';
	printable_character(id->album,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_album(id,id->size);
	}
    }
}

void decode_year(Tag *id,int size)
{
    id->year[0]='\0';
    char buffer[100];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,"TYER")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->year,buffer1,1,id->fptr_mp3_file);
	//strcpy(id->year,buffer);
	id->year[buffer1]='\0';
	printable_character(id->year,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_year(id,id->size);
	}
    }
}

void decode_music(Tag *id,int size)
{
    id->music[0]='\0';
    char buffer[100];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,"TCON")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->music,buffer1,1,id->fptr_mp3_file);
        //strcpy(id->music,buffer);
	id->music[buffer1]='\0';
	printable_character(id->music,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_music(id,id->size);
	}
    }
}

void decode_comment(Tag *id,int size)
{
    id->comment[0]='\0';
    char buffer[100];
    fread(buffer,4,1,id->fptr_mp3_file);
    buffer[4]='\0';
    int buffer1;
    if(strcmp(buffer,"COMM")==0)
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	//printf("   %d\n",buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fread(id->comment,buffer1,1,id->fptr_mp3_file);
	//strcpy(id->comment,buffer);
	id->comment[buffer1]='\0';
	printable_character(id->comment,buffer1);
    }
    else
    {
	fread(&buffer1,4,1,id->fptr_mp3_file);
	change_size(&buffer1);
	fseek(id->fptr_mp3_file,2,SEEK_CUR);
	fseek(id->fptr_mp3_file,buffer1,SEEK_CUR);
	int val=ftell(id->fptr_mp3_file);
	if(val<size)
	{
	    decode_comment(id,id->size);
	}
    }
}

void decode_title1(Tag *id)
{
    char buffer[30];
    fread(id->title,30,1,id->fptr_mp3_file);
   // strcpy(id->title,buffer);
    id->title[30]='\0';
    printable_character(id->title,31);
}

void decode_artist1(Tag *id)
{
    char buffer[30];
    fread(id->artist,30,1,id->fptr_mp3_file);
    //strcpy(id->artist,buffer);
    id->artist[30]='\0';
    printable_character(id->artist,31);
}
void decode_album1(Tag *id)
{
    char buffer[30];
    fread(id->album,30,1,id->fptr_mp3_file);
    //strcpy(id->album,buffer);
    id->album[30]='\0';
    printable_character(id->album,31);
}
void decode_year1(Tag *id)
{
    char buffer[4];
    fread(id->year,4,1,id->fptr_mp3_file);
    //strcpy(id->year,buffer);
    id->year[4]='\0';
    printable_character(id->year,5);
}
void decode_comment1(Tag *id)
{
    char buffer[30];
    fread(id->comment,30,1,id->fptr_mp3_file);
    strcpy(id->comment,buffer);
    id->comment[30]='\0';
    printable_character(id->comment,31);
}
void decode_genre1(Tag *id)
{
    char buffer[30];
    fread(id->genre,30,1,id->fptr_mp3_file);
    //strcpy(id->genre,buffer);
    id->genre[1]='\0';
    printable_character(id->genre,2);
}
void change_size(char *ptr)
{
    for(int i=0;i<2;i++)
    {
	char temp=ptr[i];
	ptr[i]=ptr[3-i];
	ptr[3-i]=temp;
    }
}

void print_details(Tag *id,int val)
{
    printf("-----------------------------SELECTED VIEW DETAILS---------------------------------\n");
    printf("\n"
	    "\n"
	    "\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("MP3 TAG READER AND EDITOR FOR ID3v%d\n",val);
    printf("-------------------------------------------------------------------------------------\n");
    printf("TITLE           :           %s\n",id->title);
    printf("ARTIST          :           %s\n",id->artist);
    printf("ALBUM           :           %s\n",id->album);
    printf("YEAR            :           %s\n",id->year);
    if(val==2)
    {
	printf("MUSIC           :           %s\n",id->music);
    }
    else if(val==1)
    {
	printf("GENRE           :           %c\n",id->genre[0]);
    }
    printf("COMMENT         :           %s\n",id->comment);
}








