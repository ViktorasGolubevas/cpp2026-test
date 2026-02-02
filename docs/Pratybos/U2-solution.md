# U2: Sprendimas - IntList Klasė ir RAII

**Dėstytojui:** Pilnas sprendimas su kodu ir paaiškinimais.

---

## 📁 Galutinė failų struktūra

```
U2/
├── README.md
├── 01/
│   ├── IntList.h
│   ├── IntList.cpp
│   ├── main.cpp
│   └── Makefile
├── 02/
│   ├── IntList.h
│   ├── IntList.cpp
│   ├── main.cpp
│   └── Makefile
└── 03/
    ├── IntList.h
    ├── IntList.cpp
    ├── main.cpp
    └── Makefile
```

---

## 1️⃣ **1 žingsnis: Basic klasė su fiksuotu masyvu**

### **IntList.h:**

```cpp
#ifndef INTLIST_H
#define INTLIST_H

class IntList {
private:
    int duomenys[100];  // Fiksuoto dydžio masyvas
    int dydis;          // Dabartinis elementų skaičius
    
public:
    // Konstruktorius
    IntList();
    
    // Metodai
    void pridetiGala(int reiksme);
    int gautiElementa(int indeksas) const;
    int gautiDydi() const;
    void spausdinti() const;
};

#endif
```

### **Pedagoginės pastabos (header guard):**
- ✅ `#ifndef` / `#define` / `#endif` - standartas
- ✅ Paprastai vardas: `KLASESVARAS_H` (uppercase)
- ⚠️ Dažna klaida: pamiršti `#endif`

---

### **IntList.cpp:**

```cpp
#include "IntList.h"
#include <iostream>

// Konstruktorius
IntList::IntList() {
    dydis = 0;  // Pradžioje sąrašas tuščias
}

// Pridėti elementą į pabaigą
void IntList::pridetiGala(int reiksme) {
    if (dydis >= 100) {
        std::cout << "[KLAIDA] Masyvas pilnas!" << std::endl;
        return;
    }
    duomenys[dydis] = reiksme;
    dydis++;
}

// Gauti elementą pagal indeksą
int IntList::gautiElementa(int indeksas) const {
    if (indeksas < 0 || indeksas >= dydis) {
        std::cout << "[KLAIDA] Blogas indeksas!" << std::endl;
        return -1;  // Klaida (vėliau bus exception)
    }
    return duomenys[indeksas];
}

// Gauti dabartinį dydį
int IntList::gautiDydi() const {
    return dydis;
}

// Spausdinti visus elementus
void IntList::spausdinti() const {
    std::cout << "IntList dydis: " << dydis << std::endl;
    std::cout << "Elementai: [";
    for (int i = 0; i < dydis; i++) {
        std::cout << duomenys[i];
        if (i < dydis - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `IntList::` - scope resolution operator (klasės narys)
- ✅ `const` metodai - nekeičia objekto būsenos
- ✅ Error handling - paprastas (`cout` + `return`)
- ⚠️ Dažna klaida: `dydis++` vietoj `dydis = dydis + 1` (bet abu OK)

---

### **main.cpp:**

```cpp
#include <iostream>
#include "IntList.h"
using namespace std;

int main() {
    cout << "=== IntList 1 žingsnis (fixed array) ===" << endl;
    
    // Sukurti IntList
    IntList sarasas;
    
    // Pridėti elementus
    cout << "\nPridedame 5 elementus:" << endl;
    for (int i = 1; i <= 5; i++) {
        sarasas.pridetiGala(i * 10);
    }
    
    // Atspausdinti
    sarasas.spausdinti();
    
    // Gauti elementą
    cout << "\nElementas [2]: " << sarasas.gautiElementa(2) << endl;
    
    // Testas: pilnas masyvas
    cout << "\nBandome pridėti 100 elementų (turėtų būti klaida):" << endl;
    IntList didelis;
    for (int i = 0; i < 105; i++) {
        didelis.pridetiGala(i);
    }
    cout << "Pridėta elementų: " << didelis.gautiDydi() << endl;
    
    return 0;
}
```

### **Makefile:**

```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o IntList.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp IntList.h
	$(CXX) $(CXXFLAGS) -c main.cpp

IntList.o: IntList.cpp IntList.h
	$(CXX) $(CXXFLAGS) -c IntList.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

### **Kompiliacija ir testavimas:**

```bash
cd U2/01/
make
./programa
```

