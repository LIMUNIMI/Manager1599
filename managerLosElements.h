/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   musicLang.h
 * Author: Ale
 *
 * Created on 3 settembre 2020, 2.17
 */

#ifndef MUSICLANG_H
#define MUSICLANG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
    
enum accidentals {double_sharp,sharp_and_a_half,sharp,demisharp,natural,demiflat,flat,flat_and_a_half,double_flat};
enum articulation_signs {normal_accent,staccatissimo,staccato,strong_accent,tenuto,stopped_note,snap_pizzicato,natural_harmonic,up_bow,down_bow,open_mute,close_mute,custom_articulation};
enum neumes {punctum,virga,punctum_inclinatum,quilisma,apostrofa,oriscus,podatus,pes,clivis,flexa,epiphonus,cephalicus,bistropha,bivirga,trigon,torculus,porrectus,scandicus,salicus,climacus,tristropha,trivirga,strophicus,pressus,custos};

//Staff Eelements START
struct string{
    int string_number;//REQUIRED
    char* string_pitch;//(A,B,C,D,E,F,G) REQUIRED
    //accidental string_accidental
    int string_octave;//REQUIRED
    
    struct string* next_string;
};

struct tablature_tuning{
    char* type;//(D,E,G,A,baroque,flat_french,other)
    struct string* strings;
    
    struct tablature_tuning* next_tablature_tuning;
};

struct barline{
    char* style;//REQUIRED (dashed,double,final,invisibile,staandard,medium,short)
    char* extensione;//REQUIRED (single_staff,staff_group,all_stave,mensurstrich
    //spine_ref
    
    struct barline* next_barline;
};

struct time_indication{
    int num;//REQUIRED
    int den;//REQUIRED
    char* abbreviation;//(yes,no) default no
    int vtu_amount;
    
    struct time_indication* next_time_indication;
};

struct time_signature{
    char* visibile;//(yes,no) default no
    //spine_ref    
    struct time_indication* time_indications;//+
    
    struct time_signature* next_time_signature;
};

struct key_accidental{
    char* step;//REQUIRED (A,B,C,D,E,F,G)
    //accidental accidental
    struct key_accidental* next_key_accidental;
};

struct custom_key_signature{
    //spine_ref
    struct key_accidental* key_accidentals;//+
    
    struct custom_key_signature* next_custom_key_signature;
};

struct key_signature{
    char* num_type;//REQUIRED(flat_num,sharp_num)
    int number;//REQUIRED (0,1,2,3,4,5,6,7)
    //spine_ref
    
    struct key_signature* next_key_signature;
};

struct clef{
    char* shape;//REQUIRED (G,F,C,gregorian_F,gregorian_C,percussion,doubleG,tabguitar)
    char* staff_step;//REQUIRED
    int octave_num;//(0,8,-8,15,-15) default 0
    //spine_ref
    
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

struct printed_accidental_list{
    char* parenthesis;//(yes,no) default no
    struct printed_accidental_list* next_printed_accidental;
};

struct printed_accidentals{
    char* shape;//(normal,small,bracketed) default normal
    struct printed_accidental_list* printed_accidentals;
};

struct pitch{
    char* step;//REQUIRED (A,B,C,D,E,F,G,none)
    int octve;//REQUIRED
    //accidental actual_accidental
};

struct notehead{
    char* id;
    //staff_ref
    char* style;//(normal,harmonic,unpitched,cymbal,parenthesis,circled,squared)
    struct pitch pitch;
    struct printed_accidentals printed_accidentals;//?
    int tie;//? yes=,no=0
    struct fingering fingering;//?
    struct notehead* next_notehead;
};

struct notehead_ref{
    //spine_ref
    
    struct notehead_ref* next_notehead_ref;
};

struct articulation{
    char articulation_sign;
    //svg per custom_articulation
    struct articulation* next_articulation;
};

struct gregorian_symbol{
    int n_noteheads;
    
    char* id;
    char* neume;//REQUIRED
    char* inflexion;//(no,resupinus,fleux) default no
    char* subpunctis;//(no,praepunctis,subpunctis,subbipunctis,subtripunctis,subquadripunctis,subquinquipunctis) default no
    char* interpretative_mark;//(no,vertical_episema,horizontal_episema,liquescens) default no
    char* mora;//(yes,no) default no
    //spine_ref
    
    struct notehead* notehead;
    
