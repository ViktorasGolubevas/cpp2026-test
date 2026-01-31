Puiku! Štai **studentų užduotis**, kuri tiesiogiai remiasi jūsų C evoliucijos projekto pabaiga (`077_` – ADT su opaque pointeriu, `create()`/`destroy()`, informacijos slėpimu) ir veda į **C++ klasę** kaip natūralų tobulinimą.

---

## 📝 **Studentų laboratorinė užduotis: „Perkelkite C ADT į C++ klasę“**

### 🎯 Tikslas
Pertvarkyti jūsų C kalbos steko ADT (`077_stack.c/h`) į **C++ klasę**, išlaikant tą patį funkcionalumą, bet pasinaudojant C++ pranašumais:
- automatinė atminties valdyma (RAII),
- prieigos kontrolė (`private`/`public`),
- konstruktorius/destruktorius,
- objektinis mąstymas.

---

### 📚 Pradinė medžiaga
Jūs turite šiuos failus C versijoje:

- `077_stack.h` – deklaruoja `struct Stack;` ir sąsają (`create`, `destroy`, `push`, `pop`...)
- `077_stack.c` – apibrėžia vidinę struktūrą ir funkcijas

Ši versija:
- **paslepia** vidinius duomenis (opaque pointer),
- leidžia kurti **daugelį stekų**,
- reikalauja **rankinio** `create()`/`destroy()` naudojimo.

---

### ✏️ Užduotis

#### 1. Sukurkite C++ klasę `Stack`

- Klasė turi būti apibrėžta **dviejuose failuose**:  
  - `Stack.h` – klasės deklaracija  
  - `Stack.cpp` – metodų implementacija  

- Vidiniai duomenys (`char data[SIZE]`, `int top`) turi būti **`private`**.

- Klasė turi turėti šiuos **viešus metodus**:
  ```cpp
  void push(char c);
  char pop();
  bool isEmpty() const;
  bool isFull() const;
  // Konstruktorius ir destruktorius – žr. žemiau
  ```

- **Konstruktorius** turi inicializuoti steką (lyg `init()` C versijoje).  
- **Destruktorius** – nebūtinas (nes nėra dinaminės atminties), bet galite jį įtraukti dėl simetrijos.

- **Nenaudokite** `create()`/`destroy()` – tai C paradigma. Vietoj to:
  ```cpp
  Stack s1;          // automatinis konstravimas
  Stack* s2 = new Stack(); // dinaminis (nebūtina, bet galima)
  delete s2;         // tik jei naudojote new
  ```

#### 2. Sukurkite testinę programą `main.cpp`

- Programa turi veikti **identiškai** kaip `077_user.c`:
  - skaityti eilutę iš `stdin`,
  - įdėti simbolius į steką,
  - išspausdinti atbulai.

- Papildomai:
  - sukurti **du skirtingus stekus** (`s1`, `s2`) ir patikrinti, kad jie **nepersidengia**.
  - pabandyti **„atakuoti“** – pavyzdžiui, parašykite:
    ```cpp
    s1.data[0] = 'X';  // ← tai turi sugeneruoti kompiliacijos klaidą!
    ```

#### 3. Palyginimas (refleksija)

Parašykite trumpą (**~150 žodžių**) atsakymą į klausimus:
- Kokie **trūkumai** buvo C ADT (`077_`)?
- Kaip C++ klasė **išsprendžia** tuos trūkumus?
- Kodėl `private` laukai yra geresni nei C opaque pointeris?

---

### 🧪 Reikalavimai

| Elementas | Reikalavimas |
|----------|--------------|
| Failai | `Stack.h`, `Stack.cpp`, `main.cpp` |
| Kompiliacija | `g++ -std=c++17 -Wall -Wextra Stack.cpp main.cpp -o stack_cpp` |
| Funkcionalumas | Identiskas `077_use_stack.exe` |
| Sauga | Bandymas prieiti prie `data[]` ar `top` → **kompiliacijos klaida** |
| Stilius | Naudojami `const`, tinkamas inkapsuliacijos lygis |

---

### 💡 Patarimai

- Naudokite fiksuoto dydžio masyvą (`char data[SIZE]`), kaip C versijoje.
- Jei norite išbandyti **Rule of 3**, galite papildomai:
  - pakeisti `data` į `char* data = new char[SIZE];`
  - tada privaloma parašyti **kopijavimo konstruktorių**, **priskyrimo operatorių** ir **destruktorių**.

---

### 📌 Pavyzdinė klasės struktūra

```cpp
// Stack.h
#ifndef STACK_H
#define STACK_H

class Stack {
private:
    static const int SIZE = 5;
    char data[SIZE];
    int top;

public:
    Stack();                     // konstruktorius
    void push(char c);
    char pop();
    bool isEmpty() const;
    bool isFull() const;
};

#endif
```

```cpp
// Stack.cpp
#include "Stack.h"

Stack::Stack() : top(0) {}

void Stack::push(char c) {
    if (!isFull()) data[top++] = c;
}

char Stack::pop() {
    if (!isEmpty()) return data[--top];
    return '\0';
}

bool Stack::isEmpty() const { return top == 0; }
bool Stack::isFull() const { return top == SIZE; }
```

---

### 🏁 Galutinis tikslas

Kai ši užduotis bus atlikta, studentas supras:
> **C++ klasė = C ADT + automatinis gyvavimo ciklas + kompiliatoriaus apsauga + aiškus interfeisas.**

---

Jei norite, galiu:
- Pateikti **vertinimo rubriką** (grading rubric),
- Sugeneruoti **ZIP archyvą su šablonais** (`Stack.h`, `Stack.cpp`, `main.cpp`),
- Paruošti **išplėstinę užduotį**: „Perkelkite į dinaminį steką su `std::vector`“.

