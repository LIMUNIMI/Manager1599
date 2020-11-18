# Manager1599
Una libreria C per il caricamento e la manipolazione di documenti IEEE 1599

Istruzioni per l'installazione

1) Installare la libreria dirent per utilizzare le funzioni in fileChooser.h
2) Installare la libreria libxml2 (che richiede le librerie zib1 e iconv).
2) Posizionare la cartella File (che contiene la cartella DTD) nella root directory del progetto.
     È possibile rimuovere ed aggiungere i file xml. Non rimuovere i file DTD.
         
Note
 
Se si riscontrano errori durante la lettura del DTD, provare a modificare la riga 23 del DTD ieee1599.dtd in uno di questi due modi:
 
1) <!ENTITY % midixml SYSTEM "`midixml.dtd" > 
2) <!ENTITY % midixml SYSTEM "MIDIEvents10.dtd" >
