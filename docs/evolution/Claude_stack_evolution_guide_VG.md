# Stack Evolution Guide: From Monolithic Code to ADT

=== "01"
    ```c
    --8<-- "code/evolution/stack-2026/01_Running_PROGRAM/01_OK_naive/usestack.c"
    ```

=== "02"
    ```cpp
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/stack.c:1:10"
    ```

---

## 📚 Įvadas: Kodėl ADT (Abstract Data Type)?

Šis vadovas parodo **evoliucinį kelią** nuo paprasčiausio monolitinio kodo iki pilnaverčio Abstract Data Type su enkapsulacija C kalboje. Kiekvienas žingsnis atskleidžia **realias problemas** ir jų sprendimus.

**Pagrindinė idėja:** Mokymasis per klaidas - kiekviena versija rodo, KODĖL reikia sekančio žingsnio.

---

## 🎯 Mokymosi tikslai

Po šio vadovo suprasite:

- ✅ Skirtumą tarp **modulio** ir **ADT**
- ✅ **Declaration** vs **Definition** (aprašas vs apibrėžimas)
- ✅ **Information hiding** principą
- ✅ **Opaque type** techniką
- ✅ **Factory pattern** C kalboje
- ✅ C → C++ sąsajas (OOP pagrindus)

---

## Etapas 1: Naivus sprendimas - viskas vienoje programoje

### 🎯 Tikslas
Parodyti paprasčiausią steką, visa logika vienoje funkcijoje.

### 💻 Sprendimas

```c
#include <stdio.h>

#define SIZE 5

char stack[SIZE];
int top = 0;

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}

int main(void) {
    char c;
    init();
    
    while ((c = getchar()) != '\n') {
        push(c);
    }
    
    while (!isEmpty()) {
        putchar(pop());
    }
    
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 01_n_usestack.c -o 01_n_usestack
```

### ✅ Veikia
```
> 01_n_usestack.exe
123456
654321
```

### ❌ Problemos

1. **Nelankstus** - negalima pakartotinio naudojimo
2. **Globalūs kintamieji** - `stack[]` ir `top` matomi visur
3. **Tik vienas stekas** - negalima turėti kelių
4. **Nemodulinė struktūra** - visa logika vienoje vietoje

### 📖 Pamoka

> "Monolitinis kodas veikia mažoms programoms, bet nėra skalabilus ir pakartotinai naudojamas."

---

## Etapas 2: Dekompozicija į failus

### 🎯 Tikslas
Atskirti steko logiką nuo vartotojo kodo.

### 💻 Sprendimas

**02_n_stack.c** (steko implementacija):
```c
#define SIZE 5

char stack[SIZE];
int top = 0;

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}
```

**02_n_user.c** (vartotojo kodas):
```c
#include <stdio.h>
#include "02_n_stack.c"  // ⚠️ Include .c failą!

int main(void) {
    char c;
    init();
    
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    
    while (!isEmpty()) 
        putchar(pop());
    
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 02_n_user.c -o 02_n_use_stack
```

### ✅ Veikia
Kompiliuojasi ir veikia, nes `#include "02_n_stack.c"` įtraukia visą kodą.

### ❌ Blogai: Bandymas kompiliuoti atskirai

**02_nx_user.c**:
```c
#include <stdio.h>
// Nėra jokio include!

int main(void) {
    char c;
    init();  // ❌ Kas yra init()?
    while ('\n' != (c = getchar())) 
        push(c);  // ❌ Kas yra push()?
    while (!isEmpty()) 
        putchar(pop());  // ❌ Kas yra isEmpty(), pop()?
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 02_n_stack.c 02_nx_user.c -o 02_nx_use_stack
```

### ❌ Klaidos

**GCC:**
```
02_nx_user.c: In function 'main':
02_nx_user.c:6:5: warning: implicit declaration of function 'init'
02_nx_user.c:7:37: warning: implicit declaration of function 'push'
02_nx_user.c:8:13: warning: implicit declaration of function 'isEmpty'
02_nx_user.c:8:32: warning: implicit declaration of function 'pop'
```

**Clang:**
```
02_nx_user.c:6:5: error: call to undeclared function 'init'
02_nx_user.c:7:37: error: call to undeclared function 'push'
02_nx_user.c:8:13: error: call to undeclared function 'isEmpty'
02_nx_user.c:8:32: error: call to undeclared function 'pop'
4 errors generated.
```

### 📖 Pamoka

> "Kompiliatoriui reikia **deklaracijų** prieš naudojimą. GCC leidžia 'implicit declarations' (su warning), Clang - ne."

**Sprendimas:** Reikalingi **header failai** su funkcijų deklaracijomis!

---

## Etapas 3: Modulis - Header failų klaidos

### 🎯 Tikslas
Sukurti teisingą modulį su header failu. Bet pirmiausia - suprasti **dažniausias klaidas**!

### ❌ Klaida #1: Multiple definition

**03_nx_stack.h** (BLOGAI!):
```c
#define SIZE 100

char stack[SIZE];  // ❌ Apibrėžimas header'yje!
int top;           // ❌ Apibrėžimas header'yje!

void init(void);
int isEmpty(void);
int isFull(void);
void push(char c);
char pop(void);
```

