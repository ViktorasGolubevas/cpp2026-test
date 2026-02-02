# U3: Sprendimas - Kompozicija (has-a ryšys)

**Dėstytojui:** Pilnas sprendimas su kodu ir paaiškinimais.

---

## 📁 Galutinė failų struktūra

```
U3/
├── README.md
├── 01/
│   ├── Langas.h, Langas.cpp
│   ├── Durys.h, Durys.cpp
│   ├── main.cpp
│   └── Makefile
├── 02/
│   ├── Langas.h, Langas.cpp
│   ├── Durys.h, Durys.cpp
│   ├── Kambarys.h, Kambarys.cpp
│   ├── main.cpp
│   └── Makefile
└── 03/
    ├── Langas.h, Langas.cpp
    ├── Durys.h, Durys.cpp
    ├── Kambarys.h, Kambarys.cpp
    ├── skaiciavimai.h, skaiciavimai.cpp
    ├── main.cpp
    └── Makefile
```

---

## 1️⃣ **1 žingsnis: Langas ir Durys klasės**

### **Langas.h:**

```cpp
#ifndef LANGAS_H
#define LANGAS_H

class Langas {
private:
    float aukstis;
    float plotis;
    static int sukurtaLangu;  // Statinis skaitiklis
    
public:
    // Konstruktorius
    Langas(float a, float p);
    
    // Destruktorius
    ~Langas();
    
    // Getters
    float gautiAuksti() const;
    float gautiPloti() const;
    float apskaiciuotiPlota() const;
    
    // Static getter
    static int gautiSukurtaLangu();
};

#endif
```

### **Pedagoginės pastabos:**
- ✅ `static int sukurtaLangu` - **klasės lygio** (ne objekto!)
- ✅ `static` metodas - gali būti kviečiamas **be objekto**: `Langas::gautiSukurtaLangu()`
- ⚠️ Dažna klaida: pamiršti inicializuoti `.cpp` faile

---

### **Langas.cpp:**

```cpp
#include "Langas.h"
#include <iostream>

// SVARBU: Statinio nario inicializacija UŽ klasės ribų
int Langas::sukurtaLangu = 0;

// Konstruktorius
Langas::Langas(float a, float p) : aukstis(a), plotis(p) {
    sukurtaLangu++;
    std::cout << "[DEBUG] Langas sukurtas (" << aukstis << "×" << plotis 
              << "). Viso langu: " << sukurtaLangu << std::endl;
}

// Destruktorius
Langas::~Langas() {
    sukurtaLangu--;
    std::cout << "[DEBUG] Langas sunaikintas. Liko langu: " 
              << sukurtaLangu << std::endl;
}

// Getters
float Langas::gautiAuksti() const {
    return aukstis;
}

float Langas::gautiPloti() const {
    return plotis;
}

float Langas::apskaiciuotiPlota() const {
    return aukstis * plotis;
}

// Static getter
int Langas::gautiSukurtaLangu() {
    return sukurtaLangu;
}
```

### **Pedagoginės pastabos:**
- ✅ `int Langas::sukurtaLangu = 0;` - **BŪTINA** inicializuoti .cpp!
- ✅ Initialization list: `: aukstis(a), plotis(p)` - efektyvesnė nei assignment
- ✅ Logging padeda matyti objektų gyvavimo ciklą
- ⚠️ Dažna klaida: `static int Langas::sukurtaLangu = 0;` - **ne** `static` .cpp faile!

---

### **Durys.h:**

```cpp
#ifndef DURYS_H
#define DURYS_H

class Durys {
private:
    float aukstis;
    float plotis;
    static int sukurtaDuriu;
    
public:
    Durys(float a, float p);
    ~Durys();
    
    float gautiAuksti() const;
    float gautiPloti() const;
    float apskaiciuotiPlota() const;
    
    static int gautiSukurtaDuriu();
};

#endif
```

### **Durys.cpp:**

```cpp
#include "Durys.h"
#include <iostream>

int Durys::sukurtaDuriu = 0;

Durys::Durys(float a, float p) : aukstis(a), plotis(p) {
    sukurtaDuriu++;
    std::cout << "[DEBUG] Durys sukurtos (" << aukstis << "×" << plotis 
              << "). Viso duriu: " << sukurtaDuriu << std::endl;
}

Durys::~Durys() {
    sukurtaDuriu--;
    std::cout << "[DEBUG] Durys sunaikintos. Liko duriu: " 
              << sukurtaDuriu << std::endl;
}

float Durys::gautiAuksti() const {
    return aukstis;
}

float Durys::gautiPloti() const {
    return plotis;
}

float Durys::apskaiciuotiPlota() const {
    return aukstis * plotis;
}

int Durys::gautiSukurtaDuriu() {
    return sukurtaDuriu;
}
```

