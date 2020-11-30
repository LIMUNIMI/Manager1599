/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerNotational.h"

static struct notational notational_layer;

struct notational loadNotational(){
    loadGraphicInstanceGroup();
    loadNotationInstanceGroup();
    
    return notational_layer;
}

void loadGraphicInstanceGroup(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct graphic_instance_group* graphic_instance_group_temp=NULL;
    struct graphic_instance_group* graphic_instance_group_head=NULL;
    struct graphic_instance_group* graphic_instance_group_p=NULL;
    notational_layer.n_graphic_insance_groups=0;
    
    xpath=(xmlChar *)"/ieee1599/notational/graphic_instance_group";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning graphic_instance_groups 
            graphic_instance_group_temp=(struct graphic_instance_group*)malloc(sizeof(struct graphic_instance_group));
            graphic_instance_group_temp=calloc(1,sizeof(struct graphic_instance_group));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;         
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    graphic_instance_group_temp->description=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            //load graphic_instance list
            struct graphic_instance* graphic_instance_temp=NULL;
            struct graphic_instance* graphic_instance_head=NULL;
            struct graphic_instance* graphic_instance_p=NULL;
            graphic_instance_group_temp->n_graphic_instances=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"graphic_instance")){
                    graphic_instance_temp=(struct graphic_instance*)malloc(sizeof(struct graphic_instance));
                    graphic_instance_temp=calloc(1,sizeof(struct graphic_instance));

                    graphic_instance_temp=loadGraphicInstance(temp_cur);
                                     
                    graphic_instance_temp->next_graphic_instance=NULL;
                    if(graphic_instance_head==NULL)
                        graphic_instance_head=graphic_instance_temp;
                    else{
                        graphic_instance_p=graphic_instance_head;
                        while(graphic_instance_p->next_graphic_instance!=NULL)
                            graphic_instance_p=graphic_instance_p->next_graphic_instance;
                        graphic_instance_p->next_graphic_instance=graphic_instance_temp;
                    }
                    graphic_instance_group_temp->n_graphic_instances++;
                }
                temp_cur=temp_cur->next;
            }
            graphic_instance_group_temp->graphic_instances=graphic_instance_head;
            
            graphic_instance_group_temp->next_graphic_instance_group=NULL;
            if(graphic_instance_group_head==NULL)
                graphic_instance_group_head=graphic_instance_group_temp;
            else{
                graphic_instance_group_p=graphic_instance_group_head;
                while(graphic_instance_group_p->next_graphic_instance_group!=NULL)
                    graphic_instance_group_p=graphic_instance_group_p->next_graphic_instance_group;
                graphic_instance_group_p->next_graphic_instance_group=graphic_instance_group_temp;
            }
            notational_layer.n_graphic_insance_groups++;
        }
    }
    notational_layer.graphic_instance_group = graphic_instance_group_head;
}

struct graphic_instance* loadGraphicInstance(xmlNodePtr cur){
    struct graphic_instance* value=(struct graphic_instance*)malloc(sizeof(struct graphic_instance));
    value=calloc(1, sizeof(struct graphic_instance));
    xmlAttr* attributes;

    struct graphic_event* graphic_event_temp=NULL;
    struct graphic_event* graphic_event_head=NULL;
    struct graphic_event* graphic_event_p=NULL;
    value->n_graphic_events=0;

    value->next_graphic_instance=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"position_in_group")){
            value->position_in_group=xmlCharToInt(xmlGetProp(cur,attributes->name));   
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);        
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_format")){
            value->file_format=xmlGetProp(cur,attributes->name);        
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"encoding_format")){
            value->encoding_format=xmlGetProp(cur,attributes->name);        
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"measurement_unit")){
            value->measurement_unit=xmlGetProp(cur,attributes->name);        
        }       
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"graphic_event")){
            graphic_event_temp=(struct graphic_event*)malloc(sizeof(struct graphic_event));
            graphic_event_temp=calloc(1, sizeof(struct graphic_event));

            if (graphic_event_temp) {
                attributes = cur->properties;
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                        graphic_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"upper_left_x")) { 
                        graphic_event_temp->upper_left_x = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"upper_left_y")) {
                        graphic_event_temp->upper_left_y = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"lower_right_x")) {  
                        graphic_event_temp->lower_right_x = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"lower_right_y")) {  
                        graphic_event_temp->lower_right_y = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"highlight_color")) {
                        graphic_event_temp->highlight_color = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        graphic_event_temp->description = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }

                graphic_event_temp->next_graphic_event = NULL;
                if (graphic_event_head == NULL)
                    graphic_event_head = graphic_event_temp;
                else {
                    graphic_event_p = graphic_event_head;
                    while (graphic_event_p->next_graphic_event != NULL)
                        graphic_event_p = graphic_event_p->next_graphic_event;
                    graphic_event_p->next_graphic_event = graphic_event_temp;
                }
                value->n_graphic_events++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'graphic_event' element\n"); }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"rights")){
            value->rights=loadRights(cur);
        } 
        cur=cur->next;
    }
    value->graphic_event=graphic_event_head;

    return value;
}

