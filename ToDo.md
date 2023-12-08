# ToDo's

## Garbage Collecten
* Gesamtes Projekt von anfang bis ende durchgehen und alle nicht notwendigen/Überflüsigen Zeilen code löschen.

## Work Over
* Indexes vollständig aus der Datei bzw den Song Informationen entfernen.
* Wenn man einen Song Eintrag entfernt soll die dazugehörige Music File automatisch gelöscht werden.
* Funktion im Music Menü die alle Songs auflistet die eine Valide Music File haben.
* ~~Ausgabe Formatierung für den Namen der Music File überarbeiten.~~

## Songs Abspielen
* ~~Beim hinzufügen eines Songs die möglichkeit geben den Pfad zu einer dazugehörigen mp3 oder mp4 Datei anzugeben.~~
* ~~Einen Eigenen menüpunkt hinzufügen um Songs abzuspielen die eine mp3 oder mp4 datei hinterlegt haben.~~
* mp3 / mp4 sollen im Windows MediaPlayer bzw mit der Standard Anwendung für mp3 / mp4 Dateien abgespielt werden.
  * Es soll eine funktion geben die jene Songs auflistet, die auch eine mp3 / mp4 datei hinterlegt haben.
* ~~Man soll den Pfad (relativ oder absolut) zur mp3 / mp4 datei eingeben nachdem man ausgewählt hat ob es sich um eine mp3 oder mp4 datei handelt, diese datei soll anschließend (mit z.B. dem system() befehl) in einen~~ 
~~Vordefinierten ordner kopiert und umbenannt werden in dem sich alle mp3 / mp4 datein befinden~~ __~~(Evtl. Auch per Explorer Fenster datei auswählen lassen fals das in C Funktioniert).~~__
* Man soll einzelne mp3 / mp4 Dateien auch wieder löschen können sodass kein Song mehr zu diesen hinterlegt ist.

## ~~UserData Speicher~~
* ~~Bei jedem Ausführen eine "Userdata" Datei laden, in der der Pfad zur Song Liste und zum Music Ordner drinnen stehen.~~
* ~~Diese Pfade soll man dann in einem extra Menüpunkt ändern können. Sollte die erste Zeile leer sein, so soll zu Start gebeten werden, den Pfad zur SongList anzugeben bzw. diese per Explorer zu öffnen. Sollte die zweite Zeile leer sein, so soll zu Start gebeten werden, den Pfad zum Music Ordner anzugeben bzw. diesen im Explorer auszuwählen.~~
* ~~Evtl. Anzahl der in der Liste vorhandenen Songs in der dritten Zeile speichern. Falls diese leer sein sollte, wird die Funktion `setIndexCount` aufgerufen. Nach jedem Hinzufügen/Entfernen/jeder Informationsänderung soll der aktualisierte IndexCount sofort wieder in die Datei geschrieben werden.~~
