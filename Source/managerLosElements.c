/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerLosElements.h"

ornament loadOrnamentValue(xmlNodePtr cur){
    ornament value;
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    
    struct chord* chord_temp;
    struct chord* chord_head;
    struct chord* chord_p;
    
    if(!xmlStrcmp(cur->name,(const xmlChar*)"acciaccatura")){//contains chord+
        chord_temp=NULL;
        chord_head=NULL;
        chord_p=NULL;

        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.acciaccatura.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.acciaccatura.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"slur")){
                if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                    value.acciaccatura.slur= 1;
                else
                    value.acciaccatura.slur= 0;
            }
            attributes=attributes->next;
        }
        
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"chord")){
                chord_temp=(struct chord*)malloc(sizeof(struct chord));
                chord_temp=calloc(1,sizeof(struct chord));
                chord_temp=loadChordValue(temp_cur);
                chord_temp->next_chord=NULL;
                if(chord_head==NULL)
                    chord_head=chord_temp;
                else{
                    chord_p=chord_head;
                    while(chord_p->next_chord!=NULL)
                        chord_p=chord_p->next_chord;
                    chord_p->next_chord=chord_temp;
                }
            }  
        }
        value.acciaccatura.chords=chord_head;
        
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"baroque_acciaccatura")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.baroque_acciaccatura.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.baroque_acciaccatura.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
                value.baroque_acciaccatura.style=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"appoggiatura")){//contains chord+
        chord_temp=NULL;
        chord_head=NULL;
        chord_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.appoggiatura.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.appoggiatura.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"slur")){
                if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                    value.appoggiatura.slur= 1;
                else
                    value.appoggiatura.slur= 0;
            }
            attributes=attributes->next;
        }
        
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"chord")){
                chord_temp=(struct chord*)malloc(sizeof(struct chord));
                chord_temp=calloc(1,sizeof(struct chord));
                chord_temp=loadChordValue(temp_cur);
                chord_temp->next_chord=NULL;
                if(chord_head==NULL)
                    chord_head=chord_temp;
                else{
                    chord_p=chord_head;
                    while(chord_p->next_chord!=NULL)
                        chord_p=chord_p->next_chord;
                    chord_p->next_chord=chord_temp;
                }
            }  
        }
        value.appoggiatura.chords=chord_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"baroque_appoggiatura")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.baroque_appoggiatura.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.baroque_appoggiatura.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
                value.baroque_appoggiatura.style=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"mordent")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.mordent.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.mordent.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.mordent.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"length")){
                value.mordent.length=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"accidental")){
                //value.mordent.accidental=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
                value.mordent.style=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"tremolo")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.tremolo.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.tremolo.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.tremolo.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"tremolo_lines")){
		if(xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"no"))
                	value.tremolo.tremolo_lines=xmlCharToInt(xmlGetProp(cur,attributes->name));                
            }
            attributes=attributes->next;
        }
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"trill")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.trill.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.trill.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"accidental")){
                value.trill.accidental=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
                value.trill.style=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_hook")){
                value.trill.start_hook=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_hook")){
                value.trill.end_hook=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"turn")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.turn.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.turn.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.turn.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
                value.turn.style=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"upper_accidental")){
                value.turn.upper_accidental=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"lower_accidental")){
                value.turn.lower_accidental=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
    }
    
    return value;
}

