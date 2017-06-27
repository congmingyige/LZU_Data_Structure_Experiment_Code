#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

void fileclose_movie_introduce(int PosMovie)
{
    char filename[100];
    //获得文件路径
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    strcat(filename,"movie_introduce.txt");
    FILE *fp_movie_introduce=fopen(filename,"w");
    fprintf(fp_movie_introduce,"0\n");
    fclose(fp_movie_introduce);
}

void fileclose_movie()
{
    long i,j;
    char filename[100],*t;
    //获得文件路径
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    strcat(filename,"movie.txt");
    FILE *fp_movie=fopen(filename,"w");
    fprintf(fp_movie,"%ld\n",total_movie);
    for (i=0;i<total_movie;i++)
    {
        printf("test\n");
        fprintf(fp_movie,"\n");
        fprintf(fp_movie,"%ld\n",movie[i].Number);
        fprintf(fp_movie,"%s\n",movie[i].Name);
        fprintf(fp_movie,"/name/\n");
        fprintf(fp_movie,"%s\n",movie[i].Place);
        fprintf(fp_movie,"/place/\n");

        t=strstr(movie[i].Photo,"\Photo");
        if (t==NULL)
            fprintf(fp_movie,"\n");
        else
            fprintf(fp_movie,"%s\n",t);
        fprintf(fp_movie,"/photo/\n");

        t=strstr(movie[i].Torrent,"\Torrent");
        if (t==NULL)
            fprintf(fp_movie,"\n");
        else
            fprintf(fp_movie,"%s\n",t);
        fprintf(fp_movie,"/torrent/\n");

        t=strstr(movie[i].File,"\File");
        if (t==NULL)
            fprintf(fp_movie,"\n");
        else
            fprintf(fp_movie,"%s\n",t);
        fprintf(fp_movie,"/file/\n");

        fprintf(fp_movie,"%s\n",movie[i].Passage);
        fprintf(fp_movie,"/passage/\n");

        fprintf(fp_movie,"%f %f %f %ld %f\n",movie[i].OverallMark,movie[i].ProfessorMark,movie[i].UserMark,movie[i].UserNumber,movie[i].RatioMark);
        fprintf(fp_movie,"%d %d %d\n",movie[i].year,movie[i].month,movie[i].day);
        fprintf(fp_movie,"%d %d %d %d\n",movie[i].Mood,movie[i].Condition,movie[i].Sex,movie[i].Age);
        for (j=1;j<10;j++)
            fprintf(fp_movie,"%d ",movie[i].Category[j]);
        fprintf(fp_movie,"\n");
    }
    fclose(fp_movie);
}

void fileclose_user()
{
    long i,j;
    char filename[100];
    GetModuleFileName(NULL,filename,100);
    *(strstr(filename,"MovieSoftware")+14)='\0';
    strcat(filename,"user.txt");
    FILE *fp_user=fopen(filename,"w");
    fprintf(fp_user,"%ld\n",CurrentUser);
    fprintf(fp_user,"%ld\n",total_user);
    for (i=0;i<total_user;i++)
    {
        fprintf(fp_user,"\n");
        fprintf(fp_user,"%ld\n",user[i].Number);
        fprintf(fp_user,"%s\n",user[i].Name);
        fprintf(fp_user,"/name/\n");
        fprintf(fp_user,"%s\n",user[i].Password);
        fprintf(fp_user,"/password/\n");
        fprintf(fp_user,"%d %d %d\n",user[i].Sex,user[i].Age,user[i].Preference);
    }
    fclose(fp_user);
}
