/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerDocument.h
 * Author: Ale
 *
 * Created on 10 settembre 2020, 1.14
 */

#ifndef MANAGERDOCUMENT_H
#define MANAGERDOCUMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "managerGeneral.h"
#include "managerLogic.h"
#include "managerNotational.h"
#include "managerStructural.h"    
#include "managerPerformance.h"     
#include "managerAudio.h"
    
struct ieee1599{
    xmlChar* file_name;

    xmlChar* version;
    xmlChar* creator;

    struct general general_layer;
    struct logic logic_layer;
    struct structural structural_layer;
    struct notational notational_layer;
    struct performance performance_layer;
    struct audio audio_layer;
};

extern struct ieee1599 ieee1599_document;

void loadDocument();
void printDocument();

#ifdef __cplusplus
}
#endif

#endif /* MANAGERDOCUMENT_H */