horizontal_symbol loadHorizontalSymbolValue(xmlNodePtr cur){
    horizontal_symbol value;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    if(!xmlStrcmp(cur->name,(const xmlChar*)"arpeggio")){       
        struct notehead_ref* notehead_ref_temp=NULL;
        struct notehead_ref* notehead_ref_head=NULL;
        struct notehead_ref* notehead_ref_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                value.arpeggio.shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"direction")){
                value.arpeggio.direction=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){//notehead_ref list in arpeggio
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead_ref")){
                notehead_ref_temp=(struct notehead_ref*)malloc(sizeof(struct notehead_ref));
                notehead_ref_temp=calloc(1,sizeof(struct notehead_ref));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"event_ref")){
                        notehead_ref_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                notehead_ref_temp->next_notehead_ref=NULL;
                if(notehead_ref_head==NULL)
                    notehead_ref_head=notehead_ref_temp;
                else{
                    notehead_ref_p=notehead_ref_head;
                    while(notehead_ref_p->next_notehead_ref!=NULL)
                        notehead_ref_p=notehead_ref_p->next_notehead_ref;
                    notehead_ref_p->next_notehead_ref=notehead_ref_temp;
                }
            }  
        }//end notehead_ref list in arpeggio
        value.arpeggio.notehead_ref=notehead_ref_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"bend")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.bend.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.bend.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.bend.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_pitch")){
                value.bend.to_pitch=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_accidental")){
                value.bend.to_accidental=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_octave")){
                value.bend.to_octave=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"breath_mark")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.breath_mark.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.breath_mark.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                value.breath_mark.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.breath_mark.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.breath_mark.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"chord_symbol")){
        value.chord_symbol.chord_symbol_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.chord_symbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.chord_symbol.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
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
        value.fermata.fermata_value=xmlCharToInt(xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.fermata.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.fermata.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"glissando")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.glissando.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.glissando.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.glissando.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"hairpin")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.hairpin.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.hairpin.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                value.hairpin.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.hairpin.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.hairpin.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"octave_bracket")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.octave_bracket.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.octave_bracket.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                value.octave_bracket.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.octave_bracket.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.octave_bracket.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_start")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.pedal_start.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.pedal_start.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_end")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.pedal_end.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.pedal_end.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_beater")){
        value.percussion_beater.percussion_beater_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.percussion_beater.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.percussion_beater.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.percussion_beater.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.percussion_beater.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_special")){
        value.percussion_special.percussion_special_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.percussion_special.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.percussion_special.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.percussion_special.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"slur")){
        //load svg
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.slur.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.slur.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.slur.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                value.slur.shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"bracketed")){
                if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                    value.slur.bracketed= 1;
                else
                    value.slur.bracketed= 0;
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"special_beam")){
        struct notehead_ref* notehead_ref_temp=NULL;
        struct notehead_ref* notehead_ref_head=NULL;
        struct notehead_ref* notehead_ref_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.special_beam.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fanned_from")){
                value.special_beam.fanned_from=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fanned_to")){
                value.special_beam.fanned_to=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){//notehead_ref list in special_beam
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead_ref")){
                notehead_ref_temp=(struct notehead_ref*)malloc(sizeof(struct notehead_ref));
                notehead_ref_temp=calloc(1,sizeof(struct notehead_ref));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"event_ref")){
                        notehead_ref_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                notehead_ref_temp->next_notehead_ref=NULL;
                if(notehead_ref_head==NULL)
                    notehead_ref_head=notehead_ref_temp;
                else{
                    notehead_ref_p=notehead_ref_head;
                    while(notehead_ref_p->next_notehead_ref!=NULL)
                        notehead_ref_p=notehead_ref_p->next_notehead_ref;
                    notehead_ref_p->next_notehead_ref=notehead_ref_temp;
                }
            }  
        }//end notehead_ref list in special_beam
        value.special_beam.notehead_ref=notehead_ref_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"tablature_hsymbol")){
        struct tablature_element* tablature_element_temp=NULL;
        struct tablature_element* tablature_element_head=NULL;
        struct tablature_element* tablature_element_p=NULL;
        
        struct barre* barre_temp=NULL;
        struct barre* barre_head=NULL;
        struct barre* barre_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.tablature_hsymbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.tablature_hsymbol.event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_number")){
                value.tablature_hsymbol.string_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_fret")){
                value.tablature_hsymbol.start_fret=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fret_number")){
                value.tablature_hsymbol.fret_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_element")){
                tablature_element_temp=(struct tablature_element*)malloc(sizeof(struct tablature_element));
                tablature_element_temp=calloc(1,sizeof(struct tablature_element));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"shape")){
                        tablature_element_temp->shape=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"string_position")){
                        tablature_element_temp->string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"fret_position")){
                        tablature_element_temp->fret_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                tablature_element_temp->next_tablature_element=NULL;
                if(tablature_element_head==NULL)
                    tablature_element_head=tablature_element_temp;
                else{
                    tablature_element_p=tablature_element_head;
                    while(tablature_element_p->next_tablature_element!=NULL)
                        tablature_element_p=tablature_element_p->next_tablature_element;
                    tablature_element_p=tablature_element_temp;
                }
            }  
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"barre")){
                barre_temp=(struct barre*)malloc(sizeof(struct barre));
                barre_temp=calloc(1,sizeof(struct barre));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"start_string_position")){
                        barre_temp->start_string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"end_string_position")){
                        barre_temp->end_string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"fret_position")){
                        barre_temp->fret_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                barre_temp->next_barre=NULL;
                if(barre_head==NULL)
                    barre_head=barre_temp;
                else{
                    barre_p=barre_head;
                    while(barre_p->next_barre!=NULL)
                        barre_p=barre_p->next_barre;
                    barre_p=barre_temp;
                }
            }   
        }
        value.tablature_hsymbol.tablature_elements=tablature_element_head;
        value.tablature_hsymbol.barres=barre_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"repeat")){
        struct jump_to* jump_to_temp=NULL;
        struct jump_to* jump_to_head=NULL;
        struct jump_to* jump_to_p=NULL;
        
        struct end* end_temp=NULL;
        struct end* end_head=NULL;
        struct end* end_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.repeat.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.repeat.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"repeat_text")){
                value.repeat.repeat_text=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
            }  
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"jump_to")){
                jump_to_temp=(struct jump_to*)malloc(sizeof(struct jump_to));
                jump_to_temp=calloc(1,sizeof(struct jump_to));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        jump_to_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"event_ref")){
                        jump_to_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                jump_to_temp->next_jump_to=NULL;
                if(jump_to_head==NULL)
                    jump_to_head=jump_to_temp;
                else{
                    jump_to_p=jump_to_head;
                    while(jump_to_p->next_jump_to!=NULL)
                        jump_to_p=jump_to_p->next_jump_to;
                    jump_to_p=jump_to_temp;
                }
            } 
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"end")){
                end_temp=(struct end*)malloc(sizeof(struct end));
                end_temp=calloc(1,sizeof(struct end));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        end_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"event_ref")){
                        end_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                end_temp->next_end=NULL;
                if(end_head==NULL)
                    end_head=end_temp;
                else{
                    end_p=end_head;
                    while(end_p->next_end!=NULL)
                        end_p=end_p->next_end;
                    end_p=end_temp;
                }
            }   
        }
        value.repeat.jump_tos=jump_to_head;
        value.repeat.ends=end_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"segno")){
        value.segno.segno_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.segno.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.segno.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"coda")){
        value.coda.coda_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.coda.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.coda.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"fine")){
        value.fine.fine_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.fine.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.fine.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"multiple_endings")){
        struct multiple_ending* multiple_ending_temp=NULL;
        struct multiple_ending* multiple_ending_head=NULL;
        struct multiple_ending* multiple_ending_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.multiple_endings.id=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"multiple_ending")){
                multiple_ending_temp=(struct multiple_ending*)malloc(sizeof(struct multiple_ending));
                multiple_ending_temp=calloc(1,sizeof(struct multiple_ending));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        multiple_ending_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"number")){
                        multiple_ending_temp->number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"start_event_ref")){
                        multiple_ending_temp->start_event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"end_event_ref")){
                        multiple_ending_temp->end_event_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"return_to")){
                        multiple_ending_temp->return_to=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                multiple_ending_temp->next_multiple_ending=NULL;
                if(multiple_ending_head==NULL)
                    multiple_ending_head=multiple_ending_temp;
                else{
                    multiple_ending_p=multiple_ending_head;
                    while(multiple_ending_p->next_multiple_ending!=NULL)
                        multiple_ending_p=multiple_ending_p->next_multiple_ending;
                    multiple_ending_p=multiple_ending_temp;
                }
            }  
        }
        value.multiple_endings.multiple_ending=multiple_ending_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"custom_hsymbol")){
        //load svg
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.custom_hsymbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                value.custom_hsymbol.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                value.custom_hsymbol.end_event_ref=xmlGetProp(cur,attributes->name);
            }

            attributes=attributes->next;
        }
    }
    else
        fprintf(stderr,"Element is not an Horizontal Symbol\n");
    
    return value;
}

