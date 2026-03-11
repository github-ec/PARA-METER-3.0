#pragma once
#include <Arduino.h>

// Created 2026/03/02 19:22:07
// ------------------------------------------
// ID  | Category Name    | Words
// ----|------------------|----------
//  0  | PRONOMEN         |     33
//  1  | ORTE             |     26
//  2  | HAUS             |     51
//  3  | VERBEN           |     51
//  4  | ADJEKTIVE        |     61
//  5  | NAMEN            |     42
//  6  | ZEIT             |     40
//  7  | GEGENSTÄNDE      |     41
//  8  | TODESURSACHEN    |     36
// ------------------------------------------

const char p0[] = "PRONOMEN/Ich/Du/Er/Sie/Es/Wir/Ihr/Sie/Mein/Dein/Sein/Ihr/Unser/Jemand/Niemand/Alle/Einer/Jeder/Wer/Was/Mann/Frau/Kind/Mädchen/Junge/Mutter/Vater/Bruder/Schwester/Fremder/Gast/Feind";
const char p1[] = "ORTE/Hier/Dort/Oben/Unten/Links/Rechts/Vorne/Hinten/Nah/Fern/Draußen/Drinnen/Dazwischen/Hinter/Unter/Neben/Gegenüber/Überall/Nirgendwo/Mitte/Ecke/Weg/Zurück/Tief/Hoch";
const char p2[] = "HAUS/Keller/Dachboden/Flur/Zimmer/Küche/Bad/Schlafzimmer/Treppe/Schrank/Spiegel/Fenster/Tür/Wand/Boden/Garten/Wald/Grab/Friedhof/Kirche/Kapelle/Turm/Ruine/Brunnen/Halle/Kammer/Verlies/Scheune/Zaun/Tor/Gasse/Schwelle/Fundament/Kamin/Balkon/Lager/Stall/Schmiede/Altar/Sarg/Gruft/Mausoleum/Krypta/Labor/Klinik/Asyl/Spital/Schule/Gefängnis/Brücke/Teich";
const char p3[] = "VERBEN/Gehen/Laufen/Verstecken/Suchen/Finden/Hören/Sehen/Fühlen/Sprechen/Rufen/Schreien/Flüstern/Warten/Töten/Sterben/Helfen/Retten/Bluten/Kratzen/Klopfen/Öffnen/Schließen/Brennen/Frieren/Zittern/Atmen/Beobachten/Folgen/Verschwinden/Erscheinen/Berühren/Warnen/Hassen/Leiden/Beten/Opfern/Graben/Schlagen/Werfen/Bewegen/Ziehen/Drücken/Kommen/Bleiben/Fliehen/Schützen/Wachen/Heilen/Zerstören/Erinnern";
const char p4[] = "ADJEKTIVE/Kalt/Heiß/Dunkel/Hell/Alt/Böse/Gut/Einsam/Verlassen/Traurig/Wütend/Hungrig/Krank/Tot/Lebendig/Schwach/Stark/Still/Laut/Grausam/Verborgen/Rein/Unrein/Blass/Schwer/Leicht/Scharf/Bitter/Faulig/Eisig/Düster/Verloren/Ewig/Heilig/Verflucht/Besessen/Sichtbar/Unsichtbar/Grauenhaft/Schrecklich/Wachsam/Stumm/Blind/Taub/Nass/Trocken/Altmodisch/Modern/Kaputt/Ganz/Sicher/Gefährlich/Düster/Modrig/Neblig/Blutig/Eiternd/Klebrig/Sanft/Wild";
const char p5[] = "NAMEN/Adolf/Albert/Andreas/Anna/August/Berta/Carl/Christian/Dorothea/Elisabeth/Emil/Emma/Friedrich/Georg/Gertrud/Hans/Heinrich/Helene/Hermann/Ida/Jakob/Johann/Johanna/Joseph/Karl/Katharina/Ludwig/Margarethe/Maria/Martha/Otto/Paul/Peter/Richard/Rosa/Rudolf/Sophie/Thomas/Ursula/Walter/Wilhelm";
const char p6[] = "ZEIT/Sekunde/Minute/Stunde/Tag/Woche/Monat/Jahr/Jahrzehnt/Jahrhundert/Frühling/Sommer/Herbst/Winter/Montag/Dienstag/Mittwoch/Donnerstag/Freitag/Samstag/Sonntag/Morgen/Mittag/Abend/Nacht/Mitternacht/Dämmerung/Gestern/Heute/Morgen/Bald/Sofort/Niemals/Ewig/Damals/Früher/Später/Jetzt/Alt/Neu";
const char p7[] = "GEGENSTÄNDE/Messer/Buch/Schlüssel/Geld/Puppe/Spielzeug/Uhr/Brief/Foto/Spiegel/Kette/Ring/Schmuck/Kerze/Bibel/Kreuz/Glas/Flasche/Gift/Strick/Hammer/Nagel/Schaufel/Laterne/Tasche/Kleid/Schuh/Hut/Stock/Kamm/Bürste/Tagebuch/Briefmarke/Münze/Kiste/Koffer/Truhe/Seil/Kette/Schloss";
const char p8[] = "TODESURSACHEN/Unfall/Gift/Seuche/Mord/Alter/Sturz/Feuer/Wasser/Hunger/Durst/Krankheit/Fieber/Pest/Krieg/Schuss/Hieb/Stich/Verrat/Suizid/Hinrichtung/Galgen/Beil/Zorn/Rache/Verzweiflung/Schock/Krampf/Lähmung/Ersticken/Ertrinken/Verbrennen/Blutverlust/Infektion/Wahnsinn/Erschöpfung";

const char* const cat_table[] = {p0, p1, p2, p3, p4, p5, p6, p7, p8};
constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);

