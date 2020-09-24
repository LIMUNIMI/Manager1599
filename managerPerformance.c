/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerPerformance.h"

void loadPerformance(){
    loadMidiInstance();
    loadCsoundInstance();
    loadMpeg4Instance();
}

void loadMidiInstance(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct midi_instance* midi_instance_temp=NULL;
    struct midi_instance* midi_instance_head=NULL;
    struct midi_instance* midi_instance_p=NULL;
    performance_layer.n_midi_instances=0;
    
    xpath=(xmlChar *)"/ieee1599/performance/midi_instance";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning midi_instances 

            midi_instance_temp=(struct midi_instance*)malloc(sizeof(struct midi_instance));
            midi_instance_temp=calloc(1,sizeof(struct midi_instance));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;         
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
                    midi_instance_temp->file_name=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"format")){
                    midi_instance_temp->format=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            //load midi_instances elements
            struct midi_mapping* midi_mapping_temp=NULL;
            struct midi_mapping* midi_mapping_head=NULL;
            struct midi_mapping* midi_mapping_p=NULL;
            midi_instance_temp->n_midi_mappings=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"midi_mapping")){
                    midi_mapping_temp=(struct midi_mapping*)malloc(sizeof(struct midi_mapping));
                    midi_mapping_temp=calloc(1,sizeof(struct midi_mapping));

                    midi_mapping_temp=loadMidiMapping(temp_cur);
                                     
                    midi_mapping_temp->next_midi_mapping=NULL;
                    if(midi_mapping_head==NULL)
                        midi_mapping_head=midi_mapping_temp;
                    else{
                        midi_mapping_p=midi_mapping_head;
                        while(midi_mapping_p->next_midi_mapping!=NULL)
                            midi_mapping_p=midi_mapping_p->next_midi_mapping;
                        midi_mapping_p->next_midi_mapping=midi_mapping_temp;
                    }
                    midi_instance_temp->n_midi_mappings++;
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"rights")){
                    midi_instance_temp->rights=loadRights(temp_cur);
                }
                temp_cur=temp_cur->next;
            }
            midi_instance_temp->midi_mappings=midi_mapping_head;
            
            midi_instance_temp->next_midi_instance=NULL;
            if(midi_instance_head==NULL)
                midi_instance_head=midi_instance_temp;
            else{
                midi_instance_p=midi_instance_head;
                while(midi_instance_p->next_midi_instance!=NULL)
                    midi_instance_p=midi_instance_p->next_midi_instance;
                midi_instance_p->next_midi_instance=midi_instance_temp;
            }
            performance_layer.n_midi_instances++;
        }
        performance_layer.midi_instance=midi_instance_head;
    }	
}

struct midi_mapping* loadMidiMapping(xmlNodePtr cur){
    struct midi_mapping* value=(struct midi_mapping*)malloc(sizeof(struct midi_mapping));
    value=calloc(1,sizeof(struct midi_mapping));
    xmlAttr* attributes;

    struct midi_event_sequence* midi_event_sequence_temp=NULL;
    struct midi_event_sequence* midi_event_sequence_head=NULL;
    struct midi_event_sequence* midi_event_sequence_p=NULL;
    value->n_midi_event_sequences=0;

    value->next_midi_mapping=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
            value->part_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
            value->part_ref =xmlGetProp(cur,attributes->name);   
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"track")){
            value->track=xmlGetProp(cur,attributes->name);        
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"channel")){
            value->channel=xmlGetProp(cur,attributes->name);        
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"midi_event_sequence")){
            midi_event_sequence_temp=(struct midi_event_sequence*)malloc(sizeof(struct midi_event_sequence));
            midi_event_sequence_temp=calloc(1, sizeof(struct midi_event_sequence*));

            midi_event_sequence_temp=loadMidiEventSequence(cur); 
                        
            midi_event_sequence_temp->next_midi_event_sequence=NULL;
            if(midi_event_sequence_head==NULL)
                midi_event_sequence_head=midi_event_sequence_temp;
            else{
                midi_event_sequence_p=midi_event_sequence_head;
                while(midi_event_sequence_p->next_midi_event_sequence!=NULL)
                    midi_event_sequence_p=midi_event_sequence_p->next_midi_event_sequence;
                midi_event_sequence_p->next_midi_event_sequence=midi_event_sequence_temp;
            }
            value->n_midi_event_sequences++;
        }
        cur=cur->next;
    }
    value->midi_event_sequences=midi_event_sequence_head;
    
    return value;
}

