/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerDocument.h"

void loadDocument(){
    
    loadGeneral();
    ieee1599_document.general_layer=general_layer;
    loadLogic();
    ieee1599_document.logic_layer=logic_layer;
    //loadStructural();
    //loadNotational();
    //loadPerformance();
    //loadAudio();
}

void printDocument(){
    
    printGeneral();
    printLogic();
    
}