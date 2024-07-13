char __datatypes[3][6]={
    "int",
    "float",
    "char"
};

char __ifel[4][5]={
    "if",
    "elif",
    "else",
    "}"
};

char __loop[6]={"while"};

char __basicFunctions[2][4]={
    "out",
    "in"
};

int whichone(char *c)
{
    int flag= 1;
    
    if (!(strcmp(c,__datatypes[0])))
    {
        return 1;
    }
    else if (!(strcmp(c,__datatypes[1])))
    {
        return 2;
    }
    else if (!(strcmp(c,__datatypes[2])))
    {
        return 3;
    }
    else if (!(strcmp(c,__ifel[0])))
    {
        return 4;
    }
    else if (!(strcmp(c,__ifel[1])))
    {
        return 5;
    }
    else if (!(strcmp(c,__ifel[2])))
    {
        return 6;
    }
    else if (!(strcmp(c,__ifel[3])))
    {
        return 7;
    }
    else if (!(strcmp(c,__loop)))
    {
        return 8;
    }
    else if (!(strcmp(c,__basicFunctions[0])))
    {
        return 9;
    }
    else if (!(strcmp(c,__basicFunctions[1])))
    {
        return 10;
    }
    else
    {
        return 11;
    }
}