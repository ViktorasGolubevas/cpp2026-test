# U4: Sprendimas - Gilus Kopijavimas (Deep Copy)

**Dėstytojui:** Pilnas sprendimas su shallow copy demo ir Rule of Three implementacija.

---

## 📁 Galutinė failų struktūra

```
U4/
├── README.md
├── 01/  ← Shallow copy problema
├── 02/  ← Copy constructor
└── 03/  ← Copy assignment (Rule of Three)
```

**Pastaba:** Visi žingsniai naudoja **tas pačias klases** iš U3 (Langas, Durys, Kambarys, skaiciavimai). Skiriasi tik `Kambarys.cpp` implementacija.

---

## 1️⃣ **1 žingsnis: Shallow copy problema**

### **Kambarys.h (kaip U3 - be copy constructor/assignment):**

```cpp
#ifndef KAMBARYS_H
#define KAMBARYS_H

#include <vector>
#include "Langas.h"
#include "Durys.h"

class Kambarys {
private:
    float ilgis;
    float plotis;
    float aukstis;
    
    std::vector<Langas> langai;
    Durys* durys;
    
public:
    Kambarys(float i, float p, float a);
    ~Kambarys();
    
    void pridetiLanga(const Langas& langas);
    void nustatytiDuris(Durys* d);
    
    float gautiIlgi() const;
    float gautiPloti() const;
    float gautiAuksti() const;
    
    // Friend funkcijos
    friend float apskaiciuotiSienuPlota(const Kambarys& k);
    friend float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);
};

#endif
```

### **Pedagoginės pastabos:**
- ❌ **Nėra** copy constructor
- ❌ **Nėra** copy assignment operator
- ✅ **Yra** destruktorius
- ⚠️ **Problema**: Rule of Three pažeidimas!

---

### **Kambarys.cpp (kaip U3):**

```cpp
#include "Kambarys.h"
#include <iostream>

Kambarys::Kambarys(float i, float p, float a) 
    : ilgis(i), plotis(p), aukstis(a), durys(nullptr) {
    std::cout << "[DEBUG] Kambarys sukurtas" << std::endl;
}

Kambarys::~Kambarys() {
    std::cout << "[DEBUG] Kambarys naikinamas" << std::endl;
    if (durys != nullptr) {
        std::cout << "[DEBUG] Kambarys naikina savo duris" << std::endl;
        delete durys;
        durys = nullptr;
    }
    langai.clear();
    std::cout << "[DEBUG] Kambarys sunaikintas" << std::endl;
}

// ... kiti metodai kaip U3 ...
```

---

### **skaiciavimai.h (su testuotiKopija funkcija):**

```cpp
#ifndef SKAICIAVIMAI_H
#define SKAICIAVIMAI_H

#include "Kambarys.h"

float apskaiciuotiSienuPlota(const Kambarys& k);
float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);

// NAUJAS: Funkcija testui (pass-by-VALUE!)
void testuotiKopija(Kambarys k);

#endif
```

---

### **skaiciavimai.cpp:**

```cpp
#include "skaiciavimai.h"
#include <iostream>

// ... (apskaiciuotiSienuPlota, apskaiciuotiGrindjuscesIlgi kaip U3) ...

// NAUJAS: Testuoti kopijavimą
void testuotiKopija(Kambarys k) {
    // Parametras 'k' yra KOPIJA (pass-by-value)
    std::cout << "[FUNKCIJOJE] Testuojame kopija" << std::endl;
    std::cout << "[FUNKCIJOJE] Sienu plotas = " 
              << apskaiciuotiSienuPlota(k) << " m²" << std::endl;
    std::cout << "[FUNKCIJOJE] Funkcija baigiasi (destruktorius bus iškviečiamas)" 
              << std::endl;
} // ← k destruktorius čia!
```

### **Pedagoginės pastabos:**
- ✅ `Kambarys k` - **pass-by-value** (ne `const Kambarys&`)
- ✅ Funkcijos pabaigoje `k` destruktorius automatiškai kviečiamas
- ⚠️ **Shallow copy**: `k.durys` rodo į tą patį objektą kaip originalo `durys`!

---

### **main.cpp (problema demo):**

