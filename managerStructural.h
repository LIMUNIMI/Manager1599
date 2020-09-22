/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manaagerStructural.h
 * Author: Ale
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
        char* id;
        char* description;
        char* displacement_ref;
        
        struct mir_feature* next_mir_feature;
    };
    
    struct mir_morphism{//(mir_feature*)
        int n_mir_features;
        
        char* id;
        char* description;
        char* domain_ref; //REQUIRED
        char* codomain_ref; //REQUIRED
        char* displacement_ref; 
        
        struct mir_feature* mir_features;
        
        struct mir_morphism* next_mir_morphism;
    };
    
    struct mir_subobject{//(mir_feature*)
        int n_mir_features;
        
        char* id;
        char* description;
        char* displacement_ref;
        char* segment_ref;
        
        struct mir_feature* mir_features;
        
        struct mir_subobject* next_mir_subobject;
    };
    
    struct mir_object{//(mir_subobject+, mir_feature*)
        int n_mir_subobjects;
        int n_mir_features;
        
        char* id;
        char* description;
        char* displacement_ref;
        
        struct mir_subobject* mir_subobjects;
        struct mir_feature* mir_features;
        
        struct mir_object* next_mir_object;
    };
    
    struct mir_model{//(mir_object+,mir_morphism*)
        int n_mir_objects;
        int n_mir_morphisms;
        
        char* id;
        char* description;
        char* file_name;
        
        struct mir_object* mir_objects;
        struct mir_morphism* mir_morphisms;
        
        struct mir_model* next_mir_model;
    };
    
    struct mir{//(mir_model+)
        int n_mir_models;
        
        struct mir_model* mir_models;
        
        struct mir* next_mir;
    };
        
//Petri Nets
    struct transition{
        char* transition_ref; //REQUIRED
        char* feature_object_relationship_ref;  //REQUIRED
        
        struct transition* next_transition;
    };
    
    struct place{
        char* place_ref; //REQUIRED
        char* segment_ref; //REQUIRED
        
        struct place* next_place;  
    };
    
    struct petri_net{//(place|transition)+
        int n_places;
        int n_transitions;
        
        char* id;
        char* author;
        char* description;
        char* file_name; //REQUIRED
        
        struct place* places;
        struct transition* transitions;
        
        struct petri_net* next_petri_net;
    };
    
    struct petri_nets{//(petr_net+)
        int n_petri_nets;
        
        struct petri_net* petri_net_list;
        
        struct petri_nets* next_petri_nets;
    };
    
//Analysis
    struct feature_object_relationship{//(ver_rule)
        //<!ELEMENT ver_rule (#PCDATA)>
        
        char* id; //REQUIRED
        
        char* ver_rule;
        
        struct feature_object_relationship* next_feature_object_relationship;
    };
    
    struct relationship{
        char* id; //REQUIRED
        char* description;
        char* segment_a_ref; //REQUIRED
        char* segment_b_ref; //REQUIRED
        char* feature_object_a_ref;
        char* feature_object_b_ref;
        char* feature_object_relationship_ref;
        
        struct relationship* next_relationship;
    };
    
    struct feature_object{//(simple_description %added_feature_object_classes)   
        //<!ENTITY % added_feature_object_classes "">
        //<!ELEMENT simple_description (#PCDATA)>
        char* id;
        char* name; //REQUIRED
        
        char* simple_description;
        
        struct feature_object* next_feature_object;
    };
    
    struct segment_event{
        //spine_ref
        
        struct segment_event* next_segment_event;
    };
    
    struct segment{//(segment_event+,feature_object*)
        int n_segment_events;
        int n_feature_objects;
        
        char* id; //REQUIRED
        
        struct segment_event* segment_events;
        struct feature_object* feature_objects;
        
        struct segment* next_segment;
    };
    
    struct segmentation{//(segment+)
        int n_segments;
        
        char* id;
        char* description;
        char* method;
        
        struct segment* segment;
    };
    
    struct analysis{//(segmentation,relationships?,feature_object_relationships?)
        int n_relationships;
        int n_feature_object_relationships;
        
        char* id;
        char* author;
        char* description;
        
        struct segmentation segmentation;
        struct relationship* relationships;//(relationship+)
        struct feature_object_relationship* feature_object_relationships;
        
        struct analysis* next_analysis;
    };
//Chord Grid
    struct chord_name{
        char* root_id;//REQUIRED
         
        char* chord_name_value;
        
        struct chord_name* next_chord_name;
    };
    
    struct chord_grid{//(chord_name+)
        int n_chord_names;
        
        char* id;
        char* author;
        char* description;
        
        struct chord_name* chord_names;
        
        struct chord_grid* next_chord_grid;
    };
    
//Structural
    struct structural{//(chord_grid*, analysis*, petri_nets*, mir*)
        int n_chord_grids;
        int n_analysis;
        int n_petri_nets;
        int n_mirs;
        
        struct chord_grid* chord_grid;
        struct analysis* analysis;
        struct petri_nets* petri_nets;
        struct mir* mir;
    };

//Variables
    struct structural structural_layer;
    
//Prototypes
    void loadStructural();
    void loadChordGrid();
    void loadAnalysis();
    void loadPetriNets();
    void loadMir();
    
    struct segmentation loadSegmentation(xmlNodePtr cur);
    struct feature_object* loadFeatureObject(xmlNodePtr cur);
    
    struct petri_net* loadPetriNet(xmlNodePtr cur);
    
    struct mir_model* loadMirModel(xmlNodePtr cur);
    struct mir_object* loadMirObject(xmlNodePtr cur);
    struct mir_morphism* loadMirMorphism(xmlNodePtr cur);
    struct mir_subobject* loadMirSubobject(xmlNodePtr cur);
    struct mir_feature* loadMirFeature(xmlNodePtr cur);

    void printStructural();
    void printChordGrid();
    void printAnalysis();
    void printPetriNet();
    void printMir();

#ifdef __cplusplus
}
#endif

#endif /* MANAAGERSTRUCTURAL_H */