**03_nx_stack.c**:
```c
#include <stdio.h>
#define SIZE 100

char stack[SIZE];  // Apibrėžimas .c faile
int top;

void init(void) { top = 0; }
int isEmpty(void) { return 0 == top; }
int isFull(void) { return SIZE == top; }
void push(char c) {
    if (!isFull()) stack[top++] = c;
}
char pop(void) {
    if (!isEmpty()) return stack[--top];
    return '\0';
}
```

**03_nx_user.c**:
```c
#include <stdio.h>
#include "03_nx_stack.h"

int main(void) {
    char c;
    init();
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    while (!isEmpty()) 
        putchar(pop());
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 03_nx_stack.c 03_nx_user.c -o 03_nx_use_stack
```

### ❌ Linker klaida

**GCC:**
```
ld.exe: multiple definition of `stack'
ld.exe: multiple definition of `top'
collect2.exe: error: ld returned 1 exit status
```

**Clang:**
```
ld: multiple definition of `stack'
ld: multiple definition of `top'
clang: error: linker command failed with exit code 1
```

### 🔍 Kodėl klaida?

1. Header'yje: `char stack[SIZE];` - tai **apibrėžimas** (definition)
2. .c faile: `char stack[SIZE];` - dar vienas **apibrėžimas**
3. Kiekvienas `.c` failas, kuris įtraukia header'į, sukuria **savo kopiją**
4. Linker'is: "Turiu 2 `stack` apibrėžimus - kurio naudoti?"

### 📖 Pamoka

> **Declaration vs Definition:**
> - **Declaration:** "Žinok, kad kažkas egzistuoja" (`extern char stack[];`)
> - **Definition:** "Sukurk atmintį daiktui" (`char stack[SIZE];`)
>
> Header'iuose - tik **deklaracijos**! Apibrėžimai - tik `.c` failuose.

---

### ❌ Klaida #2: Undefined reference

**03_ny_stack.h** (bandymas taisyti su `extern`):
```c
#define SIZE 100

extern char stack[SIZE];  // ✅ Deklaracija
extern int top;           // ✅ Deklaracija

extern void init(void);
extern int isEmpty(void);
extern int isFull(void);
extern void push(char c);
extern char pop(void);
```

**03_ny_stack.c** (bet PAMIRŠOME apibrėžti!):
```c
#include <stdio.h>
#include "03_ny_stack.h"

void init(void) {
    top = 0;  // Naudojame 'top', bet JO NĖRA!
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;  // Naudojame 'stack', bet JO NĖRA!
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}
```

### 🔧 Kompiliavimas
```bash
gcc 03_ny_stack.c 03_ny_user.c -o 03_ny_use_stack
```

### ❌ Linker klaida

```
ld.exe: undefined reference to `stack'
ld.exe: undefined reference to `top'
collect2.exe: error: ld returned 1 exit status
```

### 🔍 Kodėl klaida?

1. Header'yje: `extern char stack[SIZE];` - tik **deklaracija**
2. .c faile: **NĖRA apibrėžimo** `char stack[SIZE];`
3. Linker'is: "Žinau, kad `stack` turi egzistuoti, bet KUR jis?"

### 📖 Pamoka

> `extern` sako "tai egzistuoja **kažkur kitur**". Bet tas "kažkur kitur" turi būti **tikrai apibrėžtas**!

---

### ✅ Teisingas sprendimas

**03_stack.h**:
```c
// Tik deklaracijos
void init(void);
int isEmpty(void);
int isFull(void);
void push(char c);
char pop(void);
```

**03_stack.c**:
```c
#include "03_stack.h"

#define SIZE 5

char stack[SIZE];  // ✅ Apibrėžimas .c faile
int top;           // ✅ Apibrėžimas .c faile

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}
```

**03_user.c**:
```c
#include <stdio.h>
#include "03_stack.h"

int main(void) {
    char c;
    init();
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    while (!isEmpty()) 
        putchar(pop());
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 03_stack.c 03_user.c -o 03_use_stack
```

### ✅ Veikia!

Bet... ar tikrai **saugus**?

---

### 🔓 "Ataka" ant modulio

**03_z_user.c**:
```c
#include <stdio.h>
#include "03_stack.h"

extern char stack[];  // Galiu pasiekti globalius kintamuosius!
extern int top;

int main(void) {
    char c;
    init();
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    
    stack[top++] = '!';  // 🔓 ATAKA! Tiesioginė manipuliacija!
    
    while (!isEmpty()) 
        putchar(pop());
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 03_stack.c 03_z_user.c -o 03_z_use_stack
```

### ✅ Kompiliuojasi!

```
> 03_z_use_stack.exe
123
!321   // ← '!' buvo įterpta!
```

### 📖 Pamoka

> "Jei duomenys globalūs, jie **NEAPSAUGOTI** nuo klaidų ar piktnaudžiavimo!"
>
> Modulis ≠ Enkapsulacija

---

