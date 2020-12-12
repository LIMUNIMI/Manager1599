/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools,Templates
 * and open the template in the editor.
 */

#include "managerLogic.h"

static struct logic logic_layer;

struct logic loadLogic(){ 

    loadSpine();
    loadLos();
    loadLayout();
    
    return logic_layer;
}

void printLogic(){  

    printf("\n###Logic Layer###\n");
    printSpine();
    printLos();
    printLayout();
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
                temp=(struct event*)calloc(1,sizeof(struct event));

                if (temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                            temp->id = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"timing")) {
                            if (!xmlStrcmp(xmlGetProp(cur, attributes->name), (const xmlChar*)"null"))
                                temp->timing = -1;
                            else
                                temp->timing = xmlCharToInt(xmlGetProp(cur, attributes->name));

                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"hpos")) {
                            if (!xmlStrcmp(xmlGetProp(cur, attributes->name), (const xmlChar*)"null"))
                                temp->hpos = -1;
                            else
                                temp->hpos = xmlCharToInt(xmlGetProp(cur, attributes->name));

                        }
                        attributes = attributes->next;
                    }
                    temp->next_event = NULL;
                    if (head == NULL) {
                        head = temp;
                    }
                    else {
                        p = head;
                        while (p->next_event != NULL)
                            p = p->next_event;
                        p->next_event = temp;
                    }
                    logic_layer.n_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'event' element\n"); }
            }
            cur=cur->next;
        }
    } 
    logic_layer.spine = head;
}