struct voice_item* loadVoiceItemValue(xmlNodePtr cur){   
    xmlAttr* attributes;
    struct voice_item* value=(struct voice_item*)malloc(sizeof(struct voice_item));
    value=calloc(1,sizeof(struct voice_item));
    value->next_voice_item=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
            value->staff_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"notation_style")){
            value->notation_style=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    return value;
}

struct measure* loadMeasureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct measure* value=(struct measure*)malloc(sizeof(struct measure));
    value=calloc(1,sizeof(struct measure));
    value->next_measure=NULL;
    
    struct voice* voice_temp=NULL;
    struct voice* voice_head=NULL;
    struct voice* voice_p=NULL;
    value->n_voices= 0;
    
    value->next_measure=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"number")){
            value->number=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"show_number")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->show_number= 1;
            else
                value->show_number= 0;
        }  
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"numbering_style")){
            value->numbering_style=xmlGetProp(cur,attributes->name);
        }     
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"voice")){
            voice_temp=(struct voice*)malloc(sizeof(struct voice));
            voice_temp=calloc(1,sizeof(struct voice));
            voice_temp=loadVoiceValue(temp_cur);
            voice_temp->next_voice=NULL;
            if(voice_head==NULL){
                voice_head=voice_temp;
            }
            else{
                voice_p=voice_head;
                while(voice_p->next_voice!=NULL)
                    voice_p=voice_p->next_voice;
                voice_p->next_voice=voice_temp;
            }
            value->n_voices++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"multiple_rest")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"number_of_measures")){
                    value->multiple_rest.number_of_measures=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    value->multiple_rest.event_ref=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }  
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"measure_repeat")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"number_of_measures")){
                    value->measure_repeat.number_of_measures=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    value->measure_repeat.event_ref=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
        }
        temp_cur=temp_cur->next;
    }
    value->voices=voice_head;
    
    return value;
}

