# U5: Sprendimas - Operatorių Perkrovimas ir Išimtys

**Dėstytojui:** Pilnas sprendimas su operatoriais ir exceptions.

---

## 📁 Galutinė failų struktūra

```
U5/
├── README.md
├── 01/  ← Basic + exceptions
├── 02/  ← Operatoriai
└── 03/  ← Paprastinimas + operator<<
```

---

## 1️⃣ **1 žingsnis: Basic Trupmena + Išimtys**

### **Trupmena.h:**

```cpp
#ifndef TRUPMENA_H
#define TRUPMENA_H

#include <stdexcept>  // invalid_argument

class Trupmena {
private:
    int skaitiklis;
    int vardiklis;
    
public:
    // Konstruktorius (su validacija!)
    Trupmena(int s, int v);
    
    // Getters
    int gautiSkaitikli() const;
    int gautiVardikli() const;
    
    // Spausdinimas
    void spausdinti() const;
};

#endif
```

### **Pedagoginės pastabos:**
- ✅ `#include <stdexcept>` - **būtinas** išimtims!
- ✅ `invalid_argument` - standartinė C++ išimtis
- ⚠️ Dažna klaida: pamiršti `#include <stdexcept>`

---

### **Trupmena.cpp:**

```cpp
#include "Trupmena.h"
#include <iostream>

using namespace std;

// Konstruktorius su validacija
Trupmena::Trupmena(int s, int v) {
    // VALIDACIJA: Vardiklis negali būti 0!
    if (v == 0) {
        throw invalid_argument("Vardiklis negali būti 0!");
    }
    
    skaitiklis = s;
    vardiklis = v;
}

// Getters
int Trupmena::gautiSkaitikli() const {
    return skaitiklis;
}

int Trupmena::gautiVardikli() const {
    return vardiklis;
}

// Spausdinimas
void Trupmena::spausdinti() const {
    cout << skaitiklis << "/" << vardiklis;
}
```

### **Pedagoginės pastabos:**
- ✅ `throw invalid_argument("...")` - **mesti** išimtį
- ✅ Konstruktorius - geriausias vieta validacijai
- 💡 **Išimtis nutraukia** konstruktorių → objektas nesukuriamas!

---

### **main.cpp:**

```cpp
#include <iostream>
#include "Trupmena.h"

using namespace std;

int main() {
    cout << "=== U5 Žingsnis 1: Basic + Exceptions ===\n" << endl;
    
    // TESTAS 1: Teisinga trupmena
    cout << "--- Testas 1: Teisinga trupmena ---" << endl;
    try {
        Trupmena a(1, 2);
        cout << "Sukurta trupmena: ";
        a.spausdinti();
        cout << endl;
    } catch (invalid_argument& e) {
        cout << "KLAIDA: " << e.what() << endl;
    }
    
    // TESTAS 2: Blogas vardiklis (0)
    cout << "\n--- Testas 2: Blogas vardiklis (0) ---" << endl;
    try {
        Trupmena b(1, 0);  // Turi mesti išimtį!
        cout << "Sukurta trupmena: ";
        b.spausdinti();
        cout << endl;
    } catch (invalid_argument& e) {
        cout << "Sugauta išimtis: " << e.what() << endl;
    }
    
    // TESTAS 3: Kelios trupmenos
    cout << "\n--- Testas 3: Kelios trupmenos ---" << endl;
    try {
        Trupmena x(3, 4);
        Trupmena y(5, 6);
        
        cout << "x = ";
        x.spausdinti();
        cout << endl;
        
        cout << "y = ";
        y.spausdinti();
        cout << endl;
    } catch (invalid_argument& e) {
        cout << "KLAIDA: " << e.what() << endl;
    }
    
    cout << "\n=== Programa tęsiasi po išimčių ===" << endl;
    return 0;
}
```

### **Išvestis:**

```
=== U5 Žingsnis 1: Basic + Exceptions ===

--- Testas 1: Teisinga trupmena ---
Sukurta trupmena: 1/2

--- Testas 2: Blogas vardiklis (0) ---
Sugauta išimtis: Vardiklis negali būti 0!

--- Testas 3: Kelios trupmenos ---
x = 3/4
y = 5/6

=== Programa tęsiasi po išimčių ===
```

