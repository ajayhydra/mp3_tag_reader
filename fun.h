#ifndef FUN
#define FUN
typedef struct Tag
{
    int size;
    char title[100];
    char artist[100];
    char album[100];
    char year[5];
    char music[100];
    char comment[100];
    char genre[2];
    FILE *fptr_mp3_file;
}Tag;


void do_view_operation(Tag *id,int ret);
void decode_size(Tag *id);
void decode_title(Tag *id,int size);
void decode_artist(Tag *id,int size);
void decode_album(Tag *id,int size);
void decode_year(Tag *id,int size);
void decode_music(Tag *id,int size);
void decode_comment(Tag *id,int size);
void printable_character(char *data,int size);
void change_size(char *ptr);

void decode_title1(Tag *id);
void decode_artist1(Tag *id);
void decode_album1(Tag *id);
void decode_year1(Tag *id);
void decode_genre1(Tag *id);
void decode_comment1(Tag *id);
void print_details(Tag *id,int val);

void change_buffer(char *ptr);
void do_edit_operation(Tag *id,int ret,char *temp,char *choice);
int check_choice(Tag *id,int size,char *opt,char *temp);
#endif