struct clef* loadClefValue(xmlNodePtr cur){
    xmlAttr* attributes;
    struct clef* value=(struct clef*)malloc(sizeof(struct clef));
    value=calloc(1,sizeof(struct clef));
    value->next_clef=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
            value->shape=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_step")){
            value->staff_step=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"octave_num")){
            value->octave_num=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
            value->event_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    return value;
}

struct key_signature* loadKeySignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct key_signature* value=(struct key_signature*)malloc(sizeof(struct key_signature));
    value=calloc(1,sizeof(struct key_signature));
    value->next_key_signature=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
            value->event_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"sharp_num")||!xmlStrcmp(temp_cur->name,(const xmlChar*)"flat_num")){
            value->num_type=(xmlChar*)temp_cur->name;
            value->number=xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"number"));
        }
        temp_cur=temp_cur->next;
    }
    
    return value;
}

struct custom_key_signature* loadCustomKeySignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct custom_key_signature* value=(struct custom_key_signature*)malloc(sizeof(struct custom_key_signature));
    value=calloc(1,sizeof(struct custom_key_signature));
    value->next_custom_key_signature=NULL;
    
    struct key_accidental* key_accidental_temp=NULL;
    struct key_accidental* key_accidental_head=NULL;
    struct key_accidental* key_accidental_p=NULL;
    value->n_key_accidentals= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
            value->event_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"key_accidental")){
            key_accidental_temp=(struct key_accidental*)malloc(sizeof(struct key_accidental));
            key_accidental_temp=calloc(1,sizeof(struct key_accidental));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"step")){
                    key_accidental_temp->step=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"accidental")){
                    key_accidental_temp->accidental=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }          
            key_accidental_temp->next_key_accidental=NULL;
            if(key_accidental_head==NULL)
                key_accidental_head=key_accidental_temp;
            else{
                key_accidental_p=key_accidental_head;
                while(key_accidental_p->next_key_accidental!=NULL)
                    key_accidental_p=key_accidental_p->next_key_accidental;
                key_accidental_p->next_key_accidental=key_accidental_temp;
            }
            value->n_key_accidentals++;
        }
        temp_cur=temp_cur->next;
    }
    value->key_accidentals=key_accidental_head;
    
    return value;
}

struct time_signature* loadTimeSignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct time_signature* value=(struct time_signature*)malloc(sizeof(struct time_signature));
    value=calloc(1,sizeof(struct time_signature));
    value->next_time_signature=NULL;
    
    struct time_indication* time_indication_temp=NULL;
    struct time_indication* time_indication_head=NULL;
    struct time_indication* time_indication_p=NULL;
    value->n_time_indications= 0;
    value->visible= 1;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"visible")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->visible= 1;
            else
                value->visible= 0;
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
            value->event_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"time_indication")){
            time_indication_temp=(struct time_indication*)malloc(sizeof(struct time_indication));
            time_indication_temp=calloc(1,sizeof(struct time_indication));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"num")){
                    time_indication_temp->num=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"den")){
                    time_indication_temp->den=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"abbreviation")){
                    if(!xmlStrcmp(xmlGetProp(temp_cur,attributes->name),(const xmlChar*)"yes"))
                        time_indication_temp->abbreviation= 1;
                    else
                        time_indication_temp->abbreviation= 0;
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"vtu_amount")){
                    time_indication_temp->vtu_amount=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }          
            time_indication_temp->next_time_indication=NULL;
            if(time_indication_head==NULL)
                time_indication_head=time_indication_temp;
            else{
                time_indication_p=time_indication_head;
                while(time_indication_p->next_time_indication!=NULL)
                    time_indication_p=time_indication_p->next_time_indication;
                time_indication_p->next_time_indication=time_indication_temp;
            }
            value->n_time_indications++;
        }
        temp_cur=temp_cur->next;
    }
    value->time_indications=time_indication_head;
    
    return value;
}

