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
    
    loadGeneral();
    ieee1599_document.general_layer=general_layer;
    loadLogic();
    ieee1599_document.logic_layer=logic_layer;
    loadStructural();
    ieee1599_document.structural_layer=structural_layer;
    loadNotational();
    ieee1599_document.notational_layer=notational_layer;
    loadPerformance();
    ieee1599_document.performance_layer=performance_layer;
    loadAudio();
    ieee1599_document.audio_layer=audio_layer;
    
}

void printDocument(){
    
    printf("[version=%s creator=%s]",ieee1599_document.version,ieee1599_document.creator);
    printGeneral();
    printLogic();
    printStructural();
    printNotational();
    printPerformance();
    printAudio();
}