void printSpine(){    
    if (logic_layer.n_events != 0) {
        struct event* p = NULL;

        int i = 0;
        printf("\n#Spine#\n");
        printf("%i events\n", logic_layer.n_events);

        p = NULL;
        p = logic_layer.spine;
        while (p != NULL&&i<N_DISPLAY) {
            i++;
            printf("Event: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->timing)
                printf("timing=%i ", p->timing);
            if (p->hpos)
                printf("hpos=%i", p->hpos);
            printf("\n");
            p = p->next_event;
        }
        if (logic_layer.n_events > N_DISPLAY) printf("...");
        printf("\n");
    }
}

void loadLos(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    xmlAttr *attributes;
    
    struct agogics *agogics_head=NULL;
    struct agogics *agogics_temp=NULL;
    struct agogics *agogics_p=NULL;
    
    struct text_field *text_field_head=NULL;
    struct text_field *text_field_temp=NULL;
    struct text_field *text_field_p=NULL;
    
    struct metronomic_indication *metronomic_indication_head=NULL;
    struct metronomic_indication *metronomic_indication_temp=NULL;
    struct metronomic_indication *metronomic_indication_p=NULL;
    
    struct lyrics* lyrics_head=NULL;
    struct lyrics* lyrics_temp=NULL;
    struct lyrics* lyrics_p=NULL;
   
    struct horizontal_symbol_list* horizontal_symbol_list_head=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_temp=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_p=NULL;
    
    struct ornament_list* ornament_list_head=NULL;
    struct ornament_list* ornament_list_temp=NULL;
    struct ornament_list* ornament_list_p=NULL;
    
    struct part* part_temp=NULL;
    struct part* part_head=NULL;
    struct part* part_p=NULL;

    struct brackets* brackets_temp = NULL;
    struct brackets* brackets_head = NULL;
    struct brackets* brackets_p = NULL;

    struct staff* staff_temp = NULL;
    struct staff* staff_head = NULL;
    struct staff* staff_p = NULL;
    
    logic_layer.los.n_agogics=0;
    logic_layer.los.n_text_fields=0;
    logic_layer.los.n_lyrics=0;
    logic_layer.los.n_horizontal_symbols=0;
    logic_layer.los.n_ornaments=0;
    logic_layer.los.n_parts=0;
    logic_layer.los.n_brackets=0;
    logic_layer.los.n_staves=0;
    
    xpath=(xmlChar *)"/ieee1599/logic/los";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur!=NULL){//scan los children
            if(!xmlStrcmp(cur->name,(const xmlChar*)"agogics")){
                agogics_temp=(struct agogics*)calloc(1,sizeof(struct agogics));
                agogics_temp->agogics_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"bracketed")){
                        if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                            agogics_temp->bracketed=1; 
                        else 
                            agogics_temp->bracketed=0;
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                        agogics_temp->event_ref=xmlGetProp(cur,attributes->name);
                    }                
                    attributes=attributes->next;                     
                }  
                agogics_temp->next_agogics=NULL;
                if(agogics_head==NULL){
                    agogics_head=agogics_temp;
                }
                else{
                    agogics_p=agogics_head;
                    while(agogics_p->next_agogics!=NULL)
                        agogics_p=agogics_p->next_agogics;
                    agogics_p->next_agogics=agogics_temp;
                }
                logic_layer.los.n_agogics++;                                           
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"text_field")){
                text_field_temp=(struct text_field*)calloc(1,sizeof(struct text_field));
                text_field_temp->text_field_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_to")){
                        text_field_temp->extension_line_to=xmlGetProp(cur,attributes->name); 
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
                metronomic_indication_temp=(struct metronomic_indication*)calloc(1,sizeof(struct metronomic_indication));
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
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                        metronomic_indication_temp->event_ref=xmlGetProp(cur,attributes->name);
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
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"brackets")){
                        brackets_temp=(struct brackets*)calloc(1,sizeof(struct brackets));                             
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"marker")){
                                brackets_temp->marker=xmlGetProp(temp_cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"group_number")){
                                brackets_temp->group_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                                brackets_temp->shape=xmlGetProp(temp_cur,attributes->name);
                            }
                            attributes=attributes->next;
                        }
                        brackets_temp->next_brackets=NULL;
                        if(brackets_head==NULL){
                            brackets_head=brackets_temp;
                        }
                        else{
                            brackets_p=brackets_head;
                            while(brackets_p->next_brackets!=NULL)
                                brackets_p=brackets_p->next_brackets;
                            brackets_p->next_brackets=brackets_temp;                          
                        }
                        logic_layer.los.n_brackets++;
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"staff")){
                        struct clef* clef_temp = NULL;
                        struct clef* clef_head = NULL;
                        struct clef* clef_p = NULL;

                        struct key_signature* key_signature_temp = NULL;
                        struct key_signature* key_signature_head = NULL;
                        struct key_signature* key_signature_p = NULL;

                        struct custom_key_signature* custom_key_signature_temp = NULL;
                        struct custom_key_signature* custom_key_signature_head = NULL;
                        struct custom_key_signature* custom_key_signature_p = NULL;

                        struct time_signature* time_signature_temp = NULL;
                        struct time_signature* time_signature_head = NULL;
                        struct time_signature* time_signature_p = NULL;

                        struct barline* barline_temp = NULL;
                        struct barline* barline_head = NULL;
                        struct barline* barline_p = NULL;

                        struct tablature_tuning* tablature_tuning_temp = NULL;
                        struct tablature_tuning* tablature_tuning_head = NULL;
                        struct tablature_tuning* tablature_tuning_p = NULL;

                        staff_temp=(struct staff*)calloc(1,sizeof(struct staff)); 
                        staff_temp->n_clefs=0;
                        staff_temp->n_key_signatures=0;
                        staff_temp->n_custom_key_signatures=0;
                        staff_temp->n_time_signatures=0;
                        staff_temp->n_barlines=0;
                        staff_temp->n_tablature_tunings=0;
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                                staff_temp->id=xmlGetProp(temp_cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"line_number")){
                                staff_temp->line_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"ossia")){
                                if(!xmlStrcmp(xmlGetProp(temp_cur,attributes->name),(const xmlChar*)"yes"))
                                    staff_temp->ossia=1;
                                else
                                    staff_temp->ossia=0;
                                    
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"tablature")){
                                staff_temp->tablature=xmlGetProp(temp_cur,attributes->name);
                            }
                            attributes=attributes->next;
                        }
                        //scanning elements of staff
                        if(temp_cur->xmlChildrenNode!=NULL){
                            temp_cur=temp_cur->xmlChildrenNode;
                            if(temp_cur!=NULL){
                                int last = 0;
                                do{
                                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"clef")){
                                        clef_temp=(struct clef*)calloc(1,sizeof(struct clef));
                                        clef_temp=loadClefValue(temp_cur);
                                        clef_temp->next_clef=NULL;
                                        if(clef_head==NULL){
                                            clef_head=clef_temp;
                                        }
                                        else{
                                            clef_p=clef_head;
                                            while(clef_p->next_clef!=NULL)
                                                clef_p=clef_p->next_clef;
                                            clef_p->next_clef=clef_temp;
                                        }
                                        staff_temp->n_clefs++;
                                    }
                                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"key_signature")){
                                        key_signature_temp=(struct key_signature*)calloc(1,sizeof(struct key_signature));
                                        key_signature_temp=loadKeySignatureValue(temp_cur);
                                        key_signature_temp->next_key_signature=NULL;
                                        if(key_signature_head==NULL){
                                            key_signature_head=key_signature_temp;
                                        }
                                        else{
                                            key_signature_p=key_signature_head;
                                            while(key_signature_p->next_key_signature!=NULL)
                                                key_signature_p=key_signature_p->next_key_signature;
                                            key_signature_p->next_key_signature=key_signature_temp;
                                        }
                                        staff_temp->n_key_signatures++;
                                    }
                                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"custom_key_signature")){
                                        custom_key_signature_temp=(struct custom_key_signature*)calloc(1,sizeof(struct custom_key_signature));
                                        custom_key_signature_temp=loadCustomKeySignatureValue(temp_cur);
                                        custom_key_signature_temp->next_custom_key_signature=NULL;
                                        if(custom_key_signature_head==NULL){
                                            custom_key_signature_head=custom_key_signature_temp;
                                        }
                                        else{
                                            custom_key_signature_p=custom_key_signature_head;
                                            while(custom_key_signature_p->next_custom_key_signature!=NULL)
                                                custom_key_signature_p=custom_key_signature_p->next_custom_key_signature;
                                            custom_key_signature_p->next_custom_key_signature=custom_key_signature_temp;
                                        }
                                        staff_temp->n_custom_key_signatures++;
                                    }
                                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"time_signature")){
                                        time_signature_temp=(struct time_signature*)calloc(1,sizeof(struct time_signature));
                                        time_signature_temp=loadTimeSignatureValue(temp_cur);
                                        time_signature_temp->next_time_signature=NULL;
                                        if(time_signature_head==NULL){
                                            time_signature_head=time_signature_temp;
                                        }
                                        else{
                                            time_signature_p=time_signature_head;
                                            while(time_signature_p->next_time_signature!=NULL)
                                                time_signature_p=time_signature_p->next_time_signature;
                                            time_signature_p->next_time_signature=time_signature_temp;
                                        }
                                        staff_temp->n_time_signatures++;
                                    }
                                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"barline")){
                                        barline_temp=(struct barline*)calloc(1,sizeof(struct barline));
                                        barline_temp=loadBarlineValue(temp_cur);
                                        barline_temp->next_barline=NULL;
                                        if(barline_head==NULL){
                                            barline_head=barline_temp;
                                        }
                                        else{
                                            barline_p=barline_head;
                                            while(barline_p->next_barline!=NULL)
                                                barline_p=barline_p->next_barline;
                                            barline_p->next_barline=barline_temp;
                                        }
                                        staff_temp->n_barlines++;
                                    }
                                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_tuning")){
                                        tablature_tuning_temp=(struct tablature_tuning*)calloc(1,sizeof(struct tablature_tuning));
                                        tablature_tuning_temp=loadTablatureTuningValue(temp_cur);
                                        tablature_tuning_temp->next_tablature_tuning=NULL;
                                        if(tablature_tuning_head==NULL){
                                            tablature_tuning_head=tablature_tuning_temp;
                                        }
                                        else{
                                            tablature_tuning_p=tablature_tuning_head;
                                            while(tablature_tuning_p->next_tablature_tuning!=NULL)
                                                tablature_tuning_p=tablature_tuning_p->next_tablature_tuning;
                                            tablature_tuning_p->next_tablature_tuning=tablature_tuning_temp;
                                        }
                                        staff_temp->n_tablature_tunings++;
                                    }
                                    if (temp_cur->next != NULL)
                                        temp_cur = temp_cur->next;
                                    else
                                        last = 1;
                                }while(!last);
                            }
                            temp_cur=temp_cur->parent;
                        }
                        //end scanning elements of staff
                        staff_temp->clef=clef_head;
                        staff_temp->key_signature=key_signature_head;
                        staff_temp->custom_key_signature=custom_key_signature_head;
                        staff_temp->time_signature=time_signature_head;
                        staff_temp->barline=barline_head;
                        staff_temp->tablature_tuning=tablature_tuning_head;
                        staff_temp->next_staff=NULL;
                        if(staff_head==NULL){
                            staff_head=staff_temp;
                        }
                        else{
                            staff_p=staff_head;
                            while(staff_p->next_staff!=NULL)
                                staff_p=staff_p->next_staff;
                            staff_p->next_staff=staff_temp;                          
                        }
                        logic_layer.los.n_staves++;
                    }
                    temp_cur=temp_cur->next;
                }
            }// end if staff_list
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"part")){
                struct voice_item* voice_item_temp = NULL;
                struct voice_item* voice_item_head = NULL;
                struct voice_item* voice_item_p = NULL;

                struct measure* measure_temp = NULL;
                struct measure* measure_head = NULL;
                struct measure* measure_p = NULL;

                part_temp=(struct part*)calloc(1,sizeof(struct part));
                part_temp->n_voice_items=0;
                part_temp->n_measures=0;
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                        part_temp->id=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"performers_number")){
			if(xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"unknown"))
                            part_temp->performes_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"transposition_pitch")){
                        part_temp->transposition_pitch=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"transposition_accidental")){
                        part_temp->transposition_accidental=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"octave_offset")){
                        part_temp->octave_offset=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }
                    attributes=attributes->next;
                }
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"voice_list")&&part_temp->voice_list==NULL){
                        if(temp_cur->xmlChildrenNode!=NULL){
                            temp_cur=temp_cur->xmlChildrenNode;
                            if(temp_cur!=NULL){
                                do{
                                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"voice_item")){
                                        voice_item_temp=(struct voice_item*)calloc(1,sizeof(struct voice_item));

                                        if (voice_item_temp) {
                                            voice_item_temp = loadVoiceItemValue(temp_cur);
                                            voice_item_temp->next_voice_item = NULL;
                                            if (voice_item_head == NULL) {
                                                voice_item_head = voice_item_temp;
                                            }
                                            else {
                                                voice_item_p = voice_item_head;
                                                while (voice_item_p->next_voice_item != NULL)
                                                    voice_item_p = voice_item_p->next_voice_item;
                                                voice_item_p->next_voice_item = voice_item_temp;
                                            }
                                            part_temp->n_voice_items++;
                                        }
                                        else { fprintf(stderr, "Memory allocation failed for 'voice_item' element\n"); }
                                    }
                                    temp_cur=temp_cur->next;
                                }while(temp_cur->next!=NULL);
                                part_temp->voice_list=voice_item_head;
                            }
                            temp_cur=temp_cur->parent;//l'ultimo é null
                        }
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"measure")){
                        measure_temp=(struct measure*)calloc(1,sizeof(struct measure));
                        measure_temp=loadMeasureValue(temp_cur);
                        measure_temp->next_measure=NULL;
                        if(measure_head==NULL){
                            measure_head=measure_temp;
                        }
                        else{
                            measure_p=measure_head;
                            while(measure_p->next_measure!=NULL)
                                measure_p=measure_p->next_measure;
                            measure_p->next_measure=measure_temp;
                        }
                        part_temp->n_measures++;
                    }
                    temp_cur=temp_cur->next;
                }
                part_temp->measure=measure_head;
                part_temp->next_part=NULL;
                if(part_head==NULL){
                    part_head=part_temp;
                }
                else{
                    part_p=part_head;
                    while(part_p->next_part!=NULL)
                        part_p=part_p->next_part;
                    part_p->next_part=part_temp;
                }
                logic_layer.los.n_parts++;  
            }// end if part
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"horizontal_symbols")){                            
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(xmlStrcmp(temp_cur->name,(const xmlChar*)"text")&&xmlStrcmp(temp_cur->name,(const xmlChar*)"comment")){
                        horizontal_symbol_list_temp=(struct horizontal_symbol_list*)calloc(1,sizeof(struct horizontal_symbol_list));          
                        horizontal_symbol_list_temp->horizontal_symbol_value=loadHorizontalSymbolValue(temp_cur);
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
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(xmlStrcmp(temp_cur->name,(const xmlChar*)"text")&&xmlStrcmp(temp_cur->name,(const xmlChar*)"comment")){
                        ornament_list_temp=(struct ornament_list*)calloc(1,sizeof(struct ornament_list));
                        ornament_list_temp->ornament_value=loadOrnamentValue(temp_cur);
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
                struct syllable* syllable_head = NULL;
                struct syllable* syllable_temp = NULL;
                struct syllable* syllable_p = NULL;

                lyrics_temp=(struct lyrics*)calloc(1,sizeof(struct lyrics));
                lyrics_temp->n_syllables=0;
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
                        lyrics_temp->part_ref=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"voide_ref")){
                        lyrics_temp->voice_ref=xmlGetProp(cur,attributes->name);
                    } 
                    attributes=attributes->next;                     
                }
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){//syllable in lyrics
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"syllable")){
                        syllable_temp=(struct syllable*)calloc(1,sizeof(struct syllable));

                        if (syllable_temp) {
                            attributes = temp_cur->properties;
                            while (attributes != NULL) {
                                if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_event_ref")) {
                                    syllable_temp->start_event_ref = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_event_ref")) {
                                    syllable_temp->end_event_ref = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"hyphen")) {
                                    if (!xmlStrcmp(xmlGetProp(temp_cur, attributes->name), (const xmlChar*)"yes"))
                                        syllable_temp->hyphen = 1;
                                    else
                                        syllable_temp->hyphen = 0;
                                }
                                attributes = attributes->next;
                            }
                            syllable_temp->syllable_value = xmlNodeListGetString(doc, temp_cur->xmlChildrenNode, 1);
                            syllable_temp->next_syllable = NULL;
                            if (syllable_head == NULL) {
                                syllable_head = syllable_temp;
                            }
                            else {
                                syllable_p = syllable_head;
                                while (syllable_p->next_syllable != NULL)
                                    syllable_p = syllable_p->next_syllable;
                                syllable_p->next_syllable = syllable_temp;
                            }
                            lyrics_temp->n_syllables++;
                        }
                        else { fprintf(stderr, "Memory allocation failed for 'syllable' element\n"); }
                    }
                    temp_cur=temp_cur->next;
                }//end while syllable in lyrics
                lyrics_temp->syllable=syllable_head;
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

    logic_layer.los.agogics = agogics_head;
    logic_layer.los.text_field = text_field_head;
    logic_layer.los.metronomic_indication = metronomic_indication_head;
    logic_layer.los.staff_list = staff_head;
    logic_layer.los.staff_list_bracket = brackets_head;
    logic_layer.los.horizontal_symbols = horizontal_symbol_list_head;
    logic_layer.los.ornaments = ornament_list_head;
    logic_layer.los.lyrics = lyrics_head;
    logic_layer.los.part = part_head;
}