struct barline* loadBarlineValue(xmlNodePtr cur){
    xmlAttr* attributes;
    struct barline* value=(struct barline*)malloc(sizeof(struct barline));
    value=calloc(1,sizeof(struct barline));
    value->next_barline=NULL;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
            value->style=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension")){
            value->extension=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
           value->event_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
  
    return value;
}

struct tablature_tuning* loadTablatureTuningValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct tablature_tuning* value=(struct tablature_tuning*)malloc(sizeof(struct tablature_tuning));
    value=calloc(1,sizeof(struct tablature_tuning));
    value->next_tablature_tuning=NULL;
    
    struct string* string_temp=NULL;
    struct string* string_head=NULL;
    struct string* string_p=NULL;
    value->n_strings= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
            value->type=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"string")){
            string_temp=(struct string*)malloc(sizeof(struct string));
            string_temp=calloc(1,sizeof(struct string));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_number")){
                    string_temp->string_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_pitch")){
                    string_temp->string_pitch=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_accidental")){
                    string_temp->string_accidental=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_octave")){
                    string_temp->string_octave=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }
            string_temp->next_string=NULL;
            if(string_head==NULL){
                string_head=string_temp;
            }
            else{
                string_p=string_head;
                while(string_p->next_string!=NULL)
                    string_p=string_p->next_string;
                string_p->next_string=string_temp;
            }
            value->n_strings++;
        }
        temp_cur=temp_cur->next;
    }
    value->strings=string_head;

    return value;
}