**Išvestis:**
```
=== IntList 1 žingsnis (fixed array) ===

Pridedame 5 elementus:
IntList dydis: 5
Elementai: [10, 20, 30, 40, 50]

Elementas [2]: 30

Bandome pridėti 100 elementų (turėtų būti klaida):
[KLAIDA] Masyvas pilnas!
[KLAIDA] Masyvas pilnas!
[KLAIDA] Masyvas pilnas!
...
Pridėta elementų: 100
```

---

## 2️⃣ **2 žingsnis: Dynamic memory + RAII**

### **IntList.h (modifikuotas):**

```cpp
#ifndef INTLIST_H
#define INTLIST_H

class IntList {
private:
    int* duomenys;      // Rodyklė į dinaminį masyvą (NAUJAS!)
    int dydis;          // Dabartinis elementų skaičius
    int talpa;          // Išskirtos atminties talpa (NAUJAS!)
    
public:
    // Konstruktoriai (NAUJI!)
    IntList();                      // Default: talpa = 10
    IntList(int pradineTalpa);      // Su parametru
    
    // Destruktorius (NAUJAS!)
    ~IntList();
    
    // Metodai (tie patys kaip 1 žingsnyje)
    void pridetiGala(int reiksme);
    int gautiElementa(int indeksas) const;
    int gautiDydi() const;
    void spausdinti() const;
};

#endif
```

### **Pedagoginės pastabos:**
- ✅ `int*` - rodyklė (pointer)
- ✅ `talpa` vs `dydis` - svarbu atskirti!
- ✅ Destruktorius - `~IntList()` (tilde `~`)

---

### **IntList.cpp (modifikuotas):**

```cpp
#include "IntList.h"
#include <iostream>

// Default konstruktorius
IntList::IntList() {
    talpa = 10;
    dydis = 0;
    duomenys = new int[talpa];  // Dinaminis masyvas!
    std::cout << "[DEBUG] IntList sukurtas (talpa=" << talpa << ")" << std::endl;
}

// Konstruktorius su parametru
IntList::IntList(int pradineTalpa) {
    talpa = pradineTalpa;
    dydis = 0;
    duomenys = new int[talpa];
    std::cout << "[DEBUG] IntList sukurtas (talpa=" << talpa << ")" << std::endl;
}

// Destruktorius
IntList::~IntList() {
    std::cout << "[DEBUG] IntList naikinamas (dydis=" << dydis 
              << ", talpa=" << talpa << ")" << std::endl;
    delete[] duomenys;      // Atlaisvinti atmintį
    duomenys = nullptr;     // Saugumui
}

// Pridėti elementą
void IntList::pridetiGala(int reiksme) {
    if (dydis >= talpa) {
        std::cout << "[KLAIDA] IntList pilnas (talpa=" << talpa << ")!" << std::endl;
        return;
    }
    duomenys[dydis] = reiksme;
    dydis++;
}

// Gauti elementą (tas pats)
int IntList::gautiElementa(int indeksas) const {
    if (indeksas < 0 || indeksas >= dydis) {
        std::cout << "[KLAIDA] Blogas indeksas!" << std::endl;
        return -1;
    }
    return duomenys[indeksas];
}

// Gauti dydį (tas pats)
int IntList::gautiDydi() const {
    return dydis;
}

// Spausdinti (tas pats)
void IntList::spausdinti() const {
    std::cout << "IntList dydis: " << dydis << " / talpa: " << talpa << std::endl;
    std::cout << "Elementai: [";
    for (int i = 0; i < dydis; i++) {
        std::cout << duomenys[i];
        if (i < dydis - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `new int[talpa]` - išskirti dinaminį masyvą
- ✅ `delete[] duomenys` - **SVARBU**: `delete[]` (su `[]`), ne `delete`!
- ✅ `nullptr` po `delete[]` - gera praktika (dangling pointer prevention)
- ✅ Logging - matome, kada konstruktorius/destruktorius kviečiami
- ⚠️ **KRITINĖ KLAIDA**: `delete duomenys` vietoj `delete[] duomenys` → undefined behavior!

---

### **main.cpp (modifikuotas):**

```cpp
#include <iostream>
#include "IntList.h"
using namespace std;