struct midi_event_sequence* loadMidiEventSequence(xmlNodePtr cur){
    struct midi_event_sequence* value=(struct midi_event_sequence*)malloc(sizeof(struct midi_event_sequence));
    value=calloc(1,sizeof(struct midi_event_sequence));
    xmlAttr* attributes;

    struct midi_event* midi_event_temp=NULL;
    struct midi_event* midi_event_head=NULL;
    struct midi_event* midi_event_p=NULL;
    value->n_midi_events=0;
    
    struct sys_ex* sys_ex_temp=NULL;
    struct sys_ex* sys_ex_head=NULL;
    struct sys_ex* sys_ex_p=NULL;
    value->n_sys_exs=0;

    value->next_midi_event_sequence=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"division_type")){
            value->division_type=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"division_value")){
            value->division_value =xmlGetProp(cur,attributes->name);   
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"measurement_unit")){
            value->measurement_unit=xmlGetProp(cur,attributes->name);        
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"midi_event")){
            midi_event_temp=(struct midi_event*)malloc(sizeof(struct midi_event));
            midi_event_temp=calloc(1, sizeof(struct midi_event*));

            midi_event_temp=loadMidiEvent(cur); 
                        
            midi_event_temp->next_midi_event=NULL;
            if(midi_event_head==NULL)
                midi_event_head=midi_event_temp;
            else{
                midi_event_p=midi_event_head;
                while(midi_event_p->next_midi_event!=NULL)
                    midi_event_p=midi_event_p->next_midi_event;
                midi_event_p->next_midi_event=midi_event_temp;
            }
            value->n_midi_events++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"sys_ex")){
            sys_ex_temp=(struct sys_ex*)malloc(sizeof(struct sys_ex));
            sys_ex_temp=calloc(1, sizeof(struct sys_ex*));

            sys_ex_temp=loadSysEx(cur); 
                        
            sys_ex_temp->next_sys_ex=NULL;
            if(sys_ex_head==NULL)
                sys_ex_head=sys_ex_temp;
            else{
                sys_ex_p=sys_ex_head;
                while(sys_ex_p->next_sys_ex!=NULL)
                    sys_ex_p=sys_ex_p->next_sys_ex;
                sys_ex_p->next_sys_ex=sys_ex_temp;
            }
            value->n_sys_exs++;
        }  
        cur=cur->next;
    }
    value->midi_events=midi_event_head;
    value->sys_exs=sys_ex_head;
    
    return value;
}

struct midi_event* loadMidiEvent(xmlNodePtr cur){
    struct midi_event* value=(struct midi_event*)malloc(sizeof(struct midi_event));
    value=calloc(1,sizeof(struct midi_event));
    xmlAttr* attributes;
    
    value->next_midi_event=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"timing")){
            value->timing=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
            //value->spine_ref =xmlGetProp(cur,attributes->name);   
        }
        attributes=attributes->next;
    }
    
    //caricamento (%MIDIChannelMessage;)*
    
    return value;
}

struct sys_ex* loadSysEx(xmlNodePtr cur){
    struct sys_ex* value=(struct sys_ex*)malloc(sizeof(struct sys_ex));
    value=calloc(1,sizeof(struct sys_ex));
    xmlAttr* attributes;
    
    value->next_sys_ex=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
            //value->spine_ref =xmlGetProp(cur,attributes->name);   
        }
        attributes=attributes->next;
    }
    
    //caricamento (SysEx)
    
    return value;
}

