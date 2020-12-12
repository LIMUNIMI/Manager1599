/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerStructural.h"

static struct structural structural_layer;

struct structural loadStructural(){
    loadChordGrid();
    loadAnalysis();
    loadPetriNets();
    loadMir();
    
    return structural_layer;
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
            chord_grid_temp=(struct chord_grid*)calloc(1,sizeof(struct chord_grid));
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
                    chord_name_temp=(struct chord_name*)calloc(1,sizeof(struct chord_name));
                    

                    if (chord_name_temp) {
                        chord_name_temp->chord_name_value = xmlNodeListGetString(doc, temp_cur->xmlChildrenNode, 1);

                        attributes = temp_cur->properties;
                        while (attributes != NULL) {
                            if (!xmlStrcmp(attributes->name, (const xmlChar*)"root_id")) {
                                chord_name_temp->root_id = xmlGetProp(temp_cur, attributes->name);
                            }
                            attributes = attributes->next;
                        }

                        chord_name_temp->next_chord_name = NULL;
                        if (chord_name_head == NULL)
                            chord_name_head = chord_name_temp;
                        else {
                            chord_name_p = chord_name_head;
                            while (chord_name_p->next_chord_name != NULL)
                                chord_name_p = chord_name_p->next_chord_name;
                            chord_name_p->next_chord_name = chord_name_temp;
                        }
                        chord_grid_temp->n_chord_names++;
                    }
                    else { fprintf(stderr, "Memory allocation failed for 'chord_name' element\n");  }
                }
                temp_cur=temp_cur->next;
            }
            chord_grid_temp->chord_name=chord_name_head;
            
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
    }
    structural_layer.chord_grid = chord_grid_head;
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
            analysis_temp=(struct analysis*)calloc(1,sizeof(struct analysis));
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
                        int last = 0;
                        do{
                            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"relationship")){
                                relationship_temp=(struct relationship*)calloc(1,sizeof(struct relationship));

                                if (relationship_temp) {
                                    attributes = temp_cur->properties;
                                    while (attributes != NULL) {
                                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                                            relationship_temp->id = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                                            relationship_temp->description = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"segment_a_ref")) {
                                            relationship_temp->segment_a_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"segment_b_ref")) {
                                            relationship_temp->segment_b_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"feature_object_a_ref")) {
                                            relationship_temp->feature_object_a_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"feature_object_b_ref")) {
                                            relationship_temp->feature_object_b_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"feature_object_relationship_ref")) {
                                            relationship_temp->feature_object_relationship_ref = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        attributes = attributes->next;
                                    }

                                    relationship_temp->next_relationship = NULL;
                                    if (relationship_head == NULL)
                                        relationship_head = relationship_temp;
                                    else {
                                        relationship_p = relationship_head;
                                        while (relationship_p->next_relationship != NULL)
                                            relationship_p = relationship_p->next_relationship;
                                        relationship_p->next_relationship = relationship_temp;
                                    }
                                    analysis_temp->n_relationships++;
                                }
                                else { fprintf(stderr, "Memory allocation failed for 'relationship' element\n"); }
                            }
                            if (temp_cur->next != NULL)
                                temp_cur = temp_cur->next;
                            else
                                last = 1;
                        }while(!last);
                        temp_cur=temp_cur->parent;
                    }
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"feature_object_relationships")){
                    if(temp_cur->xmlChildrenNode!=NULL){
                        temp_cur=temp_cur->xmlChildrenNode;
                        int last = 0;
                        do{
                            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"feature_object_relationship")){
                                feature_object_relationship_temp=(struct feature_object_relationship*)calloc(1,sizeof(struct feature_object_relationship));
                                
                                if (feature_object_relationship_temp) {
                                    if (temp_cur->xmlChildrenNode != NULL) {
                                        temp_cur = temp_cur->xmlChildrenNode;
                                        feature_object_relationship_temp->ver_rule = xmlNodeListGetString(doc, temp_cur->xmlChildrenNode, 1);
                                        temp_cur = temp_cur->parent;
                                    }

                                    attributes = temp_cur->properties;
                                    while (attributes != NULL) {
                                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                                            feature_object_relationship_temp->id = xmlGetProp(temp_cur, attributes->name);
                                        }
                                        attributes = attributes->next;
                                    }

                                    feature_object_relationship_temp->next_feature_object_relationship = NULL;
                                    if (feature_object_relationship_head == NULL)
                                        feature_object_relationship_head = feature_object_relationship_temp;
                                    else {
                                        feature_object_relationship_p = feature_object_relationship_head;
                                        while (feature_object_relationship_p->next_feature_object_relationship != NULL)
                                            feature_object_relationship_p = feature_object_relationship_p->next_feature_object_relationship;
                                        feature_object_relationship_p->next_feature_object_relationship = feature_object_relationship_temp;
                                    }
                                    analysis_temp->n_feature_object_relationships++;
                                }
                                else { fprintf(stderr, "Memory allocation failed for 'feature_object_relationship' element\n"); }
                            }
                            if (temp_cur->next != NULL)
                                temp_cur = temp_cur->next;
                            else
                                last = 1;
                        } while (!last);
                        temp_cur=temp_cur->parent;
                    }
                }
                temp_cur=temp_cur->next;
            }
            analysis_temp->relationships=relationship_head;
            analysis_temp->feature_object_relationship=feature_object_relationship_head;
            
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
    }
    structural_layer.analysis = analysis_head;
}