```cpp
#include <iostream>
#include "Langas.h"
#include "Durys.h"
#include "Kambarys.h"
#include "skaiciavimai.h"

using namespace std;

int main() {
    cout << "=== U4 Žingsnis 1: Shallow Copy Problema ===\n" << endl;
    
    // Setup
    cout << "--- Sukuriame kambarį ---" << endl;
    Kambarys* k1 = new Kambarys(5.0, 4.0, 3.0);
    
    Langas l1(1.5, 1.0);
    k1->pridetiLanga(l1);
    
    Durys* d1 = new Durys(2.0, 0.9);
    k1->nustatytiDuris(d1);
    
    cout << "\nKambarys sukonfigūruotas. Duriu counter: " 
         << Durys::gautiSukurtaDuriu() << endl;
    
    // TESTAS 1: Pirmas kvietimas
    cout << "\n========================================" << endl;
    cout << "TESTAS 1: Pirmas kvietimas (veiks OK)" << endl;
    cout << "========================================" << endl;
    testuotiKopija(*k1);
    
    cout << "\nPo pirmo kvietimo. Duriu counter: " 
         << Durys::gautiSukurtaDuriu() << endl;
    
    // TESTAS 2: Antras kvietimas (PROBLEMA!)
    cout << "\n========================================" << endl;
    cout << "TESTAS 2: Antras kvietimas (CRASH/ERROR!)" << endl;
    cout << "========================================" << endl;
    
    cout << "[ĮSPĖJIMAS] Šis kvietimas turėtų sukelti problemą..." << endl;
    testuotiKopija(*k1);  // ← CRASH arba undefined behavior!
    
    cout << "\nJei programa nepasuko, čia matote blogus duomenis." << endl;
    
    delete k1;
    return 0;
}
```

---

### **Išvestis (CRASH scenario):**

```
=== U4 Žingsnis 1: Shallow Copy Problema ===

--- Sukuriame kambarį ---
[DEBUG] Kambarys sukurtas
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 2
[DEBUG] Kambarys pridejo langa. Viso langu: 1
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 1
[DEBUG] Kambarys gavo duris

Kambarys sukonfigūruotas. Duriu counter: 1

========================================
TESTAS 1: Pirmas kvietimas (veiks OK)
========================================
[FUNKCIJOJE] Testuojame kopija
[FUNKCIJOJE] Sienu plotas = 49.20 m²
[FUNKCIJOJE] Funkcija baigiasi (destruktorius bus iškviečiamas)
[DEBUG] Kambarys naikinamas
[DEBUG] Kambarys naikina savo duris
[DEBUG] Durys sunaikintos. Liko duriu: 0  ← delete durys!
[DEBUG] Langas sunaikintas. Liko langu: 1
[DEBUG] Kambarys sunaikintas

Po pirmo kvietimo. Duriu counter: 0  ← Durys jau sunaikintos!

========================================
TESTAS 2: Antras kvietimas (CRASH/ERROR!)
========================================
[ĮSPĖJIMAS] Šis kvietimas turėtų sukelti problemą...
[FUNKCIJOJE] Testuojame kopija
Segmentation fault (core dumped)  ← CRASH!
```

### **Arba (jei ne crash, tai blogai):**

```
...
TESTAS 2: Antras kvietimas (CRASH/ERROR!)
...
[FUNKCIJOJE] Sienu plotas = -nan m²  ← Blogas rezultatas!
[DEBUG] Kambarys naikinamas
[DEBUG] Kambarys naikina savo duris
double free or corruption (out): 0x... ← Double-free!
Aborted (core dumped)
```

### **Pedagoginės pastabos:**
- 💥 **Pirmas kvietimas**: Veikia, bet sunaikina `durys` objektą
- 💥 **Antras kvietimas**: `durys` jau `delete`'intos → dangling pointer!
- 💥 **Rezultatas**: Crash arba undefined behavior
- 💡 **Priežastis**: Default copy constructor daro **shallow copy**

**Vizualizacija:**

```
Prieš pirma testuotiKopija():
k1:     durys → [Durys @0x1234]

Po kopijos (shallow):
k1:     durys → [Durys @0x1234]
                  ↑
kopija: durys ────┘  (ta pati rodyklė!)

Po pirmo destruktoriaus:
k1:     durys → [DELETED @0x1234]  ← dangling!
kopija: (jau sunaikinta)

Antro testuotiKopija():
kopija: durys → [DELETED @0x1234]  ← CRASH!
```

