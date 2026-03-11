import pyttsx3, time, re, os

# EINSTELLUNG: 1 für männlich (Stefan), 0 für weiblich (Hedda)
VOICE_INDEX = 1 

##############################
WordListFile = r"WordListsESP.h"
baseMp3Path  = r'sdcard' 
##############################

engine = pyttsx3.init()
voices = engine.getProperty('voices')
if len(voices) > VOICE_INDEX:
    engine.setProperty('voice', voices[VOICE_INDEX].id)

def get_word_arrays_from_file(filepath):
    all_categories = []
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if line.startswith("const char p") and '"' in line:
                    match = re.search(r'"([^"]*)"', line)
                    if match:
                        content = match.group(1)
                        words = [w.strip() for w in content.split('/') if w.strip()]
                        if words:
                            all_categories.append(words)
        return all_categories
    except FileNotFoundError:
        print(f"Fehler: {filepath} nicht gefunden.")
        return []

wort_sammlung = get_word_arrays_from_file(WordListFile)

if not wort_sammlung:
    print("Keine Kategorien gefunden!")
else:
    if not os.path.exists(baseMp3Path):
        os.makedirs(baseMp3Path)

    start_zeit = time.time()

    for kat_idx, kategorie in enumerate(wort_sammlung, start=1):
        # NUR die Nummer als Verzeichnisname (01, 02, ...)
        sub_folder_name = f"{kat_idx:02d}"
        sub_folder_path = os.path.join(baseMp3Path, sub_folder_name)
        
        if not os.path.exists(sub_folder_path):
            os.makedirs(sub_folder_path)

        print(f"Verarbeite Verzeichnis {sub_folder_name}...")
        
        for word_idx, entry in enumerate(kategorie, start=1):
            # Bereinigung des Wortes für den Dateinamen
            clean_word = "".join([c for c in entry if c.isalnum() or c in (' ', '_')]).strip()
            # Dateiname: 001_xxxx.mp3
            file_name = f"{word_idx:03d}_{clean_word}.mp3"
            full_path = os.path.join(sub_folder_path, file_name)
            
            engine.save_to_file(entry, full_path)
            
    engine.runAndWait()
    print("\nFertig! Struktur wurde in '{}' erstellt.".format(baseMp3Path))

