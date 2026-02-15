# Stack ADT Evoliucija C kalboje
## 9 Etapų Kelionė: Nuo Monolito iki Pilno ADT

!!! abstract "Šios kelionės tikslas"
    Patirti **natūralią** Stack Abstract Data Type evoliuciją nuo paprasčiausio monolito iki pilnai realizuoto ADT su lifecycle valdymu. Kiekvienas etapas sprendžia ankstesnio problemą, mokydamas "per nagus" - ne iš teorijos, o iš praktikos. **Kompiliavimo ir linkavimo klaidos yra mokymosi įrankis**, ne problema kurią reikia slėpti.

---

## Etapas 01: Running PROGRAM
### Viskas viename faile - monolitas

Pradedame nuo paprasčiausio sprendimo - **vienas failas, visa logika kartu**.

=== "Kodas"

    ```c title="01_Running_PROGRAM/stack.c"
    --8<-- "code/evolution/stack-2026/01_Running_PROGRAM/01_OK_Naive/usestack.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc stack.c -o app
    ./app
    ```
    
    **Išvestis:**
    ```
    12345
    54321
    ```

=== "Veikimo principas"

    1. Įvedimas: skaito simbolius kol Enter
    2. Kiekvienas simbolis į steką (push)
    3. Išvedimas: iš steko (pop) atvirkščia tvarka
    4. Rezultatas: eilutė apversta

### Monolito privalumai ir problemos

??? success "Privalumai"
    - **Funkcijų eiliškumas nesvarbus:** `main()` gali būti viršuje
    - **Kompiliatorius mato viską:** Vienas kompiliavimo vienetas
    - **Paprastas build:** Viena komanda

??? danger "Problemos dideliuose projektuose"
    - **Prižiūrėjimas:** 1000+ eilučių viename faile
    - **Pakartotinis naudojimas:** Kaip kitas projektas naudotų stack?
    - **Kompiliavimo laikas:** Viskas perkompiliuojama
    - **Team collaboration:** Git conflicts garantuoti

**Dėstytojo užduotis:** *"Atskirkit stack logiką į atskirą failą!"*

---

## Etapas 02: Decomposing to UNITS
### Fizinis padalijimas - "per nagus" mokymasis

### Žingsnis 1: Naivus atskyrimas (01_NC)

**Studentų mintis:** *"Tiesiog supjausčiau į du failus!"*

=== "stack.c"

    ```c title="02_Decomposing_to_UNITS/01_NC/stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/stack.c"
    ```

=== "user.c"

    ```c title="02_Decomposing_to_UNITS/01_NC/user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/user.c"
    ```

=== "GCC (warning)"

    ```bash
    $ gcc -c user.c
    warning: implicit declaration of function 'init'
    warning: implicit declaration of function 'push'
    ```
    ⚠️ Kompiliuojasi su warnings

=== "Clang (error)"

    ```bash
    $ clang -c user.c
    error: call to undeclared function 'init'
    4 errors generated.
    ```
    ❌ Nepavyksta!

??? info "Monolito vs modulių skirtumas"
    **Monolite:** kompiliatorius mato visą failą  
    **Moduliuose:** kiekvienas `.c` = atskiras vienetas

---

### Žingsnis 2: "Logiška" idėja (02_NL)

**Studentų mintis:** *"Sujungsiu su `#include "stack.c"`!"*

=== "user.c"

    ```c title="02_Decomposing_to_UNITS/02_NL/user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/user.c"
    ```

=== "Linkavimo klaida"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    ```
    
    ```
    multiple definition of `push'
    multiple definition of `pop'
    ```
    💥 Dubliavimasis!

??? danger "Preprocesoriaus copy-paste"
    `#include "stack.c"` įklijuoja turinį → abi funkcijos abiejuose `.o` failuose

---

### Žingsnis 3: "Žingsnis atgal" (03_OK_Wrong)

**Studentų mintis:** *"Gal užtenka tik user.c?"*

=== "Kompiliavimas"

    ```bash
    gcc user.c -o app  # ✅ VEIKIA!
    ```

??? warning "Kodėl BLOGAI (antipattern)?"
    - Grįžome prie monolito
    - Negalimas pakartotinis naudojimas (keli failai → klaida)
    - `#include` skirtas `.h`, ne `.c`

---

