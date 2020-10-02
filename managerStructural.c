/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerStructural.h"

void loadStructural(){
    loadChordGrid();
    loadAnalysis();
    loadPetriNets();
    loadMir();
}

void loadChordGrid(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct chord_grid* chord_grid_temp=NULL;
    struct chord_grid* chord_grid_head=NULL;
    struct chord_grid* chord_grid_p=NULL;
    structural_layer.n_chord_grids=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/chord_grid";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning chord_grids
            chord_grid_temp=(struct chord_grid*)malloc(sizeof(struct chord_grid));
            chord_grid_temp=calloc(1,sizeof(struct chord_grid));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    chord_grid_temp->id=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"author")){
                    chord_grid_temp->author=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    chord_grid_temp->description=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            
            //load chord_name list
            struct chord_name* chord_name_temp=NULL;
            struct chord_name* chord_name_head=NULL;
            struct chord_name* chord_name_p=NULL;
            chord_grid_temp->n_chord_names=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"chord_name")){
                    chord_name_temp=(struct chord_name*)malloc(sizeof(struct chord_name));
                    chord_name_temp=calloc(1,sizeof(struct chord_name));
                    
                    chord_name_temp->chord_name_value=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
                    
                    attributes=temp_cur->properties;
                    while(attributes!=NULL){
                        if(!xmlStrcmp(attributes->name,(const xmlChar*)"root_id")){
                            chord_name_temp->root_id=xmlGetProp(temp_cur,attributes->name);
                        }
                        attributes=attributes->next;
                    }
                    
                    chord_name_temp->next_chord_name=NULL;
                    if(chord_name_head==NULL)
                        chord_name_head=chord_name_temp;
                    else{
                        chord_name_p=chord_name_head;
                        while(chord_name_p->next_chord_name!=NULL)
                            chord_name_p=chord_name_p->next_chord_name;
                        chord_name_p->next_chord_name=chord_name_temp;
                    }
                    chord_grid_temp->n_chord_names++;
                }
                temp_cur=temp_cur->next;
            }
            chord_grid_temp->chord_names=chord_name_head;
            
            chord_grid_temp->next_chord_grid=NULL;
            if(chord_grid_head==NULL)
                chord_grid_head=chord_grid_temp;
            else{
                chord_grid_p=chord_grid_head;
                while(chord_grid_p->next_chord_grid!=NULL)
                    chord_grid_p=chord_grid_p->next_chord_grid;
                chord_grid_p->next_chord_grid=chord_grid_temp;
            }
            structural_layer.n_chord_grids++;
        }
        structural_layer.chord_grid=chord_grid_head;
    }
}