void printLos(){
    if ((logic_layer.los.n_agogics != 0) ||
        (logic_layer.los.n_text_fields != 0) ||
        (logic_layer.los.n_metronomic_indications != 0) ||
        (logic_layer.los.n_lyrics != 0) ||
        (logic_layer.los.n_parts != 0) ||
        (logic_layer.los.n_staves != 0) ||
        (logic_layer.los.n_brackets != 0) ||
        (logic_layer.los.n_ornaments != 0) ||
        (logic_layer.los.n_horizontal_symbols != 0)
        ) {

        int i = 0;
        printf("\n#LOS#\n");

        if (logic_layer.los.n_agogics != 0) {
            printf("%i agogics\n",logic_layer.los.n_agogics);
            struct agogics* p = logic_layer.los.agogics;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Agogics: ");
                if (p->bracketed) {
                    printf("bracketed=");
                    if (p->bracketed == 1) printf("yes ");
                    else printf("no ");
                }
                if (p->event_ref)
                    printf("event_ref=%s ", p->event_ref);
                if (p->agogics_value)
                    printf("value=%s", p->agogics_value);
                printf("\n");
                p = p->next_agogics;
            }
            if (logic_layer.los.n_agogics > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_text_fields != 0) {
            printf("%i text fields\n", logic_layer.los.n_text_fields);
            struct text_field* p = logic_layer.los.text_field;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Text Field: ");
                if (p->extension_line_to)
                    printf("line_to=%s ", p->extension_line_to);
                if (p->extension_line_shape)
                    printf("line_shape=%s ", p->extension_line_shape);
                if (p->event_ref)
                    printf("event_ref=%s", p->event_ref);
                if (p->text_field_value)
                    printf("value=%s", p->text_field_value);
                printf("\n");
                p = p->next_text_field;
            }
            if (logic_layer.los.n_text_fields > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_metronomic_indications != 0) {
            printf("%i metronomic indications\n", logic_layer.los.n_metronomic_indications);
            struct metronomic_indication* p = logic_layer.los.metronomic_indication;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Metronomic Indication: ");
                if (p->num)
                    printf("num=%i ", p->num);
                if (p->den)
                    printf("den=%i ", p->den);
                if (p->dots)
                    printf("dots=%i", p->dots);
                if (p->value)
                    printf("value=%i", p->value);
                printf("\n");
                p = p->next_metronomic_indication;
            }
            if (logic_layer.los.n_metronomic_indications > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_parts != 0) {
            printf("%i parts\n", logic_layer.los.n_parts);
            struct part* p = logic_layer.los.part;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Part: ");
                if (p->id)
                    printf("id=%s ", p->id);
                if (p->performes_number)
                    printf("performers=%i ", p->performes_number);
                if (p->transposition_pitch)
                    printf("transposition_pitch=%s ", p->transposition_pitch);
                if (p->transposition_accidental)
                    printf("transposition_accidental=%s ", p->transposition_accidental);
                if (p->octave_offset)
                    printf("performers=%i ", p->octave_offset);
                printf("\n");
                printVoiceList(p);
                printMeasure(p);
                p = p->next_part;
            }
            if (logic_layer.los.n_parts > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_staves != 0) {
            printf("%i staves\n", logic_layer.los.n_staves);
            struct staff* p = logic_layer.los.staff_list;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Staff: ");
                if (p->id)
                    printf("id=%s ", p->id);
                if (p->line_number)
                    printf("line_number=%i ", p->line_number);
                if (p->ossia) {
                    printf("ossia=");
                    if (p->ossia == 1) printf("yes ");
                    else printf("no ");
                }
                if (p->tablature)
                    printf("tablature=%s", p->tablature);
                printf("\n");
                printClef(p);
                printKeySignature(p);
                printCustomKeySignature(p);
                printTimeSignature(p);
                printBarline(p);
                printTablatureTuning(p);
                p = p->next_staff;
            }
            if (logic_layer.los.n_staves > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_brackets != 0) {
            printf("%i brackets\n", logic_layer.los.n_brackets);
            struct brackets* p = logic_layer.los.staff_list_bracket;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Brackets: ");
                if (p->marker)
                    printf("%s ", p->marker);
                if (p->group_number)
                    printf("%i ", p->group_number);
                if (p->shape)
                    printf("%s", p->shape);
                printf("\n");
                p = p->next_brackets;
            }
            if (logic_layer.los.n_brackets > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_ornaments != 0) {
            printf("%i ornaments\n", logic_layer.los.n_ornaments);
            struct ornament_list* p = logic_layer.los.ornaments;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Ornament: ");
                printOrnament(p->ornament_value);
                printf("\n");
                p = p->next_ornament;
            }
            if (logic_layer.los.n_ornaments > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_horizontal_symbols != 0) {
            printf("%i horizontal symbols\n", logic_layer.los.n_horizontal_symbols);
            struct horizontal_symbol_list* p = logic_layer.los.horizontal_symbols;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Horizontal Symbol: ");
                printHorizontalSymbol(p->horizontal_symbol_value);
                printf("\n");
                p = p->next_horizontal_symbol;
            }
            if (logic_layer.los.n_horizontal_symbols > N_DISPLAY) printf("...");
            printf("\n");
        }

        if (logic_layer.los.n_lyrics != 0) {
            printf("%i lyrics\n", logic_layer.los.n_lyrics);
            struct lyrics* p = logic_layer.los.lyrics;
            i = 0;
            while (p != NULL && i < N_DISPLAY) {
                i++;
                printf("Lyrics: ");
                if (p->n_syllables)
                    printf("%i syllables ", p->n_syllables);
                if (p->part_ref)
                    printf("part_ref=%s ", p->part_ref);
                if (p->voice_ref)
                    printf("voice_ref=%s", p->voice_ref);
                printf("\n");
                printSyllables(p);
                p = p->next_lyrics;
            }
            if (logic_layer.los.n_lyrics > N_DISPLAY) printf("...");
            printf("\n");
        }
    }
}

void loadLayout(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    xmlAttr *attributes;
    
    struct page* page_temp=NULL;
    struct page* page_head=NULL;
    struct page* page_p=NULL;
    logic_layer.layout.n_pages=0; 
    
    xpath=(xmlChar *)"/ieee1599/logic/layout";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        attributes=cur->properties;
        
        while(attributes!=NULL){//layout attributes
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"hpos_per_unit")){
                logic_layer.layout.hpos_per_unit=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"measurement_unit")){
                logic_layer.layout.measurement_unit=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        
        cur=cur->xmlChildrenNode;
        while(cur!=NULL){//scan layout children
            if(!xmlStrcmp(cur->name,(const xmlChar*)"page")){
                page_temp=(struct page*)calloc(1,sizeof(struct page));
                
                struct layout_system* layout_system_temp=NULL;
                struct layout_system* layout_system_head=NULL;
                struct layout_system* layout_syustem_p=NULL;
                page_temp->n_layout_systems=0;
                
                struct layout_images* layout_images_temp=NULL;
                struct layout_images* layout_images_head=NULL;
                struct layout_images* layout_images_p=NULL;
                page_temp->n_layout_images=0;
                
                struct layout_shapes* layout_shapes_temp=NULL;
                struct layout_shapes* layout_shapes_head=NULL;
                struct layout_shapes* layout_shapes_p=NULL;
                page_temp->n_layout_shapes=0;
                
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                        page_temp->id=xmlGetProp(cur,attributes->name); 
                    } 
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"number")){
                        page_temp->number=xmlCharToInt(xmlGetProp(cur,attributes->name)); 
                    }  
                    attributes=attributes->next;                     
                }  
                
                //start page elements
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"standard_page_format")){
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"format")){
                                page_temp->standard_page_format.format=xmlGetProp(temp_cur,attributes->name);
                            }
                            attributes=attributes->next;
                        }
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"custom_page_format")){
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"width")){
                                page_temp->custom_page_format.width=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"height")){
                                page_temp->custom_page_format.height=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            attributes=attributes->next;
                        }
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"layout_system")){//contains layout_staff+
                        layout_system_temp=(struct layout_system*)calloc(1,sizeof(struct layout_system));
                        
                        struct layout_staff* layout_staff_temp = NULL;
                        struct layout_staff* layout_staff_head = NULL;
                        struct layout_staff* layout_staff_p = NULL;
                        layout_system_temp->n_layout_staves=0;
                        
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                                layout_system_temp->id=xmlGetProp(temp_cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"upper_left_x")){
                                layout_system_temp->upper_left_x=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"upper_left_y")){
                                layout_system_temp->upper_left_y=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"lower_right_x")){
                                layout_system_temp->lower_right_x=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"lower_right_y")){
                                layout_system_temp->lower_right_y=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                            }
                            attributes=attributes->next;
                        }
                        
                        //start scan layout_staff
                        temp_cur=temp_cur->xmlChildrenNode;
                        int last = 0;
                        do{
                            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"layout_staff")){
                                layout_staff_temp=(struct layout_staff*)calloc(1,sizeof(struct layout_staff));
                                
                                if (layout_staff_temp) {
                                    layout_staff_temp->show_key_signature = 1;
                                    layout_staff_temp->show_clef = 1;

                                    attributes = temp_cur->properties;
                                    while (attributes != NULL) {
                                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                                            layout_staff_temp->id = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"staff_ref")) {
                                            layout_staff_temp->staff_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"vertical_offset")) {
                                            layout_staff_temp->vertical_offset = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"height")) {
                                            layout_staff_temp->height = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"show_key_signature")) {
                                            if (!xmlStrcmp(xmlGetProp(temp_cur, attributes->name), (const xmlChar*)"yes"))
                                                layout_staff_temp->show_key_signature = 1;
                                            else
                                                layout_staff_temp->show_key_signature = 0;
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"show_clef")) {
                                            if (!xmlStrcmp(xmlGetProp(temp_cur, attributes->name), (const xmlChar*)"yes"))
                                                layout_staff_temp->show_clef = 1;
                                            else
                                                layout_staff_temp->show_clef = 0;
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"show_time_signature")) {
                                            if (!xmlStrcmp(xmlGetProp(temp_cur, attributes->name), (const xmlChar*)"yes"))
                                                layout_staff_temp->show_time_signature = 1;
                                            else
                                                layout_staff_temp->show_time_signature = 0;
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"ossia")) {
                                            if (!xmlStrcmp(xmlGetProp(temp_cur, attributes->name), (const xmlChar*)"yes"))
                                                layout_staff_temp->ossia = 1;
                                            else
                                                layout_staff_temp->ossia = 0;
                                        }
                                        attributes = attributes->next;
                                    }

                                    layout_staff_temp->next_layout_staff = NULL;
                                    if (layout_staff_head == NULL) {
                                        layout_staff_head = layout_staff_temp;
                                    }
                                    else {
                                        layout_staff_p = layout_staff_head;
                                        while (layout_staff_p->next_layout_staff != NULL)
                                            layout_staff_p = layout_staff_p->next_layout_staff;
                                        layout_staff_p->next_layout_staff = layout_staff_temp;
                                    }
                                    layout_system_temp->n_layout_staves++;
                                }
                                else { fprintf(stderr, "Memory allocation failed for 'layout_staff' element\n"); }
                            }
                            if (temp_cur->next != NULL)
                                temp_cur = temp_cur->next;
                            else
                                last = 1;
                        }while(!last);
                        temp_cur=temp_cur->parent;                        
                        //end scan layout staff
                        layout_system_temp->layout_staff=layout_staff_head;
                        
                        layout_system_temp->next_layout_system=NULL;
                        if(layout_system_head==NULL)
                            layout_system_head=layout_system_temp;
                        else{
                            layout_syustem_p=layout_system_head;
                            while(layout_syustem_p->next_layout_system!=NULL)
                                layout_syustem_p=layout_syustem_p->next_layout_system;
                            layout_syustem_p->next_layout_system=layout_system_temp;
                        } 
                        
                        page_temp->n_layout_systems++;
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"layout_images")){
                        layout_images_temp=(struct layout_images*)calloc(1,sizeof(struct layout_images));
                        
                        if (layout_images_temp) {
                            attributes = temp_cur->properties;
                            while (attributes != NULL) {
                                if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                                    layout_images_temp->file_name = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_format")) {
                                    layout_images_temp->file_format = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"encoding_format")) {
                                    layout_images_temp->encoding_format = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"horizontal_offset")) {
                                    layout_images_temp->horizontal_offset = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"vertical_offset")) {
                                    layout_images_temp->vertical_offset = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                                    layout_images_temp->description = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"copyright")) {
                                    layout_images_temp->copyright = xmlGetProp(temp_cur, attributes->name);
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"notes")) {
                                    layout_images_temp->notes = xmlGetProp(temp_cur, attributes->name);
                                }
                                attributes = attributes->next;
                            }

                            layout_images_temp->next_layout_images = NULL;
                            if (layout_images_head == NULL)
                                layout_images_head = layout_images_temp;
                            else {
                                layout_images_p = layout_images_head;
                                while (layout_images_p->next_layout_images != NULL)
                                    layout_images_p = layout_images_p->next_layout_images;
                                layout_images_p->next_layout_images = layout_images_temp;
                            }
                            page_temp->n_layout_images++;
                        }
                        else { fprintf(stderr, "Memory allocation failed for 'layout_images' element\n"); }
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"layout_shapes")){//contains svg
                        layout_shapes_temp=(struct layout_shapes*)calloc(1,sizeof(struct layout_shapes));
                        
                        if (layout_shapes_temp) {
                            attributes = temp_cur->properties;
                            while (attributes != NULL) {
                                if (!xmlStrcmp(attributes->name, (const xmlChar*)"horizontal_offset")) {
                                    layout_shapes_temp->horizontal_offset = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                }
                                else if (!xmlStrcmp(attributes->name, (const xmlChar*)"vertical_offset")) {
                                    layout_shapes_temp->vertical_offset = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                                }
                                attributes = attributes->next;
                            }

                            //caricare contenuto svg

                            layout_shapes_temp->next_layout_shapes = NULL;
                            if (layout_shapes_head == NULL)
                                layout_shapes_head = layout_shapes_temp;
                            else {
                                layout_shapes_p = layout_shapes_head;
                                while (layout_shapes_p->next_layout_shapes != NULL)
                                    layout_shapes_p = layout_shapes_p->next_layout_shapes;
                                layout_shapes_p->next_layout_shapes = layout_shapes_temp;
                            }
                            page_temp->n_layout_shapes++;
                        }
                        else { fprintf(stderr, "Memory allocation failed for 'layout_shapes' element\n"); }
                    }                   
                    temp_cur=temp_cur->next;
                }
                page_temp->layout_system=layout_system_head;
                page_temp->layout_images_list=layout_images_head;
                page_temp->layout_shapes_list=layout_shapes_head;
                //end page elements
                
                page_temp->next_page=NULL;
                if(page_head==NULL){
                    page_head=page_temp;
                }
                else{
                    page_p=page_head;
                    while(page_p->next_page!=NULL)
                        page_p=page_p->next_page;
                    page_p->next_page=page_temp;
                }
                logic_layer.layout.n_pages++;                                           
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"text_font")){
                //logic_layer.layout.text_font=loadTextFont(...)
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"music_font")){
                //logic_layer.layout.music_font=loadMusicFont(...);
            }
        }
    }//layout is optional
    logic_layer.layout.page = page_head;
}