int main() {
    cout << "=== IntList 2 žingsnis (dynamic memory + RAII) ===" << endl;
    
    // Testas 1: Default konstruktorius
    cout << "\n--- Testas 1: Default konstruktorius ---" << endl;
    {
        IntList sarasas;  // talpa = 10
        for (int i = 1; i <= 5; i++) {
            sarasas.pridetiGala(i * 10);
        }
        sarasas.spausdinti();
    } // Destruktorius čia!
    cout << "Destruktorius jau iškviečiamas (scope pabaiga)" << endl;
    
    // Testas 2: Konstruktorius su parametru
    cout << "\n--- Testas 2: Konstruktorius su parametru ---" << endl;
    {
        IntList mazosSarasas(3);  // talpa = 3
        mazosSarasas.pridetiGala(100);
        mazosSarasas.pridetiGala(200);
        mazosSarasas.pridetiGala(300);
        mazosSarasas.spausdinti();
        
        // Bandome pridėti 4-ą (turėtų būti klaida)
        cout << "\nBandome pridėti 4-ą elementą (klaida!):" << endl;
        mazosSarasas.pridetiGala(400);
    } // Destruktorius čia!
    
    // Testas 3: Daug objektų
    cout << "\n--- Testas 3: Daug objektų ---" << endl;
    {
        IntList s1, s2, s3;
        s1.pridetiGala(1);
        s2.pridetiGala(2);
        s3.pridetiGala(3);
        cout << "Sukurti 3 objektai (destruktoriai bus iškviečiami reverse order)" << endl;
    } // 3 destruktoriai čia!
    
    cout << "\n=== Programa baigta ===" << endl;
    return 0;
}
```

**Išvestis:**
```
=== IntList 2 žingsnis (dynamic memory + RAII) ===

--- Testas 1: Default konstruktorius ---
[DEBUG] IntList sukurtas (talpa=10)
IntList dydis: 5 / talpa: 10
Elementai: [10, 20, 30, 40, 50]
[DEBUG] IntList naikinamas (dydis=5, talpa=10)
Destruktorius jau iškviečiamas (scope pabaiga)

--- Testas 2: Konstruktorius su parametru ---
[DEBUG] IntList sukurtas (talpa=3)
IntList dydis: 3 / talpa: 3
Elementai: [100, 200, 300]

Bandome pridėti 4-ą elementą (klaida!):
[KLAIDA] IntList pilnas (talpa=3)!
[DEBUG] IntList naikinamas (dydis=3, talpa=3)

--- Testas 3: Daug objektų ---
[DEBUG] IntList sukurtas (talpa=10)
[DEBUG] IntList sukurtas (talpa=10)
[DEBUG] IntList sukurtas (talpa=10)
Sukurti 3 objektai (destruktoriai bus iškviečiami reverse order)
[DEBUG] IntList naikinamas (dydis=1, talpa=10)
[DEBUG] IntList naikinamas (dydis=1, talpa=10)
[DEBUG] IntList naikinamas (dydis=1, talpa=10)

=== Programa baigta ===
```

### **Pedagoginės pastabos:**
- ✅ **Scope** `{ ... }` - destruktorius automatiškai kviečiamas scope pabaigoje
- ✅ **Reverse order** - konstruktoriai: 1→2→3, destruktoriai: 3→2→1 (stack unwinding)
- 💡 **Diskusijos taškas**: "Kodėl destruktoriai reverse order?" (stack semantics)

---

## 3️⃣ **3 žingsnis: Automatinis išplėtimas**

### **IntList.h (papildymas):**

```cpp
#ifndef INTLIST_H
#define INTLIST_H

class IntList {
private:
    int* duomenys;
    int dydis;
    int talpa;
    
    // Private metodas (NAUJAS!)
    void isplesti();
    
public:
    IntList();
    IntList(int pradineTalpa);
    ~IntList();
    
    void pridetiGala(int reiksme);
    int gautiElementa(int indeksas) const;
    int gautiDydi() const;
    int gautiTalpa() const;  // NAUJAS - debugging
    void spausdinti() const;
};

#endif
```

---

### **IntList.cpp (galutinė versija):**

```cpp
#include "IntList.h"
#include <iostream>

// Konstruktoriai (tie patys)
IntList::IntList() {
    talpa = 10;
    dydis = 0;
    duomenys = new int[talpa];
    std::cout << "[DEBUG] IntList sukurtas (talpa=" << talpa << ")" << std::endl;
}

IntList::IntList(int pradineTalpa) {
    talpa = pradineTalpa;
    dydis = 0;
    duomenys = new int[talpa];
    std::cout << "[DEBUG] IntList sukurtas (talpa=" << talpa << ")" << std::endl;
}

// Destruktorius (tas pats)
IntList::~IntList() {
    std::cout << "[DEBUG] IntList naikinamas (dydis=" << dydis 
              << ", talpa=" << talpa << ")" << std::endl;
    delete[] duomenys;
    duomenys = nullptr;
}

