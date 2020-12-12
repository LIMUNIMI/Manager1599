/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerPerformance.h"

static struct performance performance_layer;

struct performance loadPerformance(){
    loadMidiInstance();
    loadCsoundInstance();
    loadMpeg4Instance();
    
    return performance_layer;
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

            midi_instance_temp=(struct midi_instance*)calloc(1,sizeof(struct midi_instance));
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
                    midi_mapping_temp=(struct midi_mapping*)calloc(1,sizeof(struct midi_mapping));

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
            midi_instance_temp->midi_mapping=midi_mapping_head;
            
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
    }	
    performance_layer.midi_instance = midi_instance_head;
}

struct midi_mapping* loadMidiMapping(xmlNodePtr cur){
    struct midi_mapping* value=(struct midi_mapping*)calloc(1,sizeof(struct midi_mapping));
    xmlAttr* attributes;

    if (value) {
        struct midi_event_sequence* midi_event_sequence_temp = NULL;
        struct midi_event_sequence* midi_event_sequence_head = NULL;
        struct midi_event_sequence* midi_event_sequence_p = NULL;
        value->n_midi_event_sequences = 0;

        value->next_midi_mapping = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"part_ref")) {
                value->part_ref = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"part_ref")) {
                value->part_ref = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"track")) {
                value->track = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"channel")) {
                value->channel = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"midi_event_sequence")) {
                midi_event_sequence_temp = (struct midi_event_sequence*)calloc(1, sizeof(struct midi_event_sequence));

                midi_event_sequence_temp = loadMidiEventSequence(cur);

                midi_event_sequence_temp->next_midi_event_sequence = NULL;
                if (midi_event_sequence_head == NULL)
                    midi_event_sequence_head = midi_event_sequence_temp;
                else {
                    midi_event_sequence_p = midi_event_sequence_head;
                    while (midi_event_sequence_p->next_midi_event_sequence != NULL)
                        midi_event_sequence_p = midi_event_sequence_p->next_midi_event_sequence;
                    midi_event_sequence_p->next_midi_event_sequence = midi_event_sequence_temp;
                }
                value->n_midi_event_sequences++;
            }
            cur = cur->next;
        }
        value->midi_event_sequence = midi_event_sequence_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'midi_mapping' element\n"); }
    
    return value;
}

struct midi_event_sequence* loadMidiEventSequence(xmlNodePtr cur){
    struct midi_event_sequence* value=(struct midi_event_sequence*)calloc(1,sizeof(struct midi_event_sequence));
    xmlAttr* attributes;

    if (value) {
        struct midi_event* midi_event_temp = NULL;
        struct midi_event* midi_event_head = NULL;
        struct midi_event* midi_event_p = NULL;
        value->n_midi_events = 0;

        struct sys_ex* sys_ex_temp = NULL;
        struct sys_ex* sys_ex_head = NULL;
        struct sys_ex* sys_ex_p = NULL;
        value->n_sys_exs = 0;

        value->next_midi_event_sequence = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"division_type")) {
                value->division_type = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"division_value")) {
                value->division_value = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"measurement_unit")) {
                value->measurement_unit = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"midi_event")) {
                midi_event_temp = (struct midi_event*) calloc(1, sizeof(struct midi_event));

                midi_event_temp = loadMidiEvent(cur);

                midi_event_temp->next_midi_event = NULL;
                if (midi_event_head == NULL)
                    midi_event_head = midi_event_temp;
                else {
                    midi_event_p = midi_event_head;
                    while (midi_event_p->next_midi_event != NULL)
                        midi_event_p = midi_event_p->next_midi_event;
                    midi_event_p->next_midi_event = midi_event_temp;
                }
                value->n_midi_events++;
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"sys_ex")) {
                sys_ex_temp = (struct sys_ex*)calloc(1, sizeof(struct sys_ex));

                sys_ex_temp = loadSysEx(cur);

                sys_ex_temp->next_sys_ex = NULL;
                if (sys_ex_head == NULL)
                    sys_ex_head = sys_ex_temp;
                else {
                    sys_ex_p = sys_ex_head;
                    while (sys_ex_p->next_sys_ex != NULL)
                        sys_ex_p = sys_ex_p->next_sys_ex;
                    sys_ex_p->next_sys_ex = sys_ex_temp;
                }
                value->n_sys_exs++;
            }
            cur = cur->next;
        }
        value->midi_event = midi_event_head;
        value->sys_ex = sys_ex_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'midi_event_sequence' element\n"); }
    
    return value;
}

struct midi_event* loadMidiEvent(xmlNodePtr cur) {
    struct midi_event* value = (struct midi_event*) calloc(1, sizeof(struct midi_event));
    xmlAttr* attributes;

    if (value) {
        value->next_midi_event = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"timing")) {
                value->timing = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                value->event_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        //loading (%MIDIChannelMessage;)*

    }
    else { fprintf(stderr, "Memory allocation failed for 'midi_event' element\n"); }
    
    return value;
}

struct sys_ex* loadSysEx(xmlNodePtr cur){
    struct sys_ex* value=(struct sys_ex*)calloc(1,sizeof(struct sys_ex));
    xmlAttr* attributes;
    
    if (value) {
        value->next_sys_ex = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                value->event_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        //caricamento (SysEx)
    }
    else { fprintf(stderr, "Memory allocation failed for 'sys_ex' element\n"); }

    return value;
}