---

## 2️⃣ **2 žingsnis: Copy constructor (deep copy)**

### **Kambarys.h (papildymas):**

```cpp
#ifndef KAMBARYS_H
#define KAMBARYS_H

#include <vector>
#include "Langas.h"
#include "Durys.h"

class Kambarys {
private:
    float ilgis;
    float plotis;
    float aukstis;
    
    std::vector<Langas> langai;
    Durys* durys;
    
public:
    Kambarys(float i, float p, float a);
    
    // NAUJAS: Copy constructor
    Kambarys(const Kambarys& kitas);
    
    ~Kambarys();
    
    // ... kiti metodai ...
    
    friend float apskaiciuotiSienuPlota(const Kambarys& k);
    friend float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);
};

#endif
```

---

### **Kambarys.cpp (su copy constructor):**

```cpp
#include "Kambarys.h"
#include <iostream>

// Default konstruktorius (tas pats)
Kambarys::Kambarys(float i, float p, float a) 
    : ilgis(i), plotis(p), aukstis(a), durys(nullptr) {
    std::cout << "[DEBUG] Kambarys sukurtas (default konstruktorius)" << std::endl;
}

// NAUJAS: Copy constructor
Kambarys::Kambarys(const Kambarys& kitas) 
    : ilgis(kitas.ilgis), 
      plotis(kitas.plotis), 
      aukstis(kitas.aukstis) {
    
    std::cout << "[DEBUG] Kambarys kopijuojamas (copy constructor)" << std::endl;
    
    // 1. Kopijuoti langus
    // Vector automatiškai daro deep copy!
    langai = kitas.langai;
    std::cout << "[DEBUG]   - Langai nukopijuoti (vector deep copy)" << std::endl;
    
    // 2. Kopijuoti duris (DEEP COPY - naujas objektas!)
    if (kitas.durys != nullptr) {
        durys = new Durys(*kitas.durys);  // Iškviečia Durys copy constructor
        std::cout << "[DEBUG]   - Durys nukopijuotos (deep copy, naujas objektas)" 
                  << std::endl;
    } else {
        durys = nullptr;
        std::cout << "[DEBUG]   - Durys: nullptr" << std::endl;
    }
}

// Destruktorius (tas pats)
Kambarys::~Kambarys() {
    std::cout << "[DEBUG] Kambarys naikinamas" << std::endl;
    if (durys != nullptr) {
        std::cout << "[DEBUG] Kambarys naikina savo duris" << std::endl;
        delete durys;
        durys = nullptr;
    }
    langai.clear();
    std::cout << "[DEBUG] Kambarys sunaikintas" << std::endl;
}

// ... kiti metodai kaip anksčiau ...
```

### **Pedagoginės pastabos:**
- ✅ `Kambarys(const Kambarys& kitas)` - copy constructor signature
- ✅ `: ilgis(kitas.ilgis), ...` - initialization list (kopijuoti primityvus)
- ✅ `langai = kitas.langai` - vector **automatiškai** daro deep copy!
- ✅ `new Durys(*kitas.durys)` - **naujas** Durys objektas (deep copy!)
- ✅ `*kitas.durys` - dereferencing pointer (gauti Durys objektą)
- 💡 **Durys turi turėti copy constructor** - default veiks, jei nėra pointerių

---

### **main.cpp (testas dabar veikia):**