struct segmentation* loadSegmentation(xmlNodePtr cur){
    struct segmentation* value = (struct segmentation*)calloc(1, sizeof(struct segmentation));
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    
    if (value) {
        struct segment* segment_temp = NULL;
        struct segment* segment_head = NULL;
        struct segment* segment_p = NULL;
        value->n_segments = 0;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"method")) {
                value->method = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {//scan segment+
            if (!xmlStrcmp(cur->name, (const xmlChar*)"segment")) {
                segment_temp = (struct segment*)calloc(1, sizeof(struct segment));

                if (segment_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                            segment_temp->id = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    struct segment_event* segment_event_temp = NULL;
                    struct segment_event* segment_event_head = NULL;
                    struct segment_event* segment_event_p = NULL;
                    segment_temp->n_segment_events = 0;

                    struct feature_object* feature_object_temp = NULL;
                    struct feature_object* feature_object_head = NULL;
                    struct feature_object* feature_object_p = NULL;
                    segment_temp->n_feature_objects = 0;

                    temp_cur = cur->xmlChildrenNode;
                    while (temp_cur != NULL) {
                        if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"segment_event")) {
                            segment_event_temp = (struct segment_event*)calloc(1, sizeof(struct segment_event));

                            if (segment_event_temp) {
                                attributes = temp_cur->properties;
                                while (attributes != NULL) {
                                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                                        segment_event_temp->event_ref = xmlGetProp(temp_cur, attributes->name);
                                    }
                                    attributes = attributes->next;
                                }

                                segment_event_temp->next_segment_event = NULL;
                                if (segment_event_head == NULL)
                                    segment_event_head = segment_event_temp;
                                else {
                                    segment_event_p = segment_event_head;
                                    while (segment_event_p->next_segment_event != NULL)
                                        segment_event_p = segment_event_p->next_segment_event;
                                    segment_event_p->next_segment_event = segment_event_temp;
                                }
                                segment_temp->n_segment_events++;
                            }
                            else { fprintf(stderr, "Memory allocation failed for 'segment_event' element\n"); }
                        }
                        else if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"feature_object")) {
                            feature_object_temp = (struct feature_object*)calloc(1, sizeof(struct feature_object));

                            feature_object_temp = loadFeatureObject(temp_cur);

                            feature_object_temp->next_feature_object = NULL;
                            if (feature_object_head == NULL)
                                feature_object_head = feature_object_temp;
                            else {
                                feature_object_p = feature_object_head;
                                while (feature_object_p->next_feature_object != NULL)
                                    feature_object_p = feature_object_p->next_feature_object;
                                feature_object_p->next_feature_object = feature_object_temp;
                            }
                            segment_temp->n_feature_objects++;
                        }
                        temp_cur = temp_cur->next;
                    }
                    segment_temp->segment_event = segment_event_head;
                    segment_temp->feature_object = feature_object_head;

                    segment_temp->next_segment = NULL;
                    if (segment_head == NULL)
                        segment_head = segment_temp;
                    else {
                        segment_p = segment_head;
                        while (segment_p->next_segment != NULL)
                            segment_p = segment_p->next_segment;
                        segment_p->next_segment = segment_temp;
                    }
                    value->n_segments++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'segment' element\n"); }
            }
            cur = cur->next;
        }
        value->segment = segment_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'segmentation' element\n"); }

    return value;
}