void printLayout(){
    if (logic_layer.layout.n_pages != 0) {
        printf("\n#Layout#\n");
        
        if (logic_layer.layout.hpos_per_unit)
            printf("hpos_per_unit=%i ", logic_layer.layout.hpos_per_unit);
        if (logic_layer.layout.measurement_unit)
            printf("measurement_unit=%s ", logic_layer.layout.measurement_unit);
        
         
        printf("%i pages ", logic_layer.layout.n_pages);
        if (logic_layer.layout.text_font)
            printf("text_font=%s ",logic_layer.layout.text_font);
        if (logic_layer.layout.music_font)
            printf("music_font=%s ", logic_layer.layout.music_font);
        printf("\n");

        struct page* p = logic_layer.layout.page;
        int i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("Page: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->number)
                printf("timing=%i ", p->number);
            if (p->standard_page_format.format)
                printf("format=%s ", p->standard_page_format.format);
            if (p->custom_page_format.width)
                printf("width=%i height=%i ", p->custom_page_format.width, p->custom_page_format.height);
            printf("\n");
            if (p->n_layout_systems != 0) {
                printf("    %i layout systems\n", p->n_layout_systems);
                struct layout_system* k = p->layout_system;
                while (k) {
                    printf("    Layout System: ");
                    printLayoutSystem(k);
                    k = k->next_layout_system;
                }
            }
            if (p->n_layout_images != 0) {
                printf("    %i layout images\n", p->n_layout_images);
                struct layout_images* k = p->layout_images_list;
                while (k) {
                    printf("    Layout Images: ");
                    printLayoutImages(k);
                    k = k->next_layout_images;
                }
            }
            if (p->n_layout_shapes != 0) {
                printf("    %i layout shapes\n", p->n_layout_shapes);
                struct layout_shapes* k = p->layout_shapes_list;
                while (k) {
                    printf("    Layout Shapes: ");
                    printLayoutShapes(k);
                    k = k->next_layout_shapes;
                }
            }
            p = p->next_page;
        }
        if (logic_layer.layout.n_pages > N_DISPLAY) printf("...");
        printf("\n");
    }
}

void printLayoutSystem(struct layout_system* cur) {
    if (cur->n_layout_staves != 0) {
        if (cur->id)
            printf("id=%s ", cur->id);
        if (cur->upper_left_x)
            printf("upper_left_x=%i ", cur->upper_left_x);
        if (cur->upper_left_y)
            printf("upper_left_y=%i ", cur->upper_left_y);
        if (cur->lower_right_x)
            printf("lower_right_x=%i ", cur->lower_right_x);
        if (cur->lower_right_y)
            printf("lower_right_y=%i ", cur->lower_right_y);

        printf("%i layout staves ", cur->n_layout_staves);
        struct layout_staff* p = cur->layout_staff;
        while (p != NULL) {
            printf("( Layout Staff: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->staff_ref)
                printf("staff_ref=%s ", p->staff_ref);
            if (p->vertical_offset)
                printf("vertical_offset=%i ", p->vertical_offset);
            if (p->height)
                printf("height=%i ", p->height);
            if (p->show_key_signature)
                if(p->show_key_signature==1) printf("show_key_signature");
            if (p->show_clef)
                if (p->show_clef == 1) printf("show_clef");
            if (p->show_time_signature)
                if (p->show_time_signature == 1) printf("show_time_signature");
            if (p->ossia)
                if (p->ossia == 1) printf("ossia");
            printf(") ");
            p = p->next_layout_staff;
        }
    }
}

void printLayoutImages(struct layout_images* cur) {
    if (cur->file_name) {
        printf("file_name=%s ", cur->file_name);
        if (cur->file_format)
            printf("file_format=%s ", cur->file_format);
        if (cur->encoding_format)
            printf("encoding_format=%s ", cur->encoding_format);
        if (cur->horizontal_offset)
            printf("horizontal_offset=%i ", cur->horizontal_offset);
        if (cur->vertical_offset)
            printf("vertical_offset=%i ", cur->vertical_offset);
        if (cur->description)
            printf("description=%s ", cur->description);
        if (cur->copyright)
            printf("copyright=%s ", cur->copyright);
        if (cur->notes)
            printf("notes=%s ", cur->notes);
    }
}

void printLayoutShapes(struct layout_shapes* cur) {
    if (cur->horizontal_offset) {
        printf("horizontal_offset=%i ", cur->horizontal_offset);
        if (cur->vertical_offset)
            printf("vertical_offset=%i ", cur->vertical_offset);
    }
}

void printSyllables(struct lyrics* cur) {
    if (cur->n_syllables!=0) {
        printf("    %i syllables\n", cur->n_syllables);
        int i = 0;
        printf("    Syllables: ");
        struct syllable* p = cur->syllable;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->start_event_ref)
                printf("start_event_ref=%s ", p->start_event_ref);
            if (p->end_event_ref)
                printf("end_event_ref=%s ", p->end_event_ref);
            if (p->hyphen) {
                printf("hyphen=");
                if (p->hyphen == 1) printf("yes ");
                else printf("no ");
            }
            if (p->syllable_value)
                printf("value=%s ",p->syllable_value);
            printf(") ");
            p = p->next_syllable;
        }
        if (cur->n_syllables > N_DISPLAY) printf("  ...");
        printf("\n");
    }
}

void printClef(struct staff* cur) {
    if (cur->n_clefs != 0) {
        printf("    %i clefs\n",cur->n_clefs);
        int i = 0;
        printf("    Clef: ");
        struct clef* p = cur->clef;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->shape)
                printf("shape=%s ", p->shape);
            if (p->staff_step)
                printf("step=%s ", p->staff_step);
            if (p->octave_num)
                printf("octave=%i ", p->octave_num);
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            printf(") ");
            p = p->next_clef;
        }
        if (cur->n_clefs > N_DISPLAY) printf("  ...");
        printf("\n");
    }
}