void loadCsoundInstance(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct csound_instance* csound_instance_temp=NULL;
    struct csound_instance* csound_instance_head=NULL;
    struct csound_instance* csound_instance_p=NULL;
    performance_layer.n_csound_instances=0;
    
    xpath=(xmlChar *)"/ieee1599/performance/csound_instance";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning csound_instance 

            csound_instance_temp=(struct csound_instance*)malloc(sizeof(struct csound_instance));
            csound_instance_temp=calloc(1,sizeof(struct csound_instance));
            cur=nodeset->nodeTab[i];

            //load csound_instance elements
            struct csound_score* csound_score_temp=NULL;
            struct csound_score* csound_score_head=NULL;
            struct csound_score* csound_score_p=NULL;
            csound_instance_temp->n_csound_scores=0;
            
            struct csound_orchestra* csound_orchestra_temp=NULL;
            struct csound_orchestra* csound_orchestra_head=NULL;
            struct csound_orchestra* csound_orchestra_p=NULL;
            csound_instance_temp->n_csound_orchestras=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"csound_score")){
                    csound_score_temp=(struct csound_score*)malloc(sizeof(struct csound_score));
                    csound_score_temp=calloc(1,sizeof(struct csound_score));

                    csound_score_temp=loadCsoundScore(temp_cur);
                                     
                    csound_score_temp->next_csound_score=NULL;
                    if(csound_score_head==NULL)
                        csound_score_head=csound_score_temp;
                    else{
                        csound_score_p=csound_score_head;
                        while(csound_score_p->next_csound_score!=NULL)
                            csound_score_p=csound_score_p->next_csound_score;
                        csound_score_p->next_csound_score=csound_score_temp;
                    }
                    csound_instance_temp->n_csound_scores++;
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"csound_orchestra")){
                    csound_orchestra_temp=(struct csound_orchestra*)malloc(sizeof(struct csound_orchestra));
                    csound_orchestra_temp=calloc(1,sizeof(struct csound_orchestra));

                    csound_orchestra_temp=loadCsoundOrchestra(temp_cur);
                                     
                    csound_orchestra_temp->next_csound_orchestra=NULL;
                    if(csound_orchestra_head==NULL)
                        csound_orchestra_head=csound_orchestra_temp;
                    else{
                        csound_orchestra_p=csound_orchestra_head;
                        while(csound_orchestra_p->next_csound_orchestra!=NULL)
                            csound_orchestra_p=csound_orchestra_p->next_csound_orchestra;
                        csound_orchestra_p->next_csound_orchestra=csound_orchestra_temp;
                    }
                    csound_instance_temp->n_csound_orchestras++;
                }
                temp_cur=temp_cur->next;
            }
            csound_instance_temp->csound_scores=csound_score_head;
            csound_instance_temp->csound_orchestras=csound_orchestra_head;
                    
            csound_instance_temp->next_csound_instance=NULL;
            if(csound_instance_head==NULL)
                csound_instance_head=csound_instance_temp;
            else{
                csound_instance_p=csound_instance_head;
                while(csound_instance_p->next_csound_instance!=NULL)
                    csound_instance_p=csound_instance_p->next_csound_instance;
                csound_instance_p->next_csound_instance=csound_instance_temp;
            }
            performance_layer.n_csound_instances++;
        }
        performance_layer.csound_instance=csound_instance_head;
    }	
}

struct csound_score* loadCsoundScore(xmlNodePtr cur){
    struct csound_score* value=(struct csound_score*)malloc(sizeof(struct csound_score));
    value=calloc(1,sizeof(struct csound_score));
    xmlAttr* attributes;

    struct csound_spine_event* csound_spine_event_temp=NULL;
    struct csound_spine_event* csound_spine_event_head=NULL;
    struct csound_spine_event* csound_spine_event_p=NULL;
    value->n_csound_spine_events=0;

    value->next_csound_score=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"csound_spine_event")){
            csound_spine_event_temp=(struct csound_spine_event*)malloc(sizeof(struct csound_spine_event));
            csound_spine_event_temp=calloc(1, sizeof(struct csound_spine_event*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"line_number")){
                    csound_spine_event_temp->line_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //csound_spine_event_temp->spine_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            csound_spine_event_temp->next_csound_spine_event=NULL;
            if(csound_spine_event_head==NULL)
                csound_spine_event_head=csound_spine_event_temp;
            else{
                csound_spine_event_p=csound_spine_event_head;
                while(csound_spine_event_p->next_csound_spine_event!=NULL)
                    csound_spine_event_p=csound_spine_event_p->next_csound_spine_event;
                csound_spine_event_p->next_csound_spine_event=csound_spine_event_temp;
            }
            value->n_csound_spine_events++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"rights")){
            value->rights=loadRights(cur);
        }  
        cur=cur->next;
    }
    value->csound_spine_events=csound_spine_event_head;
    
    return value;
}