struct voice* loadVoiceValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct voice* value=(struct voice*)malloc(sizeof(struct voice));
    value=calloc(1,sizeof(struct voice));   
    value->next_voice=NULL;
    
    struct chord* chord_temp=NULL;
    struct chord* chord_head=NULL;
    struct chord* chord_p=NULL;
    value->n_chords= 0;
    
    struct rest* rest_temp=NULL;
    struct rest* rest_head=NULL;
    struct rest* rest_p=NULL;
    value->n_rests= 0;
    
    struct tablature_symbol* tablature_symbol_temp=NULL;
    struct tablature_symbol* tablature_symbol_head=NULL;
    struct tablature_symbol* tablature_symbol_p=NULL;
    value->n_tablature_symbols= 0;
    
    struct gregorian_symbol* gregorian_symbol_temp=NULL;
    struct gregorian_symbol* gregorian_symbol_head=NULL;
    struct gregorian_symbol* gregorian_symbol_p=NULL;
    value->n_gregorian_symbols= 0;
    
    value->next_voice=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"voice_item_ref")){
            value->voice_item_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"ossia")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->ossia= 1;
            else
                value->ossia= 0;
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"chord")){
            chord_temp=(struct chord*)malloc(sizeof(struct chord));
            chord_temp=calloc(1,sizeof(struct chord));
            chord_temp=loadChordValue(temp_cur);
            chord_temp->next_chord=NULL;
            if(chord_head==NULL){
                chord_head=chord_temp;
            }
            else{
                chord_p=chord_head;
                while(chord_p->next_chord!=NULL)
                    chord_p=chord_p->next_chord;
                chord_p->next_chord=chord_temp;
            }
            value->n_chords++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"rest")){
            rest_temp=(struct rest*)malloc(sizeof(struct rest));
            rest_temp=calloc(1,sizeof(struct rest));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    rest_temp->id=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    rest_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                    rest_temp->staff_ref=xmlGetProp(temp_cur,attributes->name);

                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hidden")){
                    if(!xmlStrcmp(xmlGetProp(temp_cur,attributes->name),(const xmlChar*)"yes"))
                        rest_temp->hidden= 1;
                    else
                        rest_temp->hidden= 0;
                }
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"duration")){
                           rest_temp->duration=loadDurationValue(temp_cur);
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"augmentation_dots")){
                           rest_temp->augmentation_dots=(struct augmentation_dots){1};
                           if(xmlGetProp(temp_cur,(const xmlChar*)"number")!=NULL)
                            rest_temp->augmentation_dots=(struct augmentation_dots){ xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"augmentation_dots"))};
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            rest_temp->next_rest=NULL;
            if(rest_head==NULL){
                rest_head=rest_temp;
            }
            else{
                rest_p=rest_head;
                while(rest_p->next_rest!=NULL)
                    rest_p=rest_p->next_rest;
                rest_p->next_rest=rest_temp;
            }
            value->n_rests++;

        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_symbol")){
            tablature_symbol_temp=(struct tablature_symbol*)malloc(sizeof(struct tablature_symbol));
            tablature_symbol_temp=calloc(1,sizeof(struct tablature_symbol));
            
            struct key* key_temp=NULL;
            struct key* key_head=NULL;
            struct key* key_p=NULL;
            tablature_symbol_temp->n_keys= 0;
            
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    tablature_symbol_temp->id=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    tablature_symbol_temp->event_ref=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"stem_direction")){
                    tablature_symbol_temp->stem_direction=xmlGetProp(temp_cur,attributes->name);

                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_before")){
                    if(!xmlStrcmp(xmlGetProp(temp_cur,attributes->name),(const xmlChar*)"yes"))
                                    tablature_symbol_temp->beam_before= 1;
                    else
                        tablature_symbol_temp->beam_before= 0;
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_after")){
                    if(!xmlStrcmp(xmlGetProp(temp_cur,attributes->name),(const xmlChar*)"yes"))
                                    tablature_symbol_temp->beam_after=1;
                    else
                        tablature_symbol_temp->beam_after= 0;
                }
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"duration")){
                           tablature_symbol_temp->duration=loadDurationValue(temp_cur);
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"augmentation_dots")){
                           tablature_symbol_temp->augmentation_dots=(struct augmentation_dots){1};
                           if(xmlGetProp(temp_cur,(const xmlChar*)"number")!=NULL)
                            tablature_symbol_temp->augmentation_dots=(struct augmentation_dots){ xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"augmentation_dots"))};
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"key")){
                            key_temp=loadKeyValue(temp_cur);
                            key_temp->next_key=NULL;
                            if(key_head==NULL){
                                key_head=key_temp;
                            }
                            else{
                                key_p=key_head;
                                while(key_p->next_key!=NULL)
                                    key_p=key_p->next_key;
                                key_p->next_key=key_temp;
                            }
                            tablature_symbol_temp->n_keys++;
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            tablature_symbol_temp->keys=key_head;
            tablature_symbol_temp->next_tablature_symbol=NULL;
            if(tablature_symbol_head==NULL){
                tablature_symbol_head=tablature_symbol_temp;
            }
            else{
                tablature_symbol_p=tablature_symbol_head;
                while(tablature_symbol_p->next_tablature_symbol!=NULL)
                    tablature_symbol_p=tablature_symbol_p->next_tablature_symbol;
                tablature_symbol_p->next_tablature_symbol=tablature_symbol_temp;
            }
            value->n_tablature_symbols++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"gregorian_symbol")){
            gregorian_symbol_temp=(struct gregorian_symbol*)malloc(sizeof(struct gregorian_symbol));
            gregorian_symbol_temp=calloc(1,sizeof(struct gregorian_symbol));
            
            struct notehead* notehead_temp=NULL;
            struct notehead* notehead_head=NULL;
            struct notehead* notehead_p=NULL;
            gregorian_symbol_temp->n_noteheads= 0;
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(cur->name,(const xmlChar*)"id")){
                    gregorian_symbol_temp->id=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"neume")){
                    gregorian_symbol_temp->neume=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"inflexion")){
                    gregorian_symbol_temp->inflexion=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"subpunctis")){
                    gregorian_symbol_temp->subpunctis=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"interpretative_mark")){
                    gregorian_symbol_temp->interpretative_mark=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"mora")){
                    if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                        gregorian_symbol_temp->mora= 1;
                    else
                        gregorian_symbol_temp->mora= 0;
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"event_ref")){
                    gregorian_symbol_temp->event_ref=xmlGetProp(cur,attributes->name);
                }           
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead")){
                            notehead_temp=loadNoteheadValue(temp_cur);
                            notehead_temp->next_notehead=NULL;
                            if(notehead_head==NULL){
                                notehead_head=notehead_temp;
                            }
                            else{
                                notehead_p=notehead_head;
                                while(notehead_p->next_notehead!=NULL)
                                    notehead_p=notehead_p->next_notehead;
                                notehead_p->next_notehead=notehead_temp;
                            }
                            gregorian_symbol_temp->n_noteheads++;
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            gregorian_symbol_temp->notehead=notehead_head;
            gregorian_symbol_temp->next_gregorian_symbol=NULL;
            if(gregorian_symbol_head==NULL){
                gregorian_symbol_head=gregorian_symbol_temp;
            }
            else{
                gregorian_symbol_p=gregorian_symbol_head;
                while(gregorian_symbol_p->next_gregorian_symbol!=NULL)
                    gregorian_symbol_p=gregorian_symbol_p->next_gregorian_symbol;
                gregorian_symbol_p->next_gregorian_symbol=gregorian_symbol_temp;
            }
            value->n_gregorian_symbols++;
        }
        temp_cur=temp_cur->next;
    }
    value->chords=chord_head;
    value->rests=rest_head;
    value->tablature_symbols=tablature_symbol_head;
    value->gregorian_symbols=gregorian_symbol_head;
    
    return value;
}