struct feature_object* loadFeatureObject(xmlNodePtr cur){
    struct feature_object* value=(struct feature_object*)calloc(1, sizeof(struct feature_object));
    xmlAttr* attributes; 
    
    if (value) {
        value->next_feature_object = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"name")) {
                value->name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"simple_description")) {
                value->simple_description = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            }
            cur = cur->next;
        }
    }
    else { fprintf(stderr, "Memory allocation failed for 'feature_object' element\n"); }
    
    return value; 
}

void loadPetriNets(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    
    struct petri_net* petri_net_temp=NULL;
    struct petri_net* petri_net_head=NULL;
    struct petri_net* petri_net_p=NULL;
    structural_layer.n_petri_nets=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/petri_nets/petri_net";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning petri nets
            cur=nodeset->nodeTab[i];
            if (!xmlStrcmp(cur->name, (const xmlChar*)"petri_net")) {
                petri_net_temp = (struct petri_net*)calloc(1, sizeof(struct petri_net));

                petri_net_temp = loadPetriNet(cur);

                petri_net_temp->next_petri_net = NULL;
                if (petri_net_head == NULL)
                    petri_net_head = petri_net_temp;
                else {
                    petri_net_p = petri_net_head;
                    while (petri_net_p->next_petri_net != NULL)
                        petri_net_p = petri_net_p->next_petri_net;
                    petri_net_p->next_petri_net = petri_net_temp;
                }
                structural_layer.n_petri_nets++;
            }
        }
    }
    structural_layer.petri_nets = petri_net_head;
}

struct petri_net* loadPetriNet(xmlNodePtr cur){
    struct petri_net* value=(struct petri_net*)calloc(1, sizeof(struct petri_net));

    if (value) {
        xmlAttr* attributes;

        struct place* place_temp = NULL;
        struct place* place_head = NULL;
        struct place* place_p = NULL;
        value->n_places = 0;

        struct transition* transition_temp = NULL;
        struct transition* transition_head = NULL;
        struct transition* transition_p = NULL;
        value->n_transitions = 0;

        value->next_petri_net = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"author")) {
                value->author = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"place")) {
                place_temp = (struct place*)calloc(1, sizeof(struct place));

                if (place_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"place_ref")) {
                            place_temp->place_ref = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"segment_ref")) {
                            place_temp->segment_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    place_temp->next_place = NULL;
                    if (place_head == NULL)
                        place_head = place_temp;
                    else {
                        place_p = place_head;
                        while (place_p->next_place != NULL)
                            place_p = place_p->next_place;
                        place_p->next_place = place_temp;
                    }
                    value->n_places++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'place' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"transition")) {
                transition_temp = (struct transition*)calloc(1, sizeof(struct transition));

                if (transition_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"transition_ref")) {
                            transition_temp->transition_ref = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"feature_object_relationship_ref")) {
                            transition_temp->feature_object_relationship_ref = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    transition_temp->next_transition = NULL;
                    if (transition_head == NULL)
                        transition_head = transition_temp;
                    else {
                        transition_p = transition_head;
                        while (transition_p->next_transition != NULL)
                            transition_p = transition_p->next_transition;
                        transition_p->next_transition = transition_temp;
                    }
                    value->n_transitions++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'transition' element\n"); }
            }
            cur = cur->next;
        }
        value->place = place_head;
        value->transition = transition_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'petri_net' element\n"); }
    
    return value;
}

void loadMir(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    
    struct mir_model* mir_model_temp = NULL;
    struct mir_model* mir_model_head = NULL;
    struct mir_model* mir_model_p = NULL;
    structural_layer.n_mir_models=0;
    
    xpath=(xmlChar *)"/ieee1599/structural/mir/mir_model";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){
            mir_model_temp=(struct mir_model*)calloc(1,sizeof(struct mir_model));
            cur=nodeset->nodeTab[i];
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_model")) {
                mir_model_temp = (struct mir_model*)calloc(1, sizeof(struct mir_model));
                mir_model_temp = loadMirModel(cur);
                mir_model_temp->next_mir_model = NULL;
                if (mir_model_head == NULL)
                    mir_model_head = mir_model_temp;
                else {
                    mir_model_p = mir_model_head;
                    while (mir_model_p->next_mir_model != NULL)
                        mir_model_p = mir_model_p->next_mir_model;
                    mir_model_p->next_mir_model = mir_model_temp;
                }
                structural_layer.n_mir_models++;
            }
        }
        structural_layer.mir = mir_model_head;
    }
}