struct csound_orchestra* loadCsoundOrchestra(xmlNodePtr cur){
    struct csound_orchestra* value=(struct csound_orchestra*)malloc(sizeof(struct csound_orchestra));
    value=calloc(1,sizeof(struct csound_orchestra));
    xmlAttr* attributes;

    struct csound_instrument_mapping* csound_instrument_mapping_temp=NULL;
    struct csound_instrument_mapping* csound_instrument_mapping_head=NULL;
    struct csound_instrument_mapping* csound_instrument_mapping_p=NULL;
    value->n_csound_instrument_mappings=0;

    value->next_csound_orchestra=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"csound_instrument_mapping")){
            csound_instrument_mapping_temp=(struct csound_instrument_mapping*)malloc(sizeof(struct csound_instrument_mapping));
            csound_instrument_mapping_temp=calloc(1, sizeof(struct csound_instrument_mapping*));
            
            csound_instrument_mapping_temp=loadCsoundInstrumentMapping(cur);
                        
            csound_instrument_mapping_temp->next_csound_instrument_mapping=NULL;
            if(csound_instrument_mapping_head==NULL)
                csound_instrument_mapping_head=csound_instrument_mapping_temp;
            else{
                csound_instrument_mapping_p=csound_instrument_mapping_head;
                while(csound_instrument_mapping_p->next_csound_instrument_mapping!=NULL)
                    csound_instrument_mapping_p=csound_instrument_mapping_p->next_csound_instrument_mapping;
                csound_instrument_mapping_p->next_csound_instrument_mapping=csound_instrument_mapping_temp;
            }
            value->n_csound_instrument_mappings++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"rights")){
            value->rights=loadRights(cur);
        }  
        cur=cur->next;
    }
    value->csound_instrument_mappings=csound_instrument_mapping_head;
    
    return value;
}

struct csound_instrument_mapping* loadCsoundInstrumentMapping(xmlNodePtr cur){
    struct csound_instrument_mapping* value=(struct csound_instrument_mapping*)malloc(sizeof(struct csound_instrument_mapping));
    value=calloc(1,sizeof(struct csound_instrument_mapping));
    xmlAttr* attributes;

    struct csound_part_ref* csound_part_ref_temp=NULL;
    struct csound_part_ref* csound_part_ref_head=NULL;
    struct csound_part_ref* csound_part_ref_p=NULL;
    value->n_csound_part_refs=0;
    
    struct csound_spine_ref* csound_spine_ref_temp=NULL;
    struct csound_spine_ref* csound_spine_ref_head=NULL;
    struct csound_spine_ref* csound_spine_ref_p=NULL;
    value->n_csound_spine_refs=0;

