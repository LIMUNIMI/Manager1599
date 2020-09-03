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
    //(jump_to,end?)+
};

typedef union{

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