## Etapas 03: Discovering C MODULE
### Tikras C modulis su header failu

### Žingsnis 1: Header be guards (01_NC) - DI ???

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/01_NC/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/01_NC/stack.h"
    ```

??? danger "Problema: Header įtrauktas kelis kartus"
    Jei `helper.h` ir `user.c` abu įtraukia `stack.h` → dvigubos deklaracijos

---

### Žingsnis 2: Header be extern (02_NL)

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/02_NL/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/stack.h"
    ```

??? danger "Problema: Kintamųjų apibrėžimas header'yje"
    `char stack[10];` header'yje → abu failai sukuria savo kopiją → multiple definition

---

### Žingsnis 3: Nenuoseklus extern (03_OK_Wrong)

**Studentų mintis:** *"Gal stack[] header'yje, o top su extern?"*

??? warning "Problema: Nenuoseklus dizainas"
    Vienas kintamasis header'yje, kitas su extern → prasta praktika

---

### Žingsnis 4: Teisingas modulis (04_OK)

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/04_OK/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/stack.h"
    ```

=== "stack.c"

    ```c title="03_Discovering_C_MODULE/04_OK/stack.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/stack.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app  # ✅ Veikia!
    ```

??? success "Kas dabar gerai?"
    - Header guards (`#ifndef`)
    - `extern` deklaracijos
    - Apibrėžimai tik `.c` faile
    - Tikras modulis!

---

### Žingsnis 5: Ataka pavyksta (05_OK_Attack)

=== "attacker.c"

    ```c title="03_Discovering_C_MODULE/05_OK_Attack/attacker.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/user_attack.c"
    ```

??? danger "Saugumo spraga"
    ```c
    extern int top;
    top = -1;  // ← Tiesiogiai modifikuojame!
    ```
    **Sprendimas → Etapas 04:** `static` linkage

---

## Etapas 04: Protecting IMPLEMENTATION
### Information hiding su `static`

### Žingsnis 1: Ataka vis dar veikia (01_NL_Attack)

**Studentų mintis:** *"Tiesiog paslėpsiu su `static`... bet pamiršiu header'yje!"*

=== "stack.h (klaida)"

    ```c title="04_Protecting_IMPLEMENTATION/01_NL_Attack/stack.h"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/01_NL_Attack/stack.h"
    ```

??? danger "Problema: `extern` vis dar header'yje"
    Jei header'yje `extern`, bet `.c` faile `static` → konfliktas

---

### Žingsnis 2: Tikras information hiding (02_OK)

=== "stack.h"

    ```c title="04_Protecting_IMPLEMENTATION/02_OK/stack.h"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/02_OK/stack.h"
    ```

=== "stack.c"

    ```c title="04_Protecting_IMPLEMENTATION/02_OK/stack.c"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/02_OK/stack.c"
    ```

??? success "`static` linkage"
    ```c
    static char stack[STACK_SIZE];  // Matomas TIK stack.c
    static int top = 0;
    ```
    **Ataka dabar neveiks!**

??? warning "Nauja problema: Tik vienas stekas"
    `static` kintamieji = viena kopija → tik vienas stekas visoje programoje

---

## Etapas 05: Defining USER TYPE
### `struct` - kelio pradžia į objektus

### Žingsnis 1: Neteisingas perdavimas (01_NC)

**Studentų mintis:** *"Sukursiu struct tipą!"*

=== "stack.h"

    ```c title="05_Defining_USER_TYPE/01_NC/stack.h"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/01_NC/stack.h"
    ```

=== "stack.c (klaida)"

    ```c title="05_Defining_USER_TYPE/01_NC/stack.c (fragmentas)"
    void init(stack s) {  // ← Pass-by-value!
        s.top = 0;  // Modifikuoja kopiją!
    }
    ```

??? danger "Problema: Pass-by-value"
    Funkcija gauna **kopiją** → pakeitimai neišlieka

---

### Žingsnis 2: Segmentation fault (02_RT)

**Studentų mintis:** *"Naudosiu rodyklę... bet nesu tikras kaip!"*

??? danger "Runtime klaida"
    ```c
    stack *s;  // Neininicializuota rodyklė!
    init(s);   // 💥 Segfault
    ```

---

### Žingsnis 3: Teisingas struct naudojimas (03_OK)