void loadAnalysis(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct analysis* analysis_temp=NULL;
    struct analysis* analysis_head=NULL;
    struct analysis* analysis_p=NULL;
    structural_layer.n_analysis=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/analysis";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning analysis
            analysis_temp=(struct analysis*)malloc(sizeof(struct analysis));
            analysis_temp=calloc(1,sizeof(struct analysis));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    analysis_temp->id=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"author")){
                    analysis_temp->author=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    analysis_temp->description=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            
            //load analysis elements
            struct relationship* relationship_temp=NULL;
            struct relationship* relationship_head=NULL;
            struct relationship* relationship_p=NULL;
            analysis_temp->n_relationships=0;
            
            struct feature_object_relationship* feature_object_relationship_temp=NULL;
            struct feature_object_relationship* feature_object_relationship_head=NULL;
            struct feature_object_relationship* feature_object_relationship_p=NULL;
            analysis_temp->n_feature_object_relationships=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"segmentation")){
                    analysis_temp->segmentation=loadSegmentation(temp_cur);
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"relationships")){
                    if(temp_cur->xmlChildrenNode!=NULL){
                        temp_cur=temp_cur->xmlChildrenNode;
                        do{
                            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"relationship")){
                                relationship_temp=(struct relationship*)malloc(sizeof(struct relationship));
                                relationship_temp=calloc(1,sizeof(struct relationship));

                                attributes=temp_cur->properties;
                                while(attributes!=NULL){
                                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                                        relationship_temp->id=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                                        relationship_temp->description=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"segment_a_ref")){
                                        relationship_temp->segment_a_ref=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"segment_b_ref")){
                                        relationship_temp->segment_b_ref=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"feature_object_a_ref")){
                                        relationship_temp->feature_object_a_ref=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"feature_object_b_ref")){
                                        relationship_temp->feature_object_b_ref=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"feature_object_relationship_ref")){
                                        relationship_temp->feature_object_relationship_ref=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    attributes=attributes->next;
                                }

                                relationship_temp->next_relationship=NULL;
                                if(relationship_head==NULL)
                                    relationship_head=relationship_temp;
                                else{
                                    relationship_p=relationship_head;
                                    while(relationship_p->next_relationship!=NULL)
                                        relationship_p=relationship_p->next_relationship;
                                    relationship_p->next_relationship=relationship_temp;
                                }
                                analysis_temp->n_relationships++;
                            }
                            temp_cur=temp_cur->next;
                        }while(temp_cur->next!=NULL);
                        temp_cur=temp_cur->parent;
                    }
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"feature_object_relationships")){
                        if(temp_cur->xmlChildrenNode!=NULL){
                        temp_cur=temp_cur->xmlChildrenNode;
                        do{
                            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"feature_object_relationship")){
                                feature_object_relationship_temp=(struct feature_object_relationship*)malloc(sizeof(struct feature_object_relationship));
                                feature_object_relationship_temp=calloc(1,sizeof(struct feature_object_relationship));
                                
                                if(temp_cur->xmlChildrenNode!=NULL){
                                    temp_cur=temp_cur->xmlChildrenNode;
                                    feature_object_relationship_temp->ver_rule=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
                                    temp_cur=temp_cur->parent;
                                }
                                
                                attributes=temp_cur->properties;
                                while(attributes!=NULL){
                                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                                        feature_object_relationship_temp->id=xmlGetProp(temp_cur,attributes->name);
                                    }
                                    attributes=attributes->next;
                                }

                                feature_object_relationship_temp->next_feature_object_relationship=NULL;
                                if(feature_object_relationship_head==NULL)
                                    feature_object_relationship_head=feature_object_relationship_temp;
                                else{
                                    feature_object_relationship_p=feature_object_relationship_head;
                                    while(feature_object_relationship_p->next_feature_object_relationship!=NULL)
                                        feature_object_relationship_p=feature_object_relationship_p->next_feature_object_relationship;
                                    feature_object_relationship_p->next_feature_object_relationship=feature_object_relationship_temp;
                                }
                                analysis_temp->n_feature_object_relationships++;
                            }
                            temp_cur=temp_cur->next;
                        }while(temp_cur->next!=NULL);
                        temp_cur=temp_cur->parent;
                    }
                }
                temp_cur=temp_cur->next;
            }
            analysis_temp->relationships=relationship_head;
            analysis_temp->feature_object_relationships=feature_object_relationship_head;
            
            analysis_temp->next_analysis=NULL;
            if(analysis_head==NULL)
                analysis_head=analysis_temp;
            else{
                analysis_p=analysis_head;
                while(analysis_p->next_analysis!=NULL)
                    analysis_p=analysis_p->next_analysis;
                analysis_p->next_analysis=analysis_temp;
            }
            structural_layer.n_chord_grids++;
        }
        structural_layer.analysis=analysis_head;
    }
}