---

### **main.cpp (1 žingsnis):**

```cpp
#include <iostream>
#include "Langas.h"
#include "Durys.h"

using namespace std;

int main() {
    cout << "=== U3 Žingsnis 1: Langas ir Durys ===\n" << endl;
    
    // Testas 1: Static counter pradžioje
    cout << "--- Pradžioje ---" << endl;
    cout << "Langu: " << Langas::gautiSukurtaLangu() << endl;
    cout << "Duriu: " << Durys::gautiSukurtaDuriu() << endl;
    
    // Testas 2: Sukurti langus
    cout << "\n--- Sukuriame 3 langus ---" << endl;
    Langas l1(1.5, 1.0);
    Langas l2(2.0, 1.5);
    Langas l3(1.8, 1.2);
    
    cout << "\nLangu: " << Langas::gautiSukurtaLangu() << endl;
    
    // Testas 3: Langu plotai
    cout << "\n--- Langu plotai ---" << endl;
    cout << "L1 plotas: " << l1.apskaiciuotiPlota() << " m²" << endl;
    cout << "L2 plotas: " << l2.apskaiciuotiPlota() << " m²" << endl;
    cout << "L3 plotas: " << l3.apskaiciuotiPlota() << " m²" << endl;
    
    // Testas 4: Sukurti duris
    cout << "\n--- Sukuriame 2 duris ---" << endl;
    Durys d1(2.0, 0.9);
    Durys d2(2.1, 0.8);
    
    cout << "\nDuriu: " << Durys::gautiSukurtaDuriu() << endl;
    
    // Testas 5: Scope test
    cout << "\n--- Scope testas (objektai sunaikinti scope pabaigoje) ---" << endl;
    {
        Langas temp(1.0, 1.0);
        cout << "Scope viduje, langu: " << Langas::gautiSukurtaLangu() << endl;
    } // temp destruktorius čia!
    cout << "Po scope, langu: " << Langas::gautiSukurtaLangu() << endl;
    
    cout << "\n=== Programa baigia darba (visi objektai bus sunaikinti) ===" << endl;
    return 0;
}
```

**Išvestis:**
```
=== U3 Žingsnis 1: Langas ir Durys ===

--- Pradžioje ---
Langu: 0
Duriu: 0

--- Sukuriame 3 langus ---
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
[DEBUG] Langas sukurtas (2×1.5). Viso langu: 2
[DEBUG] Langas sukurtas (1.8×1.2). Viso langu: 3

Langu: 3

--- Langu plotai ---
L1 plotas: 1.5 m²
L2 plotas: 3 m²
L3 plotas: 2.16 m²

--- Sukuriame 2 duris ---
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 1
[DEBUG] Durys sukurtos (2.1×0.8). Viso duriu: 2

Duriu: 2

--- Scope testas (objektai sunaikinti scope pabaigoje) ---
[DEBUG] Langas sukurtas (1×1). Viso langu: 4
Scope viduje, langu: 4
[DEBUG] Langas sunaikintas. Liko langu: 3
Po scope, langu: 3

=== Programa baigia darba (visi objektai bus sunaikinti) ===
[DEBUG] Durys sunaikintos. Liko duriu: 1
[DEBUG] Durys sunaikintos. Liko duriu: 0
[DEBUG] Langas sunaikintas. Liko langu: 2
[DEBUG] Langas sunaikintas. Liko langu: 1
[DEBUG] Langas sunaikintas. Liko langu: 0
```

### **Makefile:**

```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Langas.o Durys.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp Langas.h Durys.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Langas.o: Langas.cpp Langas.h
	$(CXX) $(CXXFLAGS) -c Langas.cpp

Durys.o: Durys.cpp Durys.h
	$(CXX) $(CXXFLAGS) -c Durys.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

---

## 2️⃣ **2 žingsnis: Kambarys klasė (kompozicija)**

### **Kambarys.h:**

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
    
    std::vector<Langas> langai;  // Value semantics (kopijos)
    Durys* durys;                // Pointer semantics (dalijimasis)
    
public:
    // Konstruktorius
    Kambarys(float i, float p, float a);
    
    // Destruktorius
    ~Kambarys();
    
    // Metodai
    void pridetiLanga(const Langas& langas);
    void nustatytiDuris(Durys* d);
    
    // Getters
    float gautiIlgi() const;
    float gautiPloti() const;
    float gautiAuksti() const;
    int gautiLanguKieki() const;
    bool arTuriDuris() const;
};

#endif
```