```cpp
#include <iostream>
#include "Langas.h"
#include "Durys.h"
#include "Kambarys.h"
#include "skaiciavimai.h"

using namespace std;

int main() {
    cout << "=== U4 Žingsnis 2: Copy Constructor (Deep Copy) ===\n" << endl;
    
    // Setup
    cout << "--- Sukuriame kambarį ---" << endl;
    Kambarys* k1 = new Kambarys(5.0, 4.0, 3.0);
    
    Langas l1(1.5, 1.0);
    k1->pridetiLanga(l1);
    
    Durys* d1 = new Durys(2.0, 0.9);
    k1->nustatytiDuris(d1);
    
    cout << "\nDuriu counter pradžioje: " << Durys::gautiSukurtaDuriu() << endl;
    
    // TESTAS 1: Pirmas kvietimas
    cout << "\n========================================" << endl;
    cout << "TESTAS 1: Pirmas kvietimas" << endl;
    cout << "========================================" << endl;
    testuotiKopija(*k1);
    
    cout << "\nDuriu counter po pirmo: " << Durys::gautiSukurtaDuriu() << endl;
    
    // TESTAS 2: Antras kvietimas (dabar turėtų veikti!)
    cout << "\n========================================" << endl;
    cout << "TESTAS 2: Antras kvietimas (dabar OK!)" << endl;
    cout << "========================================" << endl;
    testuotiKopija(*k1);
    
    cout << "\nDuriu counter po antro: " << Durys::gautiSukurtaDuriu() << endl;
    
    // TESTAS 3: Trečias kvietimas (dar kartą!)
    cout << "\n========================================" << endl;
    cout << "TESTAS 3: Trečias kvietimas (vis dar OK!)" << endl;
    cout << "========================================" << endl;
    testuotiKopija(*k1);
    
    cout << "\nVisi testai praėjo! Copy constructor veikia." << endl;
    
    delete k1;
    return 0;
}
```

---

### **Išvestis (VEIKIA!):**

```
=== U4 Žingsnis 2: Copy Constructor (Deep Copy) ===

--- Sukuriame kambarį ---
[DEBUG] Kambarys sukurtas (default konstruktorius)
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 2
[DEBUG] Kambarys pridejo langa. Viso langu: 1
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 1
[DEBUG] Kambarys gavo duris

Duriu counter pradžioje: 1

========================================
TESTAS 1: Pirmas kvietimas
========================================
[DEBUG] Kambarys kopijuojamas (copy constructor)
[DEBUG]   - Langai nukopijuoti (vector deep copy)
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 2  ← Nauja kopija!
[DEBUG]   - Durys nukopijuotos (deep copy, naujas objektas)
[FUNKCIJOJE] Testuojame kopija
[FUNKCIJOJE] Sienu plotas = 49.20 m²
[FUNKCIJOJE] Funkcija baigiasi (destruktorius bus iškviečiamas)
[DEBUG] Kambarys naikinamas
[DEBUG] Kambarys naikina savo duris
[DEBUG] Durys sunaikintos. Liko duriu: 1  ← Kopija sunaikinta
[DEBUG] Langas sunaikintas. Liko langu: 1
[DEBUG] Kambarys sunaikintas

Duriu counter po pirmo: 1  ← Originalo durys vis dar gyvi!

========================================
TESTAS 2: Antras kvietimas (dabar OK!)
========================================
[DEBUG] Kambarys kopijuojamas (copy constructor)
[DEBUG]   - Langai nukopijuoti (vector deep copy)
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 2  ← Dar viena kopija!
[DEBUG]   - Durys nukopijuotos (deep copy, naujas objektas)
[FUNKCIJOJE] Testuojame kopija
[FUNKCIJOJE] Sienu plotas = 49.20 m²
[FUNKCIJOJE] Funkcija baigiasi (destruktorius bus iškviečiamas)
[DEBUG] Kambarys naikinamas
[DEBUG] Kambarys naikina savo duris
[DEBUG] Durys sunaikintos. Liko duriu: 1
[DEBUG] Langas sunaikintas. Liko langu: 1
[DEBUG] Kambarys sunaikintas

Duriu counter po antro: 1  ← OK!

========================================
TESTAS 3: Trečias kvietimas (vis dar OK!)
========================================
...

Visi testai praėjo! Copy constructor veikia.
...
```

### **Pedagoginės pastabos:**
- ✅ **Durų counter**: 1 originalas + 1 kopija (bet ne vienu metu!)
- ✅ **Kiekvienas copy** sukuria **naują** Durys objektą
- ✅ **Destruktoriai**: Kiekviena kopija sunaikina **savo** duris
- 💡 **Originalo durys** išlieka nepaliesti!

---

## 3️⃣ **3 žingsnis: Copy assignment operator**

### **Kambarys.h (papildymas):**

```cpp
#ifndef KAMBARYS_H
#define KAMBARYS_H

#include <vector>
#include "Langas.h"
#include "Durys.h"

class Kambarys {
private:
    float ilgis;
    float plotis;
    float aukstis;
    
    std::vector<Langas> langai;
    Durys* durys;
    
public:
    Kambarys(float i, float p, float a);
    Kambarys(const Kambarys& kitas);
    
    // NAUJAS: Copy assignment operator
    Kambarys& operator=(const Kambarys& kitas);
    
    ~Kambarys();
    
    // ... kiti metodai ...
};

#endif
```