void printKeySignature(struct staff* cur) {
    if (cur->n_key_signatures != 0) {
        printf("    %i key signatures\n", cur->n_key_signatures);
        int i = 0;
        printf("    Key Signature: ");
        struct key_signature* p = cur->key_signature;
        while (p != NULL ) {
            i++;
            printf("( ");
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            if (p->num_type)
                printf("num_type=%s ", p->num_type);
            if (p->number)
                printf("number=%i ", p->number);
            printf(") ");
            p = p->next_key_signature;
        }
        printf("\n");
    }
}

void printCustomKeySignature(struct staff* cur) {
    if (cur->n_custom_key_signatures != 0) {
        printf("    %i custom key signatures\n", cur->n_custom_key_signatures);
        int i = 0;
        printf("    Custom Key Signature: ");
        struct custom_key_signature* p = cur->custom_key_signature;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            printf(") ");
            if (p->n_key_accidentals != 0) {
                printf("\n        Key Accidentals: ");
                struct key_accidental* k = p->key_accidentals;
                while (k != NULL) {
                    printf("( ");
                    if (k->step)
                        printf("step=%s ",k->step);
                    if (k->accidental)
                        printf("accidental=%s ", k->accidental);
                    printf(") ");
                    k = k->next_key_accidental;
                }
            }
            p = p->next_custom_key_signature;
        }
        if (cur->n_custom_key_signatures > N_DISPLAY) printf("  ...");
        printf("\n");
    }
}

void printTimeSignature(struct staff* cur) {
    if (cur->n_time_signatures != 0) {
        printf("    %i time signatures\n", cur->n_time_signatures);
        int i = 0;
        printf("    Time Signature: ");
        struct time_signature* p = cur->time_signature;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->event_ref)
                printf("event_ref=%s ",p->event_ref);
            if (p->visible) {
                printf("visible=");
                if (p->visible == 0) printf("no ");
                else printf("yes ");
            }
            printf(") ");
            if (p->n_time_indications != 0) {
                printf("\n        Time Indications: ");
                struct time_indication* k = p->time_indications;
                while (k != NULL) {
                    printf("( ");
                    if (k->num)
                        printf("num=%i ", k->num);
                    if (k->den)
                        printf("den=%i ", k->den);
                    if (k->abbreviation) {
                        printf("abbreviation=");
                        if (k->abbreviation == 1) printf("yes ");
                        else printf("no ");
                    }
                    if (k->vtu_amount)
                        printf("vtu=%i ", k->vtu_amount);
                    printf(") ");
                    k = k->next_time_indication;
                }
            }
            p = p->next_time_signature;
        }
        if (cur->n_time_signatures > N_DISPLAY) printf("    ...");
        printf("\n");
    }
}

void printBarline(struct staff* cur) {
    if (cur->n_barlines != 0) {
        printf("    %i barlines\n", cur->n_time_signatures);
        int i = 0;
        printf("    Barline: ");
        struct barline* p = cur->barline;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->style)
                printf("style=%s ", p->style);
            if (p->extension) 
                printf("extension=%s ", p->extension);
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            printf(") ");
            p = p->next_barline;
        }
        if (cur->n_barlines > N_DISPLAY) printf("   ...");
        printf("\n");
    }

}

void printTablatureTuning(struct staff* cur) {
    if (cur->n_tablature_tunings != 0) {
        printf("    %i tablature tunings\n", cur->n_tablature_tunings);
        int i = 0;
        printf("    Tablature Tuning: ");
        struct tablature_tuning* p = cur->tablature_tuning;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->type)
                printf("type=%s ", p->type);
            printf(") ");
            if (p->n_strings != 0) {
                printf("\n        Strings: ");
                struct string* k = p->strings;
                while (k != NULL) {
                    printf("( ");
                    if (k->string_number)
                        printf("number=%i ", k->string_number);
                    if (k->string_pitch)
                        printf("pitch=%s ", k->string_pitch);
                    if (k->string_accidental)
                        printf("accidental=%s ", k->string_accidental);
                    if (k->string_octave)
                        printf("octave=%i ", k->string_octave);
                    printf(") ");
                    k = k->next_string;
                }
            }
            p = p->next_tablature_tuning;
        }
        if (cur->n_tablature_tunings > N_DISPLAY) printf("  ...");
        printf("\n");
    }
}

void printVoiceList(struct part* cur) {
    if (cur->n_voice_items != 0) {
        printf("    %i voice items\n", cur->n_voice_items);
        int i = 0;
        printf("    Voice List: ");
        struct voice_item* p = cur->voice_list;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->staff_ref)
                printf("staff_ref=%s ", p->staff_ref);
            if (p->notation_style)
                printf("style=%s ", p->notation_style);
            printf(") ");
            p = p->next_voice_item;
        }
        if (cur->n_voice_items > N_DISPLAY) printf("    ...");
        printf("\n");
    }
}

void printMeasure(struct part* cur) {
    if (cur->n_measures != 0) {
        printf("    %i measures\n", cur->n_measures);
        int i = 0;
        struct measure* p = cur->measure;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("    Measure: ( ");
            if (p->number)
                printf("number=%i ", p->number);
            if (p->id)
                printf("id=%s ", p->id);
            if (p->show_number)
                printf("show_number=%i ", p->show_number);
            if (p->numbering_style)
                printf("style=%s ", p->numbering_style);
            printf(")\n");
            if (p->multiple_rest.number_of_measures) {
                printf("        Multiple Rest: ");
                if (p->multiple_rest.number_of_measures) {
                    printf("number_of_measures=%i ", p->multiple_rest.number_of_measures);
                }
                if (p->multiple_rest.event_ref) {
                    printf("event_ref=%s ", p->multiple_rest.event_ref);
                }
            }
            if (p->measure_repeat.number_of_measures) {
                printf("        Measure Repeat: ");
                if (p->measure_repeat.number_of_measures) {
                    printf("number_of_measures=%i ", p->measure_repeat.number_of_measures);
                }
                if (p->measure_repeat.event_ref) {
                    printf("event_ref=%s ", p->measure_repeat.event_ref);
                }
            }
            printVoice(p);
            p = p->next_measure;
        }
        if (cur->n_measures > N_DISPLAY) printf("   ...");
        printf("\n");
    }
}

void printVoice(struct measure* cur) {
    if (cur->n_voices != 0) {
        printf("    %i voices\n", cur->n_voices);
        int i = 0;
        struct voice* p = cur->voices;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("    Voice: ( ");
            if (p->voice_item_ref)
                printf("voice_item_ref=%s ", p->voice_item_ref);
            if (p->ossia) {
                printf("ossia=");
                if (p->ossia == 1) printf("yes ");
                else printf("no ");
            }
            printf(")\n");
            if (p->n_chords != 0) {
                printf("    %i chords\n", p->n_chords);
                struct chord* k = p->chord;
                while (k) {
                    printf("        Chord: ( ");
                    printChord(k);
                    printf(")\n");
                    k = k->next_chord;
                }
            }
            printRest(p);
            printTablatureSymbol(p);
            printGregorianSymbol(p);
            p = p->next_voice;
        }
        if (cur->n_voices > N_DISPLAY) printf("   ...");
        printf("\n");
    }
}

void printChord(struct chord* cur) {
    if (cur->id)      
        printf("id=%s ", cur->id);
    if (cur->event_ref)
        printf("event_ref=%s ", cur->event_ref);
    if (cur->stem_direction)
        printf("stem_direction=%s ", cur->stem_direction);
    if (cur->beam_before) {
        printf("beam_before=");
        if (cur->beam_before == 1) printf("yes ");
        else printf("no ");
    }
    if (cur->beam_after) {
        printf("beam_after=");
        if (cur->beam_after == 1) printf("yes ");
        else printf("no ");
    }
    if (cur->cue) {
        printf("cue=");
        if (cur->cue == 1) printf("yes ");
        else printf("no ");
    }
    if (cur->tremolo_lines) {
        printf("tremolo_lines=%i ", cur->tremolo_lines);
    }
    if (cur->repetition) {
        printf("repetition=");
        if (cur->repetition == 1) printf("yes ");
        else printf("no ");
    }
    if (cur->duration.num != 0) {
        printf("duration=%i/%i ",cur->duration.num,cur->duration.den);
        if (cur->duration.tuplet_ratio) {
            printTupletRatio(cur->duration.tuplet_ratio);
        }
    }
    if (cur->augmentation_dots.number != 0) {
        printf("agumentation_dots=%i ",cur->augmentation_dots.number);
    }
    if (cur->n_noteheads != 0) {
        struct notehead* k = cur->noteheads;
        printf("[ Noteheads: ");
        while (k != NULL) {
            printNotehead(k);
            k = k->next_notehead;
        }
        printf("] ");
    }
    printArticulation(cur);
}
void printRest(struct voice* cur) {
    if (cur->n_rests != 0) {
        printf("    %i rests\n", cur->n_rests);
        int i = 0;
        struct rest* p = cur->rest;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("        Rest: ( ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            if (p->staff_ref)
                printf("staff_ref=%s ", p->staff_ref);
            if (p->hidden) {
                if (p->hidden == 1) printf("hidden");
            }
            if (p->duration.num != 0) {
                printf("duration=%i/%i ", p->duration.num, p->duration.den);
                if (p->duration.tuplet_ratio) {
                    printTupletRatio(p->duration.tuplet_ratio);
                }
            }
            if (p->augmentation_dots.number != 0) {
                printf("agumentation_dots=%i ", p->augmentation_dots.number);
            }
            printf(")\n");
            p = p->next_rest;
        }
        if (cur->n_rests > N_DISPLAY) printf("     ...");
        printf("\n");
    }
}
void printTablatureSymbol(struct voice* cur) {
    if (cur->n_tablature_symbols != 0) {
        printf("    %i tablature symbols\n", cur->n_tablature_symbols);
        int i = 0;
        struct tablature_symbol* p = cur->tablature_symbol;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("        Tablature Symbol: ( ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            if (p->stem_direction)
                printf("stem_direction=%s ", p->stem_direction);
            if (p->beam_before) {
                if (p->beam_before == 1) printf("beam_before");
            }
            if (p->beam_after) {
                if (p->beam_after == 1) printf("beam_after");
            }
            if (p->duration.num != 0) {
                printf("duration=%i/%i ", p->duration.num, p->duration.den);
                if (p->duration.tuplet_ratio) {
                    printTupletRatio(p->duration.tuplet_ratio);
                }
            }
            if (p->augmentation_dots.number != 0) {
                printf("agumentation_dots=%i ", p->augmentation_dots.number);
            }
            printf(")\n");
            if (p->n_keys != 0) {
                printf("            Keys: ");
                struct key* k = p->keys;
                while (k) {
                    printKey(k);
                    k = k->next_key;
                }
                printf("\n");
            }
            p = p->next_tablature_symbol;
        }
        if (cur->n_tablature_symbols > N_DISPLAY) printf("     ...");
        printf("\n");
    }
}
void printGregorianSymbol(struct voice* cur) {
    if (cur->n_gregorian_symbols != 0) {
        printf("    %i gregorian symbols\n", cur->n_chords);
        int i = 0;
        struct gregorian_symbol* p = cur->gregorian_symbol;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("        Gregorian Symbol: ( ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->neume)
                printf("neume=%s ", p->neume);
            if (p->inflexion)
                printf("inflexion=%s ", p->inflexion);
            if (p->subpunctis)
                printf("subpunctis=%s ", p->subpunctis);
            if (p->interpretative_mark)
                printf("interpretative_mark=%s ", p->interpretative_mark);
            if (p->mora) {
                printf("mora=");
                if (p->mora == 1) printf("yes ");
                else printf("no ");
            }
            if (p->event_ref)
                printf("event_ref=%s ", p->event_ref);
            printf(")\n");
            if (p->n_noteheads != 0) {
                struct notehead* k = p->notehead;
                printf("            Noteheads: ");
                while (k != NULL) {
                    printNotehead(k);
                    k = k->next_notehead;
                }
            }
            p = p->next_gregorian_symbol;
        }
        if (cur->n_gregorian_symbols > N_DISPLAY) printf("     ...");
        printf("\n");
    }
}