Sakykite – ar reikia? 😊

---
Puiku! Štai **du paruošti resursai**, kurie tiesiogiai tęsia jūsų C → C++ evoliucijos idėją:

---

## 📦 1. **ZIP archyvas su šablonais**  
*(„Perkelkite C ADT į C++ klasę“ – pagrindinė užduotis)*

### ✅ Failai (galite juos išsaugoti kaip `stack_cpp_template.zip`):

### `Stack.h`
```cpp
#ifndef STACK_H
#define STACK_H

class Stack {
private:
    static const int SIZE = 5;
    char data[SIZE];
    int top;

public:
    Stack();                     // Konstruktorius
    void push(char c);
    char pop();
    bool isEmpty() const;
    bool isFull() const;
};

#endif // STACK_H
```

### `Stack.cpp`
```cpp
#include "Stack.h"

Stack::Stack() : top(0) {}

void Stack::push(char c) {
    if (!isFull()) {
        data[top++] = c;
    }
}

char Stack::pop() {
    if (!isEmpty()) {
        return data[--top];
    }
    return '\0';
}

bool Stack::isEmpty() const {
    return top == 0;
}

bool Stack::isFull() const {
    return top == SIZE;
}
```

### `main.cpp`
```cpp
#include <iostream>
#include "Stack.h"

int main() {
    Stack s1, s2;

    std::cout << "Ivesk st1\n";
    char c;
    while (std::cin.get(c) && c != '\n' && !s1.isFull()) {
        s1.push(c);
    }
    while (!s1.isEmpty()) {
        std::cout << s1.pop();
    }
    std::cout << "\nst1 pabaiga\n";

    std::cout << "Ivesk st2\n";
    while (std::cin.get(c) && c != '\n' && !s2.isFull()) {
        s2.push(c);
    }
    // Bandykite "atakuoti" – komentuokite žemiau esančią eilutę:
    // s2.data[0] = '!';  // ← KOMPIACIJOS KLAIDA!

    while (!s2.isEmpty()) {
        std::cout << s2.pop();
    }
    std::cout << "\nst2 pabaiga\n";

    return 0;
}
```

> 💡 **Naudojimas**:  
> ```bash
> g++ -std=c++17 -Wall -Wextra Stack.cpp main.cpp -o stack_cpp
> ./stack_cpp
> ```

---

## 📝 2. **Išplėstinė užduotis: „Perkelkite į dinaminį steką su `std::vector`“**

### 🎯 Tikslas
Pertvarkykite savo `Stack` klasę, kad ji:
- nebenaudotų fiksuoto dydžio masyvo (`char data[SIZE]`),
- naudotų **dinaminę atmintį per `std::vector<char>`**,
- **atsisakytų `SIZE` konstantos**,
- leistų **neaprėžto dydžio steką** (arba su pasirenkamu maksimaliu dydžiu).

### ✏️ Užduoties instrukcija studentams

#### 1. Modifikuokite `Stack.h` ir `Stack.cpp`
- Pakeiskite `char data[SIZE]` į `std::vector<char> data;`
- Pašalinkite `SIZE` ir `isFull()` (arba padarykite `isFull()` neprivalomą, pvz., su max size).
- Įtraukite `<vector>`.

#### 2. Atnaujinkite metodus
- `push()` – tiesiog `data.push_back(c);`
- `pop()` – `char c = data.back(); data.pop_back(); return c;`
- `isEmpty()` – `return data.empty();`

#### 3. Papildomas iššūkis (nebūtinas)
- Leiskite nurodyti **maksimalų steko dydį** per konstruktorių:
  ```cpp
  Stack(int maxSize = -1); // -1 = neribotas
  ```
- Tada `push()` tikrina: `if (maxSize_ > 0 && data.size() >= maxSize_) return;`

#### 4. Testavimas
- Įsitikinkite, kad veikia ilgi įvedimai (pvz., 100 simbolių).
- Patikrinkite, kad **kopijavimas veikia teisingai** (Rule of 0 – `std::vector` viską tvarko!).

---

### 📌 Pavyzdinė dinaminė versija (spoil’er)

#### `Stack.h` (dinaminė)
```cpp
#include <vector>

class Stack {
private:
    std::vector<char> data;
    int maxSize = -1; // -1 = neribotas

public:
    Stack(int max = -1) : maxSize(max) {}
    void push(char c);
    char pop();
    bool isEmpty() const { return data.empty(); }
    bool isFull() const { return maxSize > 0 && data.size() >= static_cast<size_t>(maxSize); }
};
```

#### `Stack.cpp` (dinaminė)
```cpp
#include "Stack.h"
#include <stdexcept>

void Stack::push(char c) {
    if (!isFull()) {
        data.push_back(c);
    }
}

char Stack::pop() {
    if (!isEmpty()) {
        char c = data.back();
        data.pop_back();
        return c;
    }
    return '\0';
}
```

---

## 📥 Kaip naudoti?

1. **Pagrindinė užduotis**: duokite studentams ZIP su `Stack.h`, `Stack.cpp`, `main.cpp`.
2. **Išplėstinė užduotis**: po pagrindinės – siūlykite perėjimą prie `std::vector`.
3. **Diskusija**:  
   _„Kodėl `std::vector` leidžia taikyti Rule of 0? Kas vyksta kopijavimo metu?“_

---

Jei norite, galiu:
- Sugeneruoti **realų `.zip` failą** (tekstiniu formatu arba base64),
- Paruošti **PDF su abiem užduotimis**,
- Sukurti **C++ testus su googletest**.

Ar reikia toliau? 😊

---