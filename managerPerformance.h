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
       char* event_ref;

        //struct SysEx SysEx;

        struct sys_ex* next_sys_ex;
    };

    struct midi_event{//(%MIDIChannelMessage;)*
        int n_MIDIChannelMessages;

        char* timing;//REQUIRED
        char* event_ref;

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
    struct csound_spine_ref{
        char* event_ref;

        struct csound_spine_ref* next_csound_spine_ref;
    };

    struct csound_part_ref{
        char* part_ref;//REQUIRED

        struct csound_part_ref* next_csound_part_ref;
    };

    struct csound_instrument_mapping{//(csound_part_ref | csound_spine_ref)+
        int n_csound_part_refs;
        int n_csound_spine_refs;

        int instrument_number;//REQUIRED
        int start_line;
        int end_line;
        char* pnml_file;

        struct csound_part_ref* csound_part_refs;
        struct csound_spine_ref* csound_spine_refs;

        struct csound_instrument_mapping* next_csound_instrument_mapping;
    };

    struct csound_orchestra{//(csound_instrument_mapping*, rights?)
        int n_csound_instrument_mappings;

        char* file_name;//REQUIRED

        struct csound_instrument_mapping* csound_instrument_mappings;
        struct rights rights;

        struct csound_orchestra* next_csound_orchestra;
    };

    struct csound_spine_event{
        int line_number;//REQUIRED
        char* event_ref;

        struct csound_spine_event* next_csound_spine_event;
    };

    struct csound_score{//(csound_spine_event+, rights?)
        int n_csound_spine_events;

        char* file_name;//REQUIRED

        struct csound_spine_event* csound_spine_events;
        struct rights rights;

        struct csound_score* next_csound_score;
    };

    struct csound_instance{//(csound_score | csound_orchestra)+
            int n_csound_scores;
            int n_csound_orchestras;

            struct csound_score* csound_scores;
            struct csound_orchestra* csound_orchestras;

            struct csound_instance* next_csound_instance;
    };
    
//Mpeg4 Instance
    struct mpeg4_spine_ref{
        char* event_ref;

        struct mpeg4_spine_ref* next_mpeg4_spine_ref;
    };

    struct mpeg4_part_ref{
        char* part_ref;//REQUIRED

        struct mpeg4_part_ref* next_mpeg4_part_ref;
    };

    struct mpeg4_instrument_mapping{//(mpeg4_part_ref | mpeg4_spine_ref)+
        int n_mpeg4_part_refs;
        int n_mpeg4_spine_refs;

        char* instrument_name;//REQUIRED
        int start_line;
        int end_line;
        char* pnml_file;

        struct mpeg4_part_ref* mpeg4_part_refs;
        struct mpeg4_spine_ref* mpeg4_spine_refs;

        struct mpeg4_instrument_mapping* next_mpeg4_instrument_mapping;
    };

    struct mpeg4_orchestra{//(mpeg4_instrument_mapping*, rights?)
        int n_mpeg4_instrument_mappings;

        char* file_name;//REQUIRED

        struct mpeg4_instrument_mapping* mpeg4_instrument_mappings;
        struct rights rights;

        struct mpeg4_orchestra* next_mpeg4_orchestra;
    };

    struct mpeg4_spine_event{
        int line_number;//REQUIRED
        char* event_ref;

        struct mpeg4_spine_event* next_mpeg4_spine_event;
    };

    struct mpeg4_score{//(mpeg4_spine_event+, rights?)
        int n_mpeg4_spine_events;

        char* file_name;//REQUIRED

        struct mpeg4_spine_event* mpeg4_spine_events;
        struct rights rights;

        struct mpeg4_score* next_mpeg4_score;
    };
	
    struct mpeg4_instance{//(mpeg4_score | mpeg4_orchestra)+
        int n_mpeg4_scores;
        int n_mpeg4_orchestras;

        struct mpeg4_score* mpeg4_scores;
        struct mpeg4_orchestra* mpeg4_orchestras;

        struct mpeg4_instance* next_mpeg4_instance;
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
    
    struct midi_mapping* loadMidiMapping(xmlNodePtr cur);
    struct midi_event_sequence* loadMidiEventSequence(xmlNodePtr cur);
    struct midi_event* loadMidiEvent(xmlNodePtr cur);
    struct sys_ex* loadSysEx(xmlNodePtr cur);
    
    struct csound_score* loadCsoundScore(xmlNodePtr cur);
    struct csound_orchestra* loadCsoundOrchestra(xmlNodePtr cur);
    struct csound_instrument_mapping* loadCsoundInstrumentMapping(xmlNodePtr cur);
    
    struct mpeg4_score* loadMpeg4Score(xmlNodePtr cur);
    struct mpeg4_orchestra* loadMpeg4Orchestra(xmlNodePtr cur);
    struct mpeg4_instrument_mapping* loadMpeg4InstrumentMapping(xmlNodePtr cur);
    
    void printPerformance();
    void printMidiInstance();
    void printCsoundInstance();
    void printMpeg4Instance();
    
#ifdef __cplusplus
}
#endif

#endif /* MANAGERPERFORMANCE_H */