    value->next_csound_instrument_mapping=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"instrument_number")){
            value->instrument_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_line")){
            value->start_line=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_line")){
            value->end_line=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"pnml_file")){
            value->pnml_file=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"csound_part_ref")){
            csound_part_ref_temp=(struct csound_part_ref*)malloc(sizeof(struct csound_part_ref));
            csound_part_ref_temp=calloc(1, sizeof(struct csound_part_ref*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
                    csound_part_ref_temp->part_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            csound_part_ref_temp->next_csound_part_ref=NULL;
            if(csound_part_ref_head==NULL)
                csound_part_ref_head=csound_part_ref_temp;
            else{
                csound_part_ref_p=csound_part_ref_head;
                while(csound_part_ref_p->next_csound_part_ref!=NULL)
                    csound_part_ref_p=csound_part_ref_p->next_csound_part_ref;
                csound_part_ref_p->next_csound_part_ref=csound_part_ref_temp;
            }
            value->n_csound_part_refs++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"csound_spine_ref")){
            csound_spine_ref_temp=(struct csound_spine_ref*)malloc(sizeof(struct csound_spine_ref));
            csound_spine_ref_temp=calloc(1, sizeof(struct csound_spine_ref*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //csound_spine_ref_temp->spine_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            csound_spine_ref_temp->next_csound_spine_ref=NULL;
            if(csound_spine_ref_head==NULL)
                csound_spine_ref_head=csound_spine_ref_temp;
            else{
                csound_spine_ref_p=csound_spine_ref_head;
                while(csound_spine_ref_p->next_csound_spine_ref!=NULL)
                    csound_spine_ref_p=csound_spine_ref_p->next_csound_spine_ref;
                csound_spine_ref_p->next_csound_spine_ref=csound_spine_ref_temp;
            }
            value->n_csound_spine_refs++;
        }  
        cur=cur->next;
    }
    value->csound_part_refs=csound_part_ref_head;
    value->csound_spine_refs=csound_spine_ref_head;
    
    return value;
}
    
void loadMpeg4Instance(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct mpeg4_instance* mpeg4_instance_temp=NULL;
    struct mpeg4_instance* mpeg4_instance_head=NULL;
    struct mpeg4_instance* mpeg4_instance_p=NULL;
    performance_layer.n_mpeg4_instances=0;
    
    xpath=(xmlChar *)"/ieee1599/performance/mpeg4_instance";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning mpeg4_instances 

            mpeg4_instance_temp=(struct mpeg4_instance*)malloc(sizeof(struct mpeg4_instance));
            mpeg4_instance_temp=calloc(1,sizeof(struct mpeg4_instance));
            cur=nodeset->nodeTab[i];

            //load mpeg4_instance elements
            struct mpeg4_score* mpeg4_score_temp=NULL;
            struct mpeg4_score* mpeg4_score_head=NULL;
            struct mpeg4_score* mpeg4_score_p=NULL;
            mpeg4_instance_temp->n_mpeg4_scores=0;
            
            struct mpeg4_orchestra* mpeg4_orchestra_temp=NULL;
            struct mpeg4_orchestra* mpeg4_orchestra_head=NULL;
            struct mpeg4_orchestra* mpeg4_orchestra_p=NULL;
            mpeg4_instance_temp->mpeg4_orchestras=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"mpeg4_score")){
                    mpeg4_score_temp=(struct mpeg4_score*)malloc(sizeof(struct mpeg4_score));
                    mpeg4_score_temp=calloc(1,sizeof(struct mpeg4_score));

                    mpeg4_score_temp=loadMpeg4Score(temp_cur);
                                     
                    mpeg4_score_temp->next_mpeg4_score=NULL;
                    if(mpeg4_score_head==NULL)
                        mpeg4_score_head=mpeg4_score_temp;
                    else{
                        mpeg4_score_p=mpeg4_score_head;
                        while(mpeg4_score_p->next_mpeg4_score!=NULL)
                            mpeg4_score_p=mpeg4_score_p->next_mpeg4_score;
                        mpeg4_score_p->next_mpeg4_score=mpeg4_score_temp;
                    }
                    mpeg4_instance_temp->n_mpeg4_scores++;
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"mpeg4_orchestra")){
                    mpeg4_orchestra_temp=(struct mpeg4_orchestra*)malloc(sizeof(struct mpeg4_orchestra));
                    mpeg4_orchestra_temp=calloc(1,sizeof(struct mpeg4_orchestra));

                    mpeg4_orchestra_temp=loadMpeg4Orchestra(temp_cur);
                                     
                    mpeg4_orchestra_temp->next_mpeg4_orchestra=NULL;
                    if(mpeg4_orchestra_head==NULL)
                        mpeg4_orchestra_head=mpeg4_orchestra_temp;
                    else{
                        mpeg4_orchestra_p=mpeg4_orchestra_head;
                        while(mpeg4_orchestra_p->next_mpeg4_orchestra!=NULL)
                            mpeg4_orchestra_p=mpeg4_orchestra_p->next_mpeg4_orchestra;
                        mpeg4_orchestra_p->next_mpeg4_orchestra=mpeg4_orchestra_temp;
                    }
                    mpeg4_instance_temp->n_mpeg4_orchestras++;
                }
                temp_cur=temp_cur->next;
            }
            mpeg4_instance_temp->mpeg4_scores=mpeg4_score_head;
            mpeg4_instance_temp->mpeg4_orchestras=mpeg4_orchestra_head;
                    
            mpeg4_instance_temp->next_mpeg4_instance=NULL;
            if(mpeg4_instance_head==NULL)
                mpeg4_instance_head=mpeg4_instance_temp;
            else{
                mpeg4_instance_p=mpeg4_instance_head;
                while(mpeg4_instance_p->next_mpeg4_instance!=NULL)
                    mpeg4_instance_p=mpeg4_instance_p->next_mpeg4_instance;
                mpeg4_instance_p->next_mpeg4_instance=mpeg4_instance_temp;
            }
            performance_layer.n_mpeg4_instances++;
        }
        performance_layer.mpeg4_instance=mpeg4_instance_head;
    }
}

