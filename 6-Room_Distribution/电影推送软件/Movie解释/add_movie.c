#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
//get current exe address
    char s[100],s1[100],s2[100],category[30][15],mood[30][15];
    int i,j;
    j=0;
    for (i=0;*(argv[0]+i);i++)
    {
        s[j]=*(argv[0]+i);
        if (*(argv[0]+i)=='\\')
        {
            j++;
            s[j]='\\';
        }
        j++;
    }
    while (s[j]!='\\') j--;
    s[j+1]='\0';
//////////////////////////////
//input movie categories&information
    strcpy(s1,s);
    strcat(s1,"data\\movie_category.txt");
    strcpy(s2,s);
    strcat(s1,"data\\mood.txt");
    strcpy(s3,s);
    strcat(s3,"data\\movie_information.txt");

    fp1=fopen(s1,"r");
    ans1=0;
    while (fscanf(fp1,"%s",category[ans1])!=NULL) { ans1++; }
    fclose(fp1);

    fp2=fopen(s2,"r");
    ans2=0;
    while (fscanf(fp2,"%s",mood[ans2])!=NULL) { ans2++; }
    fclose(fp2);

    fp3=fopen(s3,"a+");
    printf("")
}