=== "stack.h"

    ```c title="05_Defining_USER_TYPE/03_OK/stack.h"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/03_OK/stack.h"
    ```

=== "stack.c"

    ```c title="05_Defining_USER_TYPE/03_OK/stack.c (fragmentas)"
    void init(stack *s) {  // ← Pass-by-pointer
        s->top = 0;
    }
    ```

=== "user.c"

    ```c title="05_Defining_USER_TYPE/03_OK/user.c (fragmentas)"
    stack s1, s2;  // Du stekai!
    init(&s1);
    init(&s2);
    ```

??? success "Dabar veikia!"
    - Kelių steką galimybė
    - Rodyklės perdavimas
    - Aiški sintaksė

??? warning "Nauja problema: Struktūra vieša"
    ```c
    stack s;
    s.top = -1;  // ← Tiesioginis prieiga!
    ```
    **Sprendimas → Etapas 06-07:** Encapsulation

---

## Etapas 06: ENCAPSULATING UDT in Module
### Modulinis UDT - bet struktūra vis dar vieša

### Žingsnis 1: Struktūra header'yje (01_OK)

=== "stack.h"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    ```

??? success "Modulinis dizainas"
    - Aiški interface
    - Kelių objektų palaikymas
    - Rodyklių naudojimas

---

### Žingsnis 2: Ataka pavyksta (02_OK_Attack)

=== "attacker.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/attacker.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/attacker.c"
    ```

??? danger "Struktūros nariai vieši"
    ```c
    stack s;
    s.top = 999;  // ← Galima!
    ```
    **Encapsulation ≠ Information hiding**

---

## Etapas 07: HIDING UDT Information
### Opaque pointer - forward declaration

### Žingsnis 1: Forward declaration, bet per anksti (01_NC)

**Studentų mintis:** *"Jei paslėpsiu struktūrą, niekas nematys narių!"*

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/01_NC/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/01_NC/stack.h"
    ```

=== "stack.c"

    ```c title="07_HIDING_UDT_Information/01_NC/stack.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/01_NC/stack.c"
    ```

=== "user.c"

    ```c title="07_HIDING_UDT_Information/01_NC/user.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/01_NC/user.c"
    ```

??? danger "Kompiliavimo klaida: Incomplete type"
    ```c
    stack s;  // ❌ error: storage size of 's' isn't known
    ```
    
    Kompiliatorius nežino `sizeof(stack)` - tik forward declaration!

---

### Žingsnis 2: Bandymas su malloc, bet linkavimo klaida (02_NL)

**Studentų mintis:** *"Naudosiu malloc!"*

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/02_NL/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/02_NL/stack.h"
    ```

=== "stack.c"

    ```c title="07_HIDING_UDT_Information/02_NL/stack.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/02_NL/stack.c"
    ```

??? danger "Linkavimo klaida"
    Greičiausiai problema su funkcijų deklaracijomis arba multiple definition.

---

### Žingsnis 3: Runtime klaida - neininicializuotos rodyklės (03_RT)

**Studentų mintis:** *"Opaque pointer veikia, naudosiu rodykles!"*

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/03_RT/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/stack.h"
    ```

=== "stack.c"

    ```c title="07_HIDING_UDT_Information/03_RT/stack.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/stack.c"
    ```

=== "user.c"

    ```c title="07_HIDING_UDT_Information/03_RT/user.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/user.c"
    ```

=== "Runtime klaida"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    ./app
    ```
    
    ```
    Input 1st Stack:
    Segmentation fault (core dumped)
    ```
    
    💥 **Crash!**

??? danger "Problema: Neininicializuotos rodyklės"
    ```c
    struct Stack *pst1, *pst2;  // ← Rodo į RANDOM memory!
    
    init(pst1);  // ← Bandymas rašyti į atsitiktinę vietą → CRASH
    ```
    
    **Kas reikalinga:**
    - `malloc()` išskirti atmintį
    - Rodyklei priskirti malloc() rezultatą
    - Tik tada galima naudoti
    
    **Sprendimas → Etapas 08:** Factory pattern su `create()`/`destroy()`

??? info "Kodėl kompiliavimas pavyko?"
    Kompiliatorius **nemato** problemos:
    - `struct Stack *pst1;` - teisinga sintaksė
    - `init(pst1);` - teisingas funkcijos kvietimas
    
    Problema pasireiškia tik **runtime** - bandant prieiti atmintį.

