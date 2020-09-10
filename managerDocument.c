/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerDocument.h"

void loadDocument(){
    
    loadGeneral();
    loadLogic();
    //loadStructural();
    //loadNotational();
    //loadPerformance();
    //loadAudio();
}

void printDocument(){
    
    printDescription();
    printRelatedFiles();
    printAnalogMedia();
    printNotes();
    
}