void loadCsoundInstance(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct csound_mpeg4_instance* csound_instance_temp=NULL;
    struct csound_mpeg4_instance* csound_instance_head=NULL;
    struct csound_mpeg4_instance* csound_instance_p=NULL;
    performance_layer.n_csound_instances=0;
    
    xpath=(xmlChar *)"/ieee1599/performance/csound_instance";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning csound_instance 

            csound_instance_temp=(struct csound_mpeg4_instance*)calloc(1,sizeof(struct csound_mpeg4_instance));
            cur=nodeset->nodeTab[i];

            if (csound_instance_temp) {
                //load csound_instance elements
                struct csound_mpeg4_score* csound_score_temp = NULL;
                struct csound_mpeg4_score* csound_score_head = NULL;
                struct csound_mpeg4_score* csound_score_p = NULL;
                csound_instance_temp->n_csound_mpeg4_scores = 0;

                struct csound_mpeg4_orchestra* csound_orchestra_temp = NULL;
                struct csound_mpeg4_orchestra* csound_orchestra_head = NULL;
                struct csound_mpeg4_orchestra* csound_orchestra_p = NULL;
                csound_instance_temp->n_csound_mpeg4_orchestras = 0;

                temp_cur = cur->xmlChildrenNode;
                while (temp_cur != NULL) {
                    if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"csound_score")) {
                        csound_score_temp = (struct csound_mpeg4_score*) calloc(1, sizeof(struct csound_mpeg4_score));

                        csound_score_temp = loadCsoundScore(temp_cur);

                        csound_score_temp->next_csound_mpeg4_score = NULL;
                        if (csound_score_head == NULL)
                            csound_score_head = csound_score_temp;
                        else {
                            csound_score_p = csound_score_head;
                            while (csound_score_p->next_csound_mpeg4_score != NULL)
                                csound_score_p = csound_score_p->next_csound_mpeg4_score;
                            csound_score_p->next_csound_mpeg4_score = csound_score_temp;
                        }
                        csound_instance_temp->n_csound_mpeg4_scores++;
                    }
                    else if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"csound_orchestra")) {
                        csound_orchestra_temp = (struct csound_mpeg4_orchestra*)calloc(1, sizeof(struct csound_mpeg4_orchestra));

                        csound_orchestra_temp = loadCsoundOrchestra(temp_cur);

                        csound_orchestra_temp->next_csound_mpeg4_orchestra = NULL;
                        if (csound_orchestra_head == NULL)
                            csound_orchestra_head = csound_orchestra_temp;
                        else {
                            csound_orchestra_p = csound_orchestra_head;
                            while (csound_orchestra_p->next_csound_mpeg4_orchestra != NULL)
                                csound_orchestra_p = csound_orchestra_p->next_csound_mpeg4_orchestra;
                            csound_orchestra_p->next_csound_mpeg4_orchestra = csound_orchestra_temp;
                        }
                        csound_instance_temp->n_csound_mpeg4_orchestras++;
                    }
                    temp_cur = temp_cur->next;
                }
                csound_instance_temp->csound_mpeg4_score = csound_score_head;
                csound_instance_temp->csound_mpeg4_orchestra = csound_orchestra_head;

                csound_instance_temp->next_csound_mpeg4_instance = NULL;
                if (csound_instance_head == NULL)
                    csound_instance_head = csound_instance_temp;
                else {
                    csound_instance_p = csound_instance_head;
                    while (csound_instance_p->next_csound_mpeg4_instance != NULL)
                        csound_instance_p = csound_instance_p->next_csound_mpeg4_instance;
                    csound_instance_p->next_csound_mpeg4_instance = csound_instance_temp;
                }
                performance_layer.n_csound_instances++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'csound_instance' element\n"); }
        }
    }
    performance_layer.csound_instance = csound_instance_head;
}

struct csound_mpeg4_score* loadCsoundScore(xmlNodePtr cur){
    struct csound_mpeg4_score* value=(struct csound_mpeg4_score*)calloc(1,sizeof(struct csound_mpeg4_score));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_spine_event* csound_spine_event_temp = NULL;
        struct csound_mpeg4_spine_event* csound_spine_event_head = NULL;
        struct csound_mpeg4_spine_event* csound_spine_event_p = NULL;
        value->n_csound_mpeg4_spine_events = 0;

