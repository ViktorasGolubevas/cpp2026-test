# Rule of Five - Mokomoji Medžiaga

## 📦 Turinys

Šioje medžiagoje rasite:

### 1. **demo_07_fixed.cpp** ✅
**Tikslas:** Veikiantis, pataisytas kodas su pilna Rule of Five implementacija

**Naudojimas:**
```bash
g++ demo_07_fixed.cpp -o demo_07_fixed -std=c++11
./demo_07_fixed
```

**Kas viduje:**
- ✅ Pilnai veikiantis Student klasės pavyzdys
- ✅ Visi 5 special member functions
- ✅ Detalūs komentarai lietuvių kalba
- ✅ Demonstracija: emplace_back, push_back, sort, insert, erase
- ✅ Išvados ir patarimai failo pabaigoje

**Kam skirta:** Studentams, kurie nori matyti TEISINGĄ implementaciją

---

### 2. **demo_07_pedagogy.cpp** 🎓
**Tikslas:** Pedagoginis pavyzdys su palaipsniu išaiškinimu

**Naudojimas:**
```bash
g++ demo_07_pedagogy.cpp -o demo_pedagogy -std=c++11
./demo_pedagogy
```

**Kas viduje:**
- 🔴 VERSION 1: Broken - tyčia sugadintas kodas (nekompiliuojasi!)
- 🟡 VERSION 2: Minimal Fix - naudojant `= default`
- 🟢 VERSION 3: Full Implementation - su logging
- 📊 Testai, kurie parodo skirtingą elgesį
- 💡 Demonstracija, kodėl reikia assignment operators

**Kam skirta:** 
- Dėstytojams - rodyti paskaitoje
- Studentams - eksperimentuoti, keisti, mokytis

**Užduotys studentams:**
1. Išjungti `#if 0` ir bandyti kompiliuoti VERSION 1 (pamatyti klaidas)
2. Palyginti logging output tarp Minimal ir Full
3. Pridėti savo debug messages
4. Eksperimentuoti su `= delete`

---

### 3. **Rule_of_Five_CheatSheet.md** 📋
**Tikslas:** Greitas reference guide

**Formatas:** Markdown (skaitomas bet kuriame teksto redaktoriuje)

**Kas viduje:**
- 🎯 Pagrindinė taisyklė
- 📋 Sintaksė su pavyzdžiais
- 🚀 `= default` naudojimas
- 🚫 `= delete` naudojimas
- ⚠️ Kodėl tai svarbu
- 📊 Kada kas vyksta lentelė
- 🎓 STL reikalavimai
- 💡 Geriausios praktikos
- 🐛 Dažniausios klaidos

**Kam skirta:** Spausdinti ir laikyti ant stalo, kai koduojate

**HTML versija:** `Rule_of_Five_CheatSheet.html` - galima atidaryti naršyklėje

---

### 4. **Rule_of_Five_Comparison.md** 📊
**Tikslas:** Detalus palyginimas tarp skirtingų scenarijų

**Formatas:** Markdown su išsamiomis lentelėmis

**Kas viduje:**
- 📊 Kompiliatoriaus elgesio lentelė
- 🎯 5 praktiniai scenarijai:
  1. Pradedantis (nieko neapibrėžta)
  2. Tik Move Constructor (BROKEN!)
  3. = default (FIXED)
  4. Custom Resource (raw pointer)
  5. Move-only pattern
- 📈 Efektyvumo palyginimas (copy vs move)
- 🎓 STL konteinerių reikalavimai
- ⚡ Quick Decision Tree

**Kam skirta:** 
- Gilesniam supratimui
- Kada naudoti kurį variantą
- Performance implications

**HTML versija:** `Rule_of_Five_Comparison.html` - gražiau formatuota

---

## 🎯 Rekomenduojama Mokymosi Seka

### Dėstytojams (paskaitoje):

1. **demo_07_pedagogy.cpp** - demonstracija:
   - Rodyti VERSION 1 kompiliavimo klaidas (5 min)
   - Paaiškinti Rule of Five (10 min)
   - Paleisti VERSION 2 ir VERSION 3, palyginti output (10 min)

2. **Rule_of_Five_CheatSheet.md** - išdalinti studentams

3. **demo_07_fixed.cpp** - studentai gali naudoti kaip template

### Studentams (savarankiškai):

1. **Rule_of_Five_CheatSheet.md** - perskaityti (15 min)
   - Suprasti pagrindinę taisyklę
   - Žiūrėti į sintaksę

2. **demo_07_pedagogy.cpp** - paleisti ir eksperimentuoti (30 min)
   - Įjungti VERSION 1, pamatyti klaidas
   - Palyginti logging output
   - Keisti kodą, stebėti rezultatus

3. **demo_07_fixed.cpp** - analizuoti (20 min)
   - Skaityti komentarus
   - Suprasti, kaip veikia STL algoritmai

4. **Rule_of_Five_Comparison.md** - gilintis (30 min)
   - Kada naudoti kurį variantą
   - Efektyvumo aspektai

---

## 🔧 Kompiliavimas

### Linux / Git Bash / WSL:
```bash
g++ demo_07_fixed.cpp -o app -std=c++11 -Wall
g++ demo_07_pedagogy.cpp -o pedagogy -std=c++11 -Wall
```

### Windows (MinGW):
```bash
g++ demo_07_fixed.cpp -o app.exe -std=c++11 -Wall
g++ demo_07_pedagogy.cpp -o pedagogy.exe -std=c++11 -Wall
```

### Code::Blocks:
1. Project → Build options → Compiler settings → Compiler flags
2. ✅ Enable `-std=c++11`
3. Build → Run

---

## 📚 Papildoma Literatūra

- **Scott Meyers** - "Effective Modern C++" (Item 17)
- **cppreference.com** - "The rule of three/five/zero"
- **Howard Hinnant** - "A Brief Introduction to Rvalue References"

---

## 🐛 Dažniausios Problemos

### Problema: Kompiliavimo klaida "use of deleted function"

**Sprendimas:** 
```cpp
// Pridėti:
MyClass& operator=(const MyClass&) = default;
MyClass& operator=(MyClass&&) noexcept = default;
```

### Problema: Emoji nerodo Windows Console

**Sprendimas:**
```bash
chcp 65001
```
arba programoje:
```cpp
#include <windows.h>
SetConsoleOutputCP(CP_UTF8);
```

### Problema: std::sort() nekompiliuojasi

**Sprendimas:** Reikia:
1. `operator<` arba custom comparator
2. Copy/Move assignment operators

---

## ✅ Checklistai

### Prieš pradedant dėstyti:

- [ ] Patikrinti, ar visi failai kompiliuojasi
- [ ] Atsispausdinti Rule_of_Five_CheatSheet.md
- [ ] Pasiruošti demo_07_pedagogy.cpp demonstracijai
- [ ] Paruošti užduotis studentams

### Studentams po paskaitos:

- [ ] Paleisti visus pavyzdžius
- [ ] Perskaityti Cheat Sheet
- [ ] Eksperimentuoti su broken code
- [ ] Atlikti užduotis pedagogy faile
- [ ] Pasitikrinti su Comparison.md

---

## 📝 Licencija

Ši medžiaga skirta edukaciniais tikslais.  
Autorius: Viktoras Golubevas  
Kursas: Objektinis Programavimas su C++  
Data: 2026-02-12

---

## 💬 Atsiliepimai

Jei rasite klaidų arba turite pasiūlymų, praneškite dėstytojui!

**Happy Coding!** 🚀