    struct gregorian_symbol* next_gregorian_symbol;
};

struct tablature_fingering{
    char* tablature_fingering_value;
    char* shape;//REQUIRED (number,dot,other)
};

struct tablature_articulation{
    char* shape;//REQUIRED (cross,tie,other)
};

struct tablature_pitch{
    int string_number;
    int key_number;//REQUIRED
};

struct key{
    struct tablature_pitch tablature_pitch;
    struct tablature_articulation tablature_articulation;//?
    int tie;//? yes=,no=0
    struct tablature_fingering tablature_fingering;//?
    char* id;
    //staff_ref
    struct key* next_key;
};

struct tuplet_ratio{//(tuplet_ratio)
    int enter_num;//REQUIRED
    int enter_den;//REQUIRED
    int enter_dots;
    int in_num;//REQUIRED
    int in_den;//REQUIRED
    int in_dots;
    struct tuplet_ratio* next_tuplet_ratio;
};

struct duration{
    int num;//REQUIRED
    int den;//REQUIRED
    struct tuplet_ratio* tuplet_ratio;//?
};

struct tablature_symbol{
    int n_keys;
    
    char* id;
    //spine_ref
    char* stem_direction;//(up,down,none)
    char* beam_before;//(yes,no) default no
    char* beam_after;//(yes,no) default no
    
    struct duration duration;
    struct augmentation_dots augmentation_dots;//?
    struct key* keys;
    
    struct tablature_symbol* next_tablature_symbol;
};

struct rest{
    char* id;
    //spine_ref
    //staff_ref
    char* hidden;//(yes,no)
    
    struct duration duration;
    struct augmentation_dots augmentation_dots;//?
    
    struct rest* next_rest;
};

struct chord{
    int n_noteheads;
    int n_articulations;
    
    char* id;
    //spine_ref
    char* stem_direction;//(up,down,none)
    char* beam_before;//(yes,no) default no
    char* beam_after;//(yes,no) default no
    char* cue;//(yes,no) default no
    char* tremolo_lines;//(no,1,2,3,4,5,6)    
    
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
    
    //voice_item_ref REQUIRED
    char* ossia;//(yes,no) default no
    
    struct chord* chords;
    struct rest* rests;
    struct tablature_symbol* tablature_symbols;
    struct gregorian_symbol* gregorian_symbols;
    
    struct voice* next_voice;
};

struct measure_repeat{
    int number_of_measures;//REQUIRED
    //event_ref
};

struct multiple_rest{
    int number_of_measures;//REQUIRED
    //event_ref
};

struct measure{
    int n_voices;
    
    int number;//REQUIRED
    char* id;
    char* show_number;//(yes,no)
    char* numbering_style;//(arabic_numbers,roman_numbers,small_letter,capital_letters)
    
    //(voice+ | multiple_rest | measure_repeat?)
    struct voice* voices;//+
    struct multiple_rest multiple_rest;//1
    struct measure_repeat measure_repeat;//?    
    
    struct measure* next_measure;
};

struct voice_item{
    char* id;//REQUIRED
    //staff_ref REQUIRED
    char* notation_style;///(normal,rhythmic,slash,blank))
    
    struct voice_item* next_voice_item;
};
//Part Elements  END

//Horizontal Symbols START
struct custom_hsymbol{
    //svg
    char* id;
    //start_event_ref REQUIRED
    //end_event_ref
};    

struct multiple_ending{
    char* id;
    int number;//REQUIRED
    //spine_start_end_ref
    //return_to IDREF
    
    struct multiple_ending* next_multiple_ending;
};

struct multiple_endings{//+
    char* id;

    struct multiple_ending* multiple_ending;
};

struct fine{
    char* id;
    //spine_ref
    
    char* fine_value;
};

struct coda{
    char* id;
    //spine_ref

    char* coda_value;
};

struct segno{
    char* id;
    //spine_ref
    
    char* segno_value;
};

struct jump_to{
    char* id;
    //spine_ref
    
    struct jump_to* next_jump_to;
};

struct end{
    char* id;
    //spine_ref
    
    struct end* next_end;
};

struct repeat{
    char* id;
    //spine_ref
    
    char* repeat_text;//?
    struct jump_to* jump_tos;//(jump_to,end?)+
    struct end* ends;//
};

struct barre{
    char* start_string_position;//REQUIRED
    char* end_string_position;//REQUIRED
    char* fret_position;//REQUIRED
    
    struct barre* next_barre;
};

struct tablature_element{
    char* shape;//REQUIRED (empty_circle,full_circle,cross,rhombus,1,2,3,4,T)
    char* string_position;//REQUIRED
    char* fret_position;//REQUIRED
    
    struct tablature_element* next_tablature_element;
};

struct tablature_hsymbol{//(tablature_element|barre)+
    char *id;
    //spine_ref
    int string_number;//REQUIRED
    char* start_fret;//REQUIRED
    int fret_number;//REQUIRED
    
    struct barre* barres;
    struct tablature_element* tablature_elements;
};

struct special_beam{//(notehead_ref+)
    char* id;
    char* fanned_from;
    char* fanned_to;
    
