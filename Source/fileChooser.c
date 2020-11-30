/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "fileChooser.h"
#include "managerDocument.h"

char* rootFolderPath;

char* chooseFile(){
    char* file_name;
    int choice=-1;
        
    file_name=(char*)"";

    while(!strcmp(file_name,(const char*)"") && choice!=0){
        do {
            printf("Choose File [0 to exit]:\n");
            showFiles();
        } while (!scanf("%i", &choice));
        if(choice>0){
            file_name=readFileName(choice);
            file_name=concat(getFileRootFolder(),file_name);
        }
    }  
    
    return file_name;
}

int showFiles(){
    DIR *dir;//Directory stream
    struct dirent *ent;
    struct stat filestat;
    int i=0;
    
    if ((dir=opendir(getFileRootFolder()))!=NULL){
        /* print every contained file */
        while((ent=readdir(dir))!=NULL){
            stat(concat(getFileRootFolder(),ent->d_name),&filestat);
            if(!S_ISDIR(filestat.st_mode)){  
                if(!strcmp(getExtension(ent->d_name),(const char*)"xml")){
                    i++;
                    printf(" %i) %s\n",i,ent->d_name);
                }            
            }
        }
        closedir(dir);
     }
    else{
        fprintf(stderr,"Can't open direcotry %s\n", getFileRootFolder());
        return 0;
    }
    
    return 1;
}

char* readFileName(int choice){
    DIR *dir;//Directory stream
    struct dirent *ent;
    struct stat filestat;
    int i=0;
    char* file_name;
    
    if ((dir=opendir(getFileRootFolder()))!=NULL){
        /* print every contained file */
        while((ent=readdir(dir))!=NULL){
            stat(concat(getFileRootFolder(),ent->d_name),&filestat);
            if(!S_ISDIR(filestat.st_mode)){  
                if(!strcmp(getExtension(ent->d_name),(const char*)"xml")){
                    i++;
                    if(i==choice){
                        file_name=ent->d_name;
                        return file_name;
                    }
                }            
            }
        }
        closedir(dir);
    }
    else{
        fprintf(stderr,"Can't open direcotry %s\n", getFileRootFolder());
        return 0;
    }

    return (char*)"";
}

const char* getExtension(const char *file_name) {
    const char *dot = strrchr(file_name, '.');
    if(!dot || dot == file_name) return "";
    return dot + 1;
}

