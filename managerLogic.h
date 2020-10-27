/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerLogic.h
 * Author: Ale
 *
 * Created on 2 settembre 2020, 16.52
 */

#ifndef MANAGERLOGIC_H
#define MANAGERLOGIC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "common.h"
#include "managerLosElements.h"
    
//Spine
struct event{//EMPTY
    xmlChar* id;//required
    int timing;//null
    int hpos;//null
    
    struct event* next_event;
};

//Los
struct agogics{
    int bracketed;//(yes,no) default no
    xmlChar* event_ref;
    
    xmlChar* agogics_value;
    
    struct agogics* next_agogics;
};

struct text_field{
    xmlChar* text_field_value;
    xmlChar* extension_line_to;
    xmlChar* extension_line_shape;//(normal,dotted,slashed)
    xmlChar* event_ref;
    
    struct text_field* next_text_field;
};

struct metronomic_indication{//EMPTY
    int num;//REQUIRED
    int den;//REQUIRED
    int value;//REQUIRED
    int dots;
    xmlChar* event_ref;
    
    struct metronomic_indication* next_metronomic_indication;
};

struct horizontal_symbol_list{
    horizontal_symbol horizontal_symbol_value;
    struct horizontal_symbol_list* next_horizontal_symbol;
};

struct ornament_list{
    ornament ornament_value;
    struct ornament_list* next_ornament;
};

struct syllable{
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
    int hyphen;//(yes,no) default no
    
    xmlChar* syllable_value;
    
    struct syllable* next_syllable;
};

struct lyrics{//(syllable+)
    int n_syllables;
    
    struct syllable* syllables;
    xmlChar* part_ref;
    xmlChar* voice_ref;
    
    struct lyrics* next_lyrics;
};

struct part{
    int n_voice_items;
    int n_measures;
    
    xmlChar* id;//REQUIRED
    int performes_number;//default unknown
    xmlChar* transposition_pitch;//(A,B,C,D,E,F,G)
    xmlChar* transposition_accidental;
    int octave_offset;
  
    struct voice_item* voice_list;
    struct measure* measures;
    
    struct part* next_part;
};

struct brackets{
    xmlChar* marker;//REQUIRED (start_of_staff_group|end_of_staff_group)
    int group_number;//REQUIRED
    xmlChar* shape;//REQUIRED (square,rounded_square,brace,vertical_bar,none)
    
    struct brackets* next_brackets;
};

struct staff{//(clef|(key_signature|custom_key_signature)|time_signature|barline|tablature_tuning)*
    int n_clefs;
    int n_key_signatures;
    int n_custom_key_signatures;
    int n_time_signatures;
    int n_barlines;
    int n_tablature_tunings;
    
    xmlChar* id;
    int line_number;//default 5
    int ossia;//(yes,no) default no
    xmlChar* tablature;//(none,french,german,italian)
    
    struct clef* clefs;
    struct key_signature* key_signatures;
    struct custom_key_signature* custom_key_singatures;
    struct time_signature* time_signatures;
    struct barline* barlines;
    struct tablature_tuning* tablature_tunings;
    
    struct staff* next_staff;
};

struct los{//?
    int n_agogics;
    int n_text_fields;
    int n_metronomic_indications;
    int n_lyrics;
    int n_parts;
    int n_staves;
    int n_brackets;
    int n_ornaments;
    int n_horizontal_symbols;
    
    //(brackets,staff)+
    struct staff* staff_list;//1    
    struct brackets* staff_list_brackets;
    struct horizontal_symbol_list* horizontal_symbols;//?
    struct ornament_list* ornaments;//?    
    struct agogics* agogics;
    struct text_field* text_field;
    struct metronomic_indication* metronomic_indication;
    struct lyrics* lyrics;
    struct part* part;//+
};

//Layout
struct layout_shapes{
    int horizontal_offset;//REQUIRED
    int vertical_offset;//REQUIRED
    
    //svg
    
    struct layout_shapes* next_layout_shapes;
};

struct layout_images{
    xmlChar* file_name;//#REQUIRED
    xmlChar* file_format;//REQUIRED
    xmlChar* encoding_format;//REQUIRED
    int horizontal_offset;//#REQUIRED
    int vertical_offset;//#REQUIRED
    xmlChar* description;
    xmlChar* copyright; 
    xmlChar* notes;   
    
    struct layout_images* next_layout_images;
};

struct layout_staff{
    xmlChar* id;
    xmlChar* staff_ref;//REQUIRED
    int vertical_offset;//REQUIRED
    int height;//REQUIRED
    int show_key_signature;//(yes,no) default yes
    int show_clef;//(yes,no) default yes
    int show_time_signature;//(yes,no) default no
    int ossia;//(yes,no) default no

    struct layout_staff* next_layout_staff;
};

struct layout_system{
    int n_layout_staves;
    
    xmlChar* id;
    int upper_left_x;//REQUIRED
    int upper_left_y;//REQUIRED
    int lower_right_x;//REQUIRED
    int lower_right_y;//REQUIRED
    
    struct layout_staff* layout_staves;//+
    
    struct layout_system* next_layout_system;
};

struct custom_page_format{
    int width;//REQUIRED
    int height;//REQUIRED
};

struct standard_page_format{
    xmlChar* format;//REQUIRED (a0,a1,a2,a3,a4,a5,a6,a7,a8,b0,b1,b2,b3,b4,b5,b6,b7,b8,c0,c1,c2,c3,c4,c5,c6,c7,c8,ansi_a,ansi_b,ansi_c,ansi_d,ansi_e,arch_a,arch_b,arch_c,arch_e,arch_e1,quarto,foolscap,executive,monarch,government_letter,letter,legal,ledger,tabloid,post,crown,large_post,demy,medium,royal,elephant,double_demy,quad_demy,statement) 
};

struct page{//((standard_page_format | custom_page_format), layout_system*, layout_images*, layout_shapes*)
    int n_layout_systems;
    int n_layout_images;
    int n_layout_shapes;
    
    xmlChar* id;//REQUIRED
    int number;
    
    struct standard_page_format standard_page_formats;
    struct custom_page_format custom_page_formats;
    struct layout_system* layout_systems;
    struct layout_images* layout_images_list;
    struct layout_shapes* layout_shapes_list;
    
    struct page* next_page;
};

struct layout{//(page+, text_font?, music_font?)
    int n_pages;
    
    int hpos_per_unit;//REQUIRED
    xmlChar* measurement_unit;//REQUIRED (centimeters,millimeters,inches,decimal_inches,points,picas,pixels,twips)
    
    struct page* pages;//+
    xmlChar* text_font;
    xmlChar* music_font;
};

//Logic
struct logic{
    int n_events;
    
    struct event* spine;//+
    struct los los;//?
    struct layout layout;//?
};

//Variables


//Prototypes
struct logic loadLogic();
void loadSpine();
void loadLos();
void loadLayout();
    
void printLogic();
void printSpine();
void printLos();
void printLayout();

#ifdef __cplusplus
}
#endif

#endif /* MANAGERLOGIC_H */

