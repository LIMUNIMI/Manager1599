/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools,Templates
 * and open the template in the editor.
 */

#include "managerLogic.h"

void loadLogic(){ 
    //inizializzare logic_layer
    
    loadSpine();
    loadLos();
    //loadLayout();
    
    printSpine();
    printLos();
    //printLayout();
}

void loadSpine(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct event *head=NULL;
    struct event *temp=NULL;
    struct event *p=NULL;
    
    logic_layer.n_events=0;
    
    xpath=(xmlChar *)"/ieee1599/logic/spine";
    result=getNodeset(doc,xpath);
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        fprintf(stderr,"Missing Spine in Logic layer\n");
    }
    else{
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur->next!=NULL){
            if(!xmlStrcmp(cur->name,(const xmlChar*)"event")){
                temp=(struct event*)malloc(sizeof(struct event));
                temp=calloc(1,sizeof(struct event));
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                        temp->id=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"timing")){
                        temp->timing=xmlGetProp(cur,attributes->name);

                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hpos")){
                        temp->hpos=xmlGetProp(cur,attributes->name);

                    }                   
                    attributes=attributes->next;                     
                }  
                temp->next_event=NULL;
                if(head==NULL){
                    head=temp;
                }
                else{
                    p=head;
                    while(p->next_event!=NULL)
                        p=p->next_event;
                    p->next_event=temp;
                }
                logic_layer.n_events++;
            }
            cur=cur->next;
        }
        logic_layer.spine=head;
    }   
}

void printSpine(){
    struct event* p=NULL;
    
    if(logic_layer.n_events!=0){
        printf("%i event\n",logic_layer.n_events);
    }   
    
    p=NULL;
    p=logic_layer.spine;
    while(p!=NULL){
       printf("Event: %s %s %s\n",p->id,p->timing,p->hpos);
       p=p->next_event;
    }
}