## Etapas 4: Information Hiding su `static`

### 🎯 Tikslas
Paslėpti steko realizacijos detales nuo išorės pasaulio.

### 💻 Sprendimas

**04_stack.h**:
```c
void init(void);
int isEmpty(void);
int isFull(void);
void push(char c);
char pop(void);
```

**04_stack.c**:
```c
#include "04_stack.h"

#define SIZE 5

static char stack[SIZE];  // ✅ PRIVATE!
static int top;           // ✅ PRIVATE!

static void reset(void) { // ✅ Helper funkcija - PRIVATE!
    top = 0;
}

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}
```

**04_user.c**:
```c
#include <stdio.h>
#include "04_stack.h"

int main(void) {
    char c;
    init();
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    while (!isEmpty()) 
        putchar(pop());
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 04_stack.c 04_user.c -o 04_use_stack
```

### ✅ Veikia!

---

### 🔒 "Ataka" NEPAVYKSTA!

**04_zx_user.c**:
```c
#include <stdio.h>
#include "04_stack.h"

extern char stack[];  // Bandau pasiekti
extern int top;
extern void reset(void);

int main(void) {
    char c;
    init();
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    
    stack[top++] = '!';  // 🔒 Bandau atakuoti
    
    while (!isEmpty()) 
        putchar(pop());
    putchar('\n');
    
    reset();  // 🔒 Bandau iškviesti privatų metodą
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 04_stack.c 04_zx_user.c -o 04_zx_use_stack
```

### ❌ Linker klaida!

```
ld.exe: undefined reference to `reset'
ld.exe: undefined reference to `stack'
ld.exe: undefined reference to `top'
collect2.exe: error: ld returned 1 exit status
```

### 🔍 Kas nutiko?

`static` C kalboje sukuria **internal linkage**:
- Kintamasis/funkcija matoma **TIK** tame `.c` faile
- Kiti failai **negali** jos pasiekti, net su `extern`
- Tai C kalbos būdas padaryti "private" duomenis

### 📖 Pamoka

> **Information Hiding principas:**
> - Paslėpti realizacijos detales
> - Eksportuoti tik **sąsają** (interface)
> - `static` ≈ `private` C++ kalboje

### ⚠️ Problema

Vis tiek **tik vienas stekas**! Negalime turėti `st1`, `st2` egzempliorių.

---

## Etapas 5: User Defined Type - 3 klaidos anatomija

### 🎯 Tikslas
Sukurti **tipą**, kad galėtume turėti kelis stekas.

---

### ❌ Bandymas #1: `static` struktūroje

**05_nx_usestack.c**:
```c
#include <stdio.h>

#define SIZE 5

struct Stack {
    static char stack[SIZE];  // ❌ Galvojame: "static narys"
    static int top;           // ❌ Kaip C++
};

void init(struct Stack st) {
    st.top = 0;
}
// ... kitos funkcijos
```

### 🔧 Kompiliavimas
```bash
gcc 05_nx_usestack.c -o 05_nx_usestack
```

### ❌ Kompiliavimo klaida

**GCC:**
```
05_nx_usestack.c:7:3: error: expected specifier-qualifier-list before 'static'
    7 |   static char stack[SIZE];
      |   ^~~~~~
```

**Clang:**
```
05_nx_usestack.c:7:3: error: type name does not allow storage class to be specified
    7 |   static char stack[SIZE];
      |   ^
```

### 🔍 Kodėl klaida?

**C kalba draudžia storage-class specifikatorius struktūros nariams!**

- `struct` aprašo **tipo šabloną**
- `static` taikomas **kintamiesiems/funkcijoms**, ne tipo nariams
- C++ turi `static` narius, bet C - **NE**

### 📖 Pamoka

> C ir C++ skiriasi! C struktūros - tik duomenų konteineriai, ne klasės.

---

### ❌ Bandymas #2: Pass-by-value

**05_ny_usestack.c**:
```c
#include <stdio.h>

#define SIZE 5

struct Stack {
    char stack[SIZE];
    int top;
};

void init(struct Stack st) {  // ❌ Kopija!
    st.top = 0;
}

int isEmpty(struct Stack st) {  // ❌ Kopija!
    return 0 == st.top;
}

int isFull(struct Stack st) {  // ❌ Kopija!
    return SIZE == st.top;
}

void push(struct Stack st, char c) {  // ❌ Kopija!
    if (!isFull(st)) {
        st.stack[st.top++] = c;
    }
}

char pop(struct Stack st) {  // ❌ Kopija!
    if (!isEmpty(st)) {
        return st.stack[--st.top];
    }
    return '\0';
}