// NAUJAS: Privatus metodas - išplėsti masyvą
void IntList::isplesti() {
    int naujaTalpa = talpa + 5;  // Didinti po 5
    
    std::cout << "[DEBUG] IntList isplesta (sena talpa=" << talpa 
              << ", nauja talpa=" << naujaTalpa << ")" << std::endl;
    
    // 1. Išskirti naują masyvą
    int* naujasDuomenys = new int[naujaTalpa];
    
    // 2. Nukopijuoti senus duomenis
    for (int i = 0; i < dydis; i++) {
        naujasDuomenys[i] = duomenys[i];
    }
    
    // 3. Atlaisvinti seną masyvą
    delete[] duomenys;
    
    // 4. Priskirti naują masyvą
    duomenys = naujasDuomenys;
    talpa = naujaTalpa;
}

// MODIFIKUOTAS: Pridėti elementą (dabar su auto-expand)
void IntList::pridetiGala(int reiksme) {
    if (dydis >= talpa) {
        isplesti();  // Automatinis išplėtimas!
    }
    duomenys[dydis] = reiksme;
    dydis++;
}

// Kiti metodai (tie patys)
int IntList::gautiElementa(int indeksas) const {
    if (indeksas < 0 || indeksas >= dydis) {
        std::cout << "[KLAIDA] Blogas indeksas!" << std::endl;
        return -1;
    }
    return duomenys[indeksas];
}

int IntList::gautiDydi() const {
    return dydis;
}

// NAUJAS - debugging
int IntList::gautiTalpa() const {
    return talpa;
}