struct segmentation loadSegmentation(xmlNodePtr cur){
    struct segmentation value;
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    
    struct segment* segment_temp=NULL;
    struct segment* segment_head=NULL;
    struct segment* segment_p=NULL;
    value.n_segments=0;  
   
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value.id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value.description=xmlGetProp(cur,attributes->name);   
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"method")){
            value.method=xmlGetProp(cur,attributes->name);        
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){//scan segment+
        if(!xmlStrcmp(cur->name,(const xmlChar*)"segment")){
            segment_temp=(struct segment*)malloc(sizeof(struct segment));
            segment_temp=calloc(1, sizeof(struct segment*));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    segment_temp->id=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            } 
                                   
            struct segment_event* segment_event_temp=NULL;
            struct segment_event* segment_event_head=NULL;
            struct segment_event* segment_event_p=NULL;
            segment_temp->n_segment_events=0;
            
            struct feature_object* feature_object_temp=NULL;
            struct feature_object* feature_object_head=NULL;
            struct feature_object* feature_object_p=NULL;
            segment_temp->n_feature_objects=0;
            
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"segment_event")){
                    segment_event_temp=(struct segment_event*)malloc(sizeof(struct segment_event));
                    segment_event_temp=calloc(1, sizeof(struct segment_event*));
                    
                    attributes=temp_cur->properties;
                    while(attributes!=NULL){
                        if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                            segment_event_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                        }
                        attributes=attributes->next;
                    } 
                    
                    segment_event_temp->next_segment_event=NULL;
                    if(segment_event_head==NULL)
                        segment_event_head=segment_event_temp;
                    else{
                        segment_event_p=segment_event_head;
                        while(segment_event_p->next_segment_event!=NULL)
                            segment_event_p=segment_event_p->next_segment_event;
                        segment_event_p->next_segment_event=segment_event_temp;
                    }
                    segment_temp->n_segment_events++;
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"feature_object")){
                    feature_object_temp=(struct feature_object*)malloc(sizeof(struct feature_object));
                    feature_object_temp=calloc(1, sizeof(struct feature_object*));
                    
                    feature_object_temp=loadFeatureObject(temp_cur);
                    
                    feature_object_temp->next_feature_object=NULL;
                    if(feature_object_head==NULL)
                        feature_object_head=feature_object_temp;
                    else{
                        feature_object_p=feature_object_head;
                        while(feature_object_p->next_feature_object!=NULL)
                            feature_object_p=feature_object_p->next_feature_object;
                        feature_object_p->next_feature_object=feature_object_temp;
                    }
                    segment_temp->n_feature_objects++;
                }
                temp_cur=temp_cur->next;
            }
            segment_temp->segment_events=segment_event_head;
            segment_temp->feature_objects=feature_object_head;
                        
            segment_temp->next_segment=NULL;
            if(segment_head==NULL)
                segment_head=segment_temp;
            else{
                segment_p=segment_head;
                while(segment_p->next_segment!=NULL)
                    segment_p=segment_p->next_segment;
                segment_p->next_segment=segment_temp;
            }
            value.n_segments++;
        }
        cur=cur->next;
    }
    value.segment=segment_head;
    
    return value;
}

struct feature_object* loadFeatureObject(xmlNodePtr cur){
    struct feature_object* value=(struct feature_object*)malloc(sizeof(struct feature_object));
    value=calloc(1, sizeof(struct feature_object*));
    xmlAttr* attributes; 
    
    value->next_feature_object=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"name")){
            value->name=xmlGetProp(cur,attributes->name);   
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"simple_description")){
            value->simple_description=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }
        cur=cur->next; 
    }
    
    return value; 
}

void loadPetriNets(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct petri_nets* petri_nets_temp=NULL;
    struct petri_nets* petri_nets_head=NULL;
    struct petri_nets* petri_nets_p=NULL;
    structural_layer.n_petri_nets=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/petri_nets";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning petri nets
            petri_nets_temp=(struct petri_nets*)malloc(sizeof(struct petri_nets));
            petri_nets_temp=calloc(1,sizeof(struct petri_nets));
            cur=nodeset->nodeTab[i];
            
            //load petri net list elements
            struct petri_net* petri_net_temp=NULL;
            struct petri_net* petri_net_head=NULL;
            struct petri_net* petri_net_p=NULL;
            petri_nets_temp->n_petri_nets=0;
         
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"petri_net")){
                    petri_net_temp=(struct petri_net*)malloc(sizeof(struct petri_net));
                    petri_net_temp=calloc(1,sizeof(struct petri_net));
                    
                    petri_net_temp=loadPetriNet(temp_cur);
                    
                    petri_net_temp->next_petri_net=NULL;
                    if(petri_net_head==NULL)
                        petri_net_head=petri_net_temp;
                    else{
                        petri_net_p=petri_net_head;
                        while(petri_net_p->next_petri_net!=NULL)
                            petri_net_p=petri_net_p->next_petri_net;
                        petri_net_p->next_petri_net=petri_net_temp;
                    }
                    petri_nets_temp->n_petri_nets++;
                }
                temp_cur=temp_cur->next;
            }
            petri_nets_temp->petri_net_list=petri_net_head;
            
            petri_nets_temp->next_petri_nets=NULL;
            if(petri_nets_head==NULL)
                petri_nets_head=petri_nets_temp;
            else{
                petri_nets_p=petri_nets_head;
                while(petri_nets_p->next_petri_nets!=NULL)
                    petri_nets_p=petri_nets_p->next_petri_nets;
                petri_nets_p->next_petri_nets=petri_nets_temp;
            }
            structural_layer.n_petri_nets++;
        }
        structural_layer.petri_nets=petri_nets_head;
    }
}

