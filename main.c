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

int main(int argc, char **argv) {

    encoding="ISO-8859-1";
    file_name="File/gottes_macht.xml";
    
    doc=getDoc(file_name);
    //creare struttura ieee1599
    //encoding check
    //validate DTD
    
    if(doc!=NULL){
        fprintf(stdout,"Loaded %s\n",file_name);
        
        loadDocument(file_name);
    }
    
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return (EXIT_SUCCESS);
}