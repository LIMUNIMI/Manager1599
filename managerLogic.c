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
    
    xmlNodePtr temp_cur;
    
    struct agogic *agogic_head=NULL;
    struct agogic *agogic_temp=NULL;
    struct agogic *agogic_p=NULL;
    
    struct text_field *text_field_head=NULL;
    struct text_field *text_field_temp=NULL;
    struct text_field *text_field_p=NULL;
    
    struct metronomic_indication *metronomic_indication_head=NULL;
    struct metronomic_indication *metronomic_indication_temp=NULL;
    struct metronomic_indication *metronomic_indication_p=NULL;
    
    struct lyrics* lyrics_head=NULL;
    struct lyrics* lyrics_temp=NULL;
    struct lyrics* lyrics_p=NULL;
    
    struct syllabe* syllabe_head=NULL;
    struct syllabe* syllabe_temp=NULL;
    struct syllabe* syllabe_p=NULL;
    
    struct horizontal_symbol_list* horizontal_symbol_list_head=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_temp=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_p=NULL;
    horizontal_symbol horizontal_symbol_value;
    
    struct ornament_list* ornament_list_head=NULL;
    struct ornament_list* ornament_list_temp=NULL;
    struct ornament_list* ornament_list_p=NULL;
    ornament ornament_value;
    
    logic_layer.los.n_agogics=0;
    logic_layer.los.n_text_fields=0;
    logic_layer.los.n_lyrics=0;
    logic_layer.los.n_horizontal_symbols=0;
    logic_layer.los.n_ornaments=0;
    
    xpath=(xmlChar *)"/ieee1599/logic/los";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur!=NULL){//scan los children
            if(!xmlStrcmp(cur->name,(const xmlChar*)"agogics")){
                agogic_temp=(struct agogic*)malloc(sizeof(struct agogic));
                agogic_temp=calloc(1,sizeof(struct agogic));
                agogic_temp->agogic_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"bracketed")){
                        agogic_temp->bracketed=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                        //agogic_temp->spine_ref=xmlGetProp(cur,attributes->name);
                    }                
                    attributes=attributes->next;                     
                }  
                agogic_temp->next_agogic=NULL;
                if(agogic_head==NULL){
                    agogic_head=agogic_temp;
                }
                else{
                    agogic_p=agogic_head;
                    while(agogic_p->next_agogic!=NULL)
                        agogic_p=agogic_p->next_agogic;
                    agogic_p->next_agogic=agogic_temp;
                }
                logic_layer.los.n_agogics++;                                           
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"text_field")){
                text_field_temp=(struct text_field*)malloc(sizeof(struct text_field));
                text_field_temp=calloc(1,sizeof(struct text_field));
                text_field_temp->text_field_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_to")){
                        //text_field_temp->extensione_lines_shape=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_shape")){
                        text_field_temp->extension_line_shape=xmlGetProp(cur,attributes->name);
                    }                
                    attributes=attributes->next;                     
                }  
                text_field_temp->next_text_field=NULL;
                if(text_field_head==NULL){
                    text_field_head=text_field_temp;
                }
                else{
                    text_field_p=text_field_head;
                    while(text_field_p->next_text_field!=NULL)
                        text_field_p=text_field_p->next_text_field;
                    text_field_p->next_text_field=text_field_temp;
                }
                logic_layer.los.n_text_fields++;  
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"metronomic_indication")){
                metronomic_indication_temp=(struct metronomic_indication*)malloc(sizeof(struct metronomic_indication));
                metronomic_indication_temp=calloc(1,sizeof(struct metronomic_indication));
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"num")){
                        metronomic_indication_temp->num=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"den")){
                        metronomic_indication_temp->den=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"value")){
                        metronomic_indication_temp->value=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }  
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"dots")){
                        metronomic_indication_temp->dots=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }  
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                        //metronomic_indication_temp->spine_ref=xmlGetProp(cur,attributes->name);
                    }  
                    attributes=attributes->next;                     
                }  
                metronomic_indication_temp->next_metronomic_indication=NULL;
                if(metronomic_indication_head==NULL){
                    metronomic_indication_head=metronomic_indication_temp;
                }
                else{
                    metronomic_indication_p=metronomic_indication_head;
                    while(metronomic_indication_p->next_metronomic_indication!=NULL)
                        metronomic_indication_p=metronomic_indication_p->next_metronomic_indication;
                    metronomic_indication_p->next_metronomic_indication=metronomic_indication_temp;
                }
                logic_layer.los.n_metronomic_indications++;
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"staff_list")){
            
            }// end if staff_list
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"part")){
            
            }// end if part
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"horizontal_symbols")){
                horizontal_symbol_list_temp=(struct horizontal_symbol_list*)malloc(sizeof(struct horizontal_symbol_list));
                horizontal_symbol_list_temp=calloc(1,sizeof(struct horizontal_symbol_list));
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    horizontal_symbol_value=loadHorizontalSymbolValue(temp_cur);
                    if(xmlStrcmp(cur->name,(const xmlChar*)"text")&&xmlStrcmp(cur->name,(const xmlChar*)"comment")){
                        horizontal_symbol_list_temp->horizontal_symbol_value=horizontal_symbol_value;
                        horizontal_symbol_list_temp->next_horizontal_symbol=NULL;
                        if(horizontal_symbol_list_head==NULL){
                            horizontal_symbol_list_head=horizontal_symbol_list_temp;
                        }
                        else{
                            horizontal_symbol_list_p=horizontal_symbol_list_head;
                            while(horizontal_symbol_list_p->next_horizontal_symbol!=NULL)
                                horizontal_symbol_list_p=horizontal_symbol_list_p->next_horizontal_symbol;
                            horizontal_symbol_list_p->next_horizontal_symbol=horizontal_symbol_list_temp;
                        }
                        logic_layer.los.n_horizontal_symbols++;
                    }
                    temp_cur=temp_cur->next;
                }
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"ornaments")){
                ornament_list_temp=(struct ornament_list*)malloc(sizeof(struct ornament_list));
                ornament_list_temp=calloc(1,sizeof(struct ornament_list));
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    ornament_value=loadOrnamentValue(temp_cur);
                    if(xmlStrcmp(cur->name,(const xmlChar*)"text")&&xmlStrcmp(cur->name,(const xmlChar*)"comment")){
                        ornament_list_temp->ornament_value=ornament_value;
                        ornament_list_temp->next_ornament=NULL;
                        if(ornament_list_head==NULL){
                            ornament_list_head=ornament_list_temp;
                        }
                        else{
                            ornament_list_p=ornament_list_head;
                            while(ornament_list_p->next_ornament!=NULL)
                                ornament_list_p=ornament_list_p->next_ornament;
                            ornament_list_p->next_ornament=ornament_list_temp;
                        }
                        logic_layer.los.n_ornaments++;
                    }
                    temp_cur=temp_cur->next;
                }
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"lyrics")){
                lyrics_temp=(struct lyrics*)malloc(sizeof(struct lyrics));
                lyrics_temp=calloc(1,sizeof(struct lyrics));
                lyrics_temp->n_syllabes=0;
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
                        //lyrics_temp->part_ref=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"voide_ref")){
                        //lyrics_temp->voice_ref=xmlGetProp(cur,attributes->name);
                    } 
                    attributes=attributes->next;                     
                }
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){//syllabe in lyrics
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"syllabe")){
                        syllabe_temp=(struct syllabe*)malloc(sizeof(struct syllabe));
                        syllabe_temp=calloc(1,sizeof(struct syllabe));
                        attributes=cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                                //lyrics_temp->part_ref=xmlGetProp(cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                                //lyrics_temp->voice_ref=xmlGetProp(cur,attributes->name);
                            } 
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hyphen")){
                                syllabe_temp->hyphen=xmlGetProp(cur,attributes->name);
                            } 
                            attributes=attributes->next;                     
                        }
                        syllabe_temp->next_syllabe=NULL;
                        if(syllabe_head==NULL){
                            syllabe_head=syllabe_temp;
                        }
                        else{
                            syllabe_p=syllabe_head;
                            while(syllabe_p->next_syllabe!=NULL)
                                syllabe_p=syllabe_p->next_syllabe;
                            syllabe_p->next_syllabe=syllabe_temp;
                        } 
                        lyrics_temp->n_syllabes++;
                    }
                    temp_cur=temp_cur->next;
                }//end while syllabe in lyrics
                lyrics_temp->next_lyrics=NULL;
                if(lyrics_head==NULL){
                    lyrics_head=lyrics_temp;
                }
                else{
                    lyrics_p=lyrics_head;
                    while(lyrics_p->next_lyrics!=NULL)
                        lyrics_p=lyrics_p->next_lyrics;
                    lyrics_p->next_lyrics=lyrics_temp;
                }
                logic_layer.los.n_lyrics++;
            }
            cur=cur->next;//next los children
        }//end while (los children)
    }//end if nodeset not empty
}

void printLos(){

}