struct petri_net* loadPetriNet(xmlNodePtr cur){
    struct petri_net* value=(struct petri_net*)malloc(sizeof(struct petri_net));
    value=calloc(1, sizeof(struct petri_net*));
    xmlAttr* attributes;
    
    struct place* place_temp=NULL;
    struct place* place_head=NULL;
    struct place* place_p=NULL;
    value->n_places=0;
    
    struct transition* transition_temp=NULL;
    struct transition* transition_head=NULL;
    struct transition* transition_p=NULL;
    value->n_transitions=0;
    
    value->next_petri_net=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"author")){
            value->author=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"place")){
            place_temp=(struct place*)malloc(sizeof(struct place));
            place_temp=calloc(1,sizeof(struct place));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"place_ref")){
                    place_temp->place_ref=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"segment_ref")){
                    place_temp->segment_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            
            place_temp->next_place=NULL;
            if(place_head=NULL)
                place_head=place_temp;
            else{
                place_p=place_head;
                while(place_p->next_place!=NULL)
                    place_p=place_p->next_place;
                place_p->next_place=place_temp;
            }
            value->n_places++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"transition")){
            transition_temp=(struct transition*)malloc(sizeof(struct transition));
            transition_temp=calloc(1,sizeof(struct transition));
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"transition_ref")){
                    transition_temp->transition_ref=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"feature_object_relationship_ref")){
                    transition_temp->feature_object_relationship_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            
            transition_temp->next_transition=NULL;
            if(transition_head=NULL)
                transition_head=transition_temp;
            else{
                transition_p=transition_head;
                while(transition_p->next_transition!=NULL)
                    transition_p=transition_p->next_transition;
                transition_p->next_transition=transition_temp;
            }
            value->n_places++;
        }
        cur=cur->next;
    }
    value->places=place_head;
    value->transitions=transition_head;
    
    return value;
}

void loadMir(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlNodePtr temp_cur;
    
    struct mir* mir_temp=NULL;
    struct mir* mir_head=NULL;
    struct mir* mir_p=NULL;
    structural_layer.n_mirs=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/mir";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning mirs
            mir_temp=(struct mir*)malloc(sizeof(struct mir));
            mir_temp=calloc(1,sizeof(struct mir));
            cur=nodeset->nodeTab[i];
            
            //load mir_model elements
            struct mir_model* mir_model_temp=NULL;
            struct mir_model* mir_model_head=NULL;
            struct mir_model* mir_model_p=NULL;
            mir_temp->n_mir_models=0;
         
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"mir_model")){
                    mir_model_temp=(struct mir_model*)malloc(sizeof(struct mir_model));
                    mir_model_temp=calloc(1,sizeof(struct mir_model));
                    
                    mir_model_temp=loadMirModel(temp_cur);
                    
                    mir_model_temp->next_mir_model=NULL;
                    if(mir_model_head==NULL)
                        mir_model_head=mir_model_temp;
                    else{
                        mir_model_p=mir_model_head;
                        while(mir_model_p->next_mir_model!=NULL)
                            mir_model_p=mir_model_p->next_mir_model;
                        mir_model_p->next_mir_model=mir_model_temp;
                    }
                    mir_temp->n_mir_models++;
                }
                temp_cur=temp_cur->next;
            }
            mir_temp->mir_models=mir_model_head;
            
            mir_temp->next_mir=NULL;
            if(mir_head==NULL)
                mir_head=mir_temp;
            else{
                mir_p=mir_head;
                while(mir_p->next_mir!=NULL)
                    mir_p=mir_p->next_mir;
                mir_p->next_mir=mir_temp;
            }
            structural_layer.n_mirs++;
        }
        structural_layer.mir=mir_head;
    }
}

