/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerNotational.h
 * Author: Ale
 *
 * Created on 5 settembre 2020, 17.34
 */

#ifndef MANAGERNOTATIONAL_H
#define MANAGERNOTATIONAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

//Graphic Instance Group
    struct graphic_event{
        xmlChar* event_ref;
        xmlChar* upper_left_x;//REQUIRED
        xmlChar* upper_left_y;//REQUIRED
        xmlChar* lower_right_x;//REQUIRED
        xmlChar* lower_right_y;//REQUIRED
        xmlChar* highlight_color;
        xmlChar* description;

        struct graphic_event* next_graphic_event;
    };

    struct graphic_instance{//(graphic_event+,rights?)
        int n_graphic_events;

        xmlChar* description;
        int position_in_group;//REQUIRED
        xmlChar* file_name;//REQUIRED
        xmlChar* file_format;//REQUIRED
        xmlChar* encoding_format;//REQUIRED
        xmlChar* measurement_unit;//REQUIRED

        struct graphic_event* graphic_event;
        struct rights rights;

        struct graphic_instance* next_graphic_instance;
    };

    struct graphic_instance_group{//(graphic_instance+)
        int n_graphic_instances;

        xmlChar* description;//REQUIRED

        struct graphic_instance* graphic_instances;

        struct graphic_instance_group* next_graphic_instance_group;
    };

//Notation Instance Group
    struct notation_event{
        xmlChar* event_ref;
        xmlChar* start_position;//REQUIRED
        xmlChar* end_position;//REQUIRED
        xmlChar* description;

        struct notation_event* next_notation_event;
    };

    struct notation_instance{//(notation_event+,rights?)
        int n_notation_events;

        xmlChar* description;
        int position_in_group;//REQUIRED
        xmlChar* file_name;//REQUIRED
        xmlChar* format;//REQUIRED
        xmlChar* measurement_unit;//REQUIRED

        struct notation_event* notation_events;
        struct rights rights;

        struct notation_instance* next_notation_instance;
    };

    struct notation_instance_group{//(notation_instance+)
        int n_notation_instances;

        xmlChar* description;//REQUIRED

        struct notation_instance* notation_instances;

        struct notation_instance_group* next_notation_instance_group;
    };

//Notational
    struct notational{//(graphic_instance_group | notation_instance_group)+
        int n_graphic_insance_groups;
        int n_notation_instance_groups;

        struct graphic_instance_group* graphic_instance_group;
        struct notation_instance_group* notation_instance_group;
    };

//Variables
    
    
//Prototypes
    MANAGERIEEE1599_API struct notational loadNotational();
    MANAGERIEEE1599_API void loadGraphicInstanceGroup();
    MANAGERIEEE1599_API void loadNotationInstanceGroup();
    
    struct graphic_instance* loadGraphicInstance(xmlNodePtr cur);
    struct notation_instance* loadNotationInstance(xmlNodePtr cur);

    MANAGERIEEE1599_API void printNotational();
    MANAGERIEEE1599_API void printGraphicInstanceGroup();
    MANAGERIEEE1599_API void printNotationInstanceGroup();

#ifdef __cplusplus
}
#endif

#endif /* MANAGERNOTATIONAL_H */

