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
    loadLayout();
}

void printLogic(){  
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
    xmlNodePtr temp_cur;
    xmlAttr *attributes;
    
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
    
    struct syllable* syllable_head=NULL;
    struct syllable* syllable_temp=NULL;
    struct syllable* syllable_p=NULL;
    
    struct horizontal_symbol_list* horizontal_symbol_list_head=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_temp=NULL;
    struct horizontal_symbol_list* horizontal_symbol_list_p=NULL;
    
    struct ornament_list* ornament_list_head=NULL;
    struct ornament_list* ornament_list_temp=NULL;
    struct ornament_list* ornament_list_p=NULL;
    
    struct part* part_temp=NULL;
    struct part* part_head=NULL;
    struct part* part_p=NULL;
    
    struct voice_item* voice_item_temp=NULL;
    struct voice_item* voice_item_head=NULL;
    struct voice_item* voice_item_p=NULL;
    
    struct measure* measure_temp=NULL;
    struct measure* measure_head=NULL;
    struct measure* measure_p=NULL;
    
    struct brackets* brackets_temp=NULL;
    struct brackets* brackets_head=NULL;
    struct brackets* brackets_p=NULL;

    struct staff* staff_temp=NULL;
    struct staff* staff_head=NULL;
    struct staff* staff_p=NULL;
    
    struct clef* clef_temp=NULL;
    struct clef* clef_head=NULL;
    struct clef* clef_p=NULL;
    
    struct key_signature* key_signature_temp=NULL;
    struct key_signature* key_signature_head=NULL;
    struct key_signature* key_signature_p=NULL;
    
    struct custom_key_signature* custom_key_signature_temp=NULL;
    struct custom_key_signature* custom_key_signature_head=NULL;
    struct custom_key_signature* custom_key_signature_p=NULL;
    
    struct time_signature* time_signature_temp=NULL;
    struct time_signature* time_signature_head=NULL;
    struct time_signature* time_signature_p=NULL;
    
    struct barline* barline_temp=NULL;
    struct barline* barline_head=NULL;
    struct barline* barline_p=NULL;
    
    struct tablature_tuning* tablature_tuning_temp=NULL;
    struct tablature_tuning* tablature_tuning_head=NULL;
    struct tablature_tuning* tablature_tuning_p=NULL;
    
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
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"brackets")){
                        brackets_temp=(struct brackets*)malloc(sizeof(struct brackets));
                        brackets_temp=calloc(1,sizeof(struct brackets));                             
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
                        staff_temp=(struct staff*)malloc(sizeof(struct staff));
                        staff_temp=calloc(1,sizeof(struct staff)); 
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
                                staff_temp->ossia=xmlGetProp(temp_cur,attributes->name);
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
                                do{
                                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"clef")){
                                        clef_temp=(struct clef*)malloc(sizeof(struct clef));
                                        clef_temp=calloc(1,sizeof(struct clef));
                                        //cleff_temp=loadCleffValue(temp_cur);
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
                                        key_signature_temp=(struct key_signature*)malloc(sizeof(struct key_signature));
                                        key_signature_temp=calloc(1,sizeof(struct key_signature));
                                        //key_signature_temp=loadKeySignatureValue(temp_cur);
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
                                        custom_key_signature_temp=(struct custom_key_signature*)malloc(sizeof(struct custom_key_signature));
                                        custom_key_signature_temp=calloc(1,sizeof(struct custom_key_signature));
                                        //custom_key_signature_temp=loadCustomKeySignatureValue(temp_cur);
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
                                        time_signature_temp=(struct time_signature*)malloc(sizeof(struct time_signature));
                                        time_signature_temp=calloc(1,sizeof(struct time_signature));
                                        //time_signature_temp=loadTimeSignatureValue(temp_cur);
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
                                        barline_temp=(struct barline*)malloc(sizeof(struct barline));
                                        barline_temp=calloc(1,sizeof(struct barline));
                                        //cleff_temp=loadBarlineValue(temp_cur);
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
                                        tablature_tuning_temp=(struct tablature_tuning*)malloc(sizeof(struct tablature_tuning));
                                        tablature_tuning_temp=calloc(1,sizeof(struct tablature_tuning));
                                        //tablature_tuning_temp=loadTablatureTuningValue(temp_cur);
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
                                    temp_cur=temp_cur->next;
                                }while(temp_cur->next!=NULL);
                            }
                            temp_cur=temp_cur->parent;
                        }
                        //end scanning elements of staff
                        staff_temp->clefs=clef_head;
                        staff_temp->key_signatures=key_signature_head;
                        staff_temp->custom_key_singatures=custom_key_signature_head;
                        staff_temp->time_signatures=time_signature_head;
                        staff_temp->barlines=barline_head;
                        staff_temp->tablature_tunings=tablature_tuning_head;
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
                part_temp=(struct part*)malloc(sizeof(struct part));
                part_temp=calloc(1,sizeof(struct part));
                part_temp->n_voice_items=0;
                part_temp->n_measures=0;
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                        part_temp->id=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"performers_number")){
                        part_temp->performes_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"transposition_pitch")){
                        part_temp->transposition_pitch=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"transposition_accidental")){
                        //part_temp->transposition_accidental=xmlGetProp(cur,attributes->name);
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
                                        voice_item_temp=(struct voice_item*)malloc(sizeof(struct voice_item));
                                        voice_item_temp=calloc(1,sizeof(struct voice_item));
                                        //voice_item_temp=loadVoiceItemValue(temp_cur);
                                        voice_item_temp->next_voice_item=NULL;
                                        if(voice_item_head==NULL){
                                            voice_item_head=voice_item_temp;
                                        }
                                        else{
                                            voice_item_p=voice_item_head;
                                            while(voice_item_p->next_voice_item!=NULL)
                                                voice_item_p=voice_item_p->next_voice_item;
                                            voice_item_p->next_voice_item=voice_item_temp;
                                        }
                                        part_temp->n_voice_items++;
                                    }
                                    temp_cur=temp_cur->next;
                                }while(temp_cur->next!=NULL);
                                part_temp->voice_list=voice_item_head;
                            }
                        temp_cur=temp_cur->parent;//l'ultimo é null
                        }
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"measure")){
                        measure_temp=(struct measure*)malloc(sizeof(struct measure));
                        measure_temp=calloc(1,sizeof(struct measure));
                        //measure_temp=loadMeasureValue(temp_cur);
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
                part_temp->measures=measure_head;
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
                        horizontal_symbol_list_temp=(struct horizontal_symbol_list*)malloc(sizeof(struct horizontal_symbol_list));
                        horizontal_symbol_list_temp=calloc(1,sizeof(struct horizontal_symbol_list));          
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
                ornament_list_temp=(struct ornament_list*)malloc(sizeof(struct ornament_list));
                ornament_list_temp=calloc(1,sizeof(struct ornament_list));
                temp_cur=cur->xmlChildrenNode;
                while(temp_cur!=NULL){
                    if(xmlStrcmp(temp_cur->name,(const xmlChar*)"text")&&xmlStrcmp(temp_cur->name,(const xmlChar*)"comment")){
                        //ornament_list_temp->ornament_value=loadOrnamentValue(temp_cur);
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
                        syllable_temp=(struct syllable*)malloc(sizeof(struct syllable));
                        syllable_temp=calloc(1,sizeof(struct syllable));
                        attributes=temp_cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                                //lyrics_temp->part_ref=xmlGetProp(temp_cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                                //lyrics_temp->voice_ref=xmlGetProp(temp_cur,attributes->name);
                            } 
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hyphen")){
                                syllable_temp->hyphen=xmlGetProp(temp_cur,attributes->name);
                            } 
                            attributes=attributes->next;                     
                        }
                        syllable_temp->syllable_value=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
                        syllable_temp->next_syllable=NULL;
                        if(syllable_head==NULL){
                            syllable_head=syllable_temp;
                        }
                        else{
                            syllable_p=syllable_head;
                            while(syllable_p->next_syllable!=NULL)
                                syllable_p=syllable_p->next_syllable;
                            syllable_p->next_syllable=syllable_temp;
                        } 
                        lyrics_temp->n_syllables++;
                    }
                    temp_cur=temp_cur->next;
                }//end while syllable in lyrics
                lyrics_temp->syllables=syllable_head;
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
        
        logic_layer.los.agogics=agogic_head;
        logic_layer.los.text_field=text_field_head;
        logic_layer.los.metronomic_indication=metronomic_indication_head;
        logic_layer.los.staff_list=staff_head;
        logic_layer.los.staff_list_brackets=brackets_head;
        logic_layer.los.horizontal_symbols=horizontal_symbol_list_head;
        logic_layer.los.ornaments=ornament_list_head;
        logic_layer.los.lyrics=lyrics_head;
        logic_layer.los.part=part_head;
        
    }//end if nodeset not empty
}

void printLos(){

}

void loadLayout(){

}

void printLayout(){

}