        value->next_csound_mpeg4_score = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"csound_spine_event")) {
                csound_spine_event_temp = (struct csound_mpeg4_spine_event*)calloc(1, sizeof(struct csound_mpeg4_spine_event));

                if (csound_spine_event_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"line_number")) {
                            csound_spine_event_temp->line_number = xmlCharToInt(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            csound_spine_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    csound_spine_event_temp->next_csound_mpeg4_spine_event = NULL;
                    if (csound_spine_event_head == NULL)
                        csound_spine_event_head = csound_spine_event_temp;
                    else {
                        csound_spine_event_p = csound_spine_event_head;
                        while (csound_spine_event_p->next_csound_mpeg4_spine_event != NULL)
                            csound_spine_event_p = csound_spine_event_p->next_csound_mpeg4_spine_event;
                        csound_spine_event_p->next_csound_mpeg4_spine_event = csound_spine_event_temp;
                    }
                    value->n_csound_mpeg4_spine_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'csound_spine_event' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->csound_mpeg4_spine_event = csound_spine_event_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'csound_score' element\n"); }
    
    return value;
}

struct csound_mpeg4_orchestra* loadCsoundOrchestra(xmlNodePtr cur){
    struct csound_mpeg4_orchestra* value=(struct csound_mpeg4_orchestra*)calloc(1,sizeof(struct csound_mpeg4_orchestra));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_instrument_mapping* csound_instrument_mapping_temp = NULL;
        struct csound_mpeg4_instrument_mapping* csound_instrument_mapping_head = NULL;
        struct csound_mpeg4_instrument_mapping* csound_instrument_mapping_p = NULL;
        value->n_csound_mpeg4_instrument_mappings = 0;

        value->next_csound_mpeg4_orchestra = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"csound_instrument_mapping")) {
                csound_instrument_mapping_temp = (struct csound_mpeg4_instrument_mapping*)calloc(1, sizeof(struct csound_mpeg4_instrument_mapping));

                csound_instrument_mapping_temp = loadCsoundInstrumentMapping(cur);

                csound_instrument_mapping_temp->next_csound_mpeg4_instrument_mapping = NULL;
                if (csound_instrument_mapping_head == NULL)
                    csound_instrument_mapping_head = csound_instrument_mapping_temp;
                else {
                    csound_instrument_mapping_p = csound_instrument_mapping_head;
                    while (csound_instrument_mapping_p->next_csound_mpeg4_instrument_mapping != NULL)
                        csound_instrument_mapping_p = csound_instrument_mapping_p->next_csound_mpeg4_instrument_mapping;
                    csound_instrument_mapping_p->next_csound_mpeg4_instrument_mapping = csound_instrument_mapping_temp;
                }
                value->n_csound_mpeg4_instrument_mappings++;
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->csound_mpeg4_instrument_mapping = csound_instrument_mapping_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'csound_orchestra' element\n"); }
    
    return value;
}

struct csound_mpeg4_instrument_mapping* loadCsoundInstrumentMapping(xmlNodePtr cur){
    struct csound_mpeg4_instrument_mapping* value=(struct csound_mpeg4_instrument_mapping*)calloc(1,sizeof(struct csound_mpeg4_instrument_mapping));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_part_ref* csound_part_ref_temp = NULL;
        struct csound_mpeg4_part_ref* csound_part_ref_head = NULL;
        struct csound_mpeg4_part_ref* csound_part_ref_p = NULL;
        value->n_csound_mpeg4_part_refs = 0;

        struct csound_mpeg4_spine_ref* csound_spine_ref_temp = NULL;
        struct csound_mpeg4_spine_ref* csound_spine_ref_head = NULL;
        struct csound_mpeg4_spine_ref* csound_spine_ref_p = NULL;
        value->n_csound_mpeg4_spine_refs = 0;

        value->next_csound_mpeg4_instrument_mapping = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"instrument_number")) {
                value->instrument_info = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_line")) {
                value->start_line = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_line")) {
                value->end_line = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"pnml_file")) {
                value->pnml_file = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"csound_part_ref")) {
                csound_part_ref_temp = (struct csound_mpeg4_part_ref*) calloc(1, sizeof(struct csound_mpeg4_part_ref));

                if (csound_part_ref_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"part_ref")) {
                            csound_part_ref_temp->part_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    csound_part_ref_temp->next_csound_mpeg4_part_ref = NULL;
                    if (csound_part_ref_head == NULL)
                        csound_part_ref_head = csound_part_ref_temp;
                    else {
                        csound_part_ref_p = csound_part_ref_head;
                        while (csound_part_ref_p->next_csound_mpeg4_part_ref != NULL)
                            csound_part_ref_p = csound_part_ref_p->next_csound_mpeg4_part_ref;
                        csound_part_ref_p->next_csound_mpeg4_part_ref = csound_part_ref_temp;
                    }
                    value->n_csound_mpeg4_part_refs++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'csound_part_ref' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"csound_spine_ref")) {
                csound_spine_ref_temp = (struct csound_mpeg4_spine_ref*)calloc(1, sizeof(struct csound_mpeg4_spine_ref));

                if (csound_spine_ref_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            csound_spine_ref_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    csound_spine_ref_temp->next_csound_mpeg4_spine_ref = NULL;
                    if (csound_spine_ref_head == NULL)
                        csound_spine_ref_head = csound_spine_ref_temp;
                    else {
                        csound_spine_ref_p = csound_spine_ref_head;
                        while (csound_spine_ref_p->next_csound_mpeg4_spine_ref != NULL)
                            csound_spine_ref_p = csound_spine_ref_p->next_csound_mpeg4_spine_ref;
                        csound_spine_ref_p->next_csound_mpeg4_spine_ref = csound_spine_ref_temp;
                    }
                    value->n_csound_mpeg4_spine_refs++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'csound_spine_ref' element\n"); }
            }
            cur = cur->next;
        }
        value->csound_mpeg4_part_ref = csound_part_ref_head;
        value->csound_mpeg4_spine_ref = csound_spine_ref_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'csound_instrument_mapping' element\n"); }

    return value;
}
    