struct mpeg4_score* loadMpeg4Score(xmlNodePtr cur){
    struct mpeg4_score* value=(struct mpeg4_score*)malloc(sizeof(struct mpeg4_score));
    value=calloc(1,sizeof(struct mpeg4_score));
    xmlAttr* attributes;

    struct mpeg4_spine_event* mpeg4_spine_event_temp=NULL;
    struct mpeg4_spine_event* mpeg4_spine_event_head=NULL;
    struct mpeg4_spine_event* mpeg4_spine_event_p=NULL;
    value->n_mpeg4_spine_events=0;

    value->next_mpeg4_score=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mpeg4_spine_event")){
            mpeg4_spine_event_temp=(struct mpeg4_spine_event*)malloc(sizeof(struct mpeg4_spine_event));
            mpeg4_spine_event_temp=calloc(1, sizeof(struct mpeg4_spine_event*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"line_number")){
                    mpeg4_spine_event_temp->line_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //mpeg4_spine_event_temp->spine_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            mpeg4_spine_event_temp->next_mpeg4_spine_event=NULL;
            if(mpeg4_spine_event_head==NULL)
                mpeg4_spine_event_head=mpeg4_spine_event_temp;
            else{
                mpeg4_spine_event_p=mpeg4_spine_event_head;
                while(mpeg4_spine_event_p->next_mpeg4_spine_event!=NULL)
                    mpeg4_spine_event_p=mpeg4_spine_event_p->next_mpeg4_spine_event;
                mpeg4_spine_event_p->next_mpeg4_spine_event=mpeg4_spine_event_temp;
            }
            value->n_mpeg4_spine_events++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"rights")){
            value->rights=loadRights(cur);
        }  
        cur=cur->next;
    }
    value->mpeg4_spine_events=mpeg4_spine_event_head;
    
    return value;
}

struct mpeg4_orchestra* loadMpeg4Orchestra(xmlNodePtr cur){
    struct mpeg4_orchestra* value=(struct mpeg4_orchestra*)malloc(sizeof(struct mpeg4_orchestra));
    value=calloc(1,sizeof(struct mpeg4_orchestra));
    xmlAttr* attributes;

    struct mpeg4_instrument_mapping* mpeg4_instrument_mapping_temp=NULL;
    struct mpeg4_instrument_mapping* mpeg4_instrument_mapping_head=NULL;
    struct mpeg4_instrument_mapping* mpeg4_instrument_mapping_p=NULL;
    value->n_mpeg4_instrument_mappings=0;

    value->next_mpeg4_orchestra=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mpeg4_instrument_mapping")){
            mpeg4_instrument_mapping_temp=(struct mpeg4_instrument_mapping*)malloc(sizeof(struct mpeg4_instrument_mapping));
            mpeg4_instrument_mapping_temp=calloc(1, sizeof(struct mpeg4_instrument_mapping*));
            
            mpeg4_instrument_mapping_temp=loadMpeg4InstrumentMapping(cur);
                        