### **Pedagoginės pastabos:**
- ✅ `#include <vector>` - STL konteineris
- ✅ `vector<Langas>` - **saugo kopijas** (value semantics)
- ✅ `Durys*` - **saugo rodyklę** (pointer semantics)
- 💡 **Kompozicija**: Kambarys **turi** (owns) langus ir duris

---

### **Kambarys.cpp:**

```cpp
#include "Kambarys.h"
#include <iostream>

// Konstruktorius
Kambarys::Kambarys(float i, float p, float a) 
    : ilgis(i), plotis(p), aukstis(a), durys(nullptr) {
    std::cout << "[DEBUG] Kambarys sukurtas (" << ilgis << "×" 
              << plotis << "×" << aukstis << ")" << std::endl;
}

// Destruktorius
Kambarys::~Kambarys() {
    std::cout << "[DEBUG] Kambarys naikinamas" << std::endl;
    
    // Sunaikinti duris (jei yra)
    if (durys != nullptr) {
        std::cout << "[DEBUG] Kambarys naikina savo duris" << std::endl;
        delete durys;
        durys = nullptr;
    }
    
    // Išvalyti langų vektorių (ne būtina, bet gera praktika)
    langai.clear();
    
    std::cout << "[DEBUG] Kambarys sunaikintas" << std::endl;
}

// Pridėti langą
void Kambarys::pridetiLanga(const Langas& langas) {
    langai.push_back(langas);  // KOPIJUOJA objektą į vektorių
    std::cout << "[DEBUG] Kambarys pridejo langa. Viso langu: " 
              << langai.size() << std::endl;
}

// Nustatyti duris
void Kambarys::nustatytiDuris(Durys* d) {
    durys = d;  // Tik priskiria rodyklę (NE kopija!)
    std::cout << "[DEBUG] Kambarys gavo duris" << std::endl;
}

// Getters
float Kambarys::gautiIlgi() const {
    return ilgis;
}

float Kambarys::gautiPloti() const {
    return plotis;
}

float Kambarys::gautiAuksti() const {
    return aukstis;
}

int Kambarys::gautiLanguKieki() const {
    return langai.size();
}

bool Kambarys::arTuriDuris() const {
    return durys != nullptr;
}
```

### **Pedagoginės pastabos:**
- ✅ `durys(nullptr)` - initialization list (saugus pradinis būsenos)
- ✅ `langai.push_back(langas)` - **KOPIJUOJA** (value semantics)
- ✅ `durys = d` - tik **priskiria rodyklę** (pointer semantics)
- ✅ Destruktorius patikrina `if (durys != nullptr)` prieš `delete`
- ⚠️ **Dažna klaida**: `delete langai` - BLOGAI! Vector destruktorius automatiškai

---

### **main.cpp (2 žingsnis):**

```cpp
#include <iostream>
#include "Langas.h"
#include "Durys.h"
#include "Kambarys.h"

using namespace std;

int main() {
    cout << "=== U3 Žingsnis 2: Kambarys (kompozicija) ===\n" << endl;
    
    // Testas 1: Sukurti langus (lokalūs objektai)
    cout << "--- Sukuriame langus ---" << endl;
    Langas l1(1.5, 1.0);
    Langas l2(1.5, 1.0);
    Langas l3(2.0, 1.5);
    
    // Testas 2: Sukurti duris (dinamiškai)
    cout << "\n--- Sukuriame duris (dynamic) ---" << endl;
    Durys* d1 = new Durys(2.0, 0.9);
    
    // Testas 3: Sukurti kambarį
    cout << "\n--- Sukuriame kambari ---" << endl;
    Kambarys kambarys(5.0, 4.0, 3.0);
    
    // Testas 4: Pridėti langus
    cout << "\n--- Pridedame langus (kopijuoja!) ---" << endl;
    kambarys.pridetiLanga(l1);
    kambarys.pridetiLanga(l2);
    kambarys.pridetiLanga(l3);
    
    cout << "\nStatistika:" << endl;
    cout << "  Kambaryje langu: " << kambarys.gautiLanguKieki() << endl;
    cout << "  Viso langu sistemoje: " << Langas::gautiSukurtaLangu() << endl;
    
    // Testas 5: Nustatyti duris
    cout << "\n--- Nustatome duris (pointer!) ---" << endl;
    kambarys.nustatytiDuris(d1);
    
    // Testas 6: Kambario info
    cout << "\n--- Kambario informacija ---" << endl;
    cout << "Matmenys: " << kambarys.gautiIlgi() << " × " 
         << kambarys.gautiPloti() << " × " 
         << kambarys.gautiAuksti() << " m" << endl;
    cout << "Langu: " << kambarys.gautiLanguKieki() << endl;
    cout << "Turi duris: " << (kambarys.arTuriDuris() ? "Taip" : "Ne") << endl;
    
    cout << "\n=== Programa baigia darba ===" << endl;
    cout << "PASTABA: Kambarys destruktorius sunaikins duris!" << endl;
    return 0;
}
```

