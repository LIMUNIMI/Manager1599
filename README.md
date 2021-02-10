# Manager1599
Una libreria C per il caricamento e la manipolazione di documenti IEEE 1599.

Per installare ed eseguire il codice sorgente, seguire le istruzioni contenute nel file _Tutorial Installazione Sorgente_.

Per compilare la libreria su Windows con Visual Studio, seguire le istruzioni contenute nel file _Tutorial Compilazione Libreria_.

Per utilizzare la libreria, seguire le istruzioni contenuto nel file _Tutorial Utilizzo Libreria_.

## Note
 
Se si riscontrano errori durante la lettura del DTD, provare a modificare la **riga 23** del DTD _ieee1599.dtd_ in uno di questi due modi:
 
- >`<!ENTITY % midixml SYSTEM "midixml.dtd" >` 
- >`<!ENTITY % midixml SYSTEM "MIDIEvents10.dtd" >`
