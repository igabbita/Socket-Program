typedef struct
{
    int i;
    float f;
    char c;
} data_struct;

float htonf(float value)
{
    float newVal = value;
    char* pCurVal = (char *)&value;
    char* pNewVal = (char *)&newVal;
    
    pNewVal[0] = pCurVal[3];
    pNewVal[1] = pCurVal[2];
    pNewVal[2] = pCurVal[1];
    pNewVal[3] = pCurVal[0];
    
    return newVal;
}
void error(char *msg)
{
    perror(msg);
    exit(0);
}