### **Pedagoginės pastabos:**
- ✅ `try { ... } catch (invalid_argument& e) { ... }` - gaudymo sintaksė
- ✅ `e.what()` - grąžina klaidos pranešimą
- ✅ Programa **nesustoja** po išimties (jei catch'inama!)
- 💡 **Be try-catch** - programa **kris** (unhandled exception)

---

### **Makefile:**

```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Trupmena.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp Trupmena.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Trupmena.o: Trupmena.cpp Trupmena.h
	$(CXX) $(CXXFLAGS) -c Trupmena.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

---

## 2️⃣ **2 žingsnis: Operatoriai (+, +=, <, ==)**

### **Trupmena.h (papildymas):**

```cpp
#ifndef TRUPMENA_H
#define TRUPMENA_H

#include <stdexcept>

class Trupmena {
private:
    int skaitiklis;
    int vardiklis;
    
public:
    Trupmena(int s, int v);
    
    int gautiSkaitikli() const;
    int gautiVardikli() const;
    void spausdinti() const;
    
    // NAUJI: Operatoriai
    Trupmena operator+(const Trupmena& kita) const;
    Trupmena& operator+=(const Trupmena& kita);
    bool operator<(const Trupmena& kita) const;
    bool operator==(const Trupmena& kita) const;
};

#endif
```

---

### **Trupmena.cpp (papildymas):**

```cpp
// ... (ankstesni metodai) ...

// operator+ (sudėtis)
Trupmena Trupmena::operator+(const Trupmena& kita) const {
    // a/b + c/d = (a*d + c*b) / (b*d)
    int naujasSk = skaitiklis * kita.vardiklis + kita.skaitiklis * vardiklis;
    int naujasVard = vardiklis * kita.vardiklis;
    
    return Trupmena(naujasSk, naujasVard);
}

// operator+= (compound assignment)
Trupmena& Trupmena::operator+=(const Trupmena& kita) {
    // Naudojame operator+
    *this = *this + kita;
    return *this;
}

// operator< (mažiau)
bool Trupmena::operator<(const Trupmena& kita) const {
    // a/b < c/d  ⟺  a*d < c*b
    return (skaitiklis * kita.vardiklis) < (kita.skaitiklis * vardiklis);
}

// operator== (lygybė)
bool Trupmena::operator==(const Trupmena& kita) const {
    // a/b == c/d  ⟺  a*d == c*b
    return (skaitiklis * kita.vardiklis) == (kita.skaitiklis * vardiklis);
}
```

### **Pedagoginės pastabos:**
- ✅ `operator+` - **const** (nekeičia objekto)
- ✅ `operator+=` - **ne const**, grąžina `&` (nuorodą)
- ✅ Palyginimo operatoriai - **const**, grąžina `bool`
- 💡 **Kryžminis dauginimas** - išvengia division by zero
- ⚠️ Dažna klaida: `operator+=` grąžina `Trupmena` (ne `&`)

---

### **main.cpp (testas):**

```cpp
#include <iostream>
#include "Trupmena.h"

using namespace std;

int main() {
    cout << "=== U5 Žingsnis 2: Operatoriai ===\n" << endl;
    
    try {
        // TESTAS 1: operator+
        cout << "--- Testas 1: operator+ ---" << endl;
        Trupmena a(1, 2);  // 1/2
        Trupmena b(1, 4);  // 1/4
        
        Trupmena c = a + b;  // operator+ !
        
        cout << "a = ";
        a.spausdinti();
        cout << endl;
        
        cout << "b = ";
        b.spausdinti();
        cout << endl;
        
        cout << "a + b = ";
        c.spausdinti();
        cout << " (kol kas nepaprastinta)" << endl;
        
        // TESTAS 2: operator+=
        cout << "\n--- Testas 2: operator+= ---" << endl;
        Trupmena x(1, 3);  // 1/3
        cout << "Pradžioje x = ";
        x.spausdinti();
        cout << endl;
        
        Trupmena y(1, 6);  // 1/6
        x += y;  // operator+= !
        
        cout << "Po x += 1/6, x = ";
        x.spausdinti();
        cout << endl;
        
        // TESTAS 3: operator<
        cout << "\n--- Testas 3: operator< ---" << endl;
        Trupmena p(1, 3);
        Trupmena q(1, 2);
        
        cout << "1/3 < 1/2? " << (p < q ? "Taip" : "Ne") << endl;
        cout << "1/2 < 1/3? " << (q < p ? "Taip" : "Ne") << endl;
        
        // TESTAS 4: operator==
        cout << "\n--- Testas 4: operator== ---" << endl;
        Trupmena r(1, 2);
        Trupmena s(2, 4);  // Tas pats kaip 1/2
        Trupmena t(1, 3);  // Skirtingas
        
        cout << "1/2 == 2/4? " << (r == s ? "Taip" : "Ne") << endl;
        cout << "1/2 == 1/3? " << (r == t ? "Taip" : "Ne") << endl;
        
    } catch (invalid_argument& e) {
        cout << "KLAIDA: " << e.what() << endl;
    }
    
    return 0;
}
```

### **Išvestis:**

```
=== U5 Žingsnis 2: Operatoriai ===

--- Testas 1: operator+ ---
a = 1/2
b = 1/4
a + b = 6/8 (kol kas nepaprastinta)

--- Testas 2: operator+= ---
Pradžioje x = 1/3
Po x += 1/6, x = 3/6

--- Testas 3: operator< ---
1/3 < 1/2? Taip
1/2 < 1/3? Ne

--- Testas 4: operator== ---
1/2 == 2/4? Taip  ← Kryžminis dauginimas veikia!
1/2 == 1/3? Ne
```

---

## 3️⃣ **3 žingsnis: Paprastinimas + operator<<**

### **Trupmena.h (galutinė versija):**

```cpp
#ifndef TRUPMENA_H
#define TRUPMENA_H

#include <stdexcept>
#include <iostream>

class Trupmena {
private:
    int skaitiklis;
    int vardiklis;
    
    // Private helper
    int dbd(int a, int b) const;  // Didžiausias bendrasis daliklis
    
public:
    Trupmena(int s, int v);
    
    int gautiSkaitikli() const;
    int gautiVardikli() const;
    
    void paprastinti();  // NAUJAS
    
    // Operatoriai
    Trupmena operator+(const Trupmena& kita) const;
    Trupmena& operator+=(const Trupmena& kita);
    bool operator<(const Trupmena& kita) const;
    bool operator==(const Trupmena& kita) const;
    
    // Friend funkcija operator<< (UŽ klasės ribų!)
    friend std::ostream& operator<<(std::ostream& out, const Trupmena& t);
};

#endif
```

### **Pedagoginės pastabos:**
- ✅ `dbd()` - **private** helper (internal)
- ✅ `friend ostream& operator<<(...)` - **friend** deklaracija
- ✅ `std::ostream` - visas vardas (arba `using`)

---

### **Trupmena.cpp (galutinė versija):**

```cpp
#include "Trupmena.h"
#include <cmath>  // abs()

using namespace std;

// Private: DBD (Euklido algoritmas)
int Trupmena::dbd(int a, int b) const {
    a = abs(a);  // Absoliučios reikšmės
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

// Public: Paprastinimas
void Trupmena::paprastinti() {
    int d = dbd(skaitiklis, vardiklis);
    
    if (d > 1) {
        skaitiklis /= d;
        vardiklis /= d;
    }
}

// Konstruktorius (su automatiniu paprastinimu!)
Trupmena::Trupmena(int s, int v) {
    if (v == 0) {
        throw invalid_argument("Vardiklis negali būti 0!");
    }
    
    skaitiklis = s;
    vardiklis = v;
    
    paprastinti();  // Automatinis paprastinimas!
}

// Getters (tie patys)
int Trupmena::gautiSkaitikli() const {
    return skaitiklis;
}

int Trupmena::gautiVardikli() const {
    return vardiklis;
}

// Operatoriai (tie patys)
Trupmena Trupmena::operator+(const Trupmena& kita) const {
    int naujasSk = skaitiklis * kita.vardiklis + kita.skaitiklis * vardiklis;
    int naujasVard = vardiklis * kita.vardiklis;
    return Trupmena(naujasSk, naujasVard);  // Automatiškai paprastins!
}

Trupmena& Trupmena::operator+=(const Trupmena& kita) {
    *this = *this + kita;
    return *this;
}

bool Trupmena::operator<(const Trupmena& kita) const {
    return (skaitiklis * kita.vardiklis) < (kita.skaitiklis * vardiklis);
}

bool Trupmena::operator==(const Trupmena& kita) const {
    return (skaitiklis * kita.vardiklis) == (kita.skaitiklis * vardiklis);
}

// NAUJAS: operator<< (UŽ klasės ribų, friend!)
ostream& operator<<(ostream& out, const Trupmena& t) {
    out << t.skaitiklis << "/" << t.vardiklis;
    return out;
}
```

### **Pedagoginės pastabos:**
- ✅ `dbd()` - Euklido algoritmas (iteratyvus)
- ✅ `abs()` - absoliučios reikšmės (`#include <cmath>`)
- ✅ `paprastinti()` kviečiamas **konstruktoriuje** (automatinis!)
- ✅ `operator<<` - **už klasės ribų** (ne `Trupmena::operator<<`)
- ✅ Grąžina `ostream&` (chain'inimui: `cout << a << b`)
- ⚠️ **Kritinė klaida**: `ostream& Trupmena::operator<<(...)` - BLOGAI!

---

### **main.cpp (galutinis testas):**

```cpp
#include <iostream>
#include "Trupmena.h"

using namespace std;

int main() {
    cout << "=== U5 Žingsnis 3: Paprastinimas + operator<< ===\n" << endl;
    
    try {
        // TESTAS 1: Automatinis paprastinimas
        cout << "--- Testas 1: Automatinis paprastinimas ---" << endl;
        Trupmena a(6, 8);  // Turėtų paprastinti → 3/4
        cout << "6/8 = " << a << " (paprastinta)" << endl;  // operator<< !
        
        Trupmena b(10, 15);  // → 2/3
        cout << "10/15 = " << b << endl;
        
        // TESTAS 2: Sudėtis su paprastinimu
        cout << "\n--- Testas 2: Sudėtis su paprastinimu ---" << endl;
        Trupmena x(1, 2);
        Trupmena y(1, 4);
        Trupmena z = x + y;
        cout << "1/2 + 1/4 = " << z << " (automatiškai paprastinta)" << endl;
        
        // TESTAS 3: Palyginimas po paprastinimo
        cout << "\n--- Testas 3: Palyginimas po paprastinimo ---" << endl;
        Trupmena p(1, 2);
        Trupmena q(2, 4);  // Paprastins → 1/2
        
        cout << "p = " << p << endl;
        cout << "q = " << q << " (iš 2/4)" << endl;
        cout << "p == q? " << (p == q ? "Taip" : "Ne") << endl;
        
        // TESTAS 4: Compound assignment
        cout << "\n--- Testas 4: Compound assignment ---" << endl;
        Trupmena m(1, 3);
        Trupmena n(1, 6);
        
        cout << "m = " << m << endl;
        cout << "n = " << n << endl;
        
        m += n;  // 1/3 + 1/6 = 1/2
        cout << "Po m += n, m = " << m << endl;
        
        // TESTAS 5: Chain output
        cout << "\n--- Testas 5: Chain output ---" << endl;
        cout << "Kelios trupmenos: " << Trupmena(1, 2) << ", " 
             << Trupmena(2, 3) << ", " << Trupmena(3, 4) << endl;
        
    } catch (invalid_argument& e) {
        cout << "KLAIDA: " << e.what() << endl;
    }
    
    return 0;
}
```

### **Išvestis:**

```
=== U5 Žingsnis 3: Paprastinimas + operator<< ===

--- Testas 1: Automatinis paprastinimas ---
6/8 = 3/4 (paprastinta)
10/15 = 2/3

--- Testas 2: Sudėtis su paprastinimu ---
1/2 + 1/4 = 3/4 (automatiškai paprastinta)

--- Testas 3: Palyginimas po paprastinimo ---
p = 1/2
q = 1/2 (iš 2/4)
p == q? Taip

--- Testas 4: Compound assignment ---
m = 1/3
n = 1/6
Po m += n, m = 1/2

--- Testas 5: Chain output ---
Kelios trupmenos: 1/2, 2/3, 3/4
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| Pamiršo `#include <stdexcept>` | ⭐⭐⭐⭐⭐ | Compiler error: `invalid_argument` unknown |
| `operator<<` kaip metodas (ne friend) | ⭐⭐⭐⭐⭐ | Compiler error: prieiga prie private |
| Pamiršo `return out` operator<< | ⭐⭐⭐⭐ | Chain neveikia: `cout << a << b` |
| `operator+=` grąžina `Trupmena` (ne `&`) | ⭐⭐⭐ | Neefektyvu, chain neveiks |
| DBD be `abs()` | ⭐⭐⭐ | Blogai su neigiamais skaičiais |
| Try-catch sintaksė (`;` vietoj `{`) | ⭐⭐ | Compiler error |

---

### **Diskusijos taškai:**

1. **Išimtys vs error codes:**
   - Išimtys: lengviau skaityti, nepraleisi klaidos
   - Error codes: senesnis stilius, manual checking

2. **Friend funkcijos:**
   - Breaks encapsulation (trade-off!)
   - Alternatyva: getters (bet verbose: `out << t.gautiSkaitikli()`)

3. **Operatorių konvencijos:**
   - Member vs non-member (kada kuris?)
   - `operator+` - const, `operator+=` - ne const

4. **DBD algoritmas:**
   - Euklidas: elegantiška, efektyvu (O(log n))
   - Iteratyvus vs rekursyvus

5. **Automatinis paprastinimas:**
   - Trade-off: efektyvumas vs paprastumas
   - Konstruktoriuje vs po operacijų

---

### **Praplėtimai stipriesiems:**

1. **Daugiau operatorių:**
   ```cpp
   Trupmena operator-(const Trupmena& kita) const;  // Atimtis
   Trupmena operator*(const Trupmena& kita) const;  // Daugyba
   Trupmena operator/(const Trupmena& kita) const;  // Dalyba
   ```

2. **Išimtys dalyba iš 0:**
   ```cpp
   Trupmena operator/(const Trupmena& kita) const {
       if (kita.skaitiklis == 0) {
           throw invalid_argument("Dalyba iš 0!");
       }
       // ...
   }
   ```

3. **Konvertavimas į double:**
   ```cpp
   operator double() const {
       return static_cast<double>(skaitiklis) / vardiklis;
   }
   ```

4. **Neigiamos trupmenos:**
   ```cpp
   // Normalizuoti: neigiamas ženklas tik skaitiklyje
   if (vardiklis < 0) {
       skaitiklis = -skaitiklis;
       vardiklis = -vardiklis;
   }
   ```

5. **operator>>** (įvestis):
   ```cpp
   friend istream& operator>>(istream& in, Trupmena& t);
   ```

---

## 💡 **Exception handling demonstracija**

### **Testas be try-catch (programa krinta):**

```cpp
int main() {
    Trupmena a(1, 0);  // CRASH! (unhandled exception)
    cout << "Ši eilutė NIEKADA nebus pasiekta" << endl;
    return 0;
}
```

**Išvestis:**
```
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Vardiklis negali būti 0!
Aborted (core dumped)
```

### **Testas su try-catch (programa tęsiasi):**

```cpp
int main() {
    try {
        Trupmena a(1, 0);  // Klaida!
    } catch (invalid_argument& e) {
        cout << "Sugauta: " << e.what() << endl;
    }
    
    cout << "Programa tęsiasi!" << endl;  // ← Pasiekiama!
    return 0;
}
```

**Išvestis:**
```
Sugauta: Vardiklis negali būti 0!
Programa tęsiasi!
```

---

**Sėkmės dėstant!** 🎓
