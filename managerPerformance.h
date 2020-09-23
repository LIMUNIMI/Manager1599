/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerPerformance.h
 * Author: Ale
 *
 * Created on 5 settembre 2020, 17.35
 */

#ifndef MANAGERPERFORMANCE_H
#define MANAGERPERFORMANCE_H

#ifdef __cplusplus
extern "C" {
#endif
 
#include "common.h"
    
//MIDI Instance
    struct sys_ex{//(SysEx)
       //spine_ref;
        
        //struct SysEx SysEx;
        
        struct sys_ex* next_sys_ex;
    };
    
    struct midi_event{//(%MIDIChannelMessage;)*
        int n_MIDIChannelMessages;
        
        char* timing;//REQUIRED
        //spine_ref;
        
        //struct MIDIChannelMessage* MIDIChannelMessages;
        
        struct midi_event* next_midi_event;
    };
    
    struct midi_event_sequence{//(midi_event | sys_ex)+
        int n_midi_events;
        int n_sys_exs;
        
        char* division_type;//REQUIRED
        char* division_value;//REQUIRED NMTOKEN
        char* measurement_unit;//REQUIRED
        
        struct midi_event* midi_events;
        struct sys_ex* sys_exs;
        
        struct midi_event_sequence* next_midi_event_sequence;
    };
    
    struct midi_mapping{//(midi_event_sequence+)
        int n_midi_event_sequences;
        
        char* part_ref;//REQUIRED
        char* voice_ref;
        char* track;//REQUIRED
        char* channel;//REQUIRED
        
        struct midi_event_sequence* midi_event_sequences;
        
        struct midi_mapping* next_midi_mapping;
    };
    
    struct midi_instance{// (midi_mapping+, rights?)
        int n_midi_mappings;
        
        char* file_name;//REQUIRED
        char* format;//REQUIRED
        
        struct rights rights;
        struct midi_mapping* midi_mappings;
        
        struct midi_instance* next_midi_instance;
    };
    
//CSound Instance
    struct csound_instance{
    
    };
    
//Mpeg4 Instance
    struct mpeg4_instance{
    
    };
    
//Performance
    struct performance{//(midi_instance | csound_instance | mpeg4_instance)+
        int n_midi_instances;
        int n_csound_instances;
        int n_mpeg4_instances;
        
        struct midi_instance* midi_instance;
        struct csound_instance* csound_instance;
        struct mpeg4_instance* mpeg4_instance;
    };

//Variables
    struct performance performance_layer;
    
//Prototypes
    void loadPerformance();
    void loadMidiInstance();
    void loadCsoundInstance();
    void loadMpeg4Instance();
    
    void printPerformance();
    void printMidiInstance();
    void printCsoundInstance();
    void printMpeg4Instance();
    
#ifdef __cplusplus
}
#endif

#endif /* MANAGERPERFORMANCE_H */