struct mir_model* loadMirModel(xmlNodePtr cur){
    struct mir_model* value=(struct mir_model*)calloc(1, sizeof(struct mir_model));
    xmlAttr* attributes;
    
    if (value) {
        struct mir_object* mir_object_temp = NULL;
        struct mir_object* mir_object_head = NULL;
        struct mir_object* mir_object_p = NULL;
        value->n_mir_objects = 0;

        struct mir_morphism* mir_morphism_temp = NULL;
        struct mir_morphism* mir_morphism_head = NULL;
        struct mir_morphism* mir_morphism_p = NULL;
        value->n_mir_morphisms = 0;

        value->next_mir_model = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_object")) {
                mir_object_temp = (struct mir_object*)calloc(1, sizeof(struct mir_object));

                mir_object_temp = loadMirObject(cur);

                mir_object_temp->next_mir_object = NULL;
                if (mir_object_head == NULL)
                    mir_object_head = mir_object_temp;
                else {
                    mir_object_p = mir_object_head;
                    while (mir_object_p->next_mir_object != NULL)
                        mir_object_p = mir_object_p->next_mir_object;
                    mir_object_p->next_mir_object = mir_object_temp;
                }
                value->n_mir_objects++;
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_morphism")) {
                mir_morphism_temp = (struct mir_morphism*) calloc(1, sizeof(struct mir_morphism));

                mir_morphism_temp = loadMirMorphism(cur);

                mir_morphism_temp->next_mir_morphism = NULL;
                if (mir_morphism_head == NULL)
                    mir_morphism_head = mir_morphism_temp;
                else {
                    mir_morphism_p = mir_morphism_head;
                    while (mir_morphism_p->next_mir_morphism != NULL)
                        mir_morphism_p = mir_morphism_p->next_mir_morphism;
                    mir_morphism_p->next_mir_morphism = mir_morphism_temp;
                }
                value->n_mir_morphisms++;
            }
            cur = cur->next;
        }
        value->mir_object = mir_object_head;
        value->mir_morphism = mir_morphism_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mir_model' element\n"); }

    return value;
}

struct mir_object* loadMirObject(xmlNodePtr cur){
    struct mir_object* value=(struct mir_object*)calloc(1, sizeof(struct mir_object));

    if (value) {
        xmlAttr* attributes;

        struct mir_subobject* mir_subobject_temp = NULL;
        struct mir_subobject* mir_subobject_head = NULL;
        struct mir_subobject* mir_subobject_p = NULL;
        value->n_mir_subobjects = 0;

        struct mir_feature* mir_feature_temp = NULL;
        struct mir_feature* mir_feature_head = NULL;
        struct mir_feature* mir_feature_p = NULL;
        value->n_mir_features = 0;

        value->next_mir_object = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"displacement_ref")) {
                value->displacement_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_subobject")) {
                mir_subobject_temp = (struct mir_subobject*)calloc(1, sizeof(struct mir_subobject));

                mir_subobject_temp = loadMirSubobject(cur);

                mir_subobject_temp->next_mir_subobject = NULL;
                if (mir_subobject_head == NULL)
                    mir_subobject_head = mir_subobject_temp;
                else {
                    mir_subobject_p = mir_subobject_head;
                    while (mir_subobject_p->next_mir_subobject != NULL)
                        mir_subobject_p = mir_subobject_p->next_mir_subobject;
                    mir_subobject_p->next_mir_subobject = mir_subobject_temp;
                }
                value->n_mir_subobjects++;
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_feature")) {
                mir_feature_temp = (struct mir_feature*)calloc(1, sizeof(struct mir_feature));

                mir_feature_temp = loadMirFeature(cur);

                mir_feature_temp->next_mir_feature = NULL;
                if (mir_feature_head == NULL)
                    mir_feature_head = mir_feature_temp;
                else {
                    mir_feature_p = mir_feature_head;
                    while (mir_feature_p->next_mir_feature != NULL)
                        mir_feature_p = mir_feature_p->next_mir_feature;
                    mir_feature_p->next_mir_feature = mir_feature_temp;
                }
                value->n_mir_features++;
            }
            cur = cur->next;
        }
        value->mir_feature = mir_feature_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mir_object' element\n"); }

    return value;
}