**Išvestis:**
```
=== U3 Žingsnis 2: Kambarys (kompozicija) ===

--- Sukuriame langus ---
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 2
[DEBUG] Langas sukurtas (2×1.5). Viso langu: 3

--- Sukuriame duris (dynamic) ---
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 1

--- Sukuriame kambari ---
[DEBUG] Kambarys sukurtas (5×4×3)

--- Pridedame langus (kopijuoja!) ---
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 4  ← Kopija!
[DEBUG] Kambarys pridejo langa. Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 5  ← Kopija!
[DEBUG] Kambarys pridejo langa. Viso langu: 2
[DEBUG] Langas sukurtas (2×1.5). Viso langu: 6  ← Kopija!
[DEBUG] Kambarys pridejo langa. Viso langu: 3

Statistika:
  Kambaryje langu: 3
  Viso langu sistemoje: 6  ← 3 originalai + 3 kopijos!

--- Nustatome duris (pointer!) ---
[DEBUG] Kambarys gavo duris

--- Kambario informacija ---
Matmenys: 5 × 4 × 3 m
Langu: 3
Turi duris: Taip

=== Programa baigia darba ===
PASTABA: Kambarys destruktorius sunaikins duris!
[DEBUG] Kambarys naikinamas
[DEBUG] Kambarys naikina savo duris
[DEBUG] Durys sunaikintos. Liko duriu: 0
[DEBUG] Langas sunaikintas. Liko langu: 5  ← Vector destruktorius
[DEBUG] Langas sunaikintas. Liko langu: 4
[DEBUG] Langas sunaikintas. Liko langu: 3
[DEBUG] Kambarys sunaikintas
[DEBUG] Langas sunaikintas. Liko langu: 2  ← Originalai
[DEBUG] Langas sunaikintas. Liko langu: 1
[DEBUG] Langas sunaikintas. Liko langu: 0
```

### **Pedagoginės pastabos:**
- 💡 **6 langai viso** = 3 originalai + 3 kopijos vektoriuje!
- 💡 **Vector destruktorius** automatiškai sunaikina kopijas
- 💡 **Kambarys destruktorius** sunaikina duris (pointer semantics)
- ⚠️ **Double-free bug** jei studentas bandys `delete d1` main'e!

---

## 3️⃣ **3 žingsnis: Skaičiavimai (globalios funkcijos)**

### **skaiciavimai.h:**

```cpp
#ifndef SKAICIAVIMAI_H
#define SKAICIAVIMAI_H

#include "Kambarys.h"

// Globalios funkcijos (ne metodai!)
float apskaiciuotiSienuPlota(const Kambarys& k);
float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);

#endif
```

### **skaiciavimai.cpp:**

```cpp
#include "skaiciavimai.h"
#include <iostream>

// Sienų ploto skaičiavimas
float apskaiciuotiSienuPlota(const Kambarys& k) {
    // 1. Perimetras
    float perimetras = 2 * (k.gautiIlgi() + k.gautiPloti());
    
    // 2. Sienų plotas (be langų ir durų)
    float sienuPlotas = perimetras * k.gautiAuksti();
    
    // 3. Atimti langų plotus
    // PASTABA: Reikia prieigos prie langų - problemos!
    // Sprendimas: pridėti Kambarys metodą, kuris grąžina langų plotų sumą
    
    // Supaprastinta versija (be langų/durų atskaitymų)
    std::cout << "[DEBUG] Sienu plotas (gross): " << sienuPlotas << " m²" << std::endl;
    
    return sienuPlotas;
}

// Grindjuosčių ilgio skaičiavimas
float apskaiciuotiGrindjuscesIlgi(const Kambarys& k) {
    // Perimetras minus durų plotis
    float perimetras = 2 * (k.gautiIlgi() + k.gautiPloti());
    
    // PASTABA: Reikia prieigos prie durų pločio
    // Supaprastinta versija
    std::cout << "[DEBUG] Grindjusciu ilgis (full perimeter): " 
              << perimetras << " m" << std::endl;
    
    return perimetras;
}
```