    struct notehead_ref* notehead_ref;//+
};

struct slur{//(svg?)
    char* id;
    //spine_start_end_ref
    char* shape;//(normal,dasched,dotted) default normal
    char* bracketed;//(yes,no) default no
};

struct percussion_special{
    char* percussion_special_value;
    char* id;
    //spine_ref
    char* type;//REQUIRED (play_on_border,stop_drumhead,muffle_with_harmonics,muffle,rub,shake)
};

struct percussion_beater{
    char* percussion_beater_value;
    char* id;
    char* type;//REQUIRED (bow,snare_stick,snare_stick_plastic,spoon_shaped,guiro,triangle,knitting_needle,hand,hammer,metal_hammer,wooden_timpani_mallet,light_timpani_mallet,medium_timpani_mallet,heavy_timpani_mallet,light_vibraphone_mallet,medium_vibraphone_mallet,heavy_vibraphone_mallet,light_bassdrum_mallet,medium_bassdrum_mallet,heavy_bassdrum_mallet,steel_core_bassdrum_mallet,coin,brush,nails)
    //strat_evenet_ref
    //end_event_ref
};

struct pedal_end{
    char* id;
    //spine_ref
};

struct pedal_start{
    char* id;
    //spine_ref
};

struct octave_bracket{
    char* id;
    char* type;//REQUIRED (8va,8vb,15ma,15mb)
    //REQUIRED staff_ref 
    //spine_start_end_ref
};

struct hairpin{
    char* id;
    char* type;//REQUIRED (crescendo,diminuendo)
    //staff_ref
    //spine_start_end_ref
};

struct glissando{
    char* id;
    //start_event_ref
    //end_event_ref
};

struct fermata{
    char* id;
    //spine_ref
    
    int fermata_value;
};

struct dynamic{
    char* id;
    char* extension_line_to;
    char* extension_line_shape;// (normal,dotted,dashed)
    char* staff_ref;
    char* event_ref;
    
    char* dynamic_value;
};

struct chord_symbol{
    char* id;
    //spine_ref
    
    char* chord_symbol_value;
};

struct breath_mark{
    char* id;
    char* type;//REQUIRED (comma,caesura)
    //staff_ref
    //spine_start_end_ref
};

struct bend{
    char* id;
    //spine_ref
    char* type;//(single,double) default single
    char* to_pitch;//REQUIRED (A,B,C,D,E,F,G,up,down)
    //accidental to_accidental;
    int to_octave;
};

struct arpeggio{
    char* shape;//REQUIRED (wavy,line,no_arpeggio)
    char* direction;//(up,down) default=down
    
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
}horizontal_symbol;
//Horizontal Symbols END

//Ornaments START
struct turn{
    char* id;
    //spine_ref
    char* type;//REQUIRED (over,after)
    char* style;//REQUIRED (normal,inverted,cut,vertical)
    //accidental upper_accidental
    //accidental lower_accidental
};

struct trill{
    char* id;
    //spine_ref
    char* style;//(t,tr,tr-,plus,double_slash,caesura_double_slash,slur_double_slash,mordent,double_mordent
    char* start_hook;//(none,up,down)
    char* end_hook;//(none,up,down)
};

struct tremolo{
    char* id;
    //spine_start_end_ref
    int tremolo_lines;//REQUIRED (1,2,3,4,5,6(
};

struct mordent{
    char* id;
    //spine_ref
    char* type;//(upper,lower) default upper
    char* length;//(normal,double) default normal
    //accidental accidental; default none
    char*style;//(normal,up_hook,down_hook) default normal
};

struct baroque_appoggiatura{
    char* id;
    //spine_ref;
    char* style;//REQUIRED (hairpin,plus,salsh,backslash,pipe,double_slup,up_hook,down_hook) 
};

struct appoggiatura{//(chord+)
    char* id;
    //spine_ref
    char* slur;//(yes,no) default no
    
    struct chord* chords;
};

struct baroque_acciaccatura{
    char *id;
    //spine_ref
    char* style;//REQUIRED (vertical_turn,mordent,flatte,tierce_coulee,slash,backslash)
};

struct acciaccatura{//(chord+)
    char* id;
    //spine_ref
    char* slur;//(yes,no) default no
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
}ornament;
//Ornaments END

//Functions
ornament loadOrnamentValue(xmlNodePtr cur);
horizontal_symbol loadHorizontalSymbolValue(xmlNodePtr cur);
struct voice_item* loadVoiceItemValue(xmlNodePtr cur);
struct measure* loadMeasureValue(xmlNodePtr cur);
struct clef* loadCleffValue(xmlNodePtr cur);
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

#ifdef __cplusplus
}
#endif

#endif /* MUSICLANG_H */

