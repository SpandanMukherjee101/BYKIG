#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ArithmaticExprEval.h"

int main(int argc, char const *argv[])
{
    struct iV *IV;
    struct fV *FV;
    struct cV *CV;

    IV= NULL;
    FV= NULL;
    CV= NULL;

    char buffer[1000], tempS[1000], name[100], tD[100], dataC, ch;
    int mode, dataI, i, j, type, c[1000], k, p= -1, b1, b2, w[1000], l= 0;
    float dataF;

    if(argc==1)
    {
        exit(4);
    }

    FILE* fp = fopen(argv[1], "r");

    while (1)
    {        
        fscanf( fp, "%s", buffer);

        if (!(strcmp(buffer, ".")))
        {
            getch();
            fclose( fp);
            break;
        }

        mode= 0;

        mode= whichone(buffer);
        switch (mode)
        {
        
        case 1:
        
        startI:
            fscanf( fp, "%s", buffer);
            strcpy(name, buffer);
            dataI=0;

            fscanf( fp, "%s", buffer);
            if (!(strcmp(buffer,",")))
            {
                appendI( &IV, name, dataI);
                goto startI;
            }
            else if (!(strcmp(buffer,"=")))
            {
                fscanf( fp, "%s", tD);
                dataI = atoi(tD);

                fscanf( fp, "%s", buffer);
                if (!(strcmp(buffer,",")))
                {
                    appendI( &IV, name, dataI);
                    goto startI;
                }
                else if (!(strcmp(buffer,";")))
                {
                    appendI( &IV, name, dataI);
                }
            }
            else if (!(strcmp(buffer,";")))
            {
                appendI( &IV, name, dataI);
            }

            break;

        case 2:
        
        startF:
            fscanf( fp, "%s", buffer);
            strcpy(name, buffer);
            dataF=0;

            fscanf( fp, "%s", buffer);
            if (!(strcmp(buffer,",")))
            {
                appendF( &FV, name, dataF);
                goto startF;
            }
            else if (!(strcmp(buffer,"=")))
            {
                fscanf( fp, "%s", tD);
                dataF = atof(tD);

                fscanf( fp, "%s", buffer);
                if (!(strcmp(buffer,",")))
                {
                    appendF( &FV, name, dataF);
                    goto startF;
                }
                else if (!(strcmp(buffer,";")))
                {
                    appendF( &FV, name, dataF);
                }
            }
            else if (!(strcmp(buffer,";")))
            {
                appendF( &FV, name, dataF);
            }

            break;
        
        case 3:
        
        startC:
            fscanf( fp, "%s", buffer);
            strcpy(name, buffer);
            dataC= '\0';

            fscanf( fp, "%s", buffer);
            if (!(strcmp(buffer,",")))
            {
                appendC( &CV, name, dataC);
                goto startC;
            }
            else if (!(strcmp(buffer,"=")))
            {
                fscanf( fp, "%s", tD);
                dataC = tD[1];

                fscanf( fp, "%s", buffer);
                if (!(strcmp(buffer,",")))
                {
                    appendC( &CV, name, dataC);
                    goto startC;
                }
                else if (!(strcmp(buffer,";")))
                {
                    appendC( &CV, name, dataC);
                }
            }
            else if (!(strcmp(buffer,";")))
            {
                appendC( &CV, name, dataC);
            }

            break;

        case 4:

            fgets(buffer, 1000, fp);
            
            p++;
            k= p-1;
           
            dataF= val(buffer, IV, FV, CV);
            if (dataF)
            {
                fgets(buffer, 1000, fp);
                c[p]= 1;
            }
            else
            {
                fgets(buffer, 1000, fp);
                while (k!=p)
                {
                    fgets(buffer, 1000, fp);

                    b1= 0;
                    b2= 0;
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='{')
                        {
                            b1= 1;
                            break;
                        }
                    }
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='}')
                        {
                            b2= 1;
                            break;
                        }
                    }

                    if (b1)
                        p++;
                    else if (b2)
                        p--;
                }

                fscanf( fp, "%s", buffer);
                if(strcmp(buffer, "elif") && strcmp(buffer, "else"))
                {
                    c[++p]=0;
                    --p;
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
                else
                {
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
            }

            break;

        case 5:

            fgets(buffer, 1000, fp);
           
            p++;
            k= p-1;
            
            dataF= val(buffer, IV, FV, CV);
            if (dataF && c[p]!=1)
            {
                fgets(buffer, 1000, fp);
                c[p]= 1;
            }
            else
            {
                fgets(buffer, 1000, fp);
                while (k!=p)
                {
                
                    fgets(buffer, 1000, fp);

                    b1= 0;
                    b2= 0;
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='{')
                        {
                            b1= 1;
                            break;
                        }
                    }
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='}')
                        {
                            b2= 1;
                            break;
                        }
                    }

                    if (b1)
                        p++;
                    else if (b2)
                        p--;
                }

                fscanf( fp, "%s", buffer);
                if(strcmp(buffer, "elif") && strcmp(buffer, "else"))
                {
                    c[++p]=0;
                    --p;
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
                else
                {
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
            }

            break;

        case 6:
            
            fgets(buffer, 1000, fp);
            
            p++;
            k= p-1;
            
            if (c[p]!= 1)
            {
                fgets(buffer, 1000, fp);
                c[p]= 1;
            }
            else
            {
                fgets(buffer, 1000, fp);
                while (k!=p)
                {
                
                    fgets(buffer, 1000, fp);

                    b1= 0;
                    b2= 0;
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='{')
                        {
                            b1= 1;
                            break;
                        }
                    }
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='}')
                        {
                            b2= 1;
                            break;
                        }
                    }

                    if (b1)
                        p++;
                    else if (b2)
                        p--;
                }

                fscanf( fp, "%s", buffer);
                if(strcmp(buffer, "elif") && strcmp(buffer, "else"))
                {
                    c[++p]=0;
                    --p;
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
                else
                {
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
            }

            break;

        case 7:
        
            fscanf( fp, "%s", buffer);
            if(strcmp(buffer, "elif") && strcmp(buffer, "else") && c[p]!= 2)
            {
                c[p]=0;
                k= --p;
                fseek( fp, -strlen(buffer), SEEK_CUR);
            }
            else
            {
                if (c[p]==2)
                {
                    fseek( fp, w[p], SEEK_SET);
                    w[p]= 0;
                    --p;
                    k= p;
                }
                else
                {
                    k= --p;
                    fseek( fp, -strlen(buffer), SEEK_CUR);
                }
            }

            break;

        case 8:

            p++;
            k= p-1;
            w[p]=ftell( fp)-5;

            fgets(buffer, 1000, fp);
            dataF= val(buffer, IV, FV, CV);
            fgets(buffer, 1000, fp);
            
            if (dataF)
            {
                c[p]= 2;
            }
            else
            {
                while (k!=p)
                {
                    fgets(buffer, 1000, fp);

                    b1= 0;
                    b2= 0;

                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='{')
                        {
                            b1= 1;
                            break;
                        }
                    }
                    
                    for(int i= 0; i<strlen(buffer); i++)
                    {
                        if(buffer[i]=='}')
                        {
                            b2= 1;
                            break;
                        }
                    }

                    if (b1)
                        p++;
                    else if (b2)
                        p--;
                }

                c[++p]=0;
                --p;
            }
            
            break;

        case 9:
        
            fgets( buffer, 1000000, fp);

            j=1;

            while (1)
            {           
                if(buffer[j]=='\"')
                {
                    j++;
                    for (i = 0; !(buffer[j]=='\"' && (buffer[j+1]!='%' && (buffer[j+2]==';' ||  buffer[j+2]=='+'))); i++)
                    {
                        if (buffer[j]=='%' && (buffer[j+1]=='+' || buffer[j+1]==';'))
                        {
                            j++;
                            i--;
                            continue;
                        }
                        else if(buffer[j]=='%' && buffer[j+1]=='n')
                        {
                            tempS[i]='\n';
                            j+=2;
                            continue;
                        }
                        
                        
                        tempS[i]= buffer[j];
                        j++;
                    }
                    
                    tempS[i]='\0';
                    j+=2;
                    printf("%s", tempS);
                    
                    for(int t = 0; t < i; t++)
                        tempS[t]= '\0';
                }
                else if (buffer[j]=='+')
                {
                    j+=2;
                }
                else if(buffer[j]!=';')
                {
                    for( i=0; !(buffer[j+1]==';' ||  buffer[j+1]=='+'); i++)
                    {
                        tempS[i]= buffer[j];
                        j++;
                    }
                    
                    tempS[i]= '\0';
                    j++;
                    
                    type= typeFetcher( tempS, IV, FV, CV);

                    if (type==1)
                    {
                        dataI= valFetcherI( tempS, IV);
                        printf("%d", dataI);
                    }
                    else if (type==2)
                    {
                        dataF= valFetcherF( tempS, FV);
                        printf("%f", dataF);
                    }
                    else if(type==3)
                    {
                        dataC= valFetcherC( tempS, CV);
                        printf("%c", dataC);
                    }
                    else
                    {
                        printf("\nVariable not found!!!\n");
                    }

                    for(int t = 0; t < i; t++)
                        tempS[t]= '\0';
                }
                if (buffer[j]==';')
                {
                    break;
                }
            }

            break;
        
        case 10:

        IN:

            fscanf( fp, "%s", buffer);

            type= typeFetcher(buffer, IV, FV, CV);
            
            if (type == 0)
            {
                goto ERROR;
            }

            if (type == 1)
            {
                scanf("%d",&dataI);
                appendI( &IV, buffer, dataI);
            }
            else if (type == 2)
            {
                scanf("%f",&dataF);
                appendF( &FV, buffer, dataF);
            }
            else if (type == 3)
            {
                scanf("%c",&dataC);
                appendC( &CV, buffer, dataC);
            }

            fscanf( fp, "%s", buffer);

            if(!(strcmp( buffer, "+")))
                goto IN;
            break;
        
        case 11:
            
            type= typeFetcher(buffer, IV, FV, CV);
            
            if (type == 0)
            {
                goto ERROR;
            }            
            strcpy(name, buffer);
            fgets(buffer, 1000, fp);

            if (type == 1)
            {
                dataI= (int)val(buffer, IV, FV, CV);
                appendI( &IV, name, dataI);
            }
            else if (type == 2)
            {
                dataF= val(buffer, IV, FV, CV);
                appendF( &FV, name, dataF);
            }
            
            break;

        default:
            
            ERROR:
                printf("Neither variable nor keyword nor function!!!\n");
                fgets( buffer, 1000000, fp);
                break;
        }
    }

    return 0;
}