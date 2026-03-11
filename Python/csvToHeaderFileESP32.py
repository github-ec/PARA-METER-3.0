
import csv
import time

# Stand 2026/03/02 - ESP32 konforme Generierung
# ec2021

##############################
# Ggf. anzupassende Parameter
##############################
csv_input = "worte.csv"
csv_Delimiter = ";"
header_output = "WordLists.h"
##############################

def read_csv_columns_as_strings(file_path, delimiter=';'):
    """
    Liest eine CSV-Datei ein und fügt die Inhalte jeder Spalte 
    zu einem mit Schrägstrichen getrennten String zusammen.
    """
    column_data = []

    with open(file_path, mode='r', encoding='utf-8') as csv_file:
        # UTF-8-sig fängt evtl. vorhandene Byte Order Marks (BOM) ab
        reader = csv.reader(csv_file, delimiter=delimiter)
        
        for row_index, row in enumerate(reader):
            if row_index == 0:
                # Erste Zeile definiert die Anzahl der Spalten/Kategorien
                column_data = [cell.strip() for cell in row]
            else:
                for col_index, cell in enumerate(row):
                    if col_index < len(column_data) and cell.strip():
                        # Wort an den bestehenden String der Spalte hängen
                        column_data[col_index] += '/' + cell.strip()
                        
    return column_data

def write_arduino_header(column_strings, output_filename):
    """
    Schreibt die extrahierten Spalten-Strings in eine ESP32-optimierte Header-Datei.
    """
    tm = time.localtime()
    time_str = "{:04d}/{:02d}/{:02d} {:02d}:{:02d}:{:02d}".format(
        tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec
    )
    
    with open(output_filename, mode='w', encoding='utf-8') as f:
        f.write("#pragma once\n")
        f.write("#include <Arduino.h>\n\n")
        f.write(f"// Created {time_str}\n")
        
        # Tabellen-Übersicht im Kommentar
        f.write("// ------------------------------------------\n")
        f.write("// ID  | Category Name    | Words\n")
        f.write("// ----|------------------|----------\n")
        
        for i, content in enumerate(column_strings):
            word_count = content.count('/') + 1 if content else 0
            category_name = content.split('/')[0]
            f.write(f"// {i:>2}  | {category_name:<16} | {word_count:>6}\n")
            
        f.write("// ------------------------------------------\n\n")
        
        # 1. String-Definitionen (ESP32 nutzt static const für Flash-Mapping)
        for i, content in enumerate(column_strings):
            f.write(f'const char p{i}[] = "{content}";\n')
        
        f.write("\n")
        
        # 2. Das Pointer-Array (Table)
        pointer_names = [f"p{i}" for i in range(len(column_strings))]
        table_content = ", ".join(pointer_names)
        f.write(f"const char* const cat_table[] = {{{table_content}}};\n")
        
        # 3. Konstante für die Anzahl
        f.write("constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);\n")

if __name__ == "__main__":
    try:
        extracted_data = read_csv_columns_as_strings(csv_input, delimiter=csv_Delimiter)
        write_arduino_header(extracted_data, header_output)
        print(f"Erfolg: '{header_output}' wurde für ESP32 generiert.")
        print(f"Anzahl Kategorien: {len(extracted_data)}")
    except FileNotFoundError:
        print(f"Fehler: Die Datei '{csv_input}' wurde nicht gefunden.")
    except Exception as e:
        print(f"Ein unerwarteter Fehler ist aufgetreten: {e}")