void printArticulation(struct chord* cur) {
    if (cur->n_articulations != 0) {
        printf("            %i articulations\n", cur->n_articulations);
        int i = 0;
        struct articulation* p = cur->articulations;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("            Articulations: ");
            if (p->articulation_sign)
                printf("%s ", p->articulation_sign);
            p = p->next_articulation;
        }
        if (cur->n_articulations > N_DISPLAY) printf(" ...");
        printf("\n");
    }
}

void printNotehead(struct notehead* cur) {
    if (cur->id)
        printf("id=%s ",cur->id);
    if (cur->staff_ref)
        printf("staff_ref=%s ", cur->staff_ref);
    if (cur->style)
        printf("style=%s ", cur->style);

    if (cur->pitch.step != NULL) {
        printf("( Pitch: ");
        printf("step=%s ",cur->pitch.step);
        if (cur->pitch.octave)
            printf("octave=%i ",cur->pitch.octave);
        if (cur->pitch.actual_accidental)
            printf("accidental=%s ", cur->pitch.actual_accidental);
        printf(") ");
    }

    if (cur->n_printed_accidentals != 0) {
        struct printed_accidental* p = cur->printed_accidentals;
        printf("( Printed Accidentals: ");
        while (p) {
            printf("%s ",p->printed_accidental_type);
            if (p->parenthesis) {
                if (p->parenthesis == 1) printf("parenthesis=yes ");
                else printf("parenthesis=no ");
            }
            p = p->next_printed_accidental;
        }
        printf(") ");
    }
    if (cur->printed_accidentals_shape)
        printf("printed_accidentals_shape=%s ",cur->printed_accidentals_shape);
    if (cur->tie) {
        if (cur->tie == 1) printf("tie");
    }
    if (cur->fingering.number) {
        printf("( Fingering: number=%i ) ",cur->fingering.number);
    }
}

void printTupletRatio(struct tuplet_ratio* cur) {
    if (cur->n_tuplet_ratios != 0) {
        while (cur != NULL){
            printf("[ Tuplet Ratio: ");
            if (cur->enter_num)
                printf("enter_num=%i ", cur->enter_num);
            if (cur->enter_den)
                printf("enter_den=%i ", cur->enter_den);
            if (cur->enter_dots)
                printf("enter_dots=%i ", cur->enter_dots);
            if (cur->in_num)
                printf("in_num=%i ", cur->in_num);
            if (cur->in_den)
                printf("in_den=%i ", cur->in_den);
            if (cur->in_dots)
                printf("in_dots=%i ", cur->in_dots);
            printTupletRatio(cur);
            printf("] ");
            cur = cur->next_tuplet_ratio;
        }
    }
}

void printKey(struct key* cur) {
    printf("[ ");
    if (cur->id)
        printf("id=%s ", cur->id);
    if (cur->staff_ref)
        printf("staff_ref=%s ", cur->staff_ref);

    if (cur->tie)
        if (cur->tie == 1) printf("tie ");
    if (cur->tablature_pitch.key_number) {
        printf("( Tablature Pitch: ");
        printf("key_number=%i ", cur->tablature_pitch.key_number);
        if (cur->tablature_pitch.string_number)
            printf("string_number=%i ", cur->tablature_pitch.string_number);
        printf(") ");
    }
    if (cur->tablature_articulation.shape) {
        printf("( Tablature Articulation: ");
        printf("shape=%s ", cur->tablature_articulation.shape);
        printf(") ");
    }
    if (cur->tablature_fingering.shape) {
        printf("( Tablature Fingering: ");
        printf("shape=%s ", cur->tablature_fingering.shape);
        if (cur->tablature_fingering.tablature_fingering_value)
            printf("tablature_fingering_value=%s ", cur->tablature_fingering.tablature_fingering_value);
        printf(") ");
    }
    printf("] ");
}

void printOrnament(ornament cur) {
    if (!xmlStrcmp(cur.acciaccatura.ornament_name, (const xmlChar*)"acciaccatura")) {
        printf("%s ", cur.acciaccatura.ornament_name);
        if (cur.acciaccatura.event_ref) printf("event_ref=%s ", cur.acciaccatura.event_ref);
        if (cur.acciaccatura.id) printf("id=%s ", cur.acciaccatura.id);
        if (cur.acciaccatura.slur) if (cur.acciaccatura.slur == 1) printf("slur ");
        if (cur.acciaccatura.n_chords != 0) {
            printf("    %i chords\n", cur.acciaccatura.n_chords);
            struct chord* k = cur.acciaccatura.chord;
            while (k) {
                printf("        Chord: ( ");
                printChord(k);
                printf(")\n");
                k = k->next_chord;
            }
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.baroque_acciaccatura.ornament_name, (const xmlChar*)"baroque_acciaccatura")) {
        printf("%s ", cur.baroque_acciaccatura.ornament_name);
        if (cur.baroque_acciaccatura.event_ref) printf("event_ref=%s ", cur.baroque_acciaccatura.event_ref);
        if (cur.baroque_acciaccatura.id) printf("id=%s ", cur.baroque_acciaccatura.id);
        if (cur.baroque_acciaccatura.style) printf("style=%s ", cur.baroque_acciaccatura.style);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.appoggiatura.ornament_name, (const xmlChar*)"appoggiatura")) {
        printf("%s ", cur.appoggiatura.ornament_name);
        if (cur.appoggiatura.event_ref) printf("event_ref=%s ", cur.appoggiatura.event_ref);
        if (cur.appoggiatura.id) printf("id=%s ", cur.appoggiatura.id);
        if (cur.appoggiatura.slur) if (cur.appoggiatura.slur == 1) printf("slur ");
        if (cur.appoggiatura.n_chords != 0) {
            printf("    %i chords\n", cur.appoggiatura.n_chords);
            struct chord* k = cur.appoggiatura.chord;
            while (k) {
                printf("        Chord: ( ");
                printChord(k);
                printf(")\n");
                k = k->next_chord;
            }
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.baroque_appoggiatura.ornament_name, (const xmlChar*)"baroque_appoggiatura")) {
        printf("%s ", cur.baroque_appoggiatura.ornament_name);
        if (cur.baroque_appoggiatura.event_ref) printf("event_ref=%s ", cur.baroque_appoggiatura.event_ref);
        if (cur.baroque_appoggiatura.id) printf("id=%s ", cur.baroque_appoggiatura.id);
        if (cur.baroque_appoggiatura.style) printf("style=%s ", cur.baroque_appoggiatura.style);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.mordent.ornament_name, (const xmlChar*)"mordent")) {
        printf("%s ", cur.mordent.ornament_name);
        if (cur.mordent.event_ref) printf("event_ref=%s ", cur.mordent.event_ref);
        if (cur.mordent.id) printf("id=%s ", cur.mordent.id);
        if (cur.mordent.type) printf("type=%s ", cur.mordent.type);
        if (cur.mordent.length) printf("length=%s ", cur.mordent.length);
        if (cur.mordent.accidental) printf("accidental=%s ", cur.mordent.accidental);
        if (cur.mordent.style) printf("style=%s ", cur.mordent.style);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.tremolo.ornament_name, (const xmlChar*)"tremolo")) {
        printf("%s ", cur.tremolo.ornament_name);
        if (cur.tremolo.id) printf("id=%s ", cur.tremolo.id);
        if (cur.tremolo.start_event_ref) printf("start_event_ref=%s ", cur.tremolo.start_event_ref);
        if (cur.tremolo.end_event_ref) printf("end_event_ref=%s ", cur.tremolo.end_event_ref);
        if (cur.tremolo.tremolo_lines) printf("tremolo_lines=%i ", cur.tremolo.tremolo_lines);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.trill.ornament_name, (const xmlChar*)"trill")) {
        printf("%s ", cur.trill.ornament_name);
        if (cur.trill.event_ref) printf("event_ref=%s ", cur.trill.event_ref);
        if (cur.trill.id) printf("id=%s ", cur.trill.id);
        if (cur.trill.accidental) printf("accidental=%s ", cur.trill.accidental);
        if (cur.trill.style) printf("style=%s ", cur.trill.style);
        if (cur.trill.start_hook) printf("start_hook=%s ", cur.trill.start_hook);
        if (cur.trill.end_hook) printf("end_hook=%s ", cur.trill.end_hook);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.turn.ornament_name, (const xmlChar*)"turn")) {
        printf("%s ", cur.turn.ornament_name);
        if (cur.turn.event_ref) printf("event_ref=%s ", cur.turn.event_ref);
        if (cur.turn.id) printf("id=%s ", cur.turn.id);
        if (cur.turn.type) printf("type=%s ", cur.turn.type);
        if (cur.turn.style) printf("style=%s ", cur.turn.style);
        if (cur.turn.upper_accidental) printf("upper_accidental=%s ", cur.turn.upper_accidental);
        if (cur.turn.lower_accidental) printf("lower_accidental=%s ", cur.turn.lower_accidental);
        printf("\n");
    }
}

