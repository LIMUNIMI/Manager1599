/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   musicLang.h
 * Author: Alessandro Talamona
 *
 * Created on 3 settembre 2020, 2.17
 */

#ifndef MUSICLANG_H
#define MUSICLANG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
 
//Staff Eelements START
struct string{
    int string_number;//REQUIRED
    xmlChar* string_pitch;//(A,B,C,D,E,F,G) REQUIRED
    xmlChar* string_accidental;
    int string_octave;//REQUIRED
    
    struct string* next_string;
};

struct tablature_tuning{
    int n_strings;
    
    xmlChar* type;//(D,E,G,A,baroque,flat_french,other)

    struct string* strings;
    
    struct tablature_tuning* next_tablature_tuning;
};

struct barline{
    xmlChar* style;//REQUIRED (dashed,double,final,invisibile,staandard,medium,short)
    xmlChar* extension;//REQUIRED (single_staff,staff_group,all_stave,mensurstrich
    xmlChar* event_ref;
    
    struct barline* next_barline;
};

struct time_indication{
    int num;//REQUIRED
    int den;//REQUIRED
    int abbreviation;//(yes,no) default no
    int vtu_amount;
    
    struct time_indication* next_time_indication;
};

struct time_signature{
    int n_time_indications;
    
    int visible;//(yes,no) default yes
    xmlChar* event_ref;
    
    struct time_indication* time_indications;//+
    
    struct time_signature* next_time_signature;
};

struct key_accidental{
    xmlChar* step;//REQUIRED (A,B,C,D,E,F,G)
    xmlChar* accidental;
    struct key_accidental* next_key_accidental;
};

struct custom_key_signature{
    int n_key_accidentals;
    
    xmlChar* event_ref;
    
    struct key_accidental* key_accidentals;//+
    
    struct custom_key_signature* next_custom_key_signature;
};

struct key_signature{
    xmlChar* event_ref;
   
    xmlChar* num_type;//REQUIRED(flat_num,sharp_num)
    
    int number;//REQUIRED (0,1,2,3,4,5,6,7)
    
    struct key_signature* next_key_signature;
};

struct clef{
    xmlChar* shape;//REQUIRED (G,F,C,gregorian_F,gregorian_C,percussion,doubleG,tabguitar)
    xmlChar* staff_step;//REQUIRED
    int octave_num;//(0,8,-8,15,-15) default 0
    xmlChar* event_ref;
    
    struct clef* next_clef;
};
//Staff Elements END 

//Part Elements START
struct augmentation_dots{
    int number;//default 1
};

struct fingering{
    int number;//REQUIRED (1,2,3,4,5)
};

struct printed_accidental{  
    int parenthesis;//(yes,no) default no
    
    xmlChar* printed_accidental_type;
    
    struct printed_accidental* next_printed_accidental;
};

struct pitch{
    xmlChar* step;//REQUIRED (A,B,C,D,E,F,G,none)
    int octave;//REQUIRED
    xmlChar* actual_accidental;
};

struct notehead{
    int n_printed_accidentals;
    
    xmlChar* id;
    xmlChar* staff_ref;
    xmlChar* style;//(normal,harmonic,unpitched,cymbal,parenthesis,circled,squared)
    
    struct pitch pitch;
    struct printed_accidental* printed_accidentals;//? and +
    xmlChar* printed_accidentals_shape;
    int tie;//? yes=1,no=0
    struct fingering fingering;//?
    
    struct notehead* next_notehead;
};

struct notehead_ref{
    xmlChar* event_ref;
    
    struct notehead_ref* next_notehead_ref;
};

struct articulation{
    xmlChar* articulation_sign;
    
    //svg per custom_articulation
    
    struct articulation* next_articulation;
};

struct gregorian_symbol{
    int n_noteheads;
    
    xmlChar* id;
    xmlChar* neume;//REQUIRED
    xmlChar* inflexion;//(no,resupinus,fleux) default no
    xmlChar* subpunctis;//(no,praepunctis,subpunctis,subbipunctis,subtripunctis,subquadripunctis,subquinquipunctis) default no
    xmlChar* interpretative_mark;//(no,vertical_episema,horizontal_episema,liquescens) default no
    int mora;//(yes,no) default no
    xmlChar* event_ref;
    
    struct notehead* notehead;
    
    struct gregorian_symbol* next_gregorian_symbol;
};

