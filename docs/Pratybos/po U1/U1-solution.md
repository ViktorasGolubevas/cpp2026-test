# U1: Sprendimas - C++ Primityvai ir Funkcijų Moduliai

**Dėstytojui:** Šis failas skirtas jums - pilnas sprendimas su kodu, paaiškinimais ir "virtuve".

---

## 📁 Galutinė failų struktūra

```
U1/
├── main.cpp
├── rusiavimas.h
├── rusiavimas.cpp
├── Makefile
└── README.txt
```

---

## 1️⃣ **1 žingsnis: Hello World ir masyvų įvestis**

### **main.cpp (pradinė versija):**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 1. Hello World
    cout << "Hello, World!" << endl;
    
    // 2. Masyvas skaičiams
    int skaiciai[100];  // Fiksuoto dydžio masyvas
    int kiekis = 0;     // Kiek elementų įvesta
    int x;
    
    // 3. Įvedimas
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai[kiekis++] = x;
    }
    
    // 4. Išvedimas
    cout << "Įvesti skaičiai: ";
    for(int i = 0; i < kiekis; i++) {
        cout << skaiciai[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### **Kompiliacija:**
```bash
g++ main.cpp -o programa
./programa
```

### **Testavimas:**
```
Hello, World!
Įveskite sveikus skaičius (0 - baigti):
42
17
99
0
Įvesti skaičiai: 42 17 99
```

### **Pedagoginės pastabos:**
- ✅ Paprastas startas - visi turėtų sugebėti
- ✅ `cin >> x` automatiškai konvertuoja įvedimą
- ⚠️ Dažna klaida: užmiršti `kiekis` kintamąjį (saugo, kiek elementų)
- ⚠️ Dažna klaida: `skaiciai[kiekis++]` vs `skaiciai[++kiekis]` (postfix/prefix)

---

## 2️⃣ **2 žingsnis: Bubble sort funkcija**

### **main.cpp (modifikuotas):**

```cpp
#include <iostream>
using namespace std;

// Funkcijos deklaracija
void rusiuotiMasyva(int masyvas[], int dydis);

int main() {
    cout << "Hello, World!" << endl;
    
    int skaiciai[100];
    int kiekis = 0;
    int x;
    
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai[kiekis++] = x;
    }
    
    // NAUJAS: Rūšiavimas
    cout << "Prieš rūšiavimą: ";
    for(int i = 0; i < kiekis; i++) {
        cout << skaiciai[i] << " ";
    }
    cout << endl;
    
    rusiuotiMasyva(skaiciai, kiekis);
    
    cout << "Po rūšiavimo: ";
    for(int i = 0; i < kiekis; i++) {
        cout << skaiciai[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// Funkcijos apibrėžimas (Bubble sort)
void rusiuotiMasyva(int masyvas[], int dydis) {
    for(int i = 0; i < dydis - 1; i++) {
        for(int j = 0; j < dydis - i - 1; j++) {
            if(masyvas[j] > masyvas[j + 1]) {
                // Sukeisti vietomis
                int temp = masyvas[j];
                masyvas[j] = masyvas[j + 1];
                masyvas[j + 1] = temp;
            }
        }
    }
}
```

### **Testavimas:**
```
Prieš rūšiavimą: 42 17 99
Po rūšiavimo: 17 42 99
```

### **Pedagoginės pastabos:**
- ✅ Bubble sort algoritmas paprastas (bet neefektyvus - O(n²))
- ⚠️ Dažna klaida: `dydis - 1` vs `dydis` (off-by-one error)
- ⚠️ Dažna klaida: `dydis - i - 1` (optimizacija - paskutiniai jau surūšiuoti)
- 💡 Galite pademonstruoti žingsnius su debug `cout` cikle

---

## 3️⃣ **3 žingsnis: Modulinė struktūra**

### **rusiavimas.h:**

```cpp
#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

// Funkcija rūšiavimui (Bubble sort)
void rusiuotiMasyva(int masyvas[], int dydis);

// Funkcija spausdinimui
void spausdintiMasyva(const int masyvas[], int dydis);

#endif
```

### **Pedagoginės pastabos (header guards):**
```cpp
#ifndef RUSIAVIMAS_H  // "if not defined"
#define RUSIAVIMAS_H  // "define it"

// ... turinys ...

#endif  // Užbaigti sąlygą
```

**Kodėl reikia?**
- Apsaugo nuo **multiple inclusion** (dvigubo įtraukimo)
- Jei `rusiavimas.h` būtų `#include` kelis kartus → kompiliavimo klaida
- Header guard užtikrina, kad turinys įtraukiamas **tik vieną kartą**

---

### **rusiavimas.cpp:**

```cpp
#include "rusiavimas.h"
#include <iostream>

// Bubble sort implementacija
void rusiuotiMasyva(int masyvas[], int dydis) {
    for(int i = 0; i < dydis - 1; i++) {
        for(int j = 0; j < dydis - i - 1; j++) {
            if(masyvas[j] > masyvas[j + 1]) {
                int temp = masyvas[j];
                masyvas[j] = masyvas[j + 1];
                masyvas[j + 1] = temp;
            }
        }
    }
}

// Spausdinimo funkcija
void spausdintiMasyva(const int masyvas[], int dydis) {
    for(int i = 0; i < dydis; i++) {
        std::cout << masyvas[i] << " ";
    }
    std::cout << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `#include "rusiavimas.h"` - **dvigubos kabutės** (local file)
- ✅ `#include <iostream>` - **kampiniai skliaustai** (system library)
- ✅ `const int masyvas[]` - spausdinimas **nekeičia** masyvo
- ⚠️ Dažna klaida: `#include <rusiavimas.h>` (turėtų būti `"`)

---

### **main.cpp (supaprastintas):**

```cpp
#include <iostream>
#include "rusiavimas.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    
    int skaiciai[100];
    int kiekis = 0;
    int x;
    
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai[kiekis++] = x;
    }
    
    cout << "Prieš rūšiavimą: ";
    spausdintiMasyva(skaiciai, kiekis);
    
    rusiuotiMasyva(skaiciai, kiekis);
    
    cout << "Po rūšiavimo: ";
    spausdintiMasyva(skaiciai, kiekis);
    
    return 0;
}
```

---

### **Makefile (rekomenduojama):**

```makefile
# Kompiliatorius
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Failai
OBJS = main.o rusiavimas.o
TARGET = programa

# Pagrindinis tikslas
all: $(TARGET)

# Linkinimas
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Kompiliacija
main.o: main.cpp rusiavimas.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rusiavimas.o: rusiavimas.cpp rusiavimas.h
	$(CXX) $(CXXFLAGS) -c rusiavimas.cpp

# Valymas
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY tikslai
.PHONY: all clean
```

### **Naudojimas:**
```bash
make           # Kompiliuoti
./programa     # Paleisti
make clean     # Išvalyti
```

### **Pedagoginės pastabos:**
- ✅ Makefile **automatizuoja** kompiliaciją
- ✅ Perkompiliuoja tik **pasikeitusius** failus (efektyvu!)
- ⚠️ **TAB** simboliai privalomi (ne spaces!)
- 💡 Studentams galite duoti šabloną, tik pritaikys vardus

---

### **Kompiliacija rankiniu būdu:**

```bash
# 1. Kompiliuoti kiekvieną .cpp failą į .o
g++ -Wall -std=c++11 -c main.cpp
g++ -Wall -std=c++11 -c rusiavimas.cpp

# 2. Sujungti (link) į vieną programą
g++ main.o rusiavimas.o -o programa

# 3. Paleisti
./programa
```

**Flag'ų paaiškinimas:**
- `-Wall` - rodyti **visus** warning'us (good practice!)
- `-std=c++11` - naudoti C++11 standartą (arba `-std=c++17`)
- `-c` - **compile only** (nesujungti į executable)
- `-o` - **output** failo vardas

---

## 4️⃣ **4 žingsnis: array → vector\<int\>**

### **main.cpp (su vector):**

```cpp
#include <iostream>
#include <vector>
#include "rusiavimas.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    
    /*
    // ==================================================
    // SENASIS KODAS SU MASYVU (UŽKOMENTUOTAS)
    // ==================================================
    int skaiciai[100];
    int kiekis = 0;
    int x;
    
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai[kiekis++] = x;
    }
    */
    
    // ==================================================
    // NAUJAS KODAS SU VECTOR
    // ==================================================
    vector<int> skaiciai;  // Dinaminis konteineris
    int x;
    
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai.push_back(x);  // Pridėti į pabaigą
    }
    
    cout << "Prieš rūšiavimą: ";
    spausdintiVektoriu(skaiciai);
    
    rusiuotiVektoriu(skaiciai);
    
    cout << "Po rūšiavimo: ";
    spausdintiVektoriu(skaiciai);
    
    return 0;
}
```

---

### **rusiavimas.h (atnaujintas):**

```cpp
#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include <vector>

// Funkcijos masyvams (senas kodas)
void rusiuotiMasyva(int masyvas[], int dydis);
void spausdintiMasyva(const int masyvas[], int dydis);

// Funkcijos vektoriams (naujas kodas)
void rusiuotiVektoriu(std::vector<int>& skaiciai);
void spausdintiVektoriu(const std::vector<int>& skaiciai);

#endif
```

---

### **rusiavimas.cpp (atnaujintas):**

```cpp
#include "rusiavimas.h"
#include <iostream>

// ==================================================
// SENOS FUNKCIJOS (MASYVAMS)
// ==================================================
void rusiuotiMasyva(int masyvas[], int dydis) {
    for(int i = 0; i < dydis - 1; i++) {
        for(int j = 0; j < dydis - i - 1; j++) {
            if(masyvas[j] > masyvas[j + 1]) {
                int temp = masyvas[j];
                masyvas[j] = masyvas[j + 1];
                masyvas[j + 1] = temp;
            }
        }
    }
}

void spausdintiMasyva(const int masyvas[], int dydis) {
    for(int i = 0; i < dydis; i++) {
        std::cout << masyvas[i] << " ";
    }
    std::cout << std::endl;
}

// ==================================================
// NAUJOS FUNKCIJOS (VEKTORIAMS)
// ==================================================
void rusiuotiVektoriu(std::vector<int>& skaiciai) {
    int dydis = skaiciai.size();  // Dinaminis dydis
    for(int i = 0; i < dydis - 1; i++) {
        for(int j = 0; j < dydis - i - 1; j++) {
            if(skaiciai[j] > skaiciai[j + 1]) {
                int temp = skaiciai[j];
                skaiciai[j] = skaiciai[j + 1];
                skaiciai[j + 1] = temp;
            }
        }
    }
}

void spausdintiVektoriu(const std::vector<int>& skaiciai) {
    for(int i = 0; i < skaiciai.size(); i++) {
        std::cout << skaiciai[i] << " ";
    }
    std::cout << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `vector<int>&` - perduodame **per nuorodą** (modifikuojame originalą)
- ✅ `const vector<int>&` - **nekeičiame** (read-only)
- ✅ `.size()` - dinaminis dydis (ne fiksuotas!)
- ✅ `.push_back()` - pridėti naują elementą
- 💡 Vector **automatiškai plečiasi** (reallocates memory)
- ⚠️ Dažna klaida: `skaiciai.size()` grąžina `size_t` (unsigned) → `-Wsign-compare` warning

---

## 5️⃣ **5 žingsnis: vector\<int\> → vector\<string\>**

### **main.cpp (su string):**

```cpp
#include <iostream>
#include <vector>
#include <string>
#include "rusiavimas.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    
    /*
    // ==================================================
    // SENASIS KODAS SU SKAIČIAIS (UŽKOMENTUOTAS)
    // ==================================================
    vector<int> skaiciai;
    int x;
    cout << "Įveskite sveikus skaičius (0 - baigti):" << endl;
    while(cin >> x && x != 0) {
        skaiciai.push_back(x);
    }
    */
    
    // ==================================================
    // NAUJAS KODAS SU ŽODŽIAIS
    // ==================================================
    vector<string> zodziai;
    string zodis;
    
    cout << "Įveskite žodžius ('-' baigti):" << endl;
    while(cin >> zodis && zodis != "-") {
        zodziai.push_back(zodis);
    }
    
    cout << "Prieš rūšiavimą: ";
    spausdintiZodzius(zodziai);
    
    rusiuotiZodzius(zodziai);
    
    cout << "Po rūšiavimo: ";
    spausdintiZodzius(zodziai);
    
    return 0;
}
```

---

### **rusiavimas.h (galutinė versija):**

```cpp
#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include <vector>
#include <string>

// Funkcijos masyvams (1-2 žingsniai)
void rusiuotiMasyva(int masyvas[], int dydis);
void spausdintiMasyva(const int masyvas[], int dydis);

// Funkcijos int vektoriams (4 žingsnis)
void rusiuotiVektoriu(std::vector<int>& skaiciai);
void spausdintiVektoriu(const std::vector<int>& skaiciai);

// Funkcijos string vektoriams (5 žingsnis)
void rusiuotiZodzius(std::vector<std::string>& zodziai);
void spausdintiZodzius(const std::vector<std::string>& zodziai);

#endif
```

---

### **rusiavimas.cpp (galutinė versija):**

```cpp
#include "rusiavimas.h"
#include <iostream>

// ... (senos funkcijos, paliekame)

// ==================================================
// STRING VEKTORIŲ FUNKCIJOS
// ==================================================
void rusiuotiZodzius(std::vector<std::string>& zodziai) {
    int dydis = zodziai.size();
    for(int i = 0; i < dydis - 1; i++) {
        for(int j = 0; j < dydis - i - 1; j++) {
            // string palaiko < operatorių (leksikografinė tvarka)
            if(zodziai[j] > zodziai[j + 1]) {
                std::string temp = zodziai[j];
                zodziai[j] = zodziai[j + 1];
                zodziai[j + 1] = temp;
            }
        }
    }
}

void spausdintiZodzius(const std::vector<std::string>& zodziai) {
    for(int i = 0; i < zodziai.size(); i++) {
        std::cout << zodziai[i] << " ";
    }
    std::cout << std::endl;
}
```

### **Pedagoginės pastabos:**
- ✅ `string` klasė palaiko `<` operatorių (leksikografinė/abėcėlės tvarka)
- ✅ Tas pats Bubble sort algoritmas veikia su skirtingais tipais!
- 💡 **Foreshadowing templates** - "ar matote pattern'ą? Vėliau naudosime templates"
- ⚠️ Lietuviškos raidės (ą, č, ė...) gali būti rūšiuojamos neteisingai (encoding problema)

---

## 📦 **README.txt pavyzdys**

```
===========================================
U1: C++ Primityvai ir Funkcijų Moduliai
===========================================

Autorius: [Vardas Pavardė]
Data: 2026-02-15

-------------------------------------------
KOMPILIAVIMAS
-------------------------------------------

Naudojant Makefile:
    make
    ./programa

Arba rankiniu būdu:
    g++ -Wall -std=c++11 -c main.cpp
    g++ -Wall -std=c++11 -c rusiavimas.cpp
    g++ main.o rusiavimas.o -o programa
    ./programa

-------------------------------------------
PROGRAMOS APRAŠYMAS
-------------------------------------------

Programa leidžia vartotojui įvesti sveikus skaičius
arba žodžius, surūšiuoja juos Bubble sort algoritmu
ir atspausdina rezultatą.

Programa demonstruoja evoliuciją:
1. Masyvas → vector<int>
2. vector<int> → vector<string>

-------------------------------------------
TESTAVIMO PAVYZDŽIAI
-------------------------------------------

Testas 1 (skaičiai):
    Įvedimas: 42 17 99 0
    Rezultatas: 17 42 99

Testas 2 (žodžiai):
    Įvedimas: obuolys bananas citrina -
    Rezultatas: bananas citrina obuolys

-------------------------------------------
PASTABOS
-------------------------------------------

- Senasis kodas užkomentuotas, bet matomas
- Naudojamas Bubble sort (ne std::sort)
- Header guards naudojami rusiavimas.h faile
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| Užmiršo header guards | ⭐⭐⭐⭐ | Parodyti kompiliavimo klaidą be jų |
| `#include <rusiavimas.h>` vietoj `"..."` | ⭐⭐⭐⭐ | Paaiškinti skirtumą |
| Neperdavė vektoriaus per nuorodą (`&`) | ⭐⭐⭐ | Parodyti, kad rūšiavimas neveikia |
| Bubble sort off-by-one error | ⭐⭐⭐ | Debug'inti su `cout` cikle |
| Neužkomentavo seno kodo | ⭐⭐ | Atimti balus (vertinimo kriterijus!) |
| Makefile su spaces vietoj TAB | ⭐⭐ | `make: *** missing separator` klaida |

### **Galimi praplėtimai stipriesiems:**

1. **Įvesti keletą testų rinkmenų**
   - Skaityti iš failų (`ifstream`)
   
2. **Matuoti rūšiavimo laiką**
   - `#include <chrono>`
   - Palyginti su `std::sort()`
   
3. **Pridėti kitus rūšiavimo algoritmus**
   - Selection sort
   - Insertion sort
   - Palyginti efektyvumą

4. **Error handling**
   - Patikrinti, ar įvedimas korektiškas
   - `cin.fail()` tikrinimas

---

## 💡 **Diskusijos taškai paskaitoje**

1. **Kodėl vector geresnis už masyvą?**
   - Dinaminis dydis
   - Automatinis memory management
   - `.size()`, `.push_back()` patogumas

2. **Kodėl reikia header guards?**
   - Pademonstruoti multiple inclusion problemą

3. **Kodėl perduoti per nuorodą (`&`)?**
   - Efektyvumas (nekopijuojama)
   - Modifikuojamas originalas

4. **Foreshadowing templates:**
   - "Ar matote, kad tas pats algoritmas veikia su `int` ir `string`?"
   - "Vėliau išmoksite templates - generinį kodą!"

---

**Sėkmės dėstant!** 🎓
