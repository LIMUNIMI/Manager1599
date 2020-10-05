/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerDocument.h"

void loadDocument(){
    
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    xpath=(xmlChar *)"/ieee1599";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
         nodeset=result->nodesetval;
         cur=nodeset->nodeTab[0];
         attributes=cur->properties;
         while(attributes!=NULL){
             if(!xmlStrcmp(attributes->name,(const xmlChar*)"version")){
                 ieee1599_document.version=xmlGetProp(cur,attributes->name);
             }
             else if(!xmlStrcmp(attributes->name,(const xmlChar*)"creator")){
                 ieee1599_document.creator=xmlGetProp(cur,attributes->name);
             }
             attributes=attributes->next;
         }
    }
    else{
        fprintf(stderr,"Can't find root element");
    }
    
    ieee1599_document.general_layer=loadGeneral();
    ieee1599_document.logic_layer=loadLogic();
    ieee1599_document.structural_layer=loadStructural();
    ieee1599_document.notational_layer=loadNotational();
    ieee1599_document.performance_layer=loadPerformance();
    ieee1599_document.audio_layer=loadAudio();
    
}

void printDocument(){
    
    if(ieee1599_document.version!=NULL || ieee1599_document.creator!=NULL){
        printf("[");
        if(ieee1599_document.version!=NULL)
            printf("version=%s",ieee1599_document.version);
        if(ieee1599_document.version!=NULL && ieee1599_document.creator!=NULL)
            printf(" ");
        if(ieee1599_document.creator!=NULL)
            printf("creator=%s",ieee1599_document.creator);
        printf("]\n");
    }
    printGeneral();
    printLogic();
    printStructural();
    printNotational();
    printPerformance();
    printAudio();
}