void loadMpeg4Instance(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct csound_mpeg4_instance* mpeg4_instance_temp=NULL;
    struct csound_mpeg4_instance* mpeg4_instance_head=NULL;
    struct csound_mpeg4_instance* mpeg4_instance_p=NULL;
    performance_layer.n_mpeg4_instances=0;
    
    xpath=(xmlChar *)"/ieee1599/performance/mpeg4_instance";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning mpeg4_instances 

            mpeg4_instance_temp=(struct csound_mpeg4_instance*)calloc(1,sizeof(struct csound_mpeg4_instance));
            cur=nodeset->nodeTab[i];

            if (mpeg4_instance_temp) {
                //load mpeg4_instance elements
                struct csound_mpeg4_score* mpeg4_score_temp = NULL;
                struct csound_mpeg4_score* mpeg4_score_head = NULL;
                struct csound_mpeg4_score* mpeg4_score_p = NULL;
                mpeg4_instance_temp->n_csound_mpeg4_scores = 0;

                struct csound_mpeg4_orchestra* mpeg4_orchestra_temp = NULL;
                struct csound_mpeg4_orchestra* mpeg4_orchestra_head = NULL;
                struct csound_mpeg4_orchestra* mpeg4_orchestra_p = NULL;
                mpeg4_instance_temp->n_csound_mpeg4_orchestras = 0;

                temp_cur = cur->xmlChildrenNode;
                while (temp_cur != NULL) {
                    if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"mpeg4_score")) {
                        mpeg4_score_temp = (struct csound_mpeg4_score*) calloc(1, sizeof(struct csound_mpeg4_score));

                        mpeg4_score_temp = loadMpeg4Score(temp_cur);

                        mpeg4_score_temp->next_csound_mpeg4_score = NULL;
                        if (mpeg4_score_head == NULL)
                            mpeg4_score_head = mpeg4_score_temp;
                        else {
                            mpeg4_score_p = mpeg4_score_head;
                            while (mpeg4_score_p->next_csound_mpeg4_score != NULL)
                                mpeg4_score_p = mpeg4_score_p->next_csound_mpeg4_score;
                            mpeg4_score_p->next_csound_mpeg4_score = mpeg4_score_temp;
                        }
                        mpeg4_instance_temp->n_csound_mpeg4_scores++;
                    }
                    else if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"mpeg4_orchestra")) {
                        mpeg4_orchestra_temp = (struct csound_mpeg4_orchestra*)calloc(1, sizeof(struct csound_mpeg4_orchestra));

                        mpeg4_orchestra_temp = loadMpeg4Orchestra(temp_cur);

                        mpeg4_orchestra_temp->next_csound_mpeg4_orchestra = NULL;
                        if (mpeg4_orchestra_head == NULL)
                            mpeg4_orchestra_head = mpeg4_orchestra_temp;
                        else {
                            mpeg4_orchestra_p = mpeg4_orchestra_head;
                            while (mpeg4_orchestra_p->next_csound_mpeg4_orchestra != NULL)
                                mpeg4_orchestra_p = mpeg4_orchestra_p->next_csound_mpeg4_orchestra;
                            mpeg4_orchestra_p->next_csound_mpeg4_orchestra = mpeg4_orchestra_temp;
                        }
                        mpeg4_instance_temp->n_csound_mpeg4_orchestras++;
                    }
                    temp_cur = temp_cur->next;
                }
                mpeg4_instance_temp->csound_mpeg4_score = mpeg4_score_head;
                mpeg4_instance_temp->csound_mpeg4_orchestra = mpeg4_orchestra_head;

                mpeg4_instance_temp->next_csound_mpeg4_instance = NULL;
                if (mpeg4_instance_head == NULL)
                    mpeg4_instance_head = mpeg4_instance_temp;
                else {
                    mpeg4_instance_p = mpeg4_instance_head;
                    while (mpeg4_instance_p->next_csound_mpeg4_instance != NULL)
                        mpeg4_instance_p = mpeg4_instance_p->next_csound_mpeg4_instance;
                    mpeg4_instance_p->next_csound_mpeg4_instance = mpeg4_instance_temp;
                }
                performance_layer.n_mpeg4_instances++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'mpeg4_instance' element\n"); }
        }
    }
    performance_layer.mpeg4_instance = mpeg4_instance_head;
}

struct csound_mpeg4_score* loadMpeg4Score(xmlNodePtr cur){
    struct csound_mpeg4_score* value=(struct csound_mpeg4_score*)calloc(1,sizeof(struct csound_mpeg4_score));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_spine_event* mpeg4_spine_event_temp = NULL;
        struct csound_mpeg4_spine_event* mpeg4_spine_event_head = NULL;
        struct csound_mpeg4_spine_event* mpeg4_spine_event_p = NULL;
        value->n_csound_mpeg4_spine_events = 0;

        value->next_csound_mpeg4_score = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mpeg4_spine_event")) {
                mpeg4_spine_event_temp = (struct csound_mpeg4_spine_event*) calloc(1, sizeof(struct csound_mpeg4_spine_event));

