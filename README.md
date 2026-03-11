# PARA-METER-V3.0-ESP
PARA-METER for ESP32

Code adapted from PARA-METER-V2.1
* V2.1 uses up to 3000 sound files placed in the directory "MP3" version
* V3.0 instead uses the directories "01" up to "99" in the main directory of an SD Card
  where 01 contains the words of the first category, 01 the words of the second etc.
* Each directory may contain up to 255 sound files named "001_xxxx.mp3" to "255_xxxx.mp3"
  where xxxx can be any text (preferably the word that is spoken in the mp3 file)

This allows to directly address 99 x 255 = 25245 files.

The unconnected yellow wire that goes from D34 to the center of the breadboard is uses as an "antenna" to gather random data.

<img width="464" height="351" alt="image" src="https://github.com/user-attachments/assets/093f2382-33a7-4a1c-9fc6-e7abc5752bdb" />

Known issue of the main program

The software will choose and replay the category names as the category names are placed as the first entry to each category string. 
They are not filtered from being chosen by the random word algorithm and the speech generation. 
Filtering the index 0 from each category would stop this behaviour. 
As it is not mandatory to put category names in front of the string you may do so or use the space for a different word.

