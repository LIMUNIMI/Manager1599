# Manager1599
Una libreria C per il caricamento e la manipolazione di documenti IEEE 1599

## Note
 
Se si riscontrano errori durante la lettura del DTD, provare a modificare la **riga 23** del DTD * *ieee1599.dtd* * in uno di questi due modi:
 
- >`<!ENTITY % midixml SYSTEM "midixml.dtd" >` 
- >`<!ENTITY % midixml SYSTEM "MIDIEvents10.dtd" >`
