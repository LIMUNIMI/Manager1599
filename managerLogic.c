/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "common.h"
#include "musicLang.h"

//Spine
struct event{//EMPTY
    char* id;//required
    char* timing;//null
    char* hpos;//null
    struct event* next_event;
};

//Los
struct agogic{
    char* agogic_value;
    int bracketed;// yes!=0, no=0
    //spine-ref
    struct agogic* next_agogic;
};

struct text_field{
    char* text_field_value;
    //extension_line_to
    //extensione_lines_shape (normal,dotted,slashed)
    //spine_ref
    struct text_field* next_text_field;
};

struct metronomic_indication{//EMPTY
    int num;//REQUIRED
    int den;//REQUIRED
    int value;//REQUIRED
    int dots;
    //spine_ref
    struct metronomic_indication* next_metronomic_indication;
};

struct ornament_list{
    ornament ornament_value;
    struct ornament_list* next_ornament;
};

struct horizontal_symbol_list{
    horizontal_symbol horizontal_symbol_value;
    struct horizontal_symbol_list* next_horizontal_symbol;
};

struct syllabe{
    char* syllabe_value;
    //start_event_ref
    //end_event_ref
    char* hyphen;//(yes,no) default no
    struct syllabe* next_syllabe;
};

struct lyrics{//(syllabe+)
    struct syllabe* syllabes;
    //part_ref
    //voice_ref
};

struct part{
    char* id;//REQUIRED
    int performes_number;//default unknown
    char* transposition_pitch;//(A,B,C,D,E,F,G)
    //accidental transposition_accidental
    int octave_offset;
  
    struct voice_item* voice_list;
    struct measure* measures;
    
    struct part* next_part;
};

struct los{//?
    struct staff* staff_list;//1    
    struct horizontal_symbol_list* horizontal_symbols;//?
    struct ornament_list* ornaments;//?    
    struct agogic* agogics;
    struct text_field* text_field;
    struct metronomic_indication* metronomic_indication;
    struct lyrics lyrics;
    struct part* part;//+
};

//Logic
struct logic{
    struct event* spine;//+
    struct los los;//?
    //struct layout;//?
};