            mpeg4_instrument_mapping_temp->next_mpeg4_instrument_mapping=NULL;
            if(mpeg4_instrument_mapping_head==NULL)
                mpeg4_instrument_mapping_head=mpeg4_instrument_mapping_temp;
            else{
                mpeg4_instrument_mapping_p=mpeg4_instrument_mapping_head;
                while(mpeg4_instrument_mapping_p->next_mpeg4_instrument_mapping!=NULL)
                    mpeg4_instrument_mapping_p=mpeg4_instrument_mapping_p->next_mpeg4_instrument_mapping;
                mpeg4_instrument_mapping_p->next_mpeg4_instrument_mapping=mpeg4_instrument_mapping_temp;
            }
            value->n_mpeg4_instrument_mappings++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"rights")){
            value->rights=loadRights(cur);
        }  
        cur=cur->next;
    }
    value->mpeg4_instrument_mappings=mpeg4_instrument_mapping_head;
    
    return value;
}

struct mpeg4_instrument_mapping* loadMpeg4InstrumentMapping(xmlNodePtr cur){
    struct mpeg4_instrument_mapping* value=(struct mpeg4_instrument_mapping*)malloc(sizeof(struct mpeg4_instrument_mapping));
    value=calloc(1,sizeof(struct mpeg4_instrument_mapping));
    xmlAttr* attributes;

    struct mpeg4_part_ref* mpeg4_part_ref_temp=NULL;
    struct mpeg4_part_ref* mpeg4_part_ref_head=NULL;
    struct mpeg4_part_ref* mpeg4_part_ref_p=NULL;
    value->n_mpeg4_part_refs=0;
    
    struct mpeg4_spine_ref* mpeg4_spine_ref_temp=NULL;
    struct mpeg4_spine_ref* mpeg4_spine_ref_head=NULL;
    struct mpeg4_spine_ref* mpeg4_spine_ref_p=NULL;
    value->n_mpeg4_spine_refs=0;

    value->next_mpeg4_instrument_mapping=NULL;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"instrument_name")){
            value->instrument_name=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_line")){
            value->start_line=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_line")){
            value->end_line=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"pnml_file")){
            value->pnml_file=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mpeg4_part_ref")){
            mpeg4_part_ref_temp=(struct mpeg4_part_ref*)malloc(sizeof(struct mpeg4_part_ref));
            mpeg4_part_ref_temp=calloc(1, sizeof(struct mpeg4_part_ref*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"part_ref")){
                    mpeg4_part_ref_temp->part_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            mpeg4_part_ref_temp->next_mpeg4_part_ref=NULL;
            if(mpeg4_part_ref_head==NULL)
                mpeg4_part_ref_head=mpeg4_part_ref_temp;
            else{
                mpeg4_part_ref_p=mpeg4_part_ref_head;
                while(mpeg4_part_ref_p->next_mpeg4_part_ref!=NULL)
                    mpeg4_part_ref_p=mpeg4_part_ref_p->next_mpeg4_part_ref;
                mpeg4_part_ref_p->next_mpeg4_part_ref=mpeg4_part_ref_temp;
            }
            value->n_mpeg4_part_refs++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"mpeg4_spine_ref")){
            mpeg4_spine_ref_temp=(struct mpeg4_spine_ref*)malloc(sizeof(struct mpeg4_spine_ref));
            mpeg4_spine_ref_temp=calloc(1, sizeof(struct mpeg4_spine_ref*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //mpeg4_spine_ref_temp->spine_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
                        
            mpeg4_spine_ref_temp->next_mpeg4_spine_ref=NULL;
            if(mpeg4_spine_ref_head==NULL)
                mpeg4_spine_ref_head=mpeg4_spine_ref_temp;
            else{
                mpeg4_spine_ref_p=mpeg4_spine_ref_head;
                while(mpeg4_spine_ref_p->next_mpeg4_spine_ref!=NULL)
                    mpeg4_spine_ref_p=mpeg4_spine_ref_p->next_mpeg4_spine_ref;
                mpeg4_spine_ref_p->next_mpeg4_spine_ref=mpeg4_spine_ref_temp;
            }
            value->n_mpeg4_spine_refs++;
        }  
        cur=cur->next;
    }
    value->mpeg4_part_refs=mpeg4_part_ref_head;
    value->mpeg4_spine_refs=mpeg4_spine_ref_head;
    
    return value;
}
void printPerformance(){
    printMidiInstance();
    printCsoundInstance();
    printMpeg4Instance();
}

void printMidiInstance(){

}

void printCsoundInstance(){

}

void printMpeg4Instance(){

}