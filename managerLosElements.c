/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerLosElements.h"

ornament loadOrnamentValue(xmlNodePtr cur){
    ornament value;
    
    return value;
}

horizontal_symbol loadHorizontalSymbolValue(xmlNodePtr cur){
    horizontal_symbol value;
    xmlAttr *attributes;
    
    if(!xmlStrcmp(cur->name,(const xmlChar*)"arpeggio")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"bend")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"breath_mark")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"chord_symbol")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"dynamic")){
        value.dynamic.dynamic_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.dynamic.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_to")){
                value.dynamic.extension_line_to=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_shape")){
                value.dynamic.extension_line_shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                value.dynamic.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.dynamic.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"fermata")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"glissando")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"hairpin")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"octave_bracket")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_start")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_end")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_beater")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_special")){
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"slur")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"special_beam")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"tablature_hsymbol")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"repeat")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"coda")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"segno")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"fine")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"multiple_ending")){
        }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"custom_hsymbol")){
    }
    else
        fprintf(stderr,"Element is not an Horizontal Symbol\n");
    
    return value;
}

struct voice_item* loadVoiceItemValue(xmlNodePtr cur){
    struct voice_item* value;
    return value;
}

struct measure* loadMeasureValue(xmlNodePtr cur){
    struct measure* value;
    return value;
}

struct clef* loadCleffValue(xmlNodePtr cur){
    struct clef* value;
    return value;
}

struct key_signature* loadKeySignatureValue(xmlNodePtr cur){
    struct key_signature* value;
    return value;
}

struct custom_key_signature* loadCustomKeySignatureValue(xmlNodePtr cur){
    struct custom_key_signature* value;
    return value;
}

struct time_signature* loadTimeSignatureValue(xmlNodePtr cur){
    struct time_signature* value;
    return value;
}

struct barline* loadBarlineValue(xmlNodePtr cur){
    struct barline* value;
    return value;
}

struct tablature_tuning* loadTablatureTuningValue(xmlNodePtr cur){
    struct tablature_tuning* value;
    return value;
}