void loadNotationInstanceGroup(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct notation_instance_group* notation_instance_group_temp=NULL;
    struct notation_instance_group* notation_instance_group_head=NULL;
    struct notation_instance_group* notation_instance_group_p=NULL;
    notational_layer.n_notation_instance_groups=0;
    
    xpath=(xmlChar *)"/ieee1599/notational/notation_instance_group";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning notation_instance_groups
            notation_instance_group_temp=(struct notation_instance_group*)malloc(sizeof(struct notation_instance_group));
            notation_instance_group_temp=calloc(1,sizeof(struct notation_instance_group));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    notation_instance_group_temp->description=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            
            //load notation_instance list
            struct notation_instance* notation_instance_temp=NULL;
            struct notation_instance* notation_instance_head=NULL;
            struct notation_instance* notation_instance_p=NULL;
            notation_instance_group_temp->n_notation_instances=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notation_instance")){
                    notation_instance_temp=(struct notation_instance*)malloc(sizeof(struct notation_instance));
                    notation_instance_temp=calloc(1,sizeof(struct notation_instance));
                    
                    notation_instance_temp=loadNotationInstance(temp_cur);
                                        
                    notation_instance_temp->next_notation_instance=NULL;
                    if(notation_instance_head==NULL)
                        notation_instance_head=notation_instance_temp;
                    else{
                        notation_instance_p=notation_instance_head;
                        while(notation_instance_p->next_notation_instance!=NULL)
                            notation_instance_p=notation_instance_p->next_notation_instance;
                        notation_instance_p->next_notation_instance=notation_instance_temp;
                    }
                    notation_instance_group_temp->n_notation_instances++;
                }
                temp_cur=temp_cur->next;
            }
            notation_instance_group_temp->notation_instances=notation_instance_head;
            
            notation_instance_group_temp->next_notation_instance_group=NULL;
            if(notation_instance_group_head==NULL)
                notation_instance_group_head=notation_instance_group_temp;
            else{
                notation_instance_group_p=notation_instance_group_head;
                while(notation_instance_group_p->next_notation_instance_group!=NULL)
                    notation_instance_group_p=notation_instance_group_p->next_notation_instance_group;
                notation_instance_group_p->next_notation_instance_group=notation_instance_group_temp;
            }
            notational_layer.n_notation_instance_groups++;
        }
    }
    notational_layer.notation_instance_group = notation_instance_group_head;
}

struct notation_instance* loadNotationInstance(xmlNodePtr cur){
    struct notation_instance* value=(struct notation_instance*)malloc(sizeof(struct notation_instance));
    value=calloc(1, sizeof(struct notation_instance));;
    xmlAttr* attributes;
     
    if (value) {
        struct notation_event* notation_event_temp = NULL;
        struct notation_event* notation_event_head = NULL;
        struct notation_event* notation_event_p = NULL;
        value->n_notation_events = 0;

        value->next_notation_instance = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"position_in_group")) {
                value->position_in_group = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"format")) {
                value->format = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"measurement_unit")) {
                value->measurement_unit = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"notation_event")) {
                notation_event_temp = (struct notation_event*)malloc(sizeof(struct notation_event));
                notation_event_temp = calloc(1, sizeof(struct notation_event));

                if (notation_event_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            notation_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_position")) {
                            notation_event_temp->start_position = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_position")) {
                            notation_event_temp->end_position = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                            notation_event_temp->description = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    notation_event_temp->next_notation_event = NULL;
                    if (notation_event_head == NULL)
                        notation_event_head = notation_event_temp;
                    else {
                        notation_event_p = notation_event_head;
                        while (notation_event_p->next_notation_event != NULL)
                            notation_event_p = notation_event_p->next_notation_event;
                        notation_event_p->next_notation_event = notation_event_temp;
                    }
                    value->n_notation_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'notation_event' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->notation_events = notation_event_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'notation_instance' element\n"); }
    
    return value;
}

void printNotational(){
	
}