void printHorizontalSymbol(horizontal_symbol cur) {
    if (!xmlStrcmp(cur.arpeggio.horizontal_symbol_name,(const xmlChar*)"arpeggio")) {
        printf("%s ", cur.arpeggio.horizontal_symbol_name);
        if(cur.arpeggio.shape) printf("shape=%s ", cur.arpeggio.shape);
        if (cur.arpeggio.direction) printf("direction=%s ", cur.arpeggio.direction);
        if (cur.arpeggio.n_notehead_refs != 0) {
            struct notehead_ref* p = cur.arpeggio.notehead_ref;
            while (p) {
                printf("notehead_ref=%s ",p->event_ref);
                p = p->next_notehead_ref;
            }
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.bend.horizontal_symbol_name, (const xmlChar*)"bend")) {
        printf("%s ", cur.bend.horizontal_symbol_name);
        if (cur.bend.id) printf("id=%s ", cur.bend.id);
        if (cur.bend.event_ref) printf("event_ref=%s ", cur.bend.event_ref);
        if (cur.bend.type) printf("type=%s ", cur.bend.type);
        if (cur.bend.to_pitch) printf("to_pitch=%s ", cur.bend.to_pitch);
        if (cur.bend.to_accidental) printf("to_accidental=%s ", cur.bend.to_accidental);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.breath_mark.horizontal_symbol_name, (const xmlChar*)"breath_mark")) {
        printf("%s ", cur.breath_mark.horizontal_symbol_name);
        if (cur.breath_mark.id) printf("id=%s ", cur.breath_mark.id);
        if (cur.breath_mark.type) printf("type=%s ", cur.breath_mark.type);
        if (cur.breath_mark.staff_ref) printf("staff_ref=%s ", cur.breath_mark.staff_ref);
        if (cur.breath_mark.start_event_ref) printf("start_event_ref=%s ", cur.breath_mark.start_event_ref);
        if (cur.breath_mark.end_event_ref) printf("end_event_ref=%s ", cur.breath_mark.end_event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.chord_symbol.horizontal_symbol_name, (const xmlChar*)"chord_symbol")) {
        printf("%s ", cur.chord_symbol.horizontal_symbol_name);
        if (cur.chord_symbol.id) printf("id=%s ", cur.chord_symbol.id);
        if (cur.chord_symbol.event_ref) printf("event_ref=%s ", cur.chord_symbol.event_ref); 
        if (cur.chord_symbol.chord_symbol_value) printf("value=%s ", cur.chord_symbol.chord_symbol_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.dynamic.horizontal_symbol_name, (const xmlChar*)"dynamic")) {
        printf("%s ", cur.dynamic.horizontal_symbol_name);
        if (cur.dynamic.id) printf("id=%s ", cur.dynamic.id);
        if (cur.dynamic.extension_line_to) printf("extension_line_to=%s ", cur.dynamic.extension_line_to);
        if (cur.dynamic.extension_line_shape) printf("extension_line_shape=%s ", cur.dynamic.extension_line_shape);
        if (cur.dynamic.staff_ref) printf("staff_ref=%s ", cur.dynamic.staff_ref);
        if (cur.dynamic.event_ref) printf("event_ref=%s ", cur.dynamic.event_ref);
        if (cur.dynamic.dynamic_value) printf("value=%s ", cur.dynamic.dynamic_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.fermata.horizontal_symbol_name, (const xmlChar*)"fermata")) {
        printf("%s ", cur.fermata.horizontal_symbol_name);
        if (cur.fermata.id) printf("id=%s ", cur.fermata.id);
        if (cur.fermata.event_ref) printf("event_ref=%s ", cur.fermata.event_ref);
        if (cur.fermata.fermata_value) printf("value=%i ", cur.fermata.fermata_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.glissando.horizontal_symbol_name, (const xmlChar*)"glissando")) {
        printf("%s ", cur.glissando.horizontal_symbol_name);
        if (cur.glissando.id) printf("id=%s ", cur.glissando.id);
        if (cur.glissando.start_event_ref) printf("start_event_ref=%s ", cur.glissando.start_event_ref);
        if (cur.glissando.end_event_ref) printf("end_event_ref=%s ", cur.glissando.end_event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.hairpin.horizontal_symbol_name, (const xmlChar*)"hairpin")) {
        printf("%s ", cur.hairpin.horizontal_symbol_name);
        if (cur.hairpin.id) printf("id=%s ", cur.hairpin.id);
        if (cur.hairpin.type) printf("type=%s ", cur.hairpin.type);
        if (cur.hairpin.staff_ref) printf("staff_ref=%s ", cur.hairpin.staff_ref);
        if (cur.hairpin.start_event_ref) printf("start_event_ref=%s ", cur.hairpin.start_event_ref);
        if (cur.hairpin.end_event_ref) printf("end_event_ref=%s ", cur.hairpin.end_event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.octave_bracket.horizontal_symbol_name, (const xmlChar*)"octave_bracket")) {
        printf("%s ", cur.octave_bracket.horizontal_symbol_name);
        if (cur.octave_bracket.id) printf("id=%s ", cur.octave_bracket.id);
        if (cur.octave_bracket.type) printf("type=%s ", cur.octave_bracket.type);
        if (cur.octave_bracket.staff_ref) printf("staff_ref=%s ", cur.octave_bracket.staff_ref);
        if (cur.octave_bracket.start_event_ref) printf("start_event_ref=%s ", cur.octave_bracket.start_event_ref);
        if (cur.octave_bracket.end_event_ref) printf("end_event_ref=%s ", cur.octave_bracket.end_event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.pedal_start.horizontal_symbol_name, (const xmlChar*)"pedal_start")) {
        printf("%s ", cur.pedal_start.horizontal_symbol_name);
        if (cur.pedal_start.id) printf("id=%s ", cur.pedal_start.id);
        if (cur.pedal_start.event_ref) printf("type=%s ", cur.pedal_start.event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.pedal_end.horizontal_symbol_name, (const xmlChar*)"pedal_end")) {
        printf("%s ", cur.pedal_end.horizontal_symbol_name);
        if (cur.pedal_end.id) printf("id=%s ", cur.pedal_end.id);
        if (cur.pedal_end.event_ref) printf("type=%s ", cur.pedal_end.event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.percussion_beater.horizontal_symbol_name, (const xmlChar*)"percussion_beater")) {
        printf("%s ", cur.percussion_beater.horizontal_symbol_name);
        if (cur.percussion_beater.percussion_beater_value) printf("value=%s ", cur.percussion_beater.percussion_beater_value);
        if (cur.percussion_beater.id) printf("id=%s ", cur.percussion_beater.id);
        if (cur.percussion_beater.type) printf("type=%s ", cur.percussion_beater.type);
        if (cur.percussion_beater.start_event_ref) printf("start_event_ref=%s ", cur.percussion_beater.start_event_ref);
        if (cur.percussion_beater.end_event_ref) printf("end_event_ref=%s ", cur.percussion_beater.end_event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.percussion_special.horizontal_symbol_name, (const xmlChar*)"percussion_special")) {
    printf("%s ", cur.percussion_special.horizontal_symbol_name);
        if (cur.percussion_special.percussion_special_value) printf("value=%s ", cur.percussion_special.percussion_special_value);
        if (cur.percussion_special.id) printf("id=%s ", cur.percussion_special.id);
        if (cur.percussion_special.type) printf("type=%s ", cur.percussion_special.type);
        if (cur.percussion_special.event_ref) printf("event_ref=%s ", cur.percussion_special.event_ref);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.slur.horizontal_symbol_name, (const xmlChar*)"slur")) {
    printf("%s ", cur.slur.horizontal_symbol_name);
        if (cur.slur.id) printf("id=%s ", cur.slur.id);
        if (cur.slur.start_event_ref) printf("start_event_ref=%s ", cur.slur.start_event_ref);
        if (cur.slur.end_event_ref) printf("end_event_ref=%s ", cur.slur.end_event_ref);
        if (cur.slur.shape) printf("shape=%s ", cur.slur.shape);
        if (cur.slur.bracketed) if (cur.slur.bracketed == 1) printf("bracketed ");
        printf("\n");
    }
    else if (!xmlStrcmp(cur.special_beam.horizontal_symbol_name, (const xmlChar*)"special_beam")) {
    printf("%s ", cur.special_beam.horizontal_symbol_name);
        if (cur.special_beam.id) printf("id=%s ", cur.special_beam.id);
        if (cur.special_beam.fanned_from) printf("fanned_from=%s ", cur.special_beam.fanned_from);
        if (cur.special_beam.fanned_to) printf("fanned_to=%s ", cur.special_beam.fanned_to);
        if (cur.special_beam.n_notehead_refs != 0) {
            struct notehead_ref* p = cur.special_beam.notehead_ref;
            while (p) {
                printf("notehead_ref=%s ", p->event_ref);
                p = p->next_notehead_ref;
            }
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.tablature_hsymbol.horizontal_symbol_name, (const xmlChar*)"tablature_hsymbol")) {
    printf("%s ", cur.tablature_hsymbol.horizontal_symbol_name);
        if (cur.tablature_hsymbol.id) printf("id=%s ", cur.tablature_hsymbol.id);
        if (cur.tablature_hsymbol.event_ref) printf("event_ref=%s ", cur.tablature_hsymbol.event_ref);
        if (cur.tablature_hsymbol.string_number) printf("string_number=%i ", cur.tablature_hsymbol.string_number);
        if (cur.tablature_hsymbol.start_fret) printf("start_fret=%s ", cur.tablature_hsymbol.start_fret);
        if (cur.tablature_hsymbol.fret_number) printf("fret_number=%i ", cur.tablature_hsymbol.fret_number);
        if (cur.tablature_hsymbol.n_barres != 0) {
            struct barre* p = cur.tablature_hsymbol.barre;
            printf("[ Barre: ");
            while (p) {
                if (p->start_string_position) printf("start_string_position=%s ", p->start_string_position);
                if (p->end_string_position) printf("end_string_position=%s ", p->end_string_position);
                if (p->fret_position) printf("fret_position=%s ", p->fret_position);
                p = p->next_barre;
            }
            printf("] ");
        }
        if (cur.tablature_hsymbol.n_tablature_elements!= 0) {
            struct tablature_element* p = cur.tablature_hsymbol.tablature_element;
            printf("[ Tablature Element: ");
            while (p) {
                if (p->shape) printf("start_string_position=%s ", p->shape);
                if (p->string_position) printf("end_string_position=%s ", p->string_position);
                if (p->fret_position) printf("fret_position=%s ", p->fret_position);
                p = p->next_tablature_element;
            }
            printf("] ");
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.repeat.horizontal_symbol_name, (const xmlChar*)"repeat")) {
    printf("%s ", cur.repeat.horizontal_symbol_name);
        if (cur.repeat.id) printf("id=%s ", cur.repeat.id);
        if (cur.repeat.event_ref) printf("event_ref=%s ", cur.repeat.event_ref);
        if (cur.repeat.repeat_text) printf("repeat_text=%s ", cur.repeat.repeat_text);
        if (cur.repeat.n_jump_tos != 0) {
            struct jump_to* p = cur.repeat.jump_to;
            printf("[ Jump To: ");
            while (p) {
                if (p->id) printf("id=%s ", p->id);
                if (p->event_ref) printf("event_ref=%s ", p->event_ref);
                p = p->next_jump_to;
            }
            printf("] ");
        }
        if (cur.repeat.n_ends != 0) {
            struct end* p = cur.repeat.end;
            printf("[ End: ");
            while (p) {
                if (p->id) printf("id=%s ", p->id);
                if (p->event_ref) printf("event_ref=%s ", p->event_ref);
                p = p->next_end;
            }
            printf("] ");
        }
        printf("\n");
    }
    else if (!xmlStrcmp(cur.segno.horizontal_symbol_name, (const xmlChar*)"segno")) {
    printf("%s ", cur.segno.horizontal_symbol_name);
        if (cur.segno.id) printf("id=%s ", cur.segno.id);
        if (cur.segno.event_ref) printf("event_ref=%s ", cur.segno.event_ref);
        if (cur.segno.segno_value) printf("value=%s ", cur.segno.segno_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.coda.horizontal_symbol_name, (const xmlChar*)"coda")) {
    printf("%s ", cur.coda.horizontal_symbol_name);
        if (cur.coda.id) printf("id=%s ", cur.coda.id);
        if (cur.coda.event_ref) printf("event_ref=%s ", cur.coda.event_ref);
        if (cur.coda.coda_value) printf("value=%s ", cur.coda.coda_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.fine.horizontal_symbol_name, (const xmlChar*)"fine")) {
    printf("%s ", cur.fine.horizontal_symbol_name);
        if (cur.fine.id) printf("id=%s ", cur.fine.id);
        if (cur.fine.event_ref) printf("event_ref=%s ", cur.fine.event_ref);
        if (cur.fine.fine_value) printf("value=%s ", cur.fine.fine_value);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.multiple_endings.horizontal_symbol_name, (const xmlChar*)"multiple_endings")) {
    printf("%s ", cur.multiple_endings.horizontal_symbol_name);
        if (cur.multiple_endings.id) printf("id=%s ", cur.multiple_endings.id);
        printf("\n");
    }
    else if (!xmlStrcmp(cur.custom_hsymbol.horizontal_symbol_name, (const xmlChar*)"custom_hsymbol")) {
    printf("%s ", cur.custom_hsymbol.horizontal_symbol_name);
        if (cur.custom_hsymbol.id) printf("id=%s ", cur.custom_hsymbol.id);
        if (cur.custom_hsymbol.start_event_ref) printf("start_event_ref=%s ", cur.custom_hsymbol.start_event_ref);
        if (cur.custom_hsymbol.end_event_ref) printf("end_event_ref=%s ", cur.custom_hsymbol.end_event_ref);
        printf("\n");
    }
}