struct mir_subobject* loadMirSubobject(xmlNodePtr cur){
    struct mir_subobject* value=(struct mir_subobject*)calloc(1, sizeof(struct mir_subobject));
    xmlAttr* attributes;
    
    if (value) {
        struct mir_feature* mir_feature_temp = NULL;
        struct mir_feature* mir_feature_head = NULL;
        struct mir_feature* mir_feature_p = NULL;
        value->n_mir_features = 0;

        value->next_mir_subobject = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"displacement_ref")) {
                value->displacement_ref = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"segment_ref")) {
                value->segment_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_feature")) {
                mir_feature_temp = (struct mir_feature*) calloc(1, sizeof(struct mir_feature));

                mir_feature_temp = loadMirFeature(cur);

                mir_feature_temp->next_mir_feature = NULL;
                if (mir_feature_head == NULL)
                    mir_feature_head = mir_feature_temp;
                else {
                    mir_feature_p = mir_feature_head;
                    while (mir_feature_p->next_mir_feature != NULL)
                        mir_feature_p = mir_feature_p->next_mir_feature;
                    mir_feature_p->next_mir_feature = mir_feature_temp;
                }
                value->n_mir_features++;
            }
            cur = cur->next;
        }
        value->mir_feature = mir_feature_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mir_subobject' element\n"); }
    
    return value;
}

struct mir_morphism* loadMirMorphism(xmlNodePtr cur){
    struct mir_morphism* value=(struct mir_morphism*)calloc(1, sizeof(struct mir_morphism));
    xmlAttr* attributes;

    if (value) {
        struct mir_feature* mir_feature_temp = NULL;
        struct mir_feature* mir_feature_head = NULL;
        struct mir_feature* mir_feature_p = NULL;
        value->n_mir_features = 0;

        value->next_mir_morphism = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"domain_ref")) {
                value->domain_ref = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"codomain_ref")) {
                value->codomain_ref = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"displacement_ref")) {
                value->displacement_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"mir_feature")) {
                mir_feature_temp = (struct mir_feature*)calloc(1, sizeof(struct mir_feature));

                mir_feature_temp = loadMirFeature(cur);

                mir_feature_temp->next_mir_feature = NULL;
                if (mir_feature_head == NULL)
                    mir_feature_head = mir_feature_temp;
                else {
                    mir_feature_p = mir_feature_head;
                    while (mir_feature_p->next_mir_feature != NULL)
                        mir_feature_p = mir_feature_p->next_mir_feature;
                    mir_feature_p->next_mir_feature = mir_feature_temp;
                }
                value->n_mir_features++;
            }
            cur = cur->next;
        }
        value->mir_feature = mir_feature_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'mir_morphism' element\n"); }
 
    return value;
}

struct mir_feature* loadMirFeature(xmlNodePtr cur){
    struct mir_feature* value=(struct mir_feature*)calloc(1, sizeof(struct mir_feature));
    xmlAttr* attributes;
    
    if (value) {
        value->next_mir_feature = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"id")) {
                value->id = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"displacement_ref")) {
                value->displacement_ref = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }
    }
    else { fprintf(stderr, "Memory allocation failed for 'mir_feature' element\n"); }
    
    return value;
}

void printStructural(){

    if (structural_layer.n_chord_grids!=0 || 
        structural_layer.n_analysis != 0 ||
        structural_layer.n_petri_nets != 0 ||
        structural_layer.n_mir_models != 0
        ) {
        printf("\n###Structural Layer###\n");
        printChordGrid();
        printAnalysis();
        printPetriNet();
        printMir();
    }
}

void printChordGrid() {
    if (structural_layer.n_chord_grids != 0) {
        printf("%i chord grids\n", structural_layer.n_chord_grids);
        struct chord_grid* p = structural_layer.chord_grid;
        while (p) {
            printf("Chord Grid: ");
            if (p->id)
                printf("id=%s ",p->id);
            if (p->author)
                printf("author=%s ", p->author);
            if (p->description)
                printf("description=%s ", p->description);

            if (p->n_chord_names != 0) {
                struct chord_name* k = p->chord_name;
                printf("( Chord Names: ");
                while (k) {
                    if (k->chord_name_value)
                        printf("%s ", k->chord_name_value);
                    if (k->root_id)
                        printf("id=%s",k->root_id);
                    k = k->next_chord_name;
                }
                printf(") ");
            }
            printf("\n");
            p = p->next_chord_grid;
        }
    }
}