struct mir_model* loadMirModel(xmlNodePtr cur){
    struct mir_model* value=(struct mir_model*)malloc(sizeof(struct mir_model));
    value=calloc(1, sizeof(struct mir_model*));
    xmlAttr* attributes;
    
    struct mir_object* mir_object_temp=NULL;
    struct mir_object* mir_object_head=NULL;
    struct mir_object* mir_object_p=NULL;
    value->n_mir_objects=0;
    
    struct mir_morphism* mir_morphism_temp=NULL;
    struct mir_morphism* mir_morphism_head=NULL;
    struct mir_morphism* mir_morphism_p=NULL;
    value->n_mir_morphisms=0;
    
    value->next_mir_model=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value->file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_object")){
            mir_object_temp=(struct mir_object*)malloc(sizeof(struct mir_object));
            mir_object_temp=calloc(1,sizeof(struct mir_object));
            
            mir_object_temp=loadMirObject(cur);
                       
            mir_object_temp->next_mir_object=NULL;
            if(mir_object_head==NULL)
                mir_object_head=mir_object_temp;
            else{
                mir_object_p=mir_object_head;
                while(mir_object_p->next_mir_object!=NULL)
                    mir_object_p=mir_object_p->next_mir_object;
                mir_object_p->next_mir_object=mir_object_temp;
            }
            value->n_mir_objects++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_morphism")){
            mir_morphism_temp=(struct mir_morphism*)malloc(sizeof(struct mir_morphism));
            mir_morphism_temp=calloc(1,sizeof(struct mir_morphism));
            
            mir_morphism_temp=loadMirMorphism(cur);
            
            mir_morphism_temp->next_mir_morphism=NULL;
            if(mir_morphism_head==NULL)
                mir_morphism_head=mir_morphism_temp;
            else{
                mir_morphism_p=mir_morphism_head;
                while(mir_morphism_p->next_mir_morphism!=NULL)
                    mir_morphism_p=mir_morphism_p->next_mir_morphism;
                mir_morphism_p->next_mir_morphism=mir_morphism_temp;
            }
            value->n_mir_morphisms++;                 
        }
        cur=cur->next;
    }
    value->mir_objects=mir_object_head;
    value->mir_morphisms=mir_morphism_head;
    
    return value;
}

struct mir_object* loadMirObject(xmlNodePtr cur){
    struct mir_object* value=(struct mir_object*)malloc(sizeof(struct mir_object));
    value=calloc(1, sizeof(struct mir_object*));
    xmlAttr* attributes;
    
    struct mir_subobject* mir_subobject_temp=NULL;
    struct mir_subobject* mir_subobject_head=NULL;
    struct mir_subobject* mir_subobject_p=NULL;
    value->n_mir_subobjects=0;
    
    struct mir_feature* mir_feature_temp=NULL;
    struct mir_feature* mir_feature_head=NULL;
    struct mir_feature* mir_feature_p=NULL;
    value->n_mir_features=0;
    
