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

struct chord{

};

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
};

struct multiple_endings{//+
    char* id;
    struct multiple_ending multiple_ending_value;
    struct multiple_ending* next_multiple_ending;
};

struct fine{
    char* fine_value;
    char* id;
    //spine_ref
};

struct coda{
    char* coda_value;
    char* id;
    //spine_ref
};

struct segno{
    char* segno_value;
    char* id;
    //spine_ref
};

struct end{
    char* id;
    //spine_ref
};

struct jump_to{
    char* id;
    //spine_ref
};

struct repeat{
    char* id;
    //spine_ref
    char* repeat_text;
    struct jumps{//(jump_to,end?)+
        struct jump_to jump_to;//REQUIRED
        struct end end;
        struct jumps* next_jump;
    }jumps;
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
    char* fre_position;//REQUIRED
    struct tablature_element next_tablature_element;
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
    //nothead_ref list

};

struct slur{//(svg?)
    char* id;
    //spine_start_end_ref
    char* shape;//(normal,dasched,dotted) default normal
    int bracketed;//no=0, yes=1, default no
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
    int fermata_value;
    char* id;
    //spine_ref
};

struct dynamic{
    char* dynamic_value;
    char* id;
    //extension_line_to
    //extension_line_shape (normal,dotted,dashed)
    //staff_ref
    //spine_ref
};

struct chord_symbol{
    char* chord_symbol_value;
    char* id;
    //spine_ref
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

struct arpeggio{//(notehead_ref+)
    //nothead_ref list
    char* shape;//REQUIRED (wavy,line,no_arpeggio)
    char* direction;//(up,down) default=down
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
    struct multiple_ending multiple_ending;
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
    int slur;//no=0, yes=1 default no
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
    int slur;//no=0, yes=1 default no
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

#ifdef __cplusplus
}
#endif

#endif /* MUSICLANG_H */