struct tablature_fingering{
    xmlChar* tablature_fingering_value;
    xmlChar* shape;//REQUIRED (number,dot,other)
};

struct tablature_articulation{
    xmlChar* shape;//REQUIRED (cross,tie,other)
};

struct tablature_pitch{
    int string_number;
    int key_number;//REQUIRED
};

struct key{
    xmlChar* id;
    xmlChar* staff_ref;

    struct tablature_pitch tablature_pitch;
    struct tablature_articulation tablature_articulation;//?
    int tie;//? yes=1,no=0
    struct tablature_fingering tablature_fingering;//?
    
    struct key* next_key;
};

struct tuplet_ratio{//(tuplet_ratio)
    int n_tuplet_ratios;

    int enter_num;//REQUIRED
    int enter_den;//REQUIRED
    int enter_dots;
    int in_num;//REQUIRED
    int in_den;//REQUIRED
    int in_dots;
	
    struct tuplet_ratio* tuplet_ratio;

    struct tuplet_ratio* next_tuplet_ratio;
};

struct duration{
    
    int num;//REQUIRED
    int den;//REQUIRED
    struct tuplet_ratio* tuplet_ratio;//?
};

struct tablature_symbol{
    int n_keys;
    
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* stem_direction;//(up,down,none)
    int beam_before;//(yes,no) default no
    int beam_after;//(yes,no) default no
    
    struct duration duration;
    struct augmentation_dots augmentation_dots;//?
    struct key* keys;
    
    struct tablature_symbol* next_tablature_symbol;
};

struct rest{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* staff_ref;
    int hidden;//(no,yes)
    
    struct duration duration;
    struct augmentation_dots augmentation_dots;//?
    
    struct rest* next_rest;
};

struct chord{
    int n_noteheads;
    int n_articulations;
    
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* stem_direction;//(up,down,none)
    int beam_before;//(yes,no) default no
    int beam_after;//(yes,no) default no
    int cue;//(yes,no) default no
    int tremolo_lines;//(no,1,2,3,4,5,6)    
    
    struct duration duration;
    struct augmentation_dots augmentation_dots;//?
    //(notehead+|repetition)
    struct notehead* noteheads;//+
    int repetition;//yes=1, no=0
    struct articulation* articulations;//?
    
    struct chord* next_chord;
};

struct voice{//(chord | rest | tablature_symbol | gregorian_symbol)+
    int n_chords;
    int n_rests;
    int n_tablature_symbols;
    int n_gregorian_symbols;
    
    xmlChar* voice_item_ref;//REQUIRED
    int ossia;//(yes,no) default no
    
    struct chord* chords;
    struct rest* rests;
    struct tablature_symbol* tablature_symbols;
    struct gregorian_symbol* gregorian_symbols;
    
    struct voice* next_voice;
};

struct measure_repeat{
    int number_of_measures;//REQUIRED
    xmlChar* event_ref;
};

struct multiple_rest{
    int number_of_measures;//REQUIRED
    xmlChar* event_ref;
};

struct measure{//(voice+ | multiple_rest | measure_repeat?)
    int n_voices;
    
    int number;//REQUIRED
    xmlChar* id;
    int show_number;//(yes,no)
    xmlChar* numbering_style;//(arabic_numbers,roman_numbers,small_letter,capital_letters)
    
    struct voice* voices;//+
    struct multiple_rest multiple_rest;//1
    struct measure_repeat measure_repeat;//?    
    
    struct measure* next_measure;
};

struct voice_item{
    xmlChar* id;//REQUIRED
    xmlChar* staff_ref;//REQUIRED
    xmlChar* notation_style;///(normal,rhythmic,slash,blank))
    
    struct voice_item* next_voice_item;
};
//Part Elements  END

//Horizontal Symbols START
struct custom_hsymbol{
    //svg
    xmlChar* id;
    xmlChar* start_event_ref;//REQUIRED
    xmlChar* end_event_ref;
};    

struct multiple_ending{
    xmlChar* id;
    int number;//REQUIRED
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
    xmlChar* return_to;
    
    struct multiple_ending* next_multiple_ending;
};

struct multiple_endings{//+
    xmlChar* id;

    struct multiple_ending* multiple_ending;
};

struct fine{
    xmlChar* id;
    xmlChar* event_ref;
    
    xmlChar* fine_value;
};