---

## Etapas 08: Acquiring RESOURCES
### Factory pattern - create() / destroy()

### Žingsnis 1: Factory su malloc (02_OK)

=== "stack.h"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.h"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/stack.h"
    ```

=== "stack.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.c (fragmentas)"
    stack* create(void) {
        stack *s = malloc(sizeof(stack));
        if (s) s->top = 0;
        return s;
    }
    
    void destroy(stack *s) {
        free(s);
    }
    ```

=== "user.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/user.c (fragmentas)"
    stack *s1 = create();
    stack *s2 = create();
    // ... naudojimas ...
    destroy(s1);
    destroy(s2);
    ```

??? success "Factory pattern privalumai"
    - **Opaque pointer** išlaikomas
    - **Dinaminis** kūrimas
    - **Lifecycle** kontrolė
    - Prototipas C++ konstruktoriams!

??? warning "Problema: Rankinis lifecycle"
    - Reikia prisiminti `destroy()`
    - Memory leak rizika
    - Nėra automatizmo

---

## Etapas 09: Completing LIFECYCLE
### Pilnas lifecycle valdymas

### Žingsnis 1: Pilnas ADT (01_OK)

=== "stack.h"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.h"
    ```

=== "stack.c"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.c"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.c"
    ```

??? success "Pasiekta: Pilnas C ADT!"
    - ✅ Information hiding (opaque pointer)
    - ✅ Lifecycle management (create/destroy)
    - ✅ Multiple instances
    - ✅ True Abstract Data Type
    - ✅ Factory pattern

??? warning "Trūksta (C++ suteiks):"
    - ❌ Automatinio lifecycle (RAII)
    - ❌ Type safety (konstruktorius/destruktorius)
    - ❌ Operatorių perkrovimas
    - ❌ Templates (generics)

---

## Evoliucijos santrauka

### 9 etapų lentelė

| Nr | Etapas | Koncepcija | Info Hiding? | Lifecycle? | Žingsnių | Esmė |
|----|--------|------------|--------------|------------|----------|------|
| **01** | Running_PROGRAM | Monolitas | ❌ | ❌ | 1 | Viskas viename |
| **02** | Decomposing_to_UNITS | Fizinis padalijimas | ❌ | ❌ | 3 | `#include` klaidos |
| **03** | Discovering_C_MODULE | C modulis (h+c) | ❌ | ❌ | 5 | Header/implementation |
| **04** | Protecting_IMPLEMENTATION | `static` linkage | ✅ (1 stekas) | ❌ | 2 | Information hiding |
| **05** | Defining_USER_TYPE | `struct` tipas | ❌ | ❌ | 3 | Pass-by-pointer |
| **06** | ENCAPSULATING_UDT | Modulinis UDT | ❌ | ❌ | 2 | Encapsulation ≠ hiding |
| **07** | HIDING_UDT_Information | Opaque pointer | ✅ | ❌ | 3 | Forward declaration |
| **08** | Acquiring_RESOURCES | Factory pattern | ✅ | ✅ (manual) | 1 | create()/destroy() |
| **09** | Completing_LIFECYCLE | Lifecycle completion | ✅ | ✅ | 1 | Pilnas C ADT |

---

### Kiekvieno etapo sprendimai

```
01 (Monolitas)
  ↓ Problema: nelankstus, globalūs kintamieji
02 (Decomposing)
  ↓ Problema: NL klaidos, antipattern
03 (MODULE)
  ↓ Problema: duomenys vieši → ataka pavyksta
04 (static)
  ↓ Problema: tik vienas stekas
05 (struct)
  ↓ Problema: NC/RT klaidos, struktūra vieša
06 (UDT in Module)
  ↓ Problema: struktūra vieša → ataka pavyksta
07 (Opaque Pointer)
  ↓ Problema: kaip sukurti objektą?
08 (Factory)
  ↓ Problema: rankinis lifecycle
09 (Lifecycle Completion)
  ✓ Pasiekta: pilnas C ADT!
```

---

## Mokymosi rezultatai

### Techniniai įgūdžiai

Po šios kelionės studentai **praktiškai supranta**:

**Kompiliavimo sistemos:**
- Kompiliavimo vienetai (translation units)
- Preprocesoriaus darbas (`#include`, `#define`)
- Kompiliavimo vs linkavimo fazės
- Objektinių failų struktūra

