#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>


#define BUFFSIZE 512
#define fValue 0xff
#define sValue 0xd8
#define tValue 0xff

typedef uint8_t  BYTE;

typedef struct 
{ 
    BYTE    first; 
    BYTE    second; 
    BYTE    third; 
    BYTE    fourth; 
} __attribute__((__packed__)) 
JPGHEADER; 

bool hasImage = false;


int main(void)
{
    FILE* rawFile = fopen("card.raw", "r");
    if(rawFile == NULL){
        printf("Could not open %s.\n", "rawFile");
        return 1;
    }
    
    FILE* outptr;
    char fileName[3];
    
    char buffer[BUFFSIZE];
    JPGHEADER header;
    
    int count = 0;
        
    while(fread(&header, sizeof(JPGHEADER), 1, rawFile)>0){
        if(header.first == fValue && header.second == sValue && header.third == tValue)
        {
            sprintf(fileName, "%03d.jpg", count++);
            outptr = fopen(fileName, "w");
            hasImage = true;
        }
        
        fseek(rawFile,-(long int)(sizeof(JPGHEADER)) , SEEK_CUR);

        if(hasImage){
            fread(&buffer, BUFFSIZE, 1, rawFile);
            fwrite(&buffer, BUFFSIZE, 1, outptr);
        }else {
             fseek(rawFile,BUFFSIZE , SEEK_CUR);
        }
    }
    return 0;
}
