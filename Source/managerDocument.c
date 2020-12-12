/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerDocument.h"

struct ieee1599 ieee1599_root;

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
                 ieee1599_root.version=xmlGetProp(cur,attributes->name);
             }
             else if(!xmlStrcmp(attributes->name,(const xmlChar*)"creator")){
                 ieee1599_root.creator=xmlGetProp(cur,attributes->name);
             }
             attributes=attributes->next;
         }
    }
    else{
        fprintf(stderr,"Can't find root element\n");
    }
    
    ieee1599_root.general_layer=loadGeneral();
    ieee1599_root.logic_layer=loadLogic();
    ieee1599_root.structural_layer=loadStructural();
    ieee1599_root.notational_layer=loadNotational();
    ieee1599_root.performance_layer=loadPerformance();
    ieee1599_root.audio_layer=loadAudio();

}

void printDocument() {
   
    printf("\n###Document Info###\n");
    if (ieee1599_root.file_name != NULL) {
        printf("File name: %s\n", ieee1599_root.file_name);
    }
    if(ieee1599_root.version!=NULL || ieee1599_root.creator!=NULL){
        printf("[");
        if(ieee1599_root.version!=NULL)
            printf("version=%s", ieee1599_root.version);
        if(ieee1599_root.version!=NULL && ieee1599_root.creator!=NULL)
            printf(" ");
        if(ieee1599_root.creator!=NULL)
            printf("creator=%s", ieee1599_root.creator);
        printf("]\n");
    }
    printGeneral();
    printLogic();
    printStructural();
    printNotational();
    printPerformance();
    printAudio();
}

struct ieee1599 getIEEE1599Root() {
    return ieee1599_root;
}

void setFileName(xmlChar* file_name) {
    ieee1599_root.file_name = file_name;
}

xmlChar* getFileName() {
    return ieee1599_root.file_name;
}


void freeDocument() {
    freeGeneralLayer(ieee1599_root.general_layer);
    freeLogicLayer(ieee1599_root.logic_layer);
    freeStructuralLayer(ieee1599_root.structural_layer);
    freeNotationalLayer(ieee1599_root.notational_layer);
    freePerformanceLayer(ieee1599_root.performance_layer);
    freeAudioLayer(ieee1599_root.audio_layer);
}