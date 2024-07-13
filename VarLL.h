#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct iV{
    char name[100];
    int data;
    struct iV *next;
};

struct fV{
    char name[100];
    float data;
    struct fV *next;
};

struct cV{
    char name[100];
    char data;
    struct cV *next;
};

void appendI(struct iV **, char *, int);
void appendF(struct fV **, char *, float);
void appendC(struct cV **, char *, char);

int typeFetcher( char *, struct iV *, struct fV *, struct cV *);

int valFetcherI( char *, struct iV *);
float valFetcherF( char *, struct fV *);
char valFetcherC( char *, struct cV *);

void appendI(struct iV **q, char *name, int n)
{
    struct iV *nnode, *temp= *q;

    if (temp == NULL)
    {
        *q= (struct iV *)malloc(sizeof(struct iV));
        strcpy((*q)->name,name);
        (*q)->data= n;
        (*q)->next= NULL;
    }
    else
    {
        if(!(strcmp(name, temp->name)))
        {
                temp->data= n;
                return;
        }
        
        while (temp->next != NULL)
        {
            temp= temp->next;

            if(!(strcmp(name, temp->name)))
            {
                temp->data= n;
                return;
            }
        }

        nnode=(struct iV *)malloc(sizeof(struct iV));
        strcpy(nnode->name,name);
        nnode->data= n;
        nnode->next= NULL;
        temp->next= nnode;
    }
}

void appendF(struct fV **q, char *name, float n)
{
    struct fV *nnode, *temp= *q;

    if (temp == NULL)
    {
        *q= (struct fV *)malloc(sizeof(struct fV));
        strcpy((*q)->name,name);
        (*q)->data= n;
        (*q)->next= NULL;
    }
    else
    {
        if(!(strcmp(name, temp->name)))
        {
                temp->data= n;
                return;
        }

        while (temp->next != NULL)
        {
            temp= temp->next;

            if(!(strcmp(name, temp->name)))
            {
                temp->data= n;
                return;
            }
        }

        nnode=(struct fV *)malloc(sizeof(struct fV));
        strcpy(nnode->name,name);
        nnode->data= n;
        nnode->next= NULL;
        temp->next= nnode;
    }
}

void appendC(struct cV **q, char *name, char n)
{
    struct cV *nnode, *temp= *q;

    if (temp == NULL)
    {
        *q= (struct cV *)malloc(sizeof(struct cV));
        strcpy((*q)->name,name);
        (*q)->data= n;
        (*q)->next= NULL;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp= temp->next;
        }

        nnode=(struct cV *)malloc(sizeof(struct cV));
        strcpy(nnode->name,name);
        nnode->data= n;
        nnode->next= NULL;
        temp->next= nnode;
    }
}

int typeFetcher( char *name, struct iV *IV, struct fV *FV, struct cV *CV)
{
    while (IV != NULL)
    {
        if (!strcmp( name, IV->name))
        {
            return 1;
        }
        IV= IV->next;
    }

    while (FV != NULL)
    {
        if (!strcmp( name, FV->name))
        {
            return 2;
        }
        FV= FV->next;
    }

    while (CV != NULL)
    {
        if (!strcmp( name, CV->name))
        {
            return 3;
        }
        CV= CV->next;
    }

    return 0;
}

int valFetcherI( char *name, struct iV *IV)
{
    while (IV != NULL)
    {
        if (!strcmp( name, IV->name))
        {
            return IV->data;
        }
        IV= IV->next;
    }
}

float valFetcherF( char *name, struct fV *FV)
{
    while (FV != NULL)
    {
        if (!strcmp( name, FV->name))
        {
            return FV->data;
        }
        FV= FV->next;
    }
}

char valFetcherC( char *name, struct cV *CV)
{
    while (CV != NULL)
    {
        if (!strcmp( name, CV->name))
        {
            return CV->data;
        }
        CV= CV->next;
    }
}