struct chord* loadChordValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct chord* value=(struct chord*)malloc(sizeof(struct chord));
    value=calloc(1,sizeof(struct chord));
    value->next_chord=NULL;
    value->repetition= 0;
    
    struct notehead* notehead_temp=NULL;
    struct notehead* notehead_head=NULL;
    struct notehead* notehead_p=NULL;
    value->n_noteheads= 0;
    
    struct articulation* articulation_temp=NULL;
    struct articulation* articulation_head=NULL;
    struct articulation* articulation_p=NULL;
    value->n_articulations= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
            value->event_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"stem_direction")){
            value->stem_direction=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_before")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->beam_before= 1;
            else
                value->beam_before= 0;
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_after")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->beam_after= 1;
            else
                value->beam_after= 0;
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"cue")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"yes"))
                value->cue= 1;
            else
                value->cue= 0;
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"tremolo_lines")){
            if(!xmlStrcmp(xmlGetProp(cur,attributes->name),(const xmlChar*)"no"))
                value->tremolo_lines= 0;
            else
                value->tremolo_lines=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"duration")){
            value->duration=loadDurationValue(temp_cur);
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"augmentation_dots")){
            value->augmentation_dots=(struct augmentation_dots){1};
            if(xmlGetProp(temp_cur,(const xmlChar*)"number")!=NULL)
             value->augmentation_dots=(struct augmentation_dots){ xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"augmentation_dots"))};
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead")){
            notehead_temp=loadNoteheadValue(temp_cur);
            notehead_temp->next_notehead=NULL;
            if(notehead_head==NULL){
                notehead_head=notehead_temp;
            }
            else{
                notehead_p=notehead_head;
                while(notehead_p->next_notehead!=NULL)
                    notehead_p=notehead_p->next_notehead;
                notehead_p->next_notehead=notehead_temp;
            }
            value->n_noteheads++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"repetition")){
            value->repetition= 1;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"articulation")){
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(xmlStrcmp(temp_cur->name,(const xmlChar*)"text")&&xmlStrcmp(temp_cur->name,(const xmlChar*)"comment")){
                            articulation_temp=loadArticulationValue(temp_cur);
                            articulation_temp->next_articulation=NULL;
                            if(articulation_head==NULL){
                                articulation_head=articulation_temp;
                            }
                            else{
                                articulation_p=articulation_head;
                                while(articulation_p->next_articulation!=NULL)
                                    articulation_p=articulation_p->next_articulation;
                                articulation_p->next_articulation=articulation_temp;
                            }
                            value->n_articulations++; 
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
        }
        temp_cur=temp_cur->next;
    }
    value->noteheads=notehead_head;
    value->articulations=articulation_head;
    
    return value;  
}