**C kalbos koncepcijos:**
- Header/implementation atskyrimas
- Forward declarations
- `extern` vs `static` linkage
- `typedef` aliasing
- Opaque pointer idiom
- Pass-by-value vs pass-by-pointer

**Dizaino principai:**
- Information hiding
- Encapsulation
- Abstract Data Type
- Factory pattern
- Lifecycle management
- Interface vs Implementation

### "Per nagus" patirtis

**Klaidos kaip mokymosi įrankis:**
- ✅ Implicit declarations (GCC vs Clang)
- ✅ Multiple definition (linkavimo klaidos)
- ✅ Segmentation faults (runtime)
- ✅ Incomplete type klaidos
- ✅ Saugumo spragos (atakos)

**Antipattern'ai:**
- ✅ `#include "*.c"`
- ✅ Globalių kintamųjų eksportas
- ✅ Struktūrų atskleidimas
- ✅ Memory leaks

### Pamokos ateičiai

??? quote "Fundamentalūs principai"
    
    **1. Veikimas ≠ Teisingumas**
    - Kodas gali kompiliuotis, bet būti antipattern
    
    **2. Klaidos yra vertingos**
    - Kompiliavimo klaidos moko dizaino sprendimų
    
    **3. Kompiliatoriai skiriasi**
    - GCC toleruoja, Clang griežtas
    - Testuoti su abiem!
    
    **4. Information hiding kritiškas**
    - Encapsulation ≠ Information hiding
    - `static` + opaque pointer kombinacija
    
    **5. Lifecycle valdymas sunkus**
    - C reikalauja rankiniu būdu
    - C++ RAII automatizuos

---

## Šuolis į C++

### Kas pasikeis su C++ `class`?

**C ADT (Etapas 09):**
```c
stack *s = create();    // Rankinis kūrimas
push(s, 'a');          // Funkcijos kvietimas
destroy(s);            // Rankinis sunaikinimas
```

**C++ Class:**
```cpp
Stack s;               // Automatinis konstruktorius
s.push('a');          // Metodas (member function)
// Automatinis destruktorius
```

### C++ privalumai:

- **Konstruktoriai/destruktoriai** → RAII
- **Private/public** → Kompiliatoriaus lygmens apsauga
- **Metodai** → Funkcijos+duomenys kartu
- **Operatoriai** → `s1 = s2` natūraliai
- **Templates** → Generics (bet koks tipas)

**Kitas žingsnis:** C++ Stack evoliucija (etapai 10+)! 🚀

---

## Papildoma medžiaga

??? tip "Naudingos kompiliavimo komandos"
    
    **Preprocesoriaus išvestis:**
    ```bash
    gcc -E user.c -o user.i
    ```
    
    **Objektinių failų simboliai:**
    ```bash
    nm stack.o
    nm -C stack.o  # C++ name demangling
    ```
    
    **Verbose kompiliavimas:**
    ```bash
    gcc -v -c user.c
    ```
    
    **Griežtas režimas:**
    ```bash
    gcc -std=c11 -Wall -Wextra -Wpedantic -Werror
    ```
    
    **Memory leaks tikrinimas:**
    ```bash
    valgrind --leak-check=full ./app
    ```

??? example "README nuorodos detalėms"
    
    Kiekvienas žingsnis turi detalų README su kompiliavimo instrukcijomis ir technine analize:
    
    **Etapas 02:**
    - [01_NC](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC)
    - [02_NL](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL)
    - [03_OK_Wrong](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong)
    
    **Etapas 03:**
    - [01_NC](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/03_Discovering_C_MODULE/01_NC)
    - [04_OK](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK)
    - [05_OK_Attack](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack)
    
    **Etapas 04-09:**
    - [04_Protecting_IMPLEMENTATION](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/04_Protecting_IMPLEMENTATION)
    - [05_Defining_USER_TYPE](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/05_Defining_USER_TYPE)
    - [06_ENCAPSULATING_UDT_in_Module](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module)
    - [07_HIDING_UDT_Information](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/07_HIDING_UDT_Information) (01_NC → 02_NL → 03_RT)
    - [08_Acquiring_RESOURCES](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/08_Acquiring_RESOURCES)
    - [09_Completing_LIFECYCLE](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/09_Completing_LIFECYCLE)