                if (mpeg4_spine_event_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"line_number")) {
                            mpeg4_spine_event_temp->line_number = xmlCharToInt(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            mpeg4_spine_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    mpeg4_spine_event_temp->next_csound_mpeg4_spine_event = NULL;
                    if (mpeg4_spine_event_head == NULL)
                        mpeg4_spine_event_head = mpeg4_spine_event_temp;
                    else {
                        mpeg4_spine_event_p = mpeg4_spine_event_head;
                        while (mpeg4_spine_event_p->next_csound_mpeg4_spine_event != NULL)
                            mpeg4_spine_event_p = mpeg4_spine_event_p->next_csound_mpeg4_spine_event;
                        mpeg4_spine_event_p->next_csound_mpeg4_spine_event = mpeg4_spine_event_temp;
                    }
                    value->n_csound_mpeg4_spine_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'mpeg4_spine_event' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->csound_mpeg4_spine_event = mpeg4_spine_event_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mpeg4_score' element\n"); }
    
    return value;
}

struct csound_mpeg4_orchestra* loadMpeg4Orchestra(xmlNodePtr cur){
    struct csound_mpeg4_orchestra* value=(struct csound_mpeg4_orchestra*)calloc(1,sizeof(struct csound_mpeg4_orchestra));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_instrument_mapping* mpeg4_instrument_mapping_temp = NULL;
        struct csound_mpeg4_instrument_mapping* mpeg4_instrument_mapping_head = NULL;
        struct csound_mpeg4_instrument_mapping* mpeg4_instrument_mapping_p = NULL;
        value->n_csound_mpeg4_instrument_mappings = 0;

        value->next_csound_mpeg4_orchestra = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mpeg4_instrument_mapping")) {
                mpeg4_instrument_mapping_temp = (struct csound_mpeg4_instrument_mapping*)calloc(1, sizeof(struct csound_mpeg4_instrument_mapping));

                mpeg4_instrument_mapping_temp = loadMpeg4InstrumentMapping(cur);

                mpeg4_instrument_mapping_temp->next_csound_mpeg4_instrument_mapping = NULL;
                if (mpeg4_instrument_mapping_head == NULL)
                    mpeg4_instrument_mapping_head = mpeg4_instrument_mapping_temp;
                else {
                    mpeg4_instrument_mapping_p = mpeg4_instrument_mapping_head;
                    while (mpeg4_instrument_mapping_p->next_csound_mpeg4_instrument_mapping != NULL)
                        mpeg4_instrument_mapping_p = mpeg4_instrument_mapping_p->next_csound_mpeg4_instrument_mapping;
                    mpeg4_instrument_mapping_p->next_csound_mpeg4_instrument_mapping = mpeg4_instrument_mapping_temp;
                }
                value->n_csound_mpeg4_instrument_mappings++;
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->csound_mpeg4_instrument_mapping = mpeg4_instrument_mapping_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mpeg4_orchestra' element\n"); }
    
    return value;
}

struct csound_mpeg4_instrument_mapping* loadMpeg4InstrumentMapping(xmlNodePtr cur){
    struct csound_mpeg4_instrument_mapping* value=(struct csound_mpeg4_instrument_mapping*)calloc(1,sizeof(struct csound_mpeg4_instrument_mapping));
    xmlAttr* attributes;

    if (value) {
        struct csound_mpeg4_part_ref* mpeg4_part_ref_temp = NULL;
        struct csound_mpeg4_part_ref* mpeg4_part_ref_head = NULL;
        struct csound_mpeg4_part_ref* mpeg4_part_ref_p = NULL;
        value->n_csound_mpeg4_part_refs = 0;

        struct csound_mpeg4_spine_ref* mpeg4_spine_ref_temp = NULL;
        struct csound_mpeg4_spine_ref* mpeg4_spine_ref_head = NULL;
        struct csound_mpeg4_spine_ref* mpeg4_spine_ref_p = NULL;
        value->n_csound_mpeg4_spine_refs = 0;

        value->next_csound_mpeg4_instrument_mapping = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"instrument_name")) {
                value->instrument_info = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_line")) {
                value->start_line = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_line")) {
                value->end_line = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"pnml_file")) {
                value->pnml_file = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mpeg4_part_ref")) {
                mpeg4_part_ref_temp = (struct csound_mpeg4_part_ref*)calloc(1, sizeof(struct csound_mpeg4_part_ref));

                if (mpeg4_part_ref_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"part_ref")) {
                            mpeg4_part_ref_temp->part_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    mpeg4_part_ref_temp->next_csound_mpeg4_part_ref = NULL;
                    if (mpeg4_part_ref_head == NULL)
                        mpeg4_part_ref_head = mpeg4_part_ref_temp;
                    else {
                        mpeg4_part_ref_p = mpeg4_part_ref_head;
                        while (mpeg4_part_ref_p->next_csound_mpeg4_part_ref != NULL)
                            mpeg4_part_ref_p = mpeg4_part_ref_p->next_csound_mpeg4_part_ref;
                        mpeg4_part_ref_p->next_csound_mpeg4_part_ref = mpeg4_part_ref_temp;
                    }
                    value->n_csound_mpeg4_part_refs++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'mpeg4_part_ref' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"mpeg4_spine_ref")) {
                mpeg4_spine_ref_temp = (struct csound_mpeg4_spine_ref*)calloc(1, sizeof(struct csound_mpeg4_spine_ref));

                if (mpeg4_spine_ref_temp) {
                    if (mpeg4_spine_ref_temp) {
                        attributes = cur->properties;
                        while (attributes != NULL) {
                            if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                                mpeg4_spine_ref_temp->event_ref = xmlGetProp(cur, attributes->name);
                            }
                            attributes = attributes->next;
                        }

                        mpeg4_spine_ref_temp->next_csound_mpeg4_spine_ref = NULL;
                        if (mpeg4_spine_ref_head == NULL)
                            mpeg4_spine_ref_head = mpeg4_spine_ref_temp;
                        else {
                            mpeg4_spine_ref_p = mpeg4_spine_ref_head;
                            while (mpeg4_spine_ref_p->next_csound_mpeg4_spine_ref != NULL)
                                mpeg4_spine_ref_p = mpeg4_spine_ref_p->next_csound_mpeg4_spine_ref;
                            mpeg4_spine_ref_p->next_csound_mpeg4_spine_ref = mpeg4_spine_ref_temp;
                        }
                        value->n_csound_mpeg4_spine_refs++;
                    }
                }
                else { fprintf(stderr, "Memory allocation failed for 'mpeg4_spine_ref' element\n"); }
            }
            cur = cur->next;
        }
        value->csound_mpeg4_part_ref = mpeg4_part_ref_head;
        value->csound_mpeg4_spine_ref = mpeg4_spine_ref_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mpeg4_instrument_mapping' element\n"); }
    
    return value;
}