int main(void) {
    struct Stack st1;
    char c;
    
    init(st1);
    while ((!isFull(st1)) && ('\n' != (c = getchar()))) 
        push(st1, c);
    while (!isEmpty(st1)) 
        putchar(pop(st1));
    putchar('\n');
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 05_ny_usestack.c -o 05_ny_usestack
```

### ✅ Kompiliuojasi!

### ❌ Bet nevykdo teisingai

```
> 05_ny_usestack.exe
123
        // ← NIEKO! Tuščia!
Pabaiga
```

### 🔍 Kas nutiko?

**Pass-by-value problema:**

```
main():
  st1.stack = [?, ?, ?, ?, ?]  ← NIEKADA nepakeistas
  st1.top = ?                  ← Neinicializuotas

init(kopija):
  kopija.top = 0  ← Modifikuoja KOPIJĄ
  // Kopija nunyksta funkcijos pabaigoje

push(kopija, 'c'):
  kopija.stack[0] = '1'
  kopija.stack[1] = '2'
  kopija.stack[2] = '3'
  kopija.top = 3
  // Kopija nunyksta

pop(kopija):
  return kopija.stack[--kopija.top]  ← Bet originalas tuščias!
```

**Rezultatas:** Originalus `st1` lieka nemodifikuotas!

### 📖 Pamoka

> **Pass-by-value vs Pass-by-reference:**
> - C perdavinėja **kopijas**
> - Norint modifikuoti - reikia **rodyklių** (pointers)
> - C++ turi references (`&`), C - tik pointers

---

### ✅ Teisingas sprendimas: Rodyklės!

**05_n_usestack.c**:
```c
#include <stdio.h>

#define SIZE 5

struct Stack {
    char stack[SIZE];
    int top;
};

static void reset(struct Stack *pst) {  // ✅ Rodyklė
    pst->top = 0;
}

void init(struct Stack *pst) {  // ✅ Rodyklė
    pst->top = 0;
}

int isEmpty(struct Stack *pst) {  // ✅ Rodyklė
    return 0 == pst->top;
}

int isFull(struct Stack *pst) {  // ✅ Rodyklė
    return SIZE == pst->top;
}

void push(struct Stack *pst, char c) {  // ✅ Rodyklė
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

char pop(struct Stack *pst) {  // ✅ Rodyklė
    if (!isEmpty(pst)) {
        return pst->stack[--pst->top];
    }
    return '\0';
}

int main(void) {
    struct Stack st1, st2;
    char c;
    
    printf("Ivesk st1\n");
    init(&st1);  // ✅ Adresas
    while ((!isFull(&st1)) && ('\n' != (c = getchar()))) 
        push(&st1, c);
    while (!isEmpty(&st1)) 
        putchar(pop(&st1));
    putchar('\n');
    printf("st1 pabaiga\n");
    
    printf("Ivesk st2\n");
    init(&st2);  // ✅ Dar vienas stekas!
    while ((!isFull(&st2)) && ('\n' != (c = getchar()))) 
        push(&st2, c);
    while (!isEmpty(&st2)) 
        putchar(pop(&st2));
    putchar('\n');
    printf("st2 pabaiga\n");
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 05_n_usestack.c -o 05_n_usestack
```

### ✅ Veikia!

```
> 05_n_usestack.exe
Ivesk st1
456
654
st1 pabaiga
Ivesk st2
456789
87654
st2 pabaiga
```

### 🎉 Pasiekta

- ✅ Turime **tipą** `struct Stack`
- ✅ Galime turėti **kelis** stekas (`st1`, `st2`)
- ✅ Tikras **ADT** - tipas su operacijomis

### ⚠️ Bet dar ne modulis!

---

## Etapas 6: ADT modulyje

### 🎯 Tikslas
Perkelti ADT į modulį (header + implementation).

### 💻 Sprendimas

**06_stack.h**:
```c
#define SIZE 5

struct Stack {
    char stack[SIZE];  // ⚠️ Matomas header'yje
    int top;           // ⚠️ Matomas header'yje
};

void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

**06_stack.c**:
```c
#include "06_stack.h"

static void reset(struct Stack *pst) {
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

int isEmpty(struct Stack *pst) {
    return 0 == pst->top;
}

int isFull(struct Stack *pst) {
    return SIZE == pst->top;
}

void push(struct Stack *pst, char c) {
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

char pop(struct Stack *pst) {
    if (!isEmpty(pst)) {
        return pst->stack[--pst->top];
    }
    return '\0';
}
```

**06_user.c**:
```c
#include <stdio.h>
#include "06_stack.h"

int main(void) {
    struct Stack st1, st2;
    char c;
    
    printf("Ivesk st1\n");
    init(&st1);
    while ((!isFull(&st1)) && ('\n' != (c = getchar()))) 
        push(&st1, c);
    while (!isEmpty(&st1)) 
        putchar(pop(&st1));
    putchar('\n');
    printf("st1 pabaiga\n");
    
    printf("Ivesk st2\n");
    init(&st2);
    while ((!isFull(&st2)) && ('\n' != (c = getchar()))) 
        push(&st2, c);
    while (!isEmpty(&st2)) 
        putchar(pop(&st2));
    putchar('\n');
    printf("st2 pabaiga\n");
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 06_stack.c 06_user.c -o 06_use_stack
```

### ✅ Veikia!

```
> 06_use_stack.exe
Ivesk st1
123
321
st1 pabaiga
Ivesk st2
123456
54321
st2 pabaiga
```

### 🎉 Pasiekta

- ✅ ADT modulyje
- ✅ Du stekai veikia
- ✅ Gražus kodas

### 🔓 Bet "ataka" pavyksta!

**06_z_user.c**:
```c
#include <stdio.h>
#include "06_stack.h"

int main(void) {
    struct Stack st2;
    char c;
    
    printf("Ivesk st2\n");
    init(&st2);
    while ((!isFull(&st2)) && ('\n' != (c = getchar()))) 
        push(&st2, c);
    
    st2.stack[st2.top++] = '!';  // 🔓 Tiesioginė manipuliacija!
    
    while (!isEmpty(&st2)) 
        putchar(pop(&st2));
    putchar('\n');
    printf("st2 pabaiga\n");
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 06_stack.c 06_z_user.c -o 06_z_use_stack
```

### ✅ Kompiliuojasi!

```
> 06_z_use_stack.exe
Ivesk st2
123456
!54321   // ← Ataka pavyko!
```

### 📖 Pamoka

> Jei struktūros apibrėžimas matomas header'yje, tai **NE enkapsulacija**!
>
> Bet kas gali pasiekti `st.top`, `st.stack[i]`.

---

## Etapas 7: Opaque Type - tikra enkapsulacija

### 🎯 Tikslas
Paslėpti struktūros apibrėžimą, palikti tik **forward declaration**.

---

### ❌ Bandymas #1: Stack objektai su forward declaration

**07_n_stack.h**:
```c
#define SIZE 5

struct Stack;  // ✅ Forward declaration

void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

**07_n_stack.c**:
```c
#include "07_n_stack.h"

struct Stack {  // ✅ Pilnas apibrėžimas TIK .c faile
    char stack[SIZE];
    int top;
};

static void reset(struct Stack *pst) {
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

int isEmpty(struct Stack *pst) {
    return 0 == pst->top;
}

int isFull(struct Stack *pst) {
    return SIZE == pst->top;
}

void push(struct Stack *pst, char c) {
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

char pop(struct Stack *pst) {
    if (!isEmpty(pst)) {
        return pst->stack[--pst->top];
    }
    return '\0';
}
```

**07_nx_user.c** (bandymas su stack objektais):
```c
#include <stdio.h>
#include "07_n_stack.h"

int main(void) {
    struct Stack st1, st2;  // ❌ Bandau deklaruoti
    // ...
}
```

### 🔧 Kompiliavimas
```bash
gcc 07_n_stack.c 07_nx_user.c -o 07_nx_use_stack
```

### ❌ Kompiliavimo klaida

**GCC:**
```
07_nx_user.c: In function 'main':
07_nx_user.c:7:18: error: storage size of 'st1' isn't known
    7 |     struct Stack st1, st2;
      |                  ^~~
07_nx_user.c:7:23: error: storage size of 'st2' isn't known
    7 |     struct Stack st1, st2;
      |                       ^~~
```

**Clang:**
```
07_nx_user.c:7:18: error: variable has incomplete type 'struct Stack'
    7 |     struct Stack st1, st2;
      |                  ^
./07_n_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
```

### 🔍 Kodėl klaida?

- Kompiliatorius **nežino** struktūros dydžio
- Negali allokuoti `st1` ir `st2` stack'e
- Forward declaration leidžia tik **rodykles**!

### 📖 Pamoka

> **Incomplete type (nepilnas tipas):**
> - Galima deklaruoti **rodykles**: `struct Stack *pst`
> - **NEGALIMA** deklaruoti objektų: `struct Stack st`
> - **NEGALIMA** naudoti `sizeof(struct Stack)`

---

### ❌ Bandymas #2: Heap allokacija su `calloc`

**07_ny_user.c**:
```c
#include <stdio.h>
#include <stdlib.h>
#include "07_n_stack.h"

int main(void) {
    struct Stack *pst1;
    char c;
    
    pst1 = calloc(sizeof(struct Stack), 1);  // ❌ sizeof incomplete type!
    
    printf("Ivesk st1\n");
    init(pst1);
    // ...
}
```

### 🔧 Kompiliavimas
```bash
gcc 07_n_stack.c 07_ny_user.c -o 07_ny_use_stack
```

### ❌ Kompiliavimo klaida

**GCC:**
```
07_ny_user.c: In function 'main':
07_ny_user.c:10:26: error: invalid application of 'sizeof' 
                          to incomplete type 'struct Stack'
   10 |     pst1 = calloc(sizeof(struct Stack), 1);
      |                          ^~~~~~
```

**Clang:**
```
07_ny_user.c:10:19: error: invalid application of 'sizeof' 
                           to an incomplete type 'struct Stack'
   10 |     pst1 = calloc(sizeof(struct Stack), 1);
      |                   ^     ~~~~~~~~~~~~~~
./07_n_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
```

### 🔍 Problema

Vartotojas **negali** naudoti `sizeof(struct Stack)` - tipas neišbaigtas!

**Sprendimas:** Reikia **factory funkcijos**!

---

### ✅ Teisingas sprendimas: Factory Pattern

**07_stack.h**:
```c
#define SIZE 5

struct Stack;  // Opaque type

struct Stack* create(void);  // ✅ Factory funkcija!
void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

**07_stack.c**:
```c
#include <stdlib.h>
#include "07_stack.h"

struct Stack {  // ✅ Pilnas apibrėžimas TIK .c faile
    char stack[SIZE];
    int top;
};

struct Stack* create(void) {  // ✅ Factory
    return (struct Stack*) calloc(sizeof(struct Stack), 1);
}

static void reset(struct Stack *pst) {
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

int isEmpty(struct Stack *pst) {
    return 0 == pst->top;
}

int isFull(struct Stack *pst) {
    return SIZE == pst->top;
}

void push(struct Stack *pst, char c) {
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

char pop(struct Stack *pst) {
    if (!isEmpty(pst)) {
        return pst->stack[--pst->top];
    }
    return '\0';
}
```

**07_user.c**:
```c
#include <stdio.h>
#include "07_stack.h"

int main(void) {
    struct Stack *pst1;
    char c;
    
    pst1 = create();  // ✅ Factory funkcija
    
    printf("Ivesk st1\n");
    init(pst1);
    while ((!isFull(pst1)) && ('\n' != (c = getchar()))) 
        push(pst1, c);
    while (!isEmpty(pst1)) 
        putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 07_stack.c 07_user.c -o 07_use_stack
```

### ✅ Veikia!

```
> 07_use_stack.exe
Ivesk st1
123456
54321
st1 pabaiga
```

---

### 🔒 "Ataka" NEPAVYKSTA!

**07_zx_user.c**:
```c
#include <stdio.h>
#include "07_stack.h"

int main(void) {
    struct Stack *pst1;
    char c;
    
    pst1 = create();
    
    printf("Ivesk st1\n");
    init(pst1);
    while ((!isFull(pst1)) && ('\n' != (c = getchar()))) 
        push(pst1, c);
    
    pst1->stack[pst1->top++] = '!';  // 🔒 Bandau atakuoti!
    
    while (!isEmpty(pst1)) 
        putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 07_stack.c 07_zx_user.c -o 07_zx_use_stack
```

### ❌ Kompiliavimo klaida!

**GCC:**
```
07_zx_user.c: In function 'main':
07_zx_user.c:15:9: error: invalid use of undefined type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |         ^~
07_zx_user.c:15:21: error: invalid use of undefined type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |                     ^~
```

**Clang:**
```
07_zx_user.c:15:9: error: incomplete definition of type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |     ~~~~^
./07_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
```

### 🎉 Pergalė!

Kompiliatorius **neleidžia** pasiekti struktūros narių!

### 📖 Pamoka

> **Opaque type / PIMPL (Pointer to Implementation) idiom:**
> - Header'yje - tik forward declaration
> - Struktūros apibrėžimas - TIK .c faile
> - Vartotojas **negali** pasiekti `pst->member`
> - Tai **kompiliatoriaus lygmens** enkapsulacija!

---

## Etapas 8: Full Lifecycle + RAII intro

### 🎯 Tikslas
Pridėti **pilną objekto lifecycle** valdymą ir paruošti C++ RAII koncepcijos įvadą.

### 💻 Sprendimas

**077_stack.h**:
```c
#define SIZE 5

struct Stack;

struct Stack* create(void);   // Constructor
void destroy(struct Stack *); // ✅ Destructor!
void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

**077_stack.c**:
```c
#include <stdlib.h>
#include "077_stack.h"

struct Stack {
    char stack[SIZE];
    int top;
};

struct Stack* create(void) {
    return (struct Stack*) calloc(sizeof(struct Stack), 1);
}

void destroy(struct Stack *pst) {  // ✅ Atlaisvinimas!
    free(pst);
}

static void reset(struct Stack *pst) {
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

int isEmpty(struct Stack *pst) {
    return 0 == pst->top;
}

int isFull(struct Stack *pst) {
    return SIZE == pst->top;
}

void push(struct Stack *pst, char c) {
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

char pop(struct Stack *pst) {
    if (!isEmpty(pst)) {
        return pst->stack[--pst->top];
    }
    return '\0';
}
```

**077_user.c**:
```c
#include <stdio.h>
#include "077_stack.h"

int main(void) {
    struct Stack *pst1;
    char c;
    
    pst1 = create();  // ✅ Sukūrimas
    
    printf("Ivesk st1\n");
    init(pst1);
    while ((!isFull(pst1)) && ('\n' != (c = getchar()))) 
        push(pst1, c);
    while (!isEmpty(pst1)) 
        putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");
    
    destroy(pst1);  // ✅ Sunaikinimas
    
    return 0;
}
```

### 🔧 Kompiliavimas
```bash
gcc 077_stack.c 077_user.c -o 077_use_stack
```

### ✅ Veikia!

```
> 077_use_stack.exe
Ivesk st1
1234567
54321
st1 pabaiga
```

### 🎉 Pasiekta: Pilnas ADT C kalboje!

**Turime:**
- ✅ **Opaque type** - struktūra paslėpta
- ✅ **Factory pattern** - `create()`
- ✅ **Enkapsulacija** - duomenys nepasiekiami
- ✅ **Full lifecycle** - `create()` / `destroy()`
- ✅ **Modulinė struktūra** - header + implementation
- ✅ **Information hiding** - `static` nariai

---

### 🔗 C → C++ tiltas: RAII įvadas

**C kalboje:**
```c
struct Stack *pst = create();  // Manual sukūrimas
// ... naudojimas
destroy(pst);                  // Manual sunaikinimas
```

**Problemos:**
1. ❌ Galima pamiršti `destroy()` → **memory leak**
2. ❌ Jei klaida tarp `create()` ir `destroy()` → **leak**
3. ❌ Reikia sekti kiekvieno objekto lifecycle **rankomis**

---

**C++ sprendimas: RAII (Resource Acquisition Is Initialization)**

```cpp
class Stack {
private:
    char stack[SIZE];
    int top;
    
public:
    Stack() : top(0) {}  // ✅ Constructor - automatinis!
    ~Stack() {}          // ✅ Destructor - automatinis!
    
    void push(char c) {
        if (top < SIZE) stack[top++] = c;
    }
    
    char pop() {
        if (top > 0) return stack[--top];
        return '\0';
    }
};

int main() {
    Stack st1;  // ✅ Constructor automatiškai iškviečiamas
    st1.push('A');
    // ...
}  // ✅ Destructor automatiškai iškviečiamas išeinant iš scope!
```

**RAII garantijos:**
- ✅ Constructor **visuomet** iškviečiamas objekto sukūrimo metu
- ✅ Destructor **visuomet** iškviečiamas objekto sunaikinimo metu
- ✅ **Automatinis** resource valdymas
- ✅ **Exception-safe** - destructor iškviestas net klaidos atveju

---

### 📖 Evoliucijos apžvalga

| Etapas | Sprendimas | Pasiekta | Trūkumai |
|--------|-----------|----------|----------|
| 1 | Monolitinis kodas | Veikia | Nelankstus, globalūs |
| 2 | Failų atskyrimas | Dekompozicija | Nėra header failų |
| 3 | Modulis | Header + .c | Globalūs duomenys |
| 4 | Information hiding | `static` | Tik 1 stekas |
| 5 | User Defined Type | Keletas stekas | Nėra enkapsuliacijos |
| 6 | ADT modulyje | Tipas + modulis | Duomenys matomi |
| 7 | Opaque type | Enkapsulacija | Reikia manual destroy |
| 8 | Full lifecycle | RAII įvadas | Manual lifecycle (C) |

---

## 🎓 Pagrindinės pamokos

### 1. **Declaration vs Definition**
```c
// DECLARATION (aprašas)
extern int x;
void foo(void);
struct Stack;  // Forward declaration

// DEFINITION (apibrėžimas)
int x = 42;
void foo(void) { /* ... */ }
struct Stack { /* ... */ };
```

### 2. **Storage classes**
```c
// Global scope
int global;           // External linkage
static int internal;  // Internal linkage
extern int external;  // Declaration

// Function scope
void foo(void) {
    static int persistent;  // Išlieka tarp kvietimų
    auto int local;         // Default (stack)
    register int fast;      // Suggestion compiler'iui
}
```

### 3. **Incomplete types**
```c
struct Stack;  // Incomplete type

struct Stack *p;        // ✅ OK - rodyklė
sizeof(struct Stack);   // ❌ KLAIDA - nepilnas tipas
struct Stack s;         // ❌ KLAIDA - reikia dydžio
```

### 4. **Opaque type pattern**
```c
// Header (.h)
struct Type;
struct Type* create(void);
void destroy(struct Type*);

// Implementation (.c)
struct Type {
    // Privačius nariai
};
```

### 5. **C vs C++ enkapsulacija**

| Aspektas | C | C++ |
|----------|---|-----|
| Private duomenys | `static` .c faile | `private:` klasėje |
| Constructor | `create()` funkcija | Automatinis `Type()` |
| Destructor | `destroy()` funkcija | Automatinis `~Type()` |
| Lifecycle | Manual | RAII (automatinis) |
| Multiple instances | Struktūrų masyvas | Objektų masyvas |

---

## 📝 Užduotys studentams

### Užduotis 1: Pataisyk klaidą
Kodėl šis kodas nesikompiliuoja? Kaip pataisyti?

```c
// my_stack.h
struct Stack {
    int data[100];
    int top;
};

// my_stack.c
#include "my_stack.h"

struct Stack {
    int data[100];
    int top;
};

void push(struct Stack *s, int val) {
    s->data[s->top++] = val;
}
```

<details>
<summary>Atsakymas</summary>

**Klaida:** Multiple definition of `struct Stack`

**Sprendimas:** Struktūros apibrėžimas turi būti TIK vienoje vietoje:
- Header'yje: jei reikia matomo tipo (Etapas 6)
- .c faile: jei naudojame opaque type (Etapas 7)

```c
// Variantas 1: Header'yje (matomas)
// my_stack.h
struct Stack {
    int data[100];
    int top;
};

void push(struct Stack *s, int val);

// my_stack.c
#include "my_stack.h"
// NEAPIBRĖŽIAME dar kartą!

void push(struct Stack *s, int val) {
    s->data[s->top++] = val;
}

// Variantas 2: Opaque type (paslėptas)
// my_stack.h
struct Stack;  // Tik forward declaration
void push(struct Stack *s, int val);

// my_stack.c
#include "my_stack.h"

struct Stack {  // Apibrėžimas TIK čia
    int data[100];
    int top;
};

void push(struct Stack *s, int val) {
    s->data[s->top++] = val;
}
```
</details>

---

### Užduotis 2: Pass-by-value vs Pass-by-pointer

Kodėl ši funkcija nemodifikuoja originalaus steko?

```c
void init(struct Stack st) {
    st.top = 0;
}

int main(void) {
    struct Stack s;
    init(s);
    printf("%d\n", s.top);  // Kas bus išspausdinta?
}
```

<details>
<summary>Atsakymas</summary>

**Atsakymas:** Spausdins neinicializuotą reikšmę (šiukšles).

**Priežastis:** `init(s)` gauna **kopiją** struktūros. Modifikuoja kopiją, ne originalą.

**Sprendimas:**
```c
void init(struct Stack *pst) {  // Rodyklė!
    pst->top = 0;
}

int main(void) {
    struct Stack s;
    init(&s);  // Perduodame adresą
    printf("%d\n", s.top);  // 0
}
```
</details>

---

### Užduotis 3: Implementuok Queue

Naudodami Opaque Type pattern (Etapas 7-8), implementuokite Queue ADT su:
- `create()` / `destroy()`
- `enqueue(Queue*, int)` - įdeda į galą
- `dequeue(Queue*)` - išima iš priekio
- `isEmpty(Queue*)`

<details>
<summary>Sprendimo pavyzdys</summary>

```c
// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 100

struct Queue;

struct Queue* create(void);
void destroy(struct Queue*);
void enqueue(struct Queue*, int);
int dequeue(struct Queue*);
int isEmpty(struct Queue*);

#endif

// queue.c
#include <stdlib.h>
#include "queue.h"

struct Queue {
    int data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
};

struct Queue* create(void) {
    struct Queue *q = (struct Queue*) calloc(sizeof(struct Queue), 1);
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;
}

void destroy(struct Queue *q) {
    free(q);
}

void enqueue(struct Queue *q, int val) {
    if (q->count < QUEUE_SIZE) {
        q->rear = (q->rear + 1) % QUEUE_SIZE;
        q->data[q->rear] = val;
        q->count++;
    }
}

int dequeue(struct Queue *q) {
    if (q->count > 0) {
        int val = q->data[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
        return val;
    }
    return -1;  // Tuščia
}

int isEmpty(struct Queue *q) {
    return q->count == 0;
}
```
</details>

---

## 🚀 Kitas žingsnis: C++

Šis vadovas paruošė jus C++ OOP:

```cpp
class Stack {
private:  // ≈ static C kalboje
    static const int SIZE = 100;
    char data[SIZE];
    int top;

public:  // ≈ header funkcijos C kalboje
    Stack() : top(0) {}  // ≈ create()
    ~Stack() {}          // ≈ destroy()
    
    void push(char c) {
        if (top < SIZE) data[top++] = c;
    }
    
    char pop() {
        if (top > 0) return data[--top];
        return '\0';
    }
    
    bool isEmpty() const {
        return top == 0;
    }
};

// Naudojimas
int main() {
    Stack s1, s2;  // ✅ Automatinis constructor
    s1.push('A');
    s2.push('B');
}  // ✅ Automatinis destructor
```

**C++ privalumai:**
- ✅ Automatinis lifecycle (RAII)
- ✅ Sintaksinis `private` / `public`
- ✅ Member funkcijos
- ✅ Operator overloading
- ✅ Templates (generic programming)

---

## 📚 Papildoma literatūra

1. **K&R "The C Programming Language"** - Chapter 6 (Structures)
2. **"Expert C Programming"** by Peter van der Linden
3. **"C Interfaces and Implementations"** by David Hanson
4. **Stroustrup "The C++ Programming Language"** - RAII (Chapter 13)

---

## 🎬 Apibendrinimas

**Evoliucijos kelias:**
1. Monolitinis kodas → Modulis
2. Globalūs duomenys → Information hiding (`static`)
3. Vienas stekas → User Defined Type (struktūra)
4. Matoma struktūra → Opaque type (forward declaration)
5. Manual lifecycle → Factory pattern (`create`/`destroy`)
6. C → C++ (RAII, automatinis lifecycle)

**Svarbiausios pamokos:**
- ✅ **Enkapsulacija** - ne tik patogumas, bet **saugumas**
- ✅ **Abstrakcija** - slėpti detales, rodyti sąsają
- ✅ **Modulinė struktūra** - pakartotinis naudojimas
- ✅ **Lifecycle valdymas** - sukūrimas ir sunaikinimas
- ✅ **C → C++ tiltas** - manual → automatic

---

**Sėkmės mokantis! 🚀**