void IntList::spausdinti() const {
    std::cout << "IntList dydis: " << dydis << " / talpa: " << talpa << std::endl;
    std::cout << "Elementai: [";
    for (int i = 0; i < dydis; i++) {
        std::cout << duomenys[i];
        if (i < dydis - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `isplesti()` - **private** metodas (internal implementation detail)
- ✅ **Reallocation algoritmas**:
  1. Išskirti naują didesnį masyvą
  2. Kopijuoti senus duomenis
  3. Atlaisvinti seną
  4. Priskirti naują
- ⚠️ **KRITINĖ KLAIDA**: Kopijuoti **prieš** `delete[]` (priešingu atveju - duomenų praradimas!)
- 💡 **Optimizacija**: Growth factor (dabar +5, galima *2 - logaritminis growth)

---

### **main.cpp (galutinis testas):**

```cpp
#include <iostream>
#include "IntList.h"
using namespace std;

int main() {
    cout << "=== IntList 3 žingsnis (auto-expand) ===" << endl;
    
    // Testas 1: Mažas talpa, daug elementų
    cout << "\n--- Testas 1: Mažas talpa (3), pridedame 10 elementų ---" << endl;
    IntList sarasas(3);
    for (int i = 1; i <= 10; i++) {
        cout << "Pridedame " << (i * 10) << "..." << endl;
        sarasas.pridetiGala(i * 10);
    }
    sarasas.spausdinti();
    
    // Testas 2: Default talpa, daug elementų
    cout << "\n--- Testas 2: Default talpa (10), pridedame 20 elementų ---" << endl;
    IntList didelis;
    for (int i = 1; i <= 20; i++) {
        didelis.pridetiGala(i);
    }
    didelis.spausdinti();
    
    // Testas 3: Labai mažas talpa (1), demonstruoti daug išplėtimų
    cout << "\n--- Testas 3: Talpa=1, pridedame 7 elementus (daug išplėtimų) ---" << endl;
    IntList mazytis(1);
    for (int i = 0; i < 7; i++) {
        mazytis.pridetiGala(i * 100);
    }
    mazytis.spausdinti();
    
    cout << "\n=== Programa baigta (destruktoriai bus iškviečiami) ===" << endl;
    return 0;
}
```

**Išvestis:**
```
=== IntList 3 žingsnis (auto-expand) ===

--- Testas 1: Mažas talpa (3), pridedame 10 elementų ---
[DEBUG] IntList sukurtas (talpa=3)
Pridedame 10...
Pridedame 20...
Pridedame 30...
Pridedame 40...
[DEBUG] IntList isplesta (sena talpa=3, nauja talpa=8)
Pridedame 50...
Pridedame 60...
Pridedame 70...
Pridedame 80...
Pridedame 90...
[DEBUG] IntList isplesta (sena talpa=8, nauja talpa=13)
Pridedame 100...
IntList dydis: 10 / talpa: 13
Elementai: [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

--- Testas 2: Default talpa (10), pridedame 20 elementų ---
[DEBUG] IntList sukurtas (talpa=10)
[DEBUG] IntList isplesta (sena talpa=10, nauja talpa=15)
[DEBUG] IntList isplesta (sena talpa=15, nauja talpa=20)
IntList dydis: 20 / talpa: 20
Elementai: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

--- Testas 3: Talpa=1, pridedame 7 elementus (daug išplėtimų) ---
[DEBUG] IntList sukurtas (talpa=1)
[DEBUG] IntList isplesta (sena talpa=1, nauja talpa=6)
[DEBUG] IntList isplesta (sena talpa=6, nauja talpa=11)
IntList dydis: 7 / talpa: 11
Elementai: [0, 100, 200, 300, 400, 500, 600]

=== Programa baigta (destruktoriai bus iškviečiami) ===
[DEBUG] IntList naikinamas (dydis=7, talpa=11)
[DEBUG] IntList naikinamas (dydis=20, talpa=20)
[DEBUG] IntList naikinamas (dydis=10, talpa=13)
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| `delete duomenys` vietoj `delete[]` | ⭐⭐⭐⭐⭐ | **Kritinė klaida!** Undefined behavior |
| Neužkomentavo destruktoriaus logging | ⭐⭐⭐⭐ | Nematys, kada destruktorius kviečiamas |
| `isplesti()` kopijuoja **po** `delete[]` | ⭐⭐⭐ | Duomenų praradimas! |
| Pamiršo `nullptr` po `delete[]` | ⭐⭐⭐ | Dangling pointer (ne kritinė, bet svarbu) |
| `talpa` vs `dydis` painiava | ⭐⭐ | Paaiškinti skirtumą |
| Konstruktorius be logging | ⭐⭐ | Nematys konstruktoriaus kvietimų |

---

### **Diskusijos taškai paskaitose:**

1. **RAII principas:**
   - "Kas būtų, jei užmirštume `delete[]`?" → Memory leak!
   - "Kodėl destruktorius **automatiškai** kviečiamas?" → RAII magic

2. **`delete` vs `delete[]`:**
   - Parodyti undefined behavior pavyzdį
   - Valgrind demo (jei galima)

3. **Growth strategy:**
   - Dabar: +5 (linear)
   - `std::vector`: ×2 (exponential)
   - Trade-off: memory vs reallocations

4. **Destruktorių tvarka:**
   - Stack unwinding (LIFO)
   - Reverse order demonstration

5. **Foreshadowing:**
   - "Vėliau išmoksime **copy constructor** - dabar shallow copy problema!"
   - "Kas būtų, jei `IntList s2 = s1;`?" → Dangling pointer!

---

### **Praplėtimai stipriesiems:**

1. **Growth factor:**
   - Pakeisti `talpa + 5` → `talpa * 2`
   - Palyginti reallocations skaičių

2. **Capacity reserve:**
   - Pridėti `void rezervuoti(int naujaTalpa)`
   - Preallocate jei žinome, kiek reikia

3. **Error handling su exceptions:**
   - `throw std::bad_alloc` jei `new` fails
   - `throw std::out_of_range` jei indeksas blogas

4. **Debugging metodai:**
   - `void spausdintiDebug()` - parodyti memory address, talpa, dydis
   - `bool arTuscias()`, `bool arPilnas()`

5. **Additional methods:**
   - `void pasalinti(int indeksas)` - remove element
   - `void isvalyti()` - clear all elements

---

## 💡 **Testai (extra):**

### **Memory leak testas:**

```cpp
// Sukurti daug objektų - neturėtų būti memory leak
for (int i = 0; i < 1000; i++) {
    IntList temp(100);
    for (int j = 0; j < 50; j++) {
        temp.pridetiGala(j);
    }
} // 1000 destruktorių - visos atmintis atlaisvinta?
```

**Tikrinti su Valgrind:**
```bash
g++ -g main.cpp IntList.cpp -o programa
valgrind --leak-check=full ./programa
```

**Rezultatas (jei teisingai):**
```
All heap blocks were freed -- no leaks are possible
```

---

### **Performance testas:**

```cpp
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

IntList didelis(1);  // Mažas talpa
for (int i = 0; i < 100000; i++) {
    didelis.pridetiGala(i);
}

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

cout << "Laikas: " << duration.count() << " ms" << endl;
cout << "Reallocations: " << (didelis.gautiTalpa() - 1) / 5 << endl;
```

**Diskusija:** Linear (+5) vs Exponential (×2) growth

---

**Sėkmės dėstant!** 🎓
