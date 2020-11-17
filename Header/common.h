/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.h
 * Author: Ale
 *
 * Created on 26 agosto 2020, 22.08
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <string.h>

enum accidentals {double_sharp,sharp_and_a_half,sharp,demisharp,natural,demiflat,flat,flat_and_a_half,double_flat};
enum articulation_signs {normal_accent,staccatissimo,staccato,strong_accent,tenuto,stopped_note,snap_pizzicato,natural_harmonic,up_bow,down_bow,open_mute,close_mute,custom_articulation};
enum neumes {punctum,virga,punctum_inclinatum,quilisma,apostrofa,oriscus,podatus,pes,clivis,flexa,epiphonus,cephalicus,bistropha,bivirga,trigon,torculus,porrectus,scandicus,salicus,climacus,tristropha,trivirga,strophicus,pressus,custos};
enum layout_measurement_units {centimeters,millimeters,inches,decimal_inches,points,picas,pixels,twips};
enum formats {a0,a1,a2,a3,a4,a5,a6,a7,a8,b0,b1,b2,b3,b4,b5,b6,b7,b8,c0,c1,c2,c3,c4,c5,c6,c7,c8,ansi_a,ansi_b,ansi_c,ansi_d,ansi_e,arch_a,arch_b,arch_c,arch_e,arch_e1,quarto,foolscap,executive,monarch,government_letter,letter,legal,ledger,tabloid,post,crown,large_post,demy,medium,royal,elephant,double_demy,quad_demy,statement};

struct rights{
    xmlChar* file_name;
};

struct genre{//?
     xmlChar* name;//REQUIRED
     xmlChar* description;
     xmlChar* weight;

     struct genre* next_genre;
};
    
extern xmlChar *docname;
extern xmlDocPtr doc;
extern char* file_name;

xmlDocPtr getDoc(xmlChar* docpath);
int validate(xmlDocPtr doc);
xmlXPathObjectPtr getNodeset(xmlDocPtr doc, xmlChar *xpath);
char* concat(const char *s1, const char *s2);  
int xmlCharToInt(xmlChar* string);
//double xmlCharToDouble(xmlChar* string);

struct rights loadRights(xmlNodePtr cur);
struct genre* loadGenre(xmlNodePtr cur);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */

