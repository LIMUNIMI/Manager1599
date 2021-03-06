/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manaagerStructural.h
 * Author: Alessandro Talamona
 *
 * Created on 5 settembre 2020, 17.33
 */

#ifndef MANAAGERSTRUCTURAL_H
#define MANAAGERSTRUCTURAL_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "common.h"
    
//Mir
    struct mir_feature{
        xmlChar* id;
        xmlChar* description;
        xmlChar* displacement_ref;
        
        struct mir_feature* next_mir_feature;
    };
    
    struct mir_morphism{//(mir_feature*)
        int n_mir_features;
        
        xmlChar* id;
        xmlChar* description;
        xmlChar* domain_ref; //REQUIRED
        xmlChar* codomain_ref; //REQUIRED
        xmlChar* displacement_ref; 
        
        struct mir_feature* mir_feature;
        
        struct mir_morphism* next_mir_morphism;
    };
    
    struct mir_subobject{//(mir_feature*)
        int n_mir_features;
        
        xmlChar* id;
        xmlChar* description;
        xmlChar* displacement_ref;
        xmlChar* segment_ref;
        
        struct mir_feature* mir_feature;
        
        struct mir_subobject* next_mir_subobject;
    };
    
    struct mir_object{//(mir_subobject+, mir_feature*)
        int n_mir_subobjects;
        int n_mir_features;
        
        xmlChar* id;
        xmlChar* description;
        xmlChar* displacement_ref;
        
        struct mir_subobject* mir_subobject;
        struct mir_feature* mir_feature;
        
        struct mir_object* next_mir_object;
    };
    
    struct mir_model{//(mir_object+,mir_morphism*)
        int n_mir_objects;
        int n_mir_morphisms;
        
        xmlChar* id;
        xmlChar* description;
        xmlChar* file_name;
        
        struct mir_object* mir_object;
        struct mir_morphism* mir_morphism;
        
        struct mir_model* next_mir_model;
    };
        
//Petri Nets
    struct transition{
        xmlChar* transition_ref; //REQUIRED
        xmlChar* feature_object_relationship_ref;  //REQUIRED
        
        struct transition* next_transition;
    };
    
    struct place{
        xmlChar* place_ref; //REQUIRED
        xmlChar* segment_ref; //REQUIRED
        
        struct place* next_place;  
    };
    
    struct petri_net{//(place|transition)+
        int n_places;
        int n_transitions;
        
        xmlChar* id;
        xmlChar* author;
        xmlChar* description;
        xmlChar* file_name; //REQUIRED
        
        struct place* place;
        struct transition* transition;
        
        struct petri_net* next_petri_net;
    };
    
//Analysis
    struct feature_object_relationship{//(ver_rule)
        //<!ELEMENT ver_rule (#PCDATA)>
        
        xmlChar* id; //REQUIRED
        
        xmlChar* ver_rule;
        
        struct feature_object_relationship* next_feature_object_relationship;
    };
    
    struct relationship{
        xmlChar* id; //REQUIRED
        xmlChar* description;
        xmlChar* segment_a_ref; //REQUIRED
        xmlChar* segment_b_ref; //REQUIRED
        xmlChar* feature_object_a_ref;
        xmlChar* feature_object_b_ref;
        xmlChar* feature_object_relationship_ref;
        
        struct relationship* next_relationship;
    };
    
    struct feature_object{//(simple_description %added_feature_object_classes)   
        //<!ENTITY % added_feature_object_classes "">
        //<!ELEMENT simple_description (#PCDATA)>
        xmlChar* id;
        xmlChar* name; //REQUIRED
        
        xmlChar* simple_description;
        
        struct feature_object* next_feature_object;
    };
    
    struct segment_event{
        xmlChar* event_ref;
        
        struct segment_event* next_segment_event;
    };
    
    struct segment{//(segment_event+,feature_object*)
        int n_segment_events;
        int n_feature_objects;
        
        xmlChar* id; //REQUIRED
        
        struct segment_event* segment_event;
        struct feature_object* feature_object;
        
        struct segment* next_segment;
    };
    
    struct segmentation{//(segment+)
        int n_segments;
        
        xmlChar* id;
        xmlChar* description;
        xmlChar* method;
        
        struct segment* segment;
    };
    
    struct analysis{//(segmentation,relationships?,feature_object_relationships?)
        int n_relationships;
        int n_feature_object_relationships;
        
        xmlChar* id;
        xmlChar* author;
        xmlChar* description;
        
        struct segmentation* segmentation;
        struct relationship* relationships;//(relationship+)
        struct feature_object_relationship* feature_object_relationship;
        
        struct analysis* next_analysis;
    };
//Chord Grid
    struct chord_name{
        xmlChar* root_id;//REQUIRED
         
        xmlChar* chord_name_value;
        
        struct chord_name* next_chord_name;
    };
    
    struct chord_grid{//(chord_name+)
        int n_chord_names;
        
        xmlChar* id;
        xmlChar* author;
        xmlChar* description;
        
        struct chord_name* chord_name;
        
        struct chord_grid* next_chord_grid;
    };
    
//Structural
    struct structural{//(chord_grid*, analysis*, petri_nets*, mir*)
        int n_chord_grids;
        int n_analysis;
        int n_petri_nets;
        int n_mir_models;
        
        struct chord_grid* chord_grid;
        struct analysis* analysis;
        struct petri_net* petri_nets;
        struct mir_model* mir;
    };

//Variables


//Prototypes
    MANAGERIEEE1599_API struct structural loadStructural();
    MANAGERIEEE1599_API void loadChordGrid();
    MANAGERIEEE1599_API void loadAnalysis();
    MANAGERIEEE1599_API void loadPetriNets();
    MANAGERIEEE1599_API void loadMir();
    
    struct segmentation* loadSegmentation(xmlNodePtr cur);
    struct feature_object* loadFeatureObject(xmlNodePtr cur);
	
    struct petri_net* loadPetriNet(xmlNodePtr cur);
    
    struct mir_model* loadMirModel(xmlNodePtr cur);
    struct mir_object* loadMirObject(xmlNodePtr cur);
    struct mir_morphism* loadMirMorphism(xmlNodePtr cur);
    struct mir_subobject* loadMirSubobject(xmlNodePtr cur);
    struct mir_feature* loadMirFeature(xmlNodePtr cur);

    MANAGERIEEE1599_API void printStructural();
    void printChordGrid();
    void printAnalysis();
    void printPetriNet();
    void printMir();

    MANAGERIEEE1599_API void freeStructuralLayer(struct structural cur);
    void freeMirFeaturesList(struct mir_feature* head);
    void freeMirMorphismsList(struct mir_morphism* head);
    void freeMirSubobjectsList(struct mir_subobject* head);
    void freeMirObjectsList(struct mir_object* head);
    void freeMirModelsList(struct mir_model* head);
    void freeTransitionsList(struct transition* head);
    void freePlacesList(struct place* head);
    void freePetriNetsList(struct petri_net* head);
    void freeFeatureObjectsList(struct feature_object* head);
    void freeSegmentEventsList(struct segment_event* head);
    void freeSegmentation(struct segmentation* head);
    void freeFeatureObjectRelationshipsList(struct feature_object_relationship* head);
    void freeRelationshipsList(struct relationship* head);
    void freeAnalysisList(struct analysis* head);
    void freeChordNamesList(struct chord_name* head);
    void freeChordGridsList(struct chord_grid* head);

#ifdef __cplusplus
}
#endif

#endif /* MANAAGERSTRUCTURAL_H */