void printPerformance(){

    if (performance_layer.n_midi_instances != 0 ||
        performance_layer.n_csound_instances != 0 ||
        performance_layer.n_mpeg4_instances != 0 ) {
        printf("\n###Performance Layer###\n");
        printMidiInstance();
        printCsoundInstance();
        printMpeg4Instance();
    }
}

void printMidiInstance(){
    if (performance_layer.n_midi_instances != 0) {
        printf("%i MIDI instances\n", performance_layer.n_midi_instances);
        struct midi_instance* p = performance_layer.midi_instance;
        while (p) {
            printf("MIDI Instance: ");
            if (p->file_name)
                printf("file_name=%s ", p->file_name);
            if (p->format)
                printf("format=%s ", p->format);
            printf("\n");
            if (p->rights.file_name) {
                printf("rights=%s ",p->rights.file_name);
            }
            if (p->n_midi_mappings != 0) {
                struct midi_mapping* k = p->midi_mapping;
                printf("    %i MIDI mappings\n", p->n_midi_mappings);
                while (k) {
                    printf("    MIDI Mapping: ");
                    if (k->part_ref)
                        printf("part_ref=%s ", k->part_ref);
                    if (k->voice_ref)
                        printf("voice_ref=%s ", k->voice_ref);
                    if (k->track)
                        printf("track=%s ", k->track);
                    if (k->channel)
                        printf("channel=%s ", k->channel);
                    printf("\n");

                    if (k->n_midi_event_sequences != 0) {
                        struct midi_event_sequence* t = k->midi_event_sequence;
                        int i = 0;
                        printf("        %i MIDI event sequences\n", k->n_midi_event_sequences);
                        while (t && i<N_DISPLAY) {
                            printf("        MIDI Event Sequence ( ");
                            if (t->division_type)
                                printf("division_type=%s ", t->division_type);
                            if (t->division_value)
                                printf("division_value=%s ", t->division_value);
                            if (t->measurement_unit)
                                printf("measurement_unit=%s ", t->measurement_unit);
                            printf(")\n ");
                            if (t->n_midi_events != 0) {
                                struct midi_event* me = t->midi_event;
                                printf("            %i midi events\n",t->n_midi_events);
                                printf("            MIDI events: ");
                                while (me) {
                                    printf("[ ");
                                    if (me->timing)
                                        printf("timing=%s ",me->timing);
                                    if (me->event_ref)
                                        printf("event_ref=%s ", me->event_ref);
                                    printf("] ");
                                    me = me->next_midi_event;
                                }
                            }
                            if (t->n_sys_exs != 0) {
                                struct sys_ex* se = t->sys_ex;
                                printf("            %i sys exs\n", t->n_midi_events);
                                printf("            Sys Ex: ");
                                while (se) {
                                    printf("[ ");
                                    if (se->event_ref)
                                        printf("event_ref=%s ", se->event_ref);
                                    printf("] ");
                                    se = se->next_sys_ex;
                                }
                            }
                            t = t->next_midi_event_sequence;
                        }
                        if (k->n_midi_event_sequences > N_DISPLAY)printf("      ...");
                    }
                    printf(")\n");
                    k = k->next_midi_mapping;
                }
            }
            p = p->next_midi_instance;
        }
    }
}