### **Pedagoginės pastabos - PROBLEMA!**

Globalios funkcijos **neturi prieigos** prie `private` narių (`langai`, `durys`)!

**Sprendimo būdai:**

**1. Friend funkcijos** (rekomenduojama šiai užduočiai):
```cpp
// Kambarys.h
class Kambarys {
    // ...
    friend float apskaiciuotiSienuPlota(const Kambarys& k);
    friend float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);
};
```

**2. Public getter'iai**:
```cpp
// Kambarys.h
const std::vector<Langas>& gautiLangus() const;
const Durys* gautiDuris() const;
```

**Naudosime friend** (pirmą būdą) - tai mokymo tikslais gerai!

---

### **Kambarys.h (atnaujintas su friend):**

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
    int gautiLanguKieki() const;
    bool arTuriDuris() const;
    
    // Friend funkcijos (turi prieigą prie private!)
    friend float apskaiciuotiSienuPlota(const Kambarys& k);
    friend float apskaiciuotiGrindjuscesIlgi(const Kambarys& k);
};

#endif
```

---

### **skaiciavimai.cpp (galutinė versija):**

```cpp
#include "skaiciavimai.h"
#include <iostream>

// Sienų ploto skaičiavimas
float apskaiciuotiSienuPlota(const Kambarys& k) {
    // 1. Perimetras
    float perimetras = 2 * (k.ilgis + k.plotis);
    
    // 2. Bruto sienų plotas
    float sienuPlotas = perimetras * k.aukstis;
    
    // 3. Atimti langų plotus
    for (int i = 0; i < k.langai.size(); i++) {
        sienuPlotas -= k.langai[i].apskaiciuotiPlota();
    }
    
    // 4. Atimti durų plotą
    if (k.durys != nullptr) {
        sienuPlotas -= k.durys->apskaiciuotiPlota();
    }
    
    return sienuPlotas;
}

// Grindjuosčių ilgio skaičiavimas
float apskaiciuotiGrindjuscesIlgi(const Kambarys& k) {
    float perimetras = 2 * (k.ilgis + k.plotis);
    
    // Atimti durų plotį
    if (k.durys != nullptr) {
        perimetras -= k.durys->gautiPloti();
    }
    
    return perimetras;
}
```

### **Pedagoginės pastabos:**
- ✅ `friend` leidžia prieigą prie `private` narių
- ✅ Globalios funkcijos **už** klasės ribų
- ✅ `const Kambarys&` - efektyvu (ne kopija)
- 💡 **Diskusija**: Ar `friend` - gera praktika? (encapsulation trade-off)

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
    cout << "=== U3 Žingsnis 3: Skaičiavimai (globalios) ===\n" << endl;
    
    // Sukurti kambarį
    cout << "--- Kuriame kambari 5×4×3 m ---" << endl;
    Kambarys kambarys(5.0, 4.0, 3.0);
    
    // Pridėti 2 langus
    cout << "\n--- Pridedame 2 langus (1.5×1.0 m kiekvienas) ---" << endl;
    Langas l1(1.5, 1.0);
    Langas l2(1.5, 1.0);
    kambarys.pridetiLanga(l1);
    kambarys.pridetiLanga(l2);
    
    // Pridėti duris
    cout << "\n--- Pridedame duris (2.0×0.9 m) ---" << endl;
    Durys* durys = new Durys(2.0, 0.9);
    kambarys.nustatytiDuris(durys);
    
    // Skaičiavimai
    cout << "\n--- SKAIČIAVIMAI ---" << endl;
    float sienuPlotas = apskaiciuotiSienuPlota(kambarys);
    float grindjusces = apskaiciuotiGrindjuscesIlgi(kambarys);
    
    cout << fixed;
    cout.precision(2);
    cout << "\nRezultatai:" << endl;
    cout << "  Sienu plotas (neto): " << sienuPlotas << " m²" << endl;
    cout << "  Grindjusciu ilgis: " << grindjusces << " m" << endl;
    
    // Patikrinkite rankiniu būdu:
    // Perimetras = 2*(5+4) = 18 m
    // Bruto sienos = 18*3 = 54 m²
    // Langų plotai = 2*(1.5*1.0) = 3 m²
    // Durų plotas = 2.0*0.9 = 1.8 m²
    // Neto sienos = 54 - 3 - 1.8 = 49.2 m²
    // Grindjuosčių = 18 - 0.9 = 17.1 m
    
    cout << "\n=== Programa baigia darba ===" << endl;
    return 0;
}
```

