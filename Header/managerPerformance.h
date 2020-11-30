/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerPerformance.h
 * Author: Alessandro Talamona
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
       xmlChar* event_ref;

        //struct SysEx SysEx;

        struct sys_ex* next_sys_ex;
    };

    struct midi_event{//(%MIDIChannelMessage;)*
        int n_MIDIChannelMessages;

        xmlChar* timing;//REQUIRED
        xmlChar* event_ref;

        //struct MIDIChannelMessage* MIDIChannelMessages;

        struct midi_event* next_midi_event;
    };

    struct midi_event_sequence{//(midi_event | sys_ex)+
        int n_midi_events;
        int n_sys_exs;

        xmlChar* division_type;//REQUIRED
        xmlChar* division_value;//REQUIRED NMTOKEN
        xmlChar* measurement_unit;//REQUIRED

        struct midi_event* midi_events;
        struct sys_ex* sys_exs;

        struct midi_event_sequence* next_midi_event_sequence;
    };

    struct midi_mapping{//(midi_event_sequence+)
        int n_midi_event_sequences;

        xmlChar* part_ref;//REQUIRED
        xmlChar* voice_ref;
        xmlChar* track;//REQUIRED
        xmlChar* channel;//REQUIRED

        struct midi_event_sequence* midi_event_sequences;

        struct midi_mapping* next_midi_mapping;
    };

    struct midi_instance{// (midi_mapping+, rights?)
        int n_midi_mappings;

        xmlChar* file_name;//REQUIRED
        xmlChar* format;//REQUIRED

        struct rights rights;
        struct midi_mapping* midi_mappings;

        struct midi_instance* next_midi_instance;
    };
    
//CSound/Mpeg4 Instance	
    struct csound_mpeg4_spine_ref{
        xmlChar* event_ref;

        struct csound_mpeg4_spine_ref* next_csound_mpeg4_spine_ref;
    };

    struct csound_mpeg4_part_ref{
        xmlChar* part_ref;//REQUIRED

        struct csound_mpeg4_part_ref* next_csound_mpeg4_part_ref;
    };

    struct csound_mpeg4_instrument_mapping{//(csound_part_ref | csound_spine_ref)+
        int n_csound_mpeg4_part_refs;
        int n_csound_mpeg4_spine_refs;

        xmlChar* instrument_info;//REQUIRED  replace instrument_name or instrument_number
        int start_line;
        int end_line;
        xmlChar* pnml_file;

        struct csound_mpeg4_part_ref* csound_mpeg4_part_refs;
        struct csound_mpeg4_spine_ref* csound_mpeg4_spine_refs;

        struct csound_mpeg4_instrument_mapping* next_csound_mpeg4_instrument_mapping;
    };

    struct csound_mpeg4_orchestra{//(csound_instrument_mapping*, rights?)
        int n_csound_mpeg4_instrument_mappings;

        xmlChar* file_name;//REQUIRED

        struct csound_mpeg4_instrument_mapping* csound_mpeg4_instrument_mappings;
        struct rights rights;

        struct csound_mpeg4_orchestra* next_csound_mpeg4_orchestra;
    };

    struct csound_mpeg4_spine_event{
        int line_number;//REQUIRED
        xmlChar* event_ref;

        struct csound_mpeg4_spine_event* next_csound_mpeg4_spine_event;
    };

    struct csound_mpeg4_score{//(csound_spine_event+, rights?)
        int n_csound_mpeg4_spine_events;

        xmlChar* file_name;//REQUIRED

        struct csound_mpeg4_spine_event* csound_mpeg4_spine_events;
        struct rights rights;

        struct csound_mpeg4_score* next_csound_mpeg4_score;
    };

    struct csound_mpeg4_instance{//(csound_score | csound_orchestra)+ or (mpeg4_score | mpeg4_orchestra)
            int n_csound_mpeg4_scores;
            int n_csound_mpeg4_orchestras;

            struct csound_mpeg4_score* csound_mpeg4_scores;
            struct csound_mpeg4_orchestra* csound_mpeg4_orchestras;

            struct csound_mpeg4_instance* next_csound_mpeg4_instance;
    };
    
//Performance
    struct performance{//(midi_instance | csound_instance | mpeg4_instance)+
        int n_midi_instances;
        int n_csound_instances;
        int n_mpeg4_instances;
        
        struct midi_instance* midi_instance;
        struct csound_mpeg4_instance* csound_instance;
        struct csound_mpeg4_instance* mpeg4_instance;
    };

//Variables
    
    
//Prototypes
    MANAGERIEEE1599_API struct performance loadPerformance();
    MANAGERIEEE1599_API void loadMidiInstance();
    MANAGERIEEE1599_API void loadCsoundInstance();
    MANAGERIEEE1599_API void loadMpeg4Instance();
    
    struct midi_mapping* loadMidiMapping(xmlNodePtr cur);
    struct midi_event_sequence* loadMidiEventSequence(xmlNodePtr cur);
    struct midi_event* loadMidiEvent(xmlNodePtr cur);
    struct sys_ex* loadSysEx(xmlNodePtr cur);
    
    struct csound_mpeg4_score* loadCsoundScore(xmlNodePtr cur);
    struct csound_mpeg4_orchestra* loadCsoundOrchestra(xmlNodePtr cur);
    struct csound_mpeg4_instrument_mapping* loadCsoundInstrumentMapping(xmlNodePtr cur);
    
    struct csound_mpeg4_score* loadMpeg4Score(xmlNodePtr cur);
    struct csound_mpeg4_orchestra* loadMpeg4Orchestra(xmlNodePtr cur);
    struct csound_mpeg4_instrument_mapping* loadMpeg4InstrumentMapping(xmlNodePtr cur);
    
    MANAGERIEEE1599_API void printPerformance();
    MANAGERIEEE1599_API void printMidiInstance();
    MANAGERIEEE1599_API void printCsoundInstance();
    MANAGERIEEE1599_API void printMpeg4Instance();
    
#ifdef __cplusplus
}
#endif

#endif /* MANAGERPERFORMANCE_H */

