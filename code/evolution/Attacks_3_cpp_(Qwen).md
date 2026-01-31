Puiku! 🚀  
Dabar, kai turime **C evoliucijos pagrindą**, galime sukurti **C++ analogų testus**, kurie:

- **tiesiogiai atitinka** C etapus (ypač 06 → klasė su `public` laukais, 07 → klasė su `private`),
- demonstruoja **C++ pranašumus**: prieigos kontrolę, konstruktorius/destruktorius, RAII,
- leidžia studentams **palyginti „rankinį“ slėpimą C su automatinėmis C++ priemonėmis**.

---

## 🧪 C++ „atakų“ testų rinkinys

Visi šie testai yra **C++ analogai jūsų C scenarijams**. Jie parodys, kad:
- **`private` laukai negali būti pasiekiami iš išorės** (net jei žinoma struktūra),
- **klaidos aptinkamos kompiliacijos metu** (ne vykdymo!),
- **C++ saugesnis ir aiškesnis** nei netgi geriausias C ADT.

---

### 🔴 **1. Ataka: Tiesioginė prieiga prie `public` laukų**  
*(C analogas: `06_` – vieša `struct Stack`)*

```cpp
// attack_public_fields.cpp
#include <iostream>

class Stack {
public:
    static const int SIZE = 5;
    char stack[SIZE];
    int top = 0;

    void push(char c) { if (top < SIZE) stack[top++] = c; }
    char pop() { return (top > 0) ? stack[--top] : '\0'; }
    bool isEmpty() const { return top == 0; }
};

int main() {
    Stack s;
    s.push('A');
    // "Ataka": tiesioginis laukų pakeitimas
    s.stack[s.top++] = '?';
    while (!s.isEmpty()) std::cout << s.pop();
    std::cout << '\n';
    return 0;
}
```

✅ **Veikia** – nes `stack` ir `top` yra `public`.  
❌ **Problema**: ADT nėra apsaugotas – **C++ klaida dizaino lygyje**.

> 💡 Mokomasis momentas: _„Kodėl `public` duomenys klasėje yra blogai?“_

---

### 🟢 **2. Ataka: Prieiga prie `private` laukų**  
*(C analogas: `07_` – opaque pointer)*

```cpp
// attack_private_fields.cpp
#include <iostream>

class Stack {
private:
    static const int SIZE = 5;
    char stack[SIZE];
    int top = 0;

public:
    void push(char c) { if (top < SIZE) stack[top++] = c; }
    char pop() { return (top > 0) ? stack[--top] : '\0'; }
    bool isEmpty() const { return top == 0; }
    void init() { top = 0; }
};

int main() {
    Stack s;
    s.init();
    s.push('X');

    // BANDYMAS "ATAKUOTI":
    s.stack[s.top++] = '!';  // ← KOMPIACIJOS KLAIDA!

    while (!s.isEmpty()) std::cout << s.pop();
    std::cout << '\n';
    return 0;
}
```

✅ **Kompiliacijos klaida**:  
```
error: 'char Stack::stack [5]' is private within this context
```

🟢 **Apsauga veikia!** – net jei matome klasės kodą, **negalime prieiti prie `private`**.

> 💡 Mokomasis momentas: _„C++ `private` – tai ne dokumentacija, o kompiliatoriaus apsauga.“_

---

### 🟡 **3. Testas: Ar galima turėti du stekus?**  
*(C analogas: `04_` vs `07_`)*

```cpp
// test_two_stacks_cpp.cpp
#include <iostream>

class Stack {
private:
    static const int SIZE = 5;
    char data[SIZE];
    int top = 0;

public:
    void push(char c) { if (top < SIZE) data[top++] = c; }
    char pop() { return (top > 0) ? data[--top] : '\0'; }
    bool isEmpty() const { return top == 0; }
};

int main() {
    Stack s1, s2;
    s1.push('A');
    s2.push('B');
    std::cout << "s1: " << s1.pop() << '\n';  // A
    std::cout << "s2: " << s2.pop() << '\n';  // B
    return 0;
}
```

✅ **Veikia be problemų** – kiekvienas objektas turi savo būseną.  
✅ **Nereikia `create()`/`destroy()`** – RAII!