---

### **Kambarys.cpp (galutinė versija - Rule of Three):**

```cpp
#include "Kambarys.h"
#include <iostream>

// Default konstruktorius
Kambarys::Kambarys(float i, float p, float a) 
    : ilgis(i), plotis(p), aukstis(a), durys(nullptr) {
    std::cout << "[DEBUG] Kambarys sukurtas (default konstruktorius)" << std::endl;
}

// Copy constructor
Kambarys::Kambarys(const Kambarys& kitas) 
    : ilgis(kitas.ilgis), plotis(kitas.plotis), aukstis(kitas.aukstis) {
    std::cout << "[DEBUG] Kambarys kopijuojamas (copy constructor)" << std::endl;
    
    langai = kitas.langai;
    
    if (kitas.durys != nullptr) {
        durys = new Durys(*kitas.durys);
    } else {
        durys = nullptr;
    }
}

// NAUJAS: Copy assignment operator
Kambarys& Kambarys::operator=(const Kambarys& kitas) {
    std::cout << "[DEBUG] Kambarys kopijuojamas (operator=)" << std::endl;
    
    // 1. Self-assignment check
    if (this == &kitas) {
        std::cout << "[DEBUG]   - Self-assignment aptiktas, praleidziama" << std::endl;
        return *this;
    }
    
    // 2. Atlaisvinti senus resursus
    std::cout << "[DEBUG]   - Atlaisvinami seni resursai" << std::endl;
    if (durys != nullptr) {
        delete durys;
        durys = nullptr;
    }
    langai.clear();
    
    // 3. Kopijuoti naujus duomenis
    std::cout << "[DEBUG]   - Kopijuojami nauji duomenys" << std::endl;
    ilgis = kitas.ilgis;
    plotis = kitas.plotis;
    aukstis = kitas.aukstis;
    
    langai = kitas.langai;  // Vector deep copy
    
    if (kitas.durys != nullptr) {
        durys = new Durys(*kitas.durys);  // Deep copy
    } else {
        durys = nullptr;
    }
    
    return *this;
}

// Destruktorius
Kambarys::~Kambarys() {
    std::cout << "[DEBUG] Kambarys naikinamas" << std::endl;
    if (durys != nullptr) {
        delete durys;
        durys = nullptr;
    }
    langai.clear();
    std::cout << "[DEBUG] Kambarys sunaikintas" << std::endl;
}

// ... kiti metodai ...
```

### **Pedagoginės pastabos:**
- ✅ `Kambarys& operator=(...)` - return reference (chaining)
- ✅ **Step 1**: Self-assignment check (`if (this == &kitas)`)
- ✅ **Step 2**: Delete old resources **BEFORE** copying
- ✅ **Step 3**: Copy new data (deep copy!)
- ✅ `return *this` - enable chaining (`a = b = c`)
- ⚠️ **Kritinė klaida**: Jei pamiršti self-check → sunaikini objektą prieš kopijuojant!

---

### **main.cpp (galutinis testas):**

```cpp
#include <iostream>
#include "Langas.h"
#include "Durys.h"
#include "Kambarys.h"
#include "skaiciavimai.h"

using namespace std;

int main() {
    cout << "=== U4 Žingsnis 3: Copy Assignment (Rule of Three) ===\n" << endl;
    
    // TESTAS 1: Assignment
    cout << "--- TESTAS 1: Assignment (k2 = k1) ---" << endl;
    
    Kambarys k1(5.0, 4.0, 3.0);
    Langas l1(1.5, 1.0);
    k1.pridetiLanga(l1);
    Durys* d1 = new Durys(2.0, 0.9);
    k1.nustatytiDuris(d1);
    
    Kambarys k2(3.0, 3.0, 2.5);  // Skirtingi matmenys
    
    cout << "\nPrieš assignment:" << endl;
    cout << "k1 sienu plotas: " << apskaiciuotiSienuPlota(k1) << endl;
    cout << "k2 sienu plotas: " << apskaiciuotiSienuPlota(k2) << endl;
    
    cout << "\nDarome: k2 = k1" << endl;
    k2 = k1;  // ← operator= iškviečiamas!
    
    cout << "\nPo assignment:" << endl;
    cout << "k1 sienu plotas: " << apskaiciuotiSienuPlota(k1) << endl;
    cout << "k2 sienu plotas: " << apskaiciuotiSienuPlota(k2) << endl;
    
    // TESTAS 2: Self-assignment
    cout << "\n--- TESTAS 2: Self-assignment (k2 = k2) ---" << endl;
    k2 = k2;  // ← Turėtų aptikti ir praleisti!
    
    cout << "Po self-assignment:" << endl;
    cout << "k2 sienu plotas: " << apskaiciuotiSienuPlota(k2) << endl;
    
    // TESTAS 3: Chaining
    cout << "\n--- TESTAS 3: Chaining (k3 = k2 = k1) ---" << endl;
    Kambarys k3(2.0, 2.0, 2.0);
    k3 = k2 = k1;  // ← Turėtų veikti (dešinė į kairę)!
    
    cout << "k3 sienu plotas: " << apskaiciuotiSienuPlota(k3) << endl;
    
    cout << "\n=== Visi testai praėjo! ===" << endl;
    return 0;
}
```