    value->next_mir_object=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"displacement_ref")){
            value->displacement_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_subobject")){
            mir_subobject_temp=(struct mir_subobject*)malloc(sizeof(struct mir_subobject));
            mir_subobject_temp=calloc(1,sizeof(struct mir_subobject));
            
            mir_subobject_temp=loadMirSubobject(cur);
                       
            mir_subobject_temp->next_mir_subobject=NULL;
            if(mir_subobject_head==NULL)
                mir_subobject_head=mir_subobject_temp;
            else{
                mir_subobject_p=mir_subobject_head;
                while(mir_subobject_p->next_mir_subobject!=NULL)
                    mir_subobject_p=mir_subobject_p->next_mir_subobject;
                mir_subobject_p->next_mir_subobject=mir_subobject_temp;
            }
            value->n_mir_subobjects++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_feature")){
            mir_feature_temp=(struct mir_feature*)malloc(sizeof(struct mir_feature));
            mir_feature_temp=calloc(1,sizeof(struct mir_feature));
            
            mir_feature_temp=loadMirFeature(cur);
                       
            mir_feature_temp->next_mir_feature=NULL;
            if(mir_feature_head==NULL)
                mir_feature_head=mir_feature_temp;
            else{
                mir_feature_p=mir_feature_head;
                while(mir_feature_p->next_mir_feature!=NULL)
                    mir_feature_p=mir_feature_p->next_mir_feature;
                mir_feature_p->next_mir_feature=mir_feature_temp;
            }
            value->n_mir_features++;
        }
        cur=cur->next;
    }
    value->mir_features=mir_feature_head;
}

struct mir_subobject* loadMirSubobject(xmlNodePtr cur){
    struct mir_subobject* value=(struct mir_subobject*)malloc(sizeof(struct mir_subobject));
    value=calloc(1, sizeof(struct mir_subobject*));
    xmlAttr* attributes;
    
    struct mir_feature* mir_feature_temp=NULL;
    struct mir_feature* mir_feature_head=NULL;
    struct mir_feature* mir_feature_p=NULL;
    value->n_mir_features=0;
    
    value->next_mir_subobject=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"displacement_ref")){
            value->displacement_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"segment_ref")){
            value->segment_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }   
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_feature")){
            mir_feature_temp=(struct mir_feature*)malloc(sizeof(struct mir_feature));
            mir_feature_temp=calloc(1,sizeof(struct mir_feature));
            
            mir_feature_temp=loadMirFeature(cur);
                       
            mir_feature_temp->next_mir_feature=NULL;
            if(mir_feature_head==NULL)
                mir_feature_head=mir_feature_temp;
            else{
                mir_feature_p=mir_feature_head;
                while(mir_feature_p->next_mir_feature!=NULL)
                    mir_feature_p=mir_feature_p->next_mir_feature;
                mir_feature_p->next_mir_feature=mir_feature_temp;
            }
            value->n_mir_features++;
        }
        cur=cur->next;
    }
    value->mir_features=mir_feature_head;
    
    return value;
}

struct mir_morphism* loadMirMorphism(xmlNodePtr cur){
    struct mir_morphism* value=(struct mir_morphism*)malloc(sizeof(struct mir_morphism));
    value=calloc(1, sizeof(struct mir_morphism*));
    xmlAttr* attributes;
    
    struct mir_feature* mir_feature_temp=NULL;
    struct mir_feature* mir_feature_head=NULL;
    struct mir_feature* mir_feature_p=NULL;
    value->n_mir_features=0;
    
    value->next_mir_morphism=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"domain_ref")){
            value->domain_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"codomain_ref")){
            value->codomain_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"displacement_ref")){
            value->displacement_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"mir_feature")){
            mir_feature_temp=(struct mir_feature*)malloc(sizeof(struct mir_feature));
            mir_feature_temp=calloc(1,sizeof(struct mir_feature));
            
            mir_feature_temp=loadMirFeature(cur);
                       
            mir_feature_temp->next_mir_feature=NULL;
            if(mir_feature_head==NULL)
                mir_feature_head=mir_feature_temp;
            else{
                mir_feature_p=mir_feature_head;
                while(mir_feature_p->next_mir_feature!=NULL)
                    mir_feature_p=mir_feature_p->next_mir_feature;
                mir_feature_p->next_mir_feature=mir_feature_temp;
            }
            value->n_mir_features++;
        }
        cur=cur->next;
    }
    value->mir_features=mir_feature_head;
 
}

struct mir_feature* loadMirFeature(xmlNodePtr cur){
    struct mir_feature* value=(struct mir_feature*)malloc(sizeof(struct mir_feature));
    value=calloc(1, sizeof(struct mir_feature*));
    xmlAttr* attributes;
    
    value->next_mir_feature=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"displacement_ref")){
            value->displacement_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    return value;
}

void printStructural(){

}