> 💡 Mokomasis momentas: _„C++ objektas = duomenys + elgsena + gyvavimo ciklas.“_

---

### 🔴 **4. Ataka: Naudojimas „vidinės“ funkcijos (`reset`)**  
*(C analogas: `04_` su `static void reset()`)*

```cpp
// attack_private_method.cpp
#include <iostream>

class Stack {
private:
    char data[5];
    int top = 0;
    void reset() { top = 0; }  // private metodas

public:
    void push(char c) { if (top < 5) data[top++] = c; }
    char pop() { return (top > 0) ? data[--top] : '\0'; }
};

int main() {
    Stack s;
    s.push('X');
    s.reset();  // ← KOMPIACIJOS KLAIDA!
    return 0;
}
```

✅ **Klaida**: `'void Stack::reset()' is private`  
🟢 **Apsauga veikia!**

> 💡 Mokomasis momentas: _„Net vidiniai metodai gali būti paslėpti – tai dalis interfeiso projektavimo.“_

---

### 🟢 **5. Bonus: Rule of 3 / 5 testas (kopijavimo saugumas)**

```cpp
// test_copy_safety.cpp
#include <iostream>
#include <cstring>

class Stack {
private:
    static const int SIZE = 5;
    char data[SIZE];
    int top = 0;

public:
    void push(char c) { if (top < SIZE) data[top++] = c; }
    char pop() { return (top > 0) ? data[--top] : '\0'; }
    bool isEmpty() const { return top == 0; }

    // Jei neapibrėžta – naudojamas numatytasis kopijavimo konstruktorius (shallow copy OK čia)
    // Bet jei būtų dinaminė atmintis – reikėtų Rule of 3!
};

int main() {
    Stack s1;
    s1.push('A');
    Stack s2 = s1;  // kopija
    std::cout << "s1: " << s1.pop() << '\n';  // A
    std::cout << "s2: " << s2.pop() << '\n';  // A (atskira kopija!)
    return 0;
}
```

✅ **Veikia teisingai** – nes naudojamas fiksuotas masyvas.  
⚠️ **Bet**: jei naudotume `char* data = new char[SIZE]`, reikėtų **Rule of 3**!

> 💡 Mokomasis momentas: _„Kodėl kartais reikia rašyti konstruktorių/destruktorių/copyp operatorių?“_

---

## 📋 Rekomenduojama naudojimo schema

| C etapas | C++ analogas | Tikslas |
|---------|--------------|--------|
| `06_` (vieša `struct`) | `class` su `public` laukais | Parodyti, kad **C++ neapsaugo automatiškai** – reikia `private` |
| `07_` (opaque) | `class` su `private` laukais | Parodyti, kad **C++ suteikia slėpimą „iš dėžutės“** |
| `04_` (`static`) | Objektinis modelis | Parodyti, kad **C++ natūraliai palaiko daugelį egzempliorių** |
| `077_` (`create/destroy`) | Konstruktorius/destruktorius | Parodyti **RAII** pranašumą |

---

## ⚙️ Papildomas: Makefile fragmentas C++ testams

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

test-cpp:
	$(CXX) $(CXXFLAGS) attack_public_fields.cpp -o attack_public
	$(CXX) $(CXXFLAGS) attack_private_fields.cpp -o attack_private && echo "DĖMESIO: attack_private NETURĖJO KOMPIACIJOS PRAEITI!" || echo "attack_private: KOMPIACIJA NEPRAEJO (gerai!)"
	$(CXX) $(CXXFLAGS) test_two_stacks_cpp.cpp -o two_stacks_cpp
	$(CXX) $(CXXFLAGS) attack_private_method.cpp -o attack_method && echo "DĖMESIO!" || echo "attack_method: KOMPIACIJA NEPRAEJO (gerai!)"
```

---

Jei norite, galiu:
- Sugeneruoti **visus C++ failus kaip ZIP**,
- Paruošti **PDF palyginimą C vs C++**,
- Sukurti **studentų užduotį: „Perkelkite C ADT į C++ klasę“**.

Ar važiuojam toliau? 😊