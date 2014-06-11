/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
 #include <stdio.h>
 #define LENGTH 7 // length of pattern "###.jpg"
 #define TRUE 1

 int main(void)
 {
    FILE* card = fopen("card.raw", "r");
    if(card == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    //getting size of the file "card"
    fseek(card, 0, SEEK_END); // seek to end of file
    int size = ftell(card); // get current file pointer
    fseek(card, 0, SEEK_SET); // seek back to beginning of file
    
    int title_track = 0; // tracking the title of images
    char title[LENGTH + 1];
    
    char buffer[512]; // char = 1 byte => buffer = 512 bytes
    FILE* image;
    
    int pos = ftell(card); // position of the file indicator
    
    while(pos != size)
    {
        fread(&buffer, sizeof(buffer), 1, card);
                
        sprintf(title, "%03d.jpg", title_track);
        // searching for the pattern 0xff 0xd8 0xff 0xe0 or 0xff 0xd8 0xff 0xe1
        if(buffer[0] == 0xffffffff && buffer[1] == 0xffffffd8 && buffer[2] == 0xffffffff && (buffer[3] == 0xffffffe0 || buffer[3] == 0xffffffe1))
        {
            if(title_track == 0)
            {
                image = fopen(title,"w");
                if(image == NULL){
                    printf("Could not create %s.\n", title);
                    return 2;
                } 
                fwrite(&buffer, sizeof(buffer),1,image);
                title_track++;
            }
            else
            {
                fclose(image);
                sprintf(title, "%03d.jpg", title_track);
                title_track++;
                image = fopen(title,"w");
                fwrite(&buffer, sizeof(buffer),1,image);
            }
        }
        else
        {
            if(title_track != 0)
                fwrite(&buffer, sizeof(buffer),1,image);
        }        
        pos = ftell(card);
    }
    fclose(card);
    
    return 0;
 }
