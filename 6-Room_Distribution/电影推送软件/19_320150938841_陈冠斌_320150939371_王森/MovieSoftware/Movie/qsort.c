#include <stdio.h>
#include <stdlib.h>
#include "define.h"
extern long ShowMovie[1000];

void qsort_OverallMark(long l,long r)
{
    long i,j,y;
    float x;
    i=l; j=r; x=movie[ShowMovie[(l+r)/2]].OverallMark;
    while (i<j)
    {
        while (movie[ShowMovie[i]].OverallMark>x) i++;
        while (movie[ShowMovie[j]].OverallMark<x) j--;
        if (i<=j)
        {
            y=ShowMovie[i];
            ShowMovie[i]=ShowMovie[j];
            ShowMovie[j]=y;
            i++;
            j--;
        }
    }
    if (i<r) qsort_OverallMark(i,r);
    if (j>l) qsort_OverallMark(l,j);
}

void qsort_ProfessorMark(long l,long r)
{
    long i,j,y;
    float x;
    i=l; j=r; x=movie[ShowMovie[(l+r)/2]].ProfessorMark;
    while (i<j)
    {
        while (movie[ShowMovie[i]].ProfessorMark>x) i++;
        while (movie[ShowMovie[j]].ProfessorMark<x) j--;
        if (i<=j)
        {
            y=ShowMovie[i];
            ShowMovie[i]=ShowMovie[j];
            ShowMovie[j]=y;
            i++;
            j--;
        }
    }
    if (i<r) qsort_ProfessorMark(i,r);
    if (j>l) qsort_ProfessorMark(l,j);
}

void qsort_Time(long l,long r)
{
    long i,j,x,y,z,t;
    i=l; j=r;
    x=movie[ShowMovie[(l+r)/2]].year;
    y=movie[ShowMovie[(l+r)/2]].month;
    z=movie[ShowMovie[(l+r)/2]].day;
    while (i<j)
    {
        while (movie[ShowMovie[i]].year>x || (movie[ShowMovie[i]].year==x && movie[ShowMovie[i]].month>y) || (movie[ShowMovie[i]].year==x && movie[ShowMovie[i]].month==y && movie[ShowMovie[i]].day>z)) i++;
        while (movie[ShowMovie[j]].year<x || (movie[ShowMovie[j]].year==x && movie[ShowMovie[j]].month<y) || (movie[ShowMovie[j]].year==x && movie[ShowMovie[j]].month==y && movie[ShowMovie[j]].day<z)) j--;
        if (i<=j)
        {
            t=ShowMovie[i];
            ShowMovie[i]=ShowMovie[j];
            ShowMovie[j]=t;
            i++;
            j--;
        }
    }
    if (i<r) qsort_Time(i,r);
    if (j>l) qsort_Time(l,j);
}