---

### **Išvestis:**

```
=== U4 Žingsnis 3: Copy Assignment (Rule of Three) ===

--- TESTAS 1: Assignment (k2 = k1) ---
[DEBUG] Kambarys sukurtas (default konstruktorius)
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
...
[DEBUG] Kambarys sukurtas (default konstruktorius)

Prieš assignment:
k1 sienu plotas: 49.20
k2 sienu plotas: 54.00

Darome: k2 = k1
[DEBUG] Kambarys kopijuojamas (operator=)
[DEBUG]   - Atlaisvinami seni resursai
[DEBUG]   - Kopijuojami nauji duomenys
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 2  ← Nauja kopija!

Po assignment:
k1 sienu plotas: 49.20
k2 sienu plotas: 49.20  ← Dabar vienodi!

--- TESTAS 2: Self-assignment (k2 = k2) ---
[DEBUG] Kambarys kopijuojamas (operator=)
[DEBUG]   - Self-assignment aptiktas, praleidziama  ← Saugumas!

Po self-assignment:
k2 sienu plotas: 49.20

--- TESTAS 3: Chaining (k3 = k2 = k1) ---
[DEBUG] Kambarys sukurtas (default konstruktorius)
[DEBUG] Kambarys kopijuojamas (operator=)
...
[DEBUG] Kambarys kopijuojamas (operator=)
...
k3 sienu plotas: 49.20

=== Visi testai praėjo! ===
...
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| Pamiršo self-assignment check | ⭐⭐⭐⭐⭐ | Sunaikina objektą prieš kopijuojant! |
| Neatlaisvino senų resursų operator= | ⭐⭐⭐⭐ | Memory leak |
| Shallow copy (nesuprasti problemą) | ⭐⭐⭐⭐ | Demo su 01/ |
| Pamiršo `return *this` | ⭐⭐⭐ | Chaining neveiks |
| `new Durys(kitas.durys)` vietoj `(*kitas.durys)` | ⭐⭐⭐ | Compiler error |
| Delete po copy (ne prieš!) | ⭐⭐ | Duomenų praradimas |

---

### **Diskusijos taškai:**

1. **Shallow vs Deep Copy visualization** - piešti lentelėje!
2. **Rule of Three** - kodėl **trys** (destruktorius + 2 copy)?
3. **Self-assignment** - demo: `k = k` be check → crash
4. **Chaining** - `a = b = c` kaip veikia? (right-to-left)
5. **Vector automatic deep copy** - kodėl lengviau už pointer?

---

### **Praplėtimai stipriesiems:**

1. **Move semantics** (Rule of Five):
   ```cpp
   Kambarys(Kambarys&& kitas) noexcept;  // Move constructor
   Kambarys& operator=(Kambarys&& kitas) noexcept;  // Move assignment
   ```

2. **Copy-and-swap idiom**:
   ```cpp
   Kambarys& operator=(Kambarys kitas) {  // Pass-by-value!
       swap(*this, kitas);
       return *this;
   }
   ```

3. **Smart pointers vietoj raw**:
   ```cpp
   std::unique_ptr<Durys> durys;  // Automatic deep copy!
   ```

---

**Sėkmės dėstant!** 🎓
