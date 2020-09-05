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
#include "managerGeneral.h"
#include "managerLogic.h"
#include "managerStructural.h"
#include "managerNotational.h"
#include "managerPerformance.h"
#include "managerAudio.h"

/*
 * 
 * 
 */

int main(int argc, char **argv) {

    encoding="ISO-8859-1";
    docpath="File/gottes_macht.xml";
    
    doc=getDoc(docpath);
    //creare struttura ieee1599
    //encoding check
    //validate DTD
    
    if(doc!=NULL){
        fprintf(stdout,"Loaded %s\n",docpath);
        
        loadGeneral();
        loadLogic();
        //loadStructura();
        //loadNotational();
        //loadPerformance();
        //loadAudio();
    }
    
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return (EXIT_SUCCESS);
}