/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Ale
 *
 * Created on 28 luglio 2020, 23.09
 */

#include "common.h"
#include "managerDocument.h"
#include "fileChooser.h"

int main(int argc, char **argv) {
    
    int confirm=1;
    
    //encoding check
    encoding="ISO-8859-1";
    
    while(confirm==1){
        file_name=chooseFile();
        if(strcmp(file_name,(const char*)"")){
            doc=getDoc((xmlChar*)file_name);

            //validate DTD

            if(doc!=NULL){
                fprintf(stdout,"Loaded %s\n",file_name);

                loadDocument();
                printDocument();  
            }
            xmlFreeDoc(doc);
            xmlCleanupParser();

            printf("\nContinue? [yes=1,No=0]\n");
            scanf("%i",&confirm);  
        }
        else confirm=0;
    }
            
    return (EXIT_SUCCESS);
}