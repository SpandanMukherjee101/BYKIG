#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Keywords.h"
#include "VarLL.h"
#include "ExprEvalStack.h"

struct node *Stack;
struct node2 *PFEval;

float val(char *, struct iV *, struct fV *, struct cV *);
int priority( char);

float val( char *buff, struct iV * IV, struct fV * FV, struct cV * CV)
{
    int c;
    float tot;
    
    char postfix[1000]="", *pf, opr;
    pf= &postfix[0];

    char *f, func[100];
    f= &func[0];

    char *t, temp[100];
    t= &temp[0];

    float x, n1, n2;

    if( *buff != '=')
    {
        buff++;
    }

    while( *buff != ';' && *buff != '\n')
    {
        if(*buff == '(')
        {
            push( &Stack, *buff);
            buff++;
        }
        else if( *buff == '=')
        {
            buff++;
            if( *buff == ' ' || *buff == '\t')
                buff++;
            continue;
        }
        else if( *buff == ' ' || *buff == '\t')
        {
            buff++;
            continue;
        }
        else if( *buff == '$' || *buff == '*' || *buff == '/' || *buff == '%' || *buff == '+' || *buff == '-' || *buff == '<' || *buff == '>' || *buff == '&' || *buff == '|' || *buff == '~' || *buff == '!')
        {
            *f='\0';
            f= &func[0];
            
            if (Stack != NULL)
            {
                opr= pop( &Stack);
                if(priority (opr) >= priority (*buff ))
                {
                    *pf= ' ';
                    pf++;
                    while ( priority (opr) >= priority (*buff ) )
				    {
		    			*pf = opr;
			    		pf++;

                        opr= pop( &Stack);

                        *pf= ' ';
                        pf++;
				    }
                }
                else
                {
                *pf= ' ';
                pf++;
                }
                
				push ( &Stack, opr );
				push ( &Stack, *buff);
            }
			else
            {
                *pf= ' ';
                pf++;
				push( &Stack, *buff );
            }

			buff++ ;
            if( *buff == ' ' || *buff == '\t')
                buff++;
        }
        else if( *buff == ')')
        {
            opr = pop ( &Stack) ;
			while ( ( opr ) != '(' )
			{
                *pf= ' ';
                pf++;
				*pf = opr ;
				pf++ ;
				opr =  pop ( &Stack) ;
			}
			buff++;
        }
        else
        {
            *pf= *buff;
            pf++;

            *f= *buff;
            *f++;

            buff++;
        }
    }

    while ( Stack != NULL)
	{
        *pf= ' ';
        pf++ ;
		opr= pop( &Stack);
		*pf= opr;
        pf++;
	}

    pf= &postfix[0];

    while(*pf != '\0')
    {
        if(*pf == ' ')
        {
            pf++;
            *t= '\0';
            c= typeFetcher( temp, IV, FV, CV);
            if (c == 1)
            {
                x= valFetcherI( temp, IV);
                pushF( x, &PFEval);
            }
            else if (c == 2)
            {
                x= valFetcherF( temp, FV);
                pushF( x, &PFEval);
            }
            else if(c == 3)
            {
                x= valFetcherC( temp, CV);
                pushF( x, &PFEval);
            }
            else if(isdigit(temp[0]))
            {
                x= atof(temp);
                pushF( x, &PFEval);
            }
            
            t= &temp[0];
        }
        if (priority(*pf))
        {
            n1= popF(&PFEval);
            n2= popF(&PFEval);
            switch(*pf)
            {
                case '$':
                    tot= pow(n2,n1);
                    break;
                case '%':
                    tot= remainder(n2,n1);
                    break;
                case '/':
                    tot= n2/n1;
                    break;
                case '*':
                    tot= n2*n1;
                    break;
                case '+':
                    tot= n2+n1;
                    break;
                case '-':
                    tot= n2-n1;
                    break;
                case '<':
                    tot= n2<n1;
                    break;
                case '>':
                    tot= n2>n1;
                    break;
                case '&':
                    tot= n2&&n1;
                    break;
                case '|':
                    tot= n2||n1;
                    break;
                case '~':  
                    tot= n2==n1;
                    break;
                case '!':
                    tot= n2!=n1;
                    break;
            }
            pushF( tot, &PFEval);
        }
        
        *t= *pf;
        t++;
        pf++;
    }

    return tot;
}


int priority(char Op)
{
    if (Op == '$')
    {
        return 7;
    }
    else if (Op == '*' || Op == '/' || Op == '%')
    {
        return 6;
    }
    else if (Op == '+' || Op == '-')
    {
        return 5;
    }
    else if (Op == '>' || Op == '<')
    {
        return 4;
    }
    else if (Op == '~' || Op == '!')
    {
        return 3;
    }
    else if (Op == '&')
    {
        return 2;
    }
    else if (Op == '|')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}