void printAnalysis() {
    if (structural_layer.n_analysis != 0) {
        printf("%i analysis\n", structural_layer.n_analysis);
        struct analysis* p = structural_layer.analysis;
        while (p) {
            printf("Analysis: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->author)
                printf("author=%s ", p->author);
            if (p->description)
                printf("description=%s ", p->description);
            printf("\n");

            if (p->segmentation->n_segments != 0) {
                printf("    Segmentation: ");
                if (p->segmentation->id)
                    printf("id=%s ", p->segmentation->id);
                if (p->segmentation->description)
                    printf("description=%s ", p->segmentation->description);
                if (p->segmentation->description)
                    printf("method=%s ", p->segmentation->method);
                struct segment* k = p->segmentation->segment;
                printf("( Segments:");
                while (k) {
                    if (k->id)
                        printf("id=%s ",k->id);
                    if (k->n_segment_events != 0){
                        struct segment_event* t = k->segment_event;
                        printf("[ Segments: ");
                        while (t) {
                            if (t->event_ref)
                                printf("event_ref=%s ",t->event_ref);
                            t = t->next_segment_event;
                        }
                        printf("] ");
                    }
                    if (k->n_feature_objects != 0) {
                        struct feature_object* t = k->feature_object;
                        printf("[ Feature Object: ");
                        while (t) {
                            if (t->id)
                                printf("id=%s ", t->id);
                            if (t->name)
                                printf("name=%s ", t->name);

                            if (t->simple_description)
                                printf("simple_description=%s ", t->simple_description);
                            t = t->next_feature_object;
                        }
                        printf("] ");
                    }
                    k = k->next_segment;
                }
                printf(")\n");
            }
            if (p->n_relationships != 0) {
                struct relationship* k = p->relationships;
                while (k) {
                    printf("    Relationships: ");
                    if (k->id)
                        printf("id=%s ", k->id);
                    if (k->description)
                        printf("description=%s", k->description);
                    if (k->segment_a_ref)
                        printf("segment_a_ref=%s", k->segment_a_ref);
                    if (k->segment_b_ref)
                        printf("segment_b_ref=%s", k->segment_b_ref);
                    if (k->feature_object_a_ref)
                        printf("feature_object_a_ref=%s", k->feature_object_a_ref);
                    if (k->feature_object_b_ref)
                        printf("feature_object_b_ref=%s", k->feature_object_b_ref);
                    if (k->feature_object_relationship_ref)
                        printf("feature_object_relationship_ref=%s", k->feature_object_relationship_ref);
                    printf("\n");
                    k = k->next_relationship;
                }
            }
            if (p->n_feature_object_relationships != 0) {
                struct feature_object_relationship* k = p->feature_object_relationship;
                while (k) {
                    printf("    Feature Object Relationship: ");
                    if (k->id)
                        printf("id=%s ", k->id);
                    if (k->ver_rule)
                        printf("ver_rule=%s", k->ver_rule);
                    printf("\n");
                    k = k->next_feature_object_relationship;
                }             
            }
            p = p->next_analysis;
        }
    }
}

void printPetriNet() {
    if (structural_layer.n_petri_nets != 0) {
        printf("%i petri nets\n", structural_layer.n_petri_nets);
        struct petri_net* p = structural_layer.petri_nets;
        while (p) {
            printf("Petri Net: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->author)
                printf("author=%s ", p->author);
            if (p->description)
                printf("description=%s ", p->description);
            if (p->file_name)
                printf("file_name=%s ", p->file_name);
            printf("\n");

            if (p->n_places != 0) {
                struct place* k = p->place;
                int i = 0;
                while (k && i < N_DISPLAY) {
                    i++;
                    printf("    Place: ");
                    if (k->place_ref)
                        printf("place_ref=%s ", k->place_ref);
                    if (k->segment_ref)
                        printf("segment_ref=%s ", k->segment_ref);
                    printf("\n");
                    k = k->next_place;
                }
                if (p->n_places>N_DISPLAY) printf("  ...");
            }
            if (p->n_transitions != 0) {
                struct transition* k = p->transition;
                int i = 0;
                while (k && i < N_DISPLAY) {
                    i++;
                    printf("    Transition: ");
                    if (k->transition_ref)
                        printf("transition_ref=%s ", k->transition_ref);
                    if (k->feature_object_relationship_ref)
                        printf("feature_object_relationship_ref=%s ", k->feature_object_relationship_ref);
                    printf("\n");
                    k = k->next_transition;
                }
                if (p->n_transitions > N_DISPLAY) printf("  ...");
            }
            p = p->next_petri_net;
        }
    }
}

void printMir() {
    if (structural_layer.n_mir_models != 0) {
        printf("%i mir models\n", structural_layer.n_mir_models);
        struct mir_model* p = structural_layer.mir;
        while (p) {
            printf("Mir Model: ");
            if (p->id)
                printf("id=%s ", p->id);
            if (p->description)
                printf("description=%s ", p->description);
            if (p->file_name)
                printf("file_name=%s ", p->file_name);
            printf("\n");

            if (p->n_mir_objects != 0) {
                struct mir_object* k = p->mir_object;
                while (k) {
                    printf("    Object: ");
                    if (k->id)
                        printf("id=%s ", k->id);
                    if (k->description)
                        printf("description=%s ", k->description);
                    if (k->displacement_ref)
                        printf("displacement_ref=%s ", k->displacement_ref);
                    printf("\n");
                    if (k->n_mir_subobjects != 0) {
                        struct mir_subobject* t = k->mir_subobject;
                        printf("        %i subobjects\n", k->n_mir_subobjects);
                        while (t) {
                            printf("        Subobject: ");
                            if (t->id)
                                printf("id=%s ", t->id);
                            if (t->description)
                                printf("description=%s ", t->description);
                            if (t->displacement_ref)
                                printf("displacement_ref=%s ", t->displacement_ref);
                            if (t->segment_ref)
                                printf("segment_ref=%s ", t->segment_ref);
                            printf("\n");
                            if (t->n_mir_features != 0) {
                                struct mir_feature* j = k->mir_feature;
                                printf("            %i features\n", t->n_mir_features);
                                while (j) {
                                    printf("            Feature: ");
                                    if (j->id)
                                        printf("id=%s ", j->id);
                                    if (j->description)
                                        printf("description=%s ", j->description);
                                    if (j->displacement_ref)
                                        printf("displacement_ref=%s ", j->displacement_ref);
                                    printf("\n");
                                    j = j->next_mir_feature;
                                }
                            }
                            t = t->next_mir_subobject;
                        }
                    }
                    if (k->n_mir_features != 0) {
                        struct mir_feature* t = k->mir_feature;
                        printf("        %i features\n", k->n_mir_features);
                        while (t) {
                            printf("        Feature: ");
                            if (t->id)
                                printf("id=%s ", t->id);
                            if (t->description)
                                printf("description=%s ", t->description);
                            if (t->displacement_ref)
                                printf("displacement_ref=%s ", t->displacement_ref);
                            printf("\n");
                            t = t->next_mir_feature;
                        }
                    }
                    k = k->next_mir_object;
                }
                printf(")\n");
            }
            if (p->n_mir_morphisms != 0) {
                struct mir_morphism* k = p->mir_morphism;
                while (k) {
                    printf("    Morphism: ");
                    if (k->id)
                        printf("id=%s ", k->id);
                    if (k->description)
                        printf("description=%s", k->description);
                    if (k->domain_ref)
                        printf("domain_ref=%s", k->domain_ref);
                    if (k->codomain_ref)
                        printf("codomain_ref=%s", k->codomain_ref);
                    if (k->displacement_ref)
                        printf("displacement_ref=%s", k->displacement_ref);                 
                    printf("\n");
                    if (k->n_mir_features != 0) {
                        struct mir_feature* t = k->mir_feature;
                        printf("        %i features\n", k->n_mir_features);
                        while (t) {
                            printf("        Feature: ");
                            if (t->id)
                                printf("id=%s ", t->id);
                            if (t->description)
                                printf("description=%s ", t->description);
                            if (t->displacement_ref)
                                printf("displacement_ref=%s ", t->displacement_ref);
                            printf("\n");
                            t = t->next_mir_feature;
                        }
                    }
                    k = k->next_mir_morphism;
                }
            }

            p = p->next_mir_model;
        }
    }
}

void freeMirFeaturesList(struct mir_feature* head) {
    struct mir_feature* temp;
    while (head) {
        temp = head;
        head = head->next_mir_feature;
        free(temp);
    }
}

void freeMirMorphismsList(struct mir_morphism* head) {
    struct mir_morphism* temp;
    while (head) {
        temp = head;
        head = head->next_mir_morphism;
        
        if (temp->mir_feature)
            freeMirFeaturesList(temp->mir_feature);

        free(temp);
    }
}

void freeMirSubobjectsList(struct mir_subobject* head) {
    struct mir_subobject* temp;
    while (head) {
        temp = head;
        head = head->next_mir_subobject;

        if (temp->mir_feature)
            freeMirFeaturesList(temp->mir_feature);

        free(temp);
    }
}

void freeMirObjectsList(struct mir_object* head) {
    struct mir_object* temp;
    while (head) {
        temp = head;
        head = head->next_mir_object;

        if (temp->mir_subobject)
            freeMirSubobjectsList(temp->mir_subobject);
        if (temp->mir_feature)
            freeMirFeaturesList(temp->mir_feature);

        free(temp);
    }
}

void freeMirModelsList(struct mir_model* head) {
    struct mir_model* temp;
    while (head) {
        temp = head;
        head = head->next_mir_model;

        if (temp->mir_object)
            freeMirObjectsList(temp->mir_object);
        if (temp->mir_morphism)
            freeMirMorphismsList(temp->mir_morphism);

        free(temp);
    }
}

void freeTransitionsList(struct transition* head) {
    struct transition* temp;
    while (head) {
        temp = head;
        head = head->next_transition;
        free(temp);
    }
}

void freePlacesList(struct place* head) {
    struct place* temp;
    while (head) {
        temp = head;
        head = head->next_place;
        free(temp);
    }
}

void freePetriNetsList(struct petri_net* head) {
    struct petri_net* temp;
    while (head) {
        temp = head;
        head = head->next_petri_net;

        if (temp->place)
            freePlacesList(temp->place);
        if (temp->transition)
            freeTransitionsList(temp->transition);

        free(temp);
    }
}

void freeFeatureObjectsList(struct feature_object* head) {
    struct feature_object* temp;
    while (head) {
        temp = head;
        head = head->next_feature_object;
        free(temp);
    }
}

void freeSegmentEventsList(struct segment_event* head) {
    struct segment_event* temp;
    while (head) {
        temp = head;
        head = head->next_segment_event;
        free(temp);
    }
}

void freeSegmentsList(struct segment* head) {
    struct segment* temp;
    while (head) {
        temp = head;
        head = head->next_segment;

        if (temp->segment_event)
            freeSegmentEventsList(temp->segment_event);
        if (temp->feature_object)
            freeFeatureObjectsList(temp->feature_object);

        free(temp);
    }
}

void freeSegmentation(struct segmentation* cur) {
        if (cur->segment)
            freeSegmentsList(cur->segment);
        free(cur);
}

void freeFeatureObjectRelationshipsList(struct feature_object_relationship* head) {
    struct feature_object_relationship* temp;
    while (head) {
        temp = head;
        head = head->next_feature_object_relationship;
        free(temp);
    }
}

void freeRelationshipsList(struct relationship* head) {
    struct relationship* temp;
    while (head) {
        temp = head;
        head = head->next_relationship;
        free(temp);
    }
}

void freeAnalysisList(struct analysis* head) {
    struct analysis* temp;
    while (head) {
        temp = head;
        head = head->next_analysis;

        if (temp->segmentation)
            freeSegmentation(temp->segmentation);
        if (temp->relationships)
            freeRelationshipsList(temp->relationships);
        if (temp->feature_object_relationship)
            freeFeatureObjectRelationshipsList(temp->feature_object_relationship);

        free(temp);
    }
}

void freeChordNamesList(struct chord_name* head) {
    struct chord_name* temp;
    while (head) {
        temp = head;
        head = head->next_chord_name;
        free(temp);
    }
}

void freeChordGridsList(struct chord_grid* head) {
    struct chord_grid* temp;
    while (head) {
        temp = head;
        head = head->next_chord_grid;

        if (temp->chord_name)
            freeChordNamesList(temp->chord_name);

        free(temp);
    }
}

void freeStructuralLayer(struct structural cur) {
    if (cur.chord_grid && cur.n_chord_grids!=0)
        freeChordGridsList(cur.chord_grid);
    if (cur.analysis && cur.n_analysis != 0)
        freeAnalysisList(cur.analysis);
    if (cur.petri_nets && cur.n_petri_nets != 0)
        freePetriNetsList(cur.petri_nets);
    if (cur.mir && cur.n_mir_models!= 0)
        freeMirModelsList(cur.mir);
}