#Tutorial Compilazione Libreria C/C++ in Visual Studio 2019

Impostare il progetto di lavoro come descritto nel file _Tutorial Installazione Sorgente_. Fatto ciò, seguire la seguente procedura:

1. Nelle Proprietá di configurazone del progetto:
  - In `Proprietà di configurazione > Generale > Tipo di configurazione` scegliere _Libreria dinamica (.dll)_.
  - In `Proprietà di configurazione > Generale > Nome di destinazione` inserire _managerieee1599_.
  - In `C/C++ > Preprocessore > Definizioni preprocessore` aggiungere la parola chiave _MANAGERIEEE1599_EXPORTS_.
  - In `C/C++ > Avanzate > Compila come` scegliere _Compila come codice C (/TC)_.
2. Aggiungere all'inzio di **common.h** le seguenti istruzioni:
      ```
      #pragma once

      #ifdef MANAGERIEEE1599_EXPORTS
      #define MANAGERIEEE1599_API __declspec(dllexport)
      #else
      #define MANAGERIEEE1599_API __declspec(dllimport)
      #endif
      ```
      
3. Aggiungere la parola chiave _MANAGERIEEE1599_API_ alle dichiarazioni delle variabili e funzioni che si vogliono esportare nella libreria.

4. Compilare.

## Packing libreria

Solitamente, le librerie suddividono i loro file tra le cartelle _include_,_bin_ e _lib_.

1. Creare la cartella _managerieee1599_ che contiene le sottocartelle _include_, _libs_ e _bin_.
2. Spostare i file _.lib_ e _.dll_, creati in fase di compilazione, il primo nella cartella _lib_ e il secondo in _bin_.
3. Copiare e incollare tutti i file di intestazione nella cartella include.

## Utilizzare la libreria

Per importare e utilizzare la libreri in programmi esterni, sono necessari i file di intestazione, i file _.lib_ e i file  _.dll_.


Nelle Proprietá di configurazone del progetto:
1. In `C/C++ > Generale > Directory di inclusione aggiuntive` aggiungere il percorso alla cartella _include_ (compresa) delle librerie **libxml2**,**iconv** e "managerieee1599".
2. In `C/C++ > Riga di comando > Opzioni aggiuntive` inserie il comando _/wd4996_.
3. In `Linker > Generale > Directory librerie aggiuntive` aggiungere il percorso alla cartella _lib_ (compresa) delle librerie **libxml2** e **iconv** e "managerieee1599".
4. In `Linker > Input > Dipendenza aggiuntive` aggiungere _libxml2.lib_, _iconv.lib_ e "managerieee1599.lib".
5. Copiare e incollare i file _.dll_ dalle cartelle _bin_ delle librerie alla directory di lavoro del programma che le utilizza.

### Packing automatico della libreria in post-compilazione e copia del file .dll all'interno del programma che la utilizza

Per non dover copiare manualmente i file necessari al funzionamento della libreria ad ogni sua nuova compilazione:

1. Creare un file batch nella cartella del progetto in Visual Studio che compila il sorgente della libreria e chiamarlo "LibraryPacker.bat".
2. In `Proprietà di configurazione del progetto > Eventi di compilazione > Riga di comando ` inserire il comando `call "../Librarypacker.bat"`.
3. Modificare il contenuto del file batch inserendo queste istruzioni, dove $PATH_NEW_PROJECT è il percorso alla directory principale del progetto che importa la libreria:
        `
        echo Packing library files...

        mkdir "..\Library\managerieee1599\bin"

        mkdir "..\Library\managerieee1599\lib"

        mkdir "..\Library\managerieee1599\include"


        copy "..\Debug\*.dll" "..\Library\managerieee1599\bin"

        copy "..\Debug\*.lib" "..\Library\managerieee1599\lib"

        copy "*.h" "..\Library\managerieee1599\include"


        copy  "..\Library\managerieee1599\bin\*.dll" $PATH_NEW_PROJECT
        `