struct coda{
    xmlChar* id;
    xmlChar* event_ref;

    xmlChar* coda_value;
};

struct segno{
    xmlChar* id;
    xmlChar* event_ref;
    
    xmlChar* segno_value;
};

struct jump_to{
    xmlChar* id;
    xmlChar* event_ref;
    
    struct jump_to* next_jump_to;
};

struct end{
    xmlChar* id;
    xmlChar* event_ref;
    
    struct end* next_end;
};

struct repeat{
    xmlChar* id;
    xmlChar* event_ref;
    
    xmlChar* repeat_text;//?
    struct jump_to* jump_tos;//(jump_to,end?)+
    struct end* ends;//
};

struct barre{
    xmlChar* start_string_position;//REQUIRED
    xmlChar* end_string_position;//REQUIRED
    xmlChar* fret_position;//REQUIRED
    
    struct barre* next_barre;
};

struct tablature_element{
    xmlChar* shape;//REQUIRED (empty_circle,full_circle,cross,rhombus,1,2,3,4,T)
    xmlChar* string_position;//REQUIRED
    xmlChar* fret_position;//REQUIRED
    
    struct tablature_element* next_tablature_element;
};

struct tablature_hsymbol{//(tablature_element|barre)+
    xmlChar *id;
    xmlChar* event_ref;
    int string_number;//REQUIRED
    xmlChar* start_fret;//REQUIRED
    int fret_number;//REQUIRED
    
    struct barre* barres;
    struct tablature_element* tablature_elements;
};

struct special_beam{//(notehead_ref+)
    xmlChar* id;
    xmlChar* fanned_from;
    xmlChar* fanned_to;
    
    struct notehead_ref* notehead_ref;//+
};

struct slur{//(svg?)
    xmlChar* id;
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
    xmlChar* shape;//(normal,dasched,dotted) default normal
    int bracketed;//(yes,no) default no
};

struct percussion_special{
    xmlChar* percussion_special_value;
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* type;//REQUIRED (play_on_border,stop_drumhead,muffle_with_harmonics,muffle,rub,shake)
};

struct percussion_beater{
    xmlChar* percussion_beater_value;
    xmlChar* id;
    xmlChar* type;//REQUIRED (bow,snare_stick,snare_stick_plastic,spoon_shaped,guiro,triangle,knitting_needle,hand,hammer,metal_hammer,wooden_timpani_mallet,light_timpani_mallet,medium_timpani_mallet,heavy_timpani_mallet,light_vibraphone_mallet,medium_vibraphone_mallet,heavy_vibraphone_mallet,light_bassdrum_mallet,medium_bassdrum_mallet,heavy_bassdrum_mallet,steel_core_bassdrum_mallet,coin,brush,nails)
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
};

struct pedal_end{
    xmlChar* id;
    xmlChar* event_ref;
};

struct pedal_start{
    xmlChar* id;
    xmlChar* event_ref;
};

struct octave_bracket{
    xmlChar* id;
    xmlChar* type;//REQUIRED (8va,8vb,15ma,15mb)
    xmlChar* staff_ref;//REQUIRED
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
};

struct hairpin{
    xmlChar* id;
    xmlChar* type;//REQUIRED (crescendo,diminuendo)
    xmlChar* staff_ref;
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
};

struct glissando{
    xmlChar* id;
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
};

struct fermata{
    xmlChar* id;
    xmlChar* event_ref;
    
    int fermata_value;
};

struct dynamic{
    xmlChar* id;
    xmlChar* extension_line_to;
    xmlChar* extension_line_shape;// (normal,dotted,dashed)
    xmlChar* staff_ref;
    xmlChar* event_ref;
    
    xmlChar* dynamic_value;
};

struct chord_symbol{
    xmlChar* id;
    xmlChar* event_ref;
    
    xmlChar* chord_symbol_value;
};

struct breath_mark{
    xmlChar* id;
    xmlChar* type;//REQUIRED (comma,caesura)
    xmlChar* staff_ref;
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
};

struct bend{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* type;//(single,double) default single
    xmlChar* to_pitch;//REQUIRED (A,B,C,D,E,F,G,up,down)
    xmlChar* to_accidental;
    int to_octave;
};

struct arpeggio{
    xmlChar* shape;//REQUIRED (wavy,line,no_arpeggio)
    xmlChar* direction;//(up,down) default=down
    