void loadLos(){
    xmlXPathObjectPtr result;
    xmlChar *xpath;
    int i,j;
    xmlNodePtr cur;
    xmlNodePtr cur_level2;
    xmlNodePtr cur_level3;
    xmlNodePtr cur_level4;
    xmlNodePtr cur_level5;
    xmlNodePtr curv_level6;
    xmlNodeSetPtr nodeset;
    xmlAttr *attributes;
    
    //logic contiene spine, los?, layout? 
    printf("=====Logic=====\n"); 
    
    xpath=(xmlChar *)"/ieee1599/logic/los";
    result=getNodeset(doc,xpath);
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        xmlXPathFreeObject(result);
        fprintf(stderr,"Missing Los level\n");
    }
    else{
        printf("[los]\n");
        nodeset=result->nodesetval;
        for(i=0;i<nodeset->nodeNr;i++){
            //los contiene staff_list,part+,horizontal_symbols?,ornaments?,lyrics*,metronomic_indication,text_field*,agogics*,commenti
            cur=nodeset->nodeTab[i];
            cur=cur->xmlChildrenNode;
            while(cur!=NULL){
                if(xmlStrcmp(cur->name,(const xmlChar*)"text")){  
                   if(!xmlStrcmp(cur->name,(const xmlChar*)"staff_list")){
                        attributes=cur->properties;
                        printf("    %s",cur->name);
                        if(attributes!=NULL){
                            printf("[");
                            int primo=1;
                            while(attributes!=NULL){
                                if(primo==0) printf("|");
                                else primo=0;
                                printf("%s:%s",attributes->name,xmlGetProp(cur,attributes->name));
                                attributes=attributes->next;
                            }
                            printf("]");
                        }
                        printf("\n");
                       //staff_list contiene (brackets | staff)+ 
                        cur_level2=cur->xmlChildrenNode; 
                       if(cur_level2==NULL){
                           fprintf(stderr,"Missing staff or brackets in staffl_list\n");
                       }
                       while(cur_level2!=NULL){
                        if(xmlStrcmp(cur_level2->name,(const xmlChar*)"text")){
                          //brackets ha marker(start_of_staff_group|end_of_staff_group), group_number,shape(square|rounded_square|brace|vertical_bar|none)
                          if(!xmlStrcmp(cur_level2->name,(const xmlChar*)"brackets")){
                            attributes=cur_level2->properties;
                            printf("    %s",cur_level2->name);
                                if(attributes!=NULL){
                                    printf("[");
                                    int primo=1;
                                    while(attributes!=NULL){
                                        if(primo==0) printf("|");
                                        else primo=0;
                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level2,attributes->name));
                                        attributes=attributes->next;
                                    }
                                    printf("]");
                                }
                            printf("\n");
                          }
                          //staff contiene (clef| (key_signature|custom_key_signature) | time_signature | barline | tablature_tuning))*
                          //staff ha id, line_number,ossia(yes|no),tablature(none|french|german|italian)
                          else if(!xmlStrcmp(cur_level2->name,(const xmlChar*)"staff")){
                            attributes=cur_level2->properties;
                            printf("    %s",cur_level2->name);
                                if(attributes!=NULL){
                                    printf("[");
                                    int primo=1;
                                    while(attributes!=NULL){
                                        if(primo==0) printf("|");
                                        else primo=0;
                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level2,attributes->name));
                                        attributes=attributes->next;
                                    }
                                    printf("]");
                                }
                            cur_level3=cur_level2->xmlChildrenNode;
                            if(cur_level3==NULL){
                                fprintf(stderr,"Empty staff element\n");
                            }
                            else{
                                while(cur_level3!=NULL){
                                    if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"clef")){
                                        //clef ha shape,staff_step,ocatve_num
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        printf("}");
                                    }
                                    else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"key_signature")){
                                       //key_signature contiene sharp_num o flat_num
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        cur_level4=cur_level3->xmlChildrenNode;
                                        if(cur_level4==NULL){
                                            fprintf(stderr,"Empty key_signature element\n");
                                        }
                                        else{
                                            while(cur_level4!=NULL){
                                                if(xmlStrcmp(cur_level4->name,(const xmlChar*)"text")){
                                                    attributes=cur_level4->properties;
                                                    printf("[");
                                                    printf("%s=",cur_level4->name);
                                                    int primo=1;
                                                    while(attributes!=NULL){
                                                        if(primo==0) printf("|");
                                                        else primo=0;
                                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                        attributes=attributes->next;
                                                    }
                                                    printf("]");
                                                }
                                                cur_level4=cur_level4->next;
                                            }
                                        }
                                        printf("}");
                                    }
                                    else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"custom_key_signature")){
                                       //custom_key_signature contiene key_accidental+ 
                                        //key_accidental
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        cur_level4=cur_level3->xmlChildrenNode;
                                        if(cur_level4==NULL){
                                            fprintf(stderr,"Empty custom_key_signature element\n");
                                        }
                                        else{
                                            while(cur_level4!=NULL){
                                                if(xmlStrcmp(cur_level4->name,(const xmlChar*)"text")){
                                                    attributes=cur_level4->properties;
                                                    printf("[");
                                                    printf("%s=",cur_level4->name);
                                                    int primo=1;
                                                    while(attributes!=NULL){
                                                        if(primo==0) printf("|");
                                                        else primo=0;
                                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                        attributes=attributes->next;
                                                    }
                                                    printf("]");
                                                }
                                                cur_level4=cur_level4->next;
                                            }
                                        }
                                        printf("}");
                                    }
                                    else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"time_signature")){
                                       //time_signature contiene time_indication+ e ha visible 
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        cur_level4=cur_level3->xmlChildrenNode;
                                        if(cur_level4==NULL){
                                            fprintf(stderr,"Empty time_signature element\n");
                                        }
                                        else{
                                            while(cur_level4!=NULL){
                                                if(xmlStrcmp(cur_level4->name,(const xmlChar*)"text")){
                                                    attributes=cur_level4->properties;
                                                    printf("[");
                                                    printf("%s=",cur_level4->name);
                                                    int primo=1;
                                                    while(attributes!=NULL){
                                                        if(primo==0) printf("|");
                                                        else primo=0;
                                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                        attributes=attributes->next;
                                                    }
                                                    printf("]");
                                                }
                                                cur_level4=cur_level4->next;
                                            }
                                        }
                                        printf("}");
                                    }
                                    else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"barline")){
                                      //barline ha style,extension  
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        printf("}");
                                    }
                                    else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"tablature_tuning")){
                                      //tablature_tuning contiene string* e ha type  
                                        //string ha string_number, string_pitch,string_accidental, string_octave
                                        attributes=cur_level3->properties;
                                        printf("{");
                                        printf("%s= ",cur_level3->name);
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        cur_level4=cur_level3->xmlChildrenNode;
                                        while(cur_level4!=NULL){
                                            if(xmlStrcmp(cur_level4->name,(const xmlChar*)"text")){
                                                attributes=cur_level4->properties;
                                                printf("[");
                                                printf("%s=",cur_level4->name);
                                                int primo=1;
                                                while(attributes!=NULL){
                                                    if(primo==0) printf("|");
                                                    else primo=0;
                                                    printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                    attributes=attributes->next;
                                                }
                                                printf("]");
                                            }
                                            cur_level4=cur_level4->next;
                                        }
                                        printf("}");
                                    }
                                    cur_level3=cur_level3->next;
                                }
                            } 
                            printf("\n");
                          }
                        }   
                        cur_level2=cur_level2->next;
                       }                                             
                    }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"part")){
                        attributes=cur->properties;
                        printf("    %s",cur->name);
                        if(attributes!=NULL){
                            printf("[");
                            int primo=1;
                            while(attributes!=NULL){
                                if(primo==0) printf("|");
                                else primo=0;
                                printf("%s:%s",attributes->name,xmlGetProp(cur,attributes->name));
                                attributes=attributes->next;
                            }
                            printf("]");
                        }
                       //part contiene voice_list, measure+
                        cur_level2=cur->xmlChildrenNode;
                        if(cur_level2==NULL){
                            fprintf(stderr,"Empty part\n");
                            printf("\n");
                        }
                        while(cur_level2!=NULL){
                            if(xmlStrcmp(cur_level2->name,(const xmlChar*)"text")){
                                if(!xmlStrcmp(cur_level2->name,(const xmlChar*)"voice_list")){
                                    //voice_list contiene voice_item+
                                    cur_level3=cur_level2->xmlChildrenNode;
                                    if(cur_level3==NULL){
                                        fprintf(stderr,"Empty voice_list\n");
                                    }
                                    while(cur_level3!=NULL){
                                        if(xmlStrcmp(cur_level3->name,(const xmlChar*)"text")){
                                            attributes=cur_level3->properties;
                                            printf("{");
                                            printf("%s=",cur_level3->name);
                                            int primo=1;
                                            while(attributes!=NULL){
                                                if(primo==0) printf("|");
                                                else primo=0;
                                                printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                                attributes=attributes->next;
                                            }
                                            printf("}");
                                        }
                                        cur_level3=cur_level3->next;
                                    }
                                    printf("\n");
                                }
                                else if(!xmlStrcmp(cur_level2->name,(const xmlChar*)"measure")){
                                    //measure contiene voice+|multiple_rest|measure_repeat?
                                    attributes=cur_level2->properties;
                                    printf("        %s",cur_level2->name);
                                    if(attributes!=NULL){
                                        printf("[");
                                        int primo=1;
                                        while(attributes!=NULL){
                                            if(primo==0) printf("|");
                                            else primo=0;
                                            printf("%s:%s",attributes->name,xmlGetProp(cur_level2,attributes->name));
                                            attributes=attributes->next;
                                        }
                                        printf("]");
                                    }
                                    cur_level3=cur_level2->xmlChildrenNode;
                                    if(cur_level3==NULL){
                                        fprintf(stderr,"Empty measure\n");
                                    }
                                    while(cur_level3!=NULL){
                                        if(xmlStrcmp(cur_level3->name,(const xmlChar*)"text")){
                                            if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"voice")){
                                                attributes=cur_level3->properties;
                                                printf("{");
                                                printf("%s= ",cur_level3->name);
                                                int primo=1;
                                                while(attributes!=NULL){
                                                    if(primo==0) printf("|");
                                                    else primo=0;
                                                    printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                                    attributes=attributes->next;
                                                }
                                                printf("}");
                                                //voice contiene (chord|rest|tablature_symbol|gregorian_symbol)+
                                                cur_level4=cur_level3->xmlChildrenNode;
                                                if(cur_level4==NULL){
                                                    fprintf(stderr,"Empty voice\n");
                                                }
                                                while(cur_level4!=NULL){
                                                    if(xmlStrcmp(cur_level4->name,(const xmlChar*)"text")){
                                                        if(!xmlStrcmp(cur_level4->name,(const xmlChar*)"chord")){
                                                            //chord contiene duration,augmentation_dots?,(nothead+|repetition),articulation?
                                                            attributes=cur_level4->properties;
                                                            printf("{");
                                                            printf("%s= ",cur_level4->name);
                                                            int primo=1;
                                                            while(attributes!=NULL){
                                                                if(primo==0) printf("|");
                                                                else primo=0;
                                                                printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                                attributes=attributes->next;
                                                            }
                                                            cur_level5=cur_level4->xmlChildrenNode;
                                                            if(cur_level5==NULL){
                                                                fprintf(stderr,"Empty chord\n");
                                                            }
                                                            while(cur_level5!=NULL){
                                                                if(xmlStrcmp(cur_level5->name,(const xmlChar*)"text")){
                                                                    attributes=cur_level5->properties;
                                                                    printf("[");
                                                                    printf("%s= ",cur_level5->name);
                                                                    int primo=1;
                                                                    while(attributes!=NULL){
                                                                        if(primo==0) printf("|");
                                                                        else primo=0;
                                                                        printf("%s:%s",attributes->name,xmlGetProp(cur_level5,attributes->name));
                                                                        attributes=attributes->next;
                                                                    }
                                                                    printf("]");                                                                   
                                                                }
                                                                cur_level5=cur_level5->next;
                                                            }
                                                            printf("}");    
                                                            //nothead contiene pitch,printed_accidentals?,tie?,fingering?
                                                                    //printed_accidentals (vari tipi di durate)+
                                                            //duration contiene tuplet_ratio?
                                                                 //tuplet_ratio contiene tuplet_ratio* 
                                                        }
                                                        else if(!xmlStrcmp(cur_level4->name,(const xmlChar*)"rest")){
                                                            //rest contiene duration,augmentation_dots? 
                                                            attributes=cur_level4->properties;
                                                            printf("{");
                                                            printf("%s= ",cur_level4->name);
                                                            int primo=1;
                                                            while(attributes!=NULL){
                                                                if(primo==0) printf("|");
                                                                else primo=0;
                                                                printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                                attributes=attributes->next;
                                                            }
                                                            printf("}");
                                                        }
                                                        else if(!xmlStrcmp(cur_level4->name,(const xmlChar*)"tablature_symbol")){
                                                           //tablature_symbol contiene duration, agumentation_dots?,key+
                                                            attributes=cur_level4->properties;
                                                            printf("{");
                                                            printf("%s= ",cur_level4->name);
                                                            int primo=1;
                                                            while(attributes!=NULL){
                                                                if(primo==0) printf("|");
                                                                else primo=0;
                                                                printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                                attributes=attributes->next;
                                                            }
                                                            printf("}");
                                                                //key contiene tablature_pitch,tablature_articulation?,tie?,tablature_fingering? 
                                                        }
                                                        else if(!xmlStrcmp(cur_level4->name,(const xmlChar*)"gregorian_symbol")){
                                                            //gregorian_symbol contiene nothead+
                                                            attributes=cur_level4->properties;
                                                            printf("{");
                                                            printf("%s= ",cur_level4->name);
                                                            int primo=1;
                                                            while(attributes!=NULL){
                                                                if(primo==0) printf("|");
                                                                else primo=0;
                                                                printf("%s:%s",attributes->name,xmlGetProp(cur_level4,attributes->name));
                                                                attributes=attributes->next;
                                                            }
                                                            printf("}");
                                                                //nothead contiene pitch,printed_accidentals?,tie?,fingering?
                                                                    //printed_accidentals (vari tipi di durate)+
                                                        }
                                                    }
                                                    cur_level4=cur_level4->next;
                                                }         
                                            }
                                            else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"multiple_rest")){
                                                attributes=cur_level3->properties;
                                                printf("{");
                                                printf("%s= ",cur_level3->name);
                                                int primo=1;
                                                while(attributes!=NULL){
                                                    if(primo==0) printf("|");
                                                    else primo=0;
                                                    printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                                    attributes=attributes->next;
                                                }
                                                printf("}");
                                            }
                                            else if(!xmlStrcmp(cur_level3->name,(const xmlChar*)"measure_repeat")){
                                                attributes=cur_level3->properties;
                                                printf("{");
                                                printf("%s= ",cur_level3->name);
                                                int primo=1;
                                                while(attributes!=NULL){
                                                    if(primo==0) printf("|");
                                                    else primo=0;
                                                    printf("%s:%s",attributes->name,xmlGetProp(cur_level3,attributes->name));
                                                    attributes=attributes->next;
                                                }
                                                printf("}");
                                            }
                                        }
                                        cur_level3=cur_level3->next;
                                    } 
                                    printf("\n");//a capo misura
                                }
                            }
                            cur_level2=cur_level2->next;
                        }
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"horizontal_symbols")){
                       //horizontal_symbol contiene (tipi di simbolo) alcuni tipi di simbolo hanno testo,538 544 596 607 hanno elementi
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"ornaments")){
                       //ornaments contiene (tipi di ornamento)* 
                       //615,62 hanno elementi
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"lyrics")){
                       //lyrics contiene syllable+
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"metronomic_indication")){
                       //metronomic_indication ha num,den,dots,value
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"text_field")){
                       //text_field ha extension_line_to, extension_line_shape(normal|dotted|dasheds
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"agogics")){
                       //agogics ha bracketed(no|yes) 
                   }
                   else if(!xmlStrcmp(cur->name,(const xmlChar*)"comment"))
                        printf("    comment: %s\n",cur->content); 

                }
                cur=cur->next;
            }
        }
    }
}

void printLos(){

}