void printCsoundInstance(){
    if (performance_layer.n_csound_instances != 0) {
        printf("%i csound instances\n", performance_layer.n_csound_instances);
        struct csound_mpeg4_instance* p = performance_layer.csound_instance;
        printf("CSound Instance:\n");
        while (p) {
            if (p->n_csound_mpeg4_scores != 0) {
                struct csound_mpeg4_score* k = p->csound_mpeg4_score;
                printf("    %i csound scores\n", p->n_csound_mpeg4_scores);
                while (k) {
                    printf("    CSound Score: ");
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->rights.file_name)
                        printf("rights=%s ", k->rights.file_name);
                    printf("\n");
                    if (k->n_csound_mpeg4_spine_events != 0) {
                        struct csound_mpeg4_spine_event* t = k->csound_mpeg4_spine_event;
                        int i = 0;
                        printf("        %i csound spine events\n", k->n_csound_mpeg4_spine_events);
                        while (t && i < N_DISPLAY) {
                            printf("        CSound Spine Events: ");
                            printf("( ");
                            if (t->line_number)
                                printf("line_number=%i ", t->line_number);
                            if (t->event_ref)
                                printf("event_ref=%s ", t->event_ref);
                            printf(") ");
                            t = t->next_csound_mpeg4_spine_event;
                        }
                        if (k->n_csound_mpeg4_spine_events > N_DISPLAY)printf("      ...");
                        printf("\n");
                    }
                    k = k->next_csound_mpeg4_score;
                }
            }
            if (p->n_csound_mpeg4_orchestras != 0) {
                struct csound_mpeg4_orchestra* k = p->csound_mpeg4_orchestra;
                printf("    %i csound orchestras\n", p->n_csound_mpeg4_orchestras);
                while (k) {
                    printf("    CSound Orchestra: ");
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->rights.file_name)
                        printf("rights=%s ", k->rights.file_name);
                    printf("\n");
                    if (k->n_csound_mpeg4_instrument_mappings != 0) {
                        struct csound_mpeg4_instrument_mapping* t = k->csound_mpeg4_instrument_mapping;
                        printf("        %i csound instrument mappings\n", k->n_csound_mpeg4_instrument_mappings);
                        while (t) {
                            printf("        CSound Instrument Mappings: ");
                            if (t->instrument_info)
                                printf("instrument_number=%s ", t->instrument_info);
                            if (t->start_line)
                                printf("start_line=%i ", t->start_line);
                            if (t->end_line)
                                printf("end_line=%i ", t->end_line);
                            if (t->pnml_file)
                                printf("pnml_file=%s ", t->pnml_file);
                            if (t->n_csound_mpeg4_part_refs) {
                                struct csound_mpeg4_part_ref* pr = t->csound_mpeg4_part_ref;
                                printf(" part_refs( ");
                                int i = 0;
                                while (pr) {
                                    i++;
                                    if (pr->part_ref) printf("part_ref=%s ",pr->part_ref);
                                    pr = pr->next_csound_mpeg4_part_ref;
                                }
                                if (t->n_csound_mpeg4_spine_refs > N_DISPLAY)printf("      ...");
                                printf(") ");
                            }
                            if (t->n_csound_mpeg4_spine_refs) {
                                struct csound_mpeg4_spine_ref* sr = t->csound_mpeg4_spine_ref;
                                printf(" spine_refs( ");
                                int i = 0;
                                while (sr) {
                                    i++;
                                    if (sr->event_ref) printf("event_ref=%s ",sr->event_ref);
                                    sr = sr->next_csound_mpeg4_spine_ref;
                                }
                                if (t->n_csound_mpeg4_spine_refs > N_DISPLAY)printf("      ...");
                                printf(") ");
                            }
                            printf("\n");
                            t = t->next_csound_mpeg4_instrument_mapping;
                        }
                    }
                    k = k->next_csound_mpeg4_orchestra;
                }
            }
            p = p->next_csound_mpeg4_instance;
        }
    }
}

void printMpeg4Instance(){
    if (performance_layer.n_mpeg4_instances != 0) {
        printf("%i mpeg4 instances\n", performance_layer.n_csound_instances);
        struct csound_mpeg4_instance* p = performance_layer.csound_instance;
        printf("MPEG4 Instance:\n");
        while (p) {
            if (p->n_csound_mpeg4_scores != 0) {
                struct csound_mpeg4_score* k = p->csound_mpeg4_score;
                printf("    %i mpeg4 scores\n", p->n_csound_mpeg4_scores);
                while (k) {
                    printf("    MPEG4 Score: ");
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->rights.file_name)
                        printf("rights=%s ", k->rights.file_name);
                    printf("\n");
                    if (k->n_csound_mpeg4_spine_events != 0) {
                        struct csound_mpeg4_spine_event* t = k->csound_mpeg4_spine_event;
                        int i = 0;
                        printf("        %i mpeg4 spine events\n", k->n_csound_mpeg4_spine_events);
                        while (t && i < N_DISPLAY) {
                            printf("        MPEG4 Spine Events: ");
                            printf("( ");
                            if (t->line_number)
                                printf("line_number=%i ", t->line_number);
                            if (t->event_ref)
                                printf("event_ref=%s ", t->event_ref);
                            printf(") ");
                            t = t->next_csound_mpeg4_spine_event;
                        }
                        if (k->n_csound_mpeg4_spine_events > N_DISPLAY)printf("      ...");
                        printf("\n");
                    }
                    k = k->next_csound_mpeg4_score;
                }
            }
            if (p->n_csound_mpeg4_orchestras != 0) {
                struct csound_mpeg4_orchestra* k = p->csound_mpeg4_orchestra;
                printf("    %i mpeg4 orchestras\n", p->n_csound_mpeg4_orchestras);
                while (k) {
                    printf("    MPEG4 Orchestra: ");
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->rights.file_name)
                        printf("rights=%s ", k->rights.file_name);
                    printf("\n");
                    if (k->n_csound_mpeg4_instrument_mappings != 0) {
                        struct csound_mpeg4_instrument_mapping* t = k->csound_mpeg4_instrument_mapping;
                        printf("        %i mpeg4 instrument mappings\n", k->n_csound_mpeg4_instrument_mappings);
                        while (t ) {
                            printf("        MPEG4 Instrument Mappings: ");
                            if (t->instrument_info)
                                printf("instrument_name=%s ", t->instrument_info);
                            if (t->start_line)
                                printf("start_line=%i ", t->start_line);
                            if (t->end_line)
                                printf("end_line=%i ", t->end_line);
                            if (t->pnml_file)
                                printf("pnml_file=%s ", t->pnml_file);
                            if (t->n_csound_mpeg4_part_refs) {
                                struct csound_mpeg4_part_ref* pr = t->csound_mpeg4_part_ref;
                                printf(" part_refs( ");
                                int i = 0;
                                while (pr && i < N_DISPLAY) {
                                    i++;
                                    if (pr->part_ref) printf("part_ref=%s ", pr->part_ref);
                                    pr = pr->next_csound_mpeg4_part_ref;
                                }
                                if (t->n_csound_mpeg4_part_refs > N_DISPLAY)printf("        ...");
                                printf(") ");
                            }
                            if (t->n_csound_mpeg4_spine_refs) {
                                struct csound_mpeg4_spine_ref* sr = t->csound_mpeg4_spine_ref;
                                printf(" spine_refs( ");
                                int i = 0;
                                while (sr && i < N_DISPLAY) {
                                    i++;
                                    if (sr->event_ref) printf("event_ref=%s ", sr->event_ref);
                                    sr = sr->next_csound_mpeg4_spine_ref;
                                }
                                if (t->n_csound_mpeg4_spine_refs > N_DISPLAY)printf("        ...");
                                printf(") ");
                            }
                            printf("\n");
                            t = t->next_csound_mpeg4_instrument_mapping;
                        }
                    }
                    k = k->next_csound_mpeg4_orchestra;
                }
            }
            p = p->next_csound_mpeg4_instance;
        }
    }
}