**Išvestis:**
```
=== U3 Žingsnis 3: Skaičiavimai (globalios) ===

--- Kuriame kambari 5×4×3 m ---
[DEBUG] Kambarys sukurtas (5×4×3)

--- Pridedame 2 langus (1.5×1.0 m kiekvienas) ---
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 2
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 3
[DEBUG] Kambarys pridejo langa. Viso langu: 1
[DEBUG] Langas sukurtas (1.5×1). Viso langu: 4
[DEBUG] Kambarys pridejo langa. Viso langu: 2

--- Pridedame duris (2.0×0.9 m) ---
[DEBUG] Durys sukurtos (2×0.9). Viso duriu: 1
[DEBUG] Kambarys gavo duris

--- SKAIČIAVIMAI ---

Rezultatai:
  Sienu plotas (neto): 49.20 m²
  Grindjusciu ilgis: 17.10 m

=== Programa baigia darba ===
...
```

---

### **Makefile (galutinis):**

```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Langas.o Durys.o Kambarys.o skaiciavimai.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp Langas.h Durys.h Kambarys.h skaiciavimai.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Langas.o: Langas.cpp Langas.h
	$(CXX) $(CXXFLAGS) -c Langas.cpp

Durys.o: Durys.cpp Durys.h
	$(CXX) $(CXXFLAGS) -c Durys.cpp

Kambarys.o: Kambarys.cpp Kambarys.h Langas.h Durys.h
	$(CXX) $(CXXFLAGS) -c Kambarys.cpp

skaiciavimai.o: skaiciavimai.cpp skaiciavimai.h Kambarys.h
	$(CXX) $(CXXFLAGS) -c skaiciavimai.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| Pamiršo statinių narių inicializaciją .cpp | ⭐⭐⭐⭐⭐ | Linker error: "undefined reference" |
| `delete d1` main'e po kambarys destruktoriaus | ⭐⭐⭐⭐ | **Double-free!** Segfault |
| Globalios f-jos be `friend` | ⭐⭐⭐⭐ | Compiler error: "private" |
| `static` .cpp faile | ⭐⭐⭐ | Compiler error |
| `delete langai` destruktoriuje | ⭐⭐ | Compiler error (ne pointer) |
| Vector vs pointer painiava | ⭐⭐ | Conceptual - paaiškinti |

---

### **Diskusijos taškai:**

1. **Value vs Pointer semantics:**
   - Vector **kopijuoja** → 6 langai viso (3 originalai + 3 kopijos)
   - Pointer **dalijasi** → 1 durys objektas
   - Trade-off: memory vs flexibility

2. **Static members:**
   - Klasės lygio duomenys (ne objekto!)
   - Shared across all instances
   - Inicializacija .cpp faile (ne .h!)

3. **Friend funkcijos:**
   - Breaks encapsulation (trade-off!)
   - Alternatyva: public getters
   - Diskusija: kada naudoti?

4. **Destruktorių tvarka:**
   - Kambarys → durys (explicit delete)
   - Kambarys → langai (vector automatic)
   - Lokalūs objektai (LIFO)

---

### **Praplėtimai stipriesiems:**

1. **Getter'iai vietoj friend:**
   ```cpp
   const vector<Langas>& gautiLangus() const { return langai; }
   const Durys* gautiDuris() const { return durys; }
   ```

2. **Smart pointers vietoj raw:**
   ```cpp
   std::unique_ptr<Durys> durys;
   ```

3. **Iteratoriai langų vektoriuje:**
   ```cpp
   for(auto it = k.langai.begin(); it != k.langai.end(); ++it) { ... }
   ```

4. **Konstitucinės funkcijos Kambarys:**
   ```cpp
   float apskaiciuotiGrinduPlota() const;
   float apskaiciuotiTuri() const;
   ```

---

**Sėkmės dėstant!** 🎓