    struct notehead_ref* notehead_ref;//+
};

typedef union{
    struct arpeggio arpeggio;
    struct bend bend;
    struct breath_mark breath_mark;
    struct chord_symbol chord_symbol;
    struct dynamic dynamic;
    struct fermata fermata;
    struct glissando glissando;
    struct hairpin hairpin;
    struct octave_bracket octave_bracket;
    struct pedal_start pedal_start;
    struct pedal_end pedal_end;
    struct percussion_beater percussion_beater;
    struct percussion_special percussion_special;
    struct slur slur;
    struct special_beam special_beam;
    struct tablature_hsymbol tablature_hsymbol;
    struct repeat repeat;
    struct coda coda;
    struct segno segno;
    struct fine fine;
    struct multiple_endings multiple_endings;
    struct custom_hsymbol custom_hsymbol;    
    int empty;
}horizontal_symbol;
//Horizontal Symbols END

//Ornaments START
struct turn{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* type;//REQUIRED (over,after)
    xmlChar* style;//REQUIRED (normal,inverted,cut,vertical)
    xmlChar* upper_accidental;
    xmlChar* lower_accidental;
};

struct trill{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* accidental;
    xmlChar* style;//(t,tr,tr-,plus,double_slash,caesura_double_slash,slur_double_slash,mordent,double_mordent)
    xmlChar* start_hook;//(none,up,down)
    xmlChar* end_hook;//(none,up,down)
};

struct tremolo{
    xmlChar* id;
    xmlChar* start_event_ref;
    xmlChar* end_event_ref;
    int tremolo_lines;//REQUIRED (1,2,3,4,5,6(
};

struct mordent{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* type;//(upper,lower) default upper
    xmlChar* length;//(normal,double) default normal
    xmlChar* accidental;// default none
    xmlChar*style;//(normal,up_hook,down_hook) default normal
};

struct baroque_appoggiatura{
    xmlChar* id;
    xmlChar* event_ref;
    xmlChar* style;//REQUIRED (hairpin,plus,salsh,backslash,pipe,double_slup,up_hook,down_hook) 
};

struct appoggiatura{//(chord+)
    xmlChar* id;
    xmlChar* event_ref;
    int slur;//(yes,no) default no
    
    struct chord* chords;
};

struct baroque_acciaccatura{
    xmlChar *id;
    xmlChar* event_ref;
    xmlChar* style;//REQUIRED (vertical_turn,mordent,flatte,tierce_coulee,slash,backslash)
};

struct acciaccatura{//(chord+)
    xmlChar* id;
    xmlChar* event_ref;
    int slur;//(yes,no) default no
    
    struct chord* chords;
};

typedef union{
    struct acciaccatura acciaccatura;
    struct baroque_acciaccatura baroque_acciaccatura;
    struct appoggiatura appoggiatura;
    struct baroque_appoggiatura baroque_appoggiatura;
    struct mordent mordent;
    struct tremolo tremolo;
    struct trill trill;
    struct turn turn;
    int empty;
}ornament;
//Ornaments END

//Functions
ornament loadOrnamentValue(xmlNodePtr cur);
horizontal_symbol loadHorizontalSymbolValue(xmlNodePtr cur);
struct voice_item* loadVoiceItemValue(xmlNodePtr cur);
struct measure* loadMeasureValue(xmlNodePtr cur);
struct clef* loadClefValue(xmlNodePtr cur);
struct key_signature* loadKeySignatureValue(xmlNodePtr cur);
struct custom_key_signature* loadCustomKeySignatureValue(xmlNodePtr cur);
struct time_signature* loadTimeSignatureValue(xmlNodePtr cur);
struct barline* loadBarlineValue(xmlNodePtr cur);
struct tablature_tuning* loadTablatureTuningValue(xmlNodePtr cur);
struct voice* loadVoiceValue(xmlNodePtr cur);
struct chord* loadChordValue(xmlNodePtr cur);
struct notehead* loadNoteheadValue(xmlNodePtr cur);
struct duration loadDurationValue(xmlNodePtr cur);
struct key* loadKeyValue(xmlNodePtr cur);
struct articulation* loadArticulationValue(xmlNodePtr cur);
struct tuplet_ratio* loadTupletRatio(xmlNodePtr cur);

#ifdef __cplusplus
}
#endif

#endif /* MUSICLANG_H */