struct notehead* loadNoteheadValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct notehead* value=(struct notehead*)malloc(sizeof(struct notehead));
    value=calloc(1,sizeof(struct notehead));
    value->next_notehead=NULL;
    value->tie= 0;
    
    struct printed_accidental* printed_accidental_temp=NULL;
    struct printed_accidental* printed_accidental_head=NULL;
    struct printed_accidental* printed_accidental_p=NULL;
    value->n_printed_accidentals= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
            value->staff_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"style")){
            value->style=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"pitch")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"step")){
                    value->pitch.step=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"octave")){
                    value->pitch.octave=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"actual_accidental")){
                    value->pitch.actual_accidental=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"printed_accidentals")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                    value->printed_accidentals_shape=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
            //printed_accidental children is REQUIRED
            temp_cur=temp_cur->xmlChildrenNode;
            do{
                if(xmlStrcmp(temp_cur->name,(const xmlChar*)"text")&&xmlStrcmp(temp_cur->name,(const xmlChar*)"comment")){
                    printed_accidental_temp=(struct printed_accidental*)malloc(sizeof(struct printed_accidental));
                    printed_accidental_temp=calloc(1,sizeof(struct printed_accidental));
                    printed_accidental_temp->printed_accidental_type=(xmlChar*)temp_cur->name;
                    if(!xmlStrcmp(xmlGetProp(temp_cur,(const xmlChar*)"parenthesis"),(const xmlChar*)"yes"))
                        printed_accidental_temp->parenthesis= 1;
                    else
                        printed_accidental_temp->parenthesis= 0;
                    printed_accidental_temp->next_printed_accidental=NULL;
                    
                    if(printed_accidental_head==NULL)
                        printed_accidental_head=printed_accidental_temp;
                    else{
                        printed_accidental_p=printed_accidental_head;
                        while(printed_accidental_p->next_printed_accidental!=NULL)
                            printed_accidental_p=printed_accidental_p->next_printed_accidental;
                        printed_accidental_p->next_printed_accidental=printed_accidental_temp;
                    }
                    value->n_printed_accidentals++;
                }
                temp_cur=temp_cur->next;
            }while(temp_cur->next!=NULL);
            temp_cur=temp_cur->parent;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tie")){
            value->tie= 1;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"fingering")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"number")){
                    value->fingering.number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }
        }      
        temp_cur=temp_cur->next;
    }
    value->printed_accidentals=printed_accidental_head;
    
    return value;    
}

struct duration loadDurationValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct duration* value=(struct duration*)malloc(sizeof(struct duration));
    value=calloc(1,sizeof(struct duration));
    
    struct tuplet_ratio* tuplet_ratio_temp=NULL;
    struct tuplet_ratio* tuplet_ratio_head=NULL;
    struct tuplet_ratio* tuplet_ratio_p=NULL;
    value->n_tuplet_ratios= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"num")){
            value->num=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"den")){
            value->den=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tuplet_ratio")){
            tuplet_ratio_temp=(struct tuplet_ratio*)malloc(sizeof(struct tuplet_ratio));
            tuplet_ratio_temp=calloc(1,sizeof(struct tuplet_ratio));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"enter_num")){
                    tuplet_ratio_temp->enter_num=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"enter_den")){
                    tuplet_ratio_temp->enter_den=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"enter_dots")){
                    tuplet_ratio_temp->enter_dots=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"in_num")){
                    tuplet_ratio_temp->in_num=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"in_den")){
                    tuplet_ratio_temp->in_den=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"in_dots")){
                    tuplet_ratio_temp->in_dots=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }
		
            //read tuplet_ratio innest

            tuplet_ratio_temp->next_tuplet_ratio=NULL;
            if(tuplet_ratio_head==NULL){
                tuplet_ratio_head=tuplet_ratio_temp;
            }
            else{
                tuplet_ratio_p=tuplet_ratio_head;
                while(tuplet_ratio_p->next_tuplet_ratio!=NULL)
                    tuplet_ratio_p=tuplet_ratio_p->next_tuplet_ratio;
                tuplet_ratio_p->next_tuplet_ratio=tuplet_ratio_temp;
            }
            value->n_tuplet_ratios++;
            temp_cur=temp_cur->xmlChildrenNode;
        }
        else{
            temp_cur=temp_cur->next;
        }
    }
    value->tuplet_ratio=tuplet_ratio_head;
    
    return *value;     
}

struct key* loadKeyValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct key* value=(struct key*)malloc(sizeof(struct key));
    value=calloc(1,sizeof(struct key));
    value->next_key=NULL;
    value->tie= 0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"ïd")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
            value->staff_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_pitch")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_number")){
                    value->tablature_pitch.string_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"key_number")){
                    value->tablature_pitch.key_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_articulation")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                    value->tablature_articulation.shape=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }        
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tie")){
            value->tie= 1;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_fingering")){
            attributes=temp_cur->properties;
            value->tablature_fingering.tablature_fingering_value=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                    value->tablature_fingering.shape=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }          
        }
        temp_cur=temp_cur->next;
    }
    
    
    return value;  
}

struct articulation* loadArticulationValue(xmlNodePtr cur){
    struct articulation* value=(struct articulation*)malloc(sizeof(struct articulation));
    value=calloc(1,sizeof(struct articulation));
    value->next_articulation=NULL;  
    
    value->articulation_sign=(xmlChar*)cur->name;
    //if custom_articulation > child contains svg
    
    return value;
}