/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools,Templates
 * and open the template in the editor.
 */

#include "managerLogic.h"

void loadLogic(){ 
    //inizializzare logic_layer
    
    loadSpine();
    loadLos();
    //loadLayout();
    
    printSpine();
    printLos();
    //printLayout();
}

void loadSpine(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct event *head=NULL;
    struct event *temp=NULL;
    struct event *p=NULL;
    
    logic_layer.n_events=0;
    
    xpath=(xmlChar *)"/ieee1599/logic/spine";
    result=getNodeset(doc,xpath);
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        fprintf(stderr,"Missing Spine in Logic layer\n");
    }
    else{
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur->next!=NULL){
            if(!xmlStrcmp(cur->name,(const xmlChar*)"event")){
                temp=(struct event*)malloc(sizeof(struct event));
                temp=calloc(1,sizeof(struct event));
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                        temp->id=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"timing")){
                        temp->timing=xmlGetProp(cur,attributes->name);

                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hpos")){
                        temp->hpos=xmlGetProp(cur,attributes->name);

                    }                   
                    attributes=attributes->next;                     
                }  
                temp->next_event=NULL;
                if(head==NULL){
                    head=temp;
                }
                else{
                    p=head;
                    while(p->next_event!=NULL)
                        p=p->next_event;
                    p->next_event=temp;
                }
                logic_layer.n_events++;
            }
            cur=cur->next;
        }
        logic_layer.spine=head;
    }   
}

void printSpine(){
    struct event* p=NULL;
    
    if(logic_layer.n_events!=0){
        printf("%i events\n",logic_layer.n_events); 
    }
        
    p=NULL;
    p=logic_layer.spine;
    while(p!=NULL){
       printf("Event: %s %s %s\n",p->id,p->timing,p->hpos);
       p=p->next_event;
    }
}

void loadLos(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct agogic *head=NULL;
    struct agogic *temp=NULL;
    struct agogic *p=NULL;
    
    logic_layer.los.n_agogics=0;
    
    xpath=(xmlChar *)"/ieee1599/logic/los";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur!=NULL){//scan los children
            if(!xmlStrcmp(cur->name,(const xmlChar*)"agogics")){
                temp=(struct agogic*)malloc(sizeof(struct agogic));
                temp=calloc(1,sizeof(struct agogic));
                temp->agogic_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"bracketed")){
                        temp->bracketed=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                        //temp->spine_ref=xmlGetProp(cur,attributes->name);
                    }                
                    attributes=attributes->next;                     
                }  
                temp->next_agogic=NULL;
                if(head==NULL){
                    head=temp;
                }
                else{
                    p=head;
                    while(p->next_agogic!=NULL)
                        p=p->next_agogic;
                    p->next_agogic=temp;
                }
                logic_layer.los.n_agogics++;                                           
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"text_field")){
            
            }
         cur=cur->next;//next los children
        }//end while (los children)
    }//end if nodeset not empty
}

void printLos(){

}