void freeSysExsList(struct sys_ex* head) {
    struct sys_ex* temp;
    while (head) {
        temp = head;
        head = head->next_sys_ex;
        free(temp);
    }
}

void freeMidiEventsList(struct midi_event* head) {
    struct midi_event* temp;
    while (head) {
        temp = head;
        head = head->next_midi_event;
        free(temp);
    }
}

void freeMidiEventSequencesList(struct midi_event_sequence* head) {
    struct midi_event_sequence* temp;
    while (head) {
        temp = head;
        head = head->next_midi_event_sequence;

        if (temp->midi_event)
            freeMidiEventsList(temp->midi_event);
        if (temp->sys_ex)
            freeSysExsList(temp->sys_ex);

        free(temp);
    }
}

void freeMidiMappingsList(struct midi_mapping* head) {
    struct midi_mapping* temp;
    while (head) {
        temp = head;
        head = head->next_midi_mapping;

        if (temp->midi_event_sequence)
            freeMidiEventSequencesList(temp->midi_event_sequence);

        free(temp);
    }
}

void freeMidiInstancesList(struct midi_instance* head) {
    struct midi_instance* temp;
    while (head) {
        temp = head;
        head = head->next_midi_instance;

        if (temp->midi_mapping)
            freeMidiMappingsList(temp->midi_mapping);

        free(temp);
    }
}

void freeCsoundMpeg4SpineRefsList(struct csound_mpeg4_spine_ref* head) {
    struct csound_mpeg4_spine_ref* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_spine_ref;
        free(temp);
    }
}

void freeCsoundMpeg4PartRefsList(struct csound_mpeg4_part_ref* head) {
    struct csound_mpeg4_part_ref* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_part_ref;
        free(temp);
    }
}

void freeCsoundMpeg4InstrumentMappingsList(struct csound_mpeg4_instrument_mapping* head) {
    struct csound_mpeg4_instrument_mapping* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_instrument_mapping;

        if (temp->csound_mpeg4_part_ref)
            freeCsoundMpeg4PartRefsList(temp->csound_mpeg4_part_ref);
        if (temp->csound_mpeg4_spine_ref)
            freeCsoundMpeg4SpineRefsList(temp->csound_mpeg4_spine_ref);

        free(temp);
    }
}

void freeCsoundMpeg4OrtchestrasList(struct csound_mpeg4_orchestra* head) {
    struct csound_mpeg4_orchestra* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_orchestra;

        if (temp->csound_mpeg4_instrument_mapping)
            freeCsoundMpeg4PartRefsList(temp->csound_mpeg4_instrument_mapping);

        free(temp);
    }
}

void freeCsoundMpeg4SpineEventsList(struct csound_mpeg4_spine_event* head) {
    struct csound_mpeg4_spine_event* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_spine_event;
        free(temp);
    }
}

void freeCsoundMpeg4ScoresList(struct csound_mpeg4_score* head) {
    struct csound_mpeg4_score* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_score;

        if (temp->csound_mpeg4_spine_event)
            freeCsoundMpeg4SpineEventsList(temp->csound_mpeg4_spine_event);

        free(temp);
    }
}

void freeCsoundMpeg4InstancesList(struct csound_mpeg4_instance* head) {
    struct csound_mpeg4_instance* temp;
    while (head) {
        temp = head;
        head = head->next_csound_mpeg4_instance;

        if (temp->csound_mpeg4_score)
            freeCsoundMpeg4ScoresList(temp->csound_mpeg4_score);
        if (temp->csound_mpeg4_orchestra)
            freeCsoundMpeg4OrtchestrasList(temp->csound_mpeg4_orchestra);

        free(temp);
    }
}

void freePerformanceLayer(struct performance cur) {
    if (cur.midi_instance && cur.n_midi_instances!=0)
        freeMidiInstancesList(cur.midi_instance);
    if (cur.csound_instance && cur.n_csound_instances != 0)
        freeCsoundMpeg4InstancesList(cur.csound_instance);
    if (cur.mpeg4_instance && cur.n_mpeg4_instances != 0)
        freeCsoundMpeg4InstancesList(cur.mpeg4_instance);
}