void freeLogicLayer(struct logic cur) {
    if (cur.spine && cur.n_events!=0) {
        freeEventsList(cur.spine);
        cur.spine = NULL;
    }

    if (cur.los.staff_list && cur.los.n_staves != 0) {
        freeStavesList(cur.los.staff_list);
        cur.los.staff_list = NULL;
    }
    if (cur.los.staff_list_bracket && cur.los.n_brackets) {
        freeBracketsList(cur.los.staff_list_bracket);
        cur.los.staff_list_bracket = NULL;
    }
    if (cur.los.horizontal_symbols && cur.los.n_horizontal_symbols) {
        freeHorizontalSymbolsList(cur.los.horizontal_symbols);
        cur.los.horizontal_symbols = NULL;
    }
    if (cur.los.ornaments && cur.los.n_ornaments) {
        freeOrnamentsList(cur.los.ornaments);
        cur.los.ornaments = NULL;
    }
    if (cur.los.agogics && cur.los.n_agogics) {
        freeAgogicsList(cur.los.agogics);
        cur.los.agogics = NULL;
    }
    if (cur.los.text_field && cur.los.n_text_fields) {
        freeTextFieldsList(cur.los.text_field);
        cur.los.text_field = NULL;
    }
    if (cur.los.metronomic_indication && cur.los.n_metronomic_indications) {
        freeMetronomicIndicationsList(cur.los.metronomic_indication);
        cur.los.metronomic_indication = NULL;
    }
    if (cur.los.lyrics && cur.los.n_lyrics) {
        freeLyricsList(cur.los.lyrics);
        cur.los.lyrics = NULL;
    }
    if (cur.los.part && cur.los.n_parts) {
        freePartsList(cur.los.part);
        cur.los.part = NULL;
    }

    if (cur.layout.page && cur.layout.n_pages) {
        freePagesList(cur.layout.page);
        cur.layout.page = NULL;
    }

}


void freeEventsList(struct event* head) {
    struct event* temp;
    while (head) {
        temp = head;
        head = head->next_event;
        free(temp);
    }
}

void freeAgogicsList(struct agogics* head) {
    struct agogics* temp;
    while (head) {
        temp = head;
        head = head->next_agogics;
        free(temp);
    }
}

void freeTextFieldsList(struct text_field* head) {
    struct text_field* temp;
    while (head) {
        temp = head;
        head = head->next_text_field;
        free(temp);
    }
}

void freeMetronomicIndicationsList(struct metronomic_indication* head) {
    struct metronomic_indication* temp;
    while (head) {
        temp = head;
        head = head->next_metronomic_indication;
        free(temp);
    }
}

void freeHorizontalSymbolsList(struct horizontal_symbol_list* head) {
    struct horizontal_symbol_list* temp;
    while (head) {
        temp = head;
        head = head->next_horizontal_symbol;
        freeHorizontalSymbolLists(temp->horizontal_symbol_value);
        free(temp);
    }
}

void freeOrnamentsList(struct ornament_list* head) {
    struct ornament_list* temp;
    while (head) {
        temp = head;
        head = head->next_ornament;
        freeOrnamentLists(temp->ornament_value);
        free(temp);
    }
}

void freeSyllablesList(struct syllable* head) {
    struct syllable* temp;
    while (head) {
        temp = head;
        head = head->next_syllable;
        free(temp);
    }
}

void freeLyricsList(struct lyrics* head) {
    struct lyrics* temp;
    while (head) {
        temp = head;
        head = head->next_lyrics;

        if (temp->syllable)
            freeSyllablesList(temp->syllable);

        free(temp);
    }
}

void freePartsList(struct part* head) {
    struct part* temp;
    while (head) {
        temp = head;
        head = head->next_part;

        if (temp->voice_list)
            freeVoiceItemsList(temp->voice_list);
        if (temp->measure)
            freeMeasuresList(temp->measure);

        free(temp);
    }
}


void freeBracketsList(struct brackets* head) {
    struct brackets* temp;
    while (head) {
        temp = head;
        head = head->next_brackets;
        free(temp);
    }
}

void freeStavesList(struct staff* head) {
    struct staff* temp;
    while (head) {
        temp = head;
        head = head->next_staff;

        if (temp->clef)
            freeClefsList(temp->clef);
        if (temp->key_signature)
            freeKeySignaturesList(temp->key_signature);
        if (temp->custom_key_signature)
            freeCustomKeySignaturesList(temp->custom_key_signature);
        if (temp->time_signature)
            freeTimeSignaturesList(temp->time_signature);
        if (temp->barline)
            freeBarlinesList(temp->barline);
        if (temp->tablature_tuning)
            freeTablatureTuningsList(temp->tablature_tuning);

        free(temp);
    }
}

void freeLayoutShapesList(struct layout_shapes* head) {
    struct layout_shapes* temp;
    while (head) {
        temp = head;
        head = head->next_layout_shapes;
        free(temp);
    }
}

void freeLayoutImagesList(struct layout_images* head) {
    struct layout_images* temp;
    while (head) {
        temp = head;
        head = head->next_layout_images;
        free(temp);
    }
}

void freeLayoutStavesList(struct layout_staff* head) {
    struct layout_staff* temp;
    while (head) {
        temp = head;
        head = head->next_layout_staff;
        free(temp);
    }
}

void freeLayoutSystemsList(struct layout_system* head) {
    struct layout_system* temp;
    while (head) {
        temp = head;
        head = head->next_layout_system;

        if (temp->layout_staff)
            freeLayoutStavesList(temp->layout_staff);

        free(temp);
    }
}

void freePagesList(struct page* head) {
    struct page* temp;
    while (head) {
        temp = head;
        head = head->next_page;

        if (temp->layout_system)
            freeLayoutSystemsList(temp->layout_system);
        if (temp->layout_images_list)
            freeLayoutImagesList(temp->layout_images_list);
        if (temp->layout_shapes_list)
            freeLayoutShapesList(temp->layout_shapes_list);

        free(temp);
    }
}
