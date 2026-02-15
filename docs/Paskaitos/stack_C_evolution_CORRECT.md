# Stack ADT Evoliucija C kalboje
## 9 Etapų Kelionė: Nuo Monolito iki Pilno ADT

!!! abstract "Šios kelionės tikslas"
    Patirti **natūralią** Stack Abstract Data Type evoliuciją nuo paprasčiausio monolito iki pilnai realizuoto ADT su lifecycle valdymu. Kiekvienas etapas sprendžia ankstesnio problemą, mokydamas "per nagus" - ne iš teorijos, o iš praktikos. **Kompiliavimo ir linkavimo klaidos yra mokymosi įrankis**, ne problema kurią reikia slėpti.

---

## Etapas 01: Running PROGRAM
### Monolitas - viskas viename faile

Pradedame nuo paprasčiausio sprendimo - **vienas failas, visa logika kartu**.

=== "usestack.c"

    ```c title="01_Running_PROGRAM/01_OK_naive/usestack.c"
    --8<-- "code/evolution/stack-2026/01_Running_PROGRAM/01_OK_naive/usestack.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc usestack.c -o usestack
    ./usestack
    ```
    
    **Išvestis:**
    ```
    123
    321
    ```

### Monolito privalumai ir problemos

??? success "Privalumai"
    - **Funkcijų eiliškumas nesvarbus:** `main()` gali būti viršuje
    - **Kompiliatorius mato viską:** Vienas kompiliavimo vienetas
    - **Paprastas build:** Viena komanda
    - **Greitas prototipavimas:** Įdarbinimo pokalbio "quick solution"

??? danger "Problemos"
    - **Globalūs kintamieji:** `stack[]` ir `top` matomi visur
    - **Tik vienas stekas:** Negalima turėti kelių
    - **Pakartotinis naudojimas:** Kaip kitas projektas naudotų?
    - **Prižiūrėjimas:** 1000+ eilučių viename faile

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
    **Moduliuose:** kiekvienas `.c` = atskiras vienetas, reikia deklaracijų

---

### Žingsnis 2: "Logiška" idėja (02_NL)

**Studentų mintis:** *"Sujungsiu su `#include "stack.c"`!"*

=== "stack.c"

    ```c title="02_Decomposing_to_UNITS/02_NL/stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/stack.c"
    ```

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

=== "stack.c"

    ```c title="02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
    ```

=== "user.c"

    ```c title="02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
    ```

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

**Struktūra:** 4 žingsniai (prasideda nuo 02_NL).

---

### Žingsnis 1: Header be extern (02_NL)

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/02_NL/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/stack.h"
    ```

=== "stack.c"

    ```c title="03_Discovering_C_MODULE/02_NL/stack.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/stack.c"
    ```

=== "user.c"

    ```c title="03_Discovering_C_MODULE/02_NL/user.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/user.c"
    ```

??? danger "Linkavimo klaida: multiple definition"
    Kintamieji apibrėžti header'yje → abu failai sukuria kopijas

---

### Žingsnis 3: Dar viena linkavimo klaida (03_NL)

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/03_NL/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/stack.h"
    ```

=== "stack.c"

    ```c title="03_Discovering_C_MODULE/03_NL/stack.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/stack.c"
    ```

=== "user.c"

    ```c title="03_Discovering_C_MODULE/03_NL/user.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/user.c"
    ```

??? danger "Dar viena NL klaida"
    Kitas bandymas, kita linkavimo problema

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

=== "user.c"

    ```c title="03_Discovering_C_MODULE/04_OK/user.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/user.c"
    ```

??? success "Dabar teisingai!"
    - `extern` deklaracijos header'yje
    - Apibrėžimai stack.c
    - Tikras C modulis

---

### Žingsnis 5: Ataka pavyksta (05_OK_Attack)

=== "stack.h"

    ```c title="03_Discovering_C_MODULE/05_OK_Attack/stack.h"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/stack.h"
    ```

=== "stack.c"

    ```c title="03_Discovering_C_MODULE/05_OK_Attack/stack.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/stack.c"
    ```

=== "attacker.c"

    ```c title="03_Discovering_C_MODULE/05_OK_Attack/attacker.c"
    --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/attacker.c"
    ```

??? danger "Globalūs kintamieji vieši"
    ```c
    extern int top;
    top = -1;  // ← Galima manipuliuoti!
    ```
    **Sprendimas → Etapas 04:** `static` linkage

---

## Etapas 04: Protecting IMPLEMENTATION
### Information hiding su `static`

### Žingsnis 1: Ataka su static (01_NL_Attack)

=== "stack.h"

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

??? success "`static` linkage veikia!"
    ```c
    static char stack[STACK_SIZE];
    static int top = 0;
    ```
    Ataka dabar neveiks! Bet... tik vienas stekas.

---

## Etapas 05: Defining USER TYPE
### Struct monolite - "greitas entry point"

**Koncepcija:** Grįžtame į monolitą, bet su **struct** - tarsi įdarbinimo pokalbio "quick solution".

### Žingsnis 1: static struktūroje (01_NC)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/01_NC/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/01_NC/usestack.c"
    ```

??? danger "Kompiliavimo klaida"
    ```c
    struct Stack {
        static char stack[SIZE];  // ❌ Neleidžiama!
    };
    ```
    C draudžia storage-class specifiers struktūroje

---

### Žingsnis 2: Pass-by-value (02_RT)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/02_RT/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/02_RT/usestack.c"
    ```

??? danger "Runtime problema"
    ```c
    void init(struct Stack st) {  // Kopija!
        st.top = 0;  // Keičia kopiją, ne originalą
    }
    ```

---

### Žingsnis 3: Pass-by-pointer (03_OK)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/03_OK/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/03_OK/usestack.c"
    ```

??? success "Dabar veikia!"
    ```c
    void init(struct Stack *pst) {
        pst->top = 0;  // Keičia originalą
    }
    
    struct Stack st1, st2;  // Du stekai!
    ```

---

## Etapas 06: ENCAPSULATING UDT in Module
### Struct + modulis = apjungimas idėjų

**Koncepcija:** Dabar **struct modulyje** - apjungiame 05 (struct) + 03 (modulis).

### Žingsnis 1: Modulinis UDT (01_OK)

=== "stack.h"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    ```

=== "stack.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/stack.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/stack.c"
    ```

=== "user.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/user.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/user.c"
    ```

---

### Žingsnis 2: Ataka pavyksta (02_OK_Attack)

=== "attacker.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/attacker.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/attacker.c"
    ```

??? danger "Struktūros nariai vieši"
    ```c
    struct Stack st;
    st.top = 999;  // ← Galima!
    ```
    **Encapsulation ≠ Information hiding**

---

## Etapas 07: HIDING UDT Information
### Opaque pointer - forward declaration

### Žingsnis 1: Incomplete type (01_NC)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/01_NC/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/01_NC/stack.h"
    ```

??? danger "Kompiliavimo klaida"
    ```c
    struct Stack st;  // ❌ Incomplete type
    ```
    Kompiliatorius nežino sizeof(Stack)

---

### Žingsnis 2: Bandymas su malloc (02_NL)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/02_NL/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/02_NL/stack.h"
    ```

??? danger "Linkavimo klaida"
    Greičiausiai problema su funkcijų deklaracijomis

---

### Žingsnis 3: Neininicializuotos rodyklės (03_RT)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/03_RT/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/stack.h"
    ```

=== "user.c"

    ```c title="07_HIDING_UDT_Information/03_RT/user.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/user.c"
    ```

??? danger "Segmentation fault"
    ```c
    struct Stack *pst1, *pst2;  // Neininicializuotos!
    init(pst1);  // 💥 Crash
    ```
    **Sprendimas → Etapas 08:** Factory pattern

---

## Etapas 08: Acquiring RESOURCES
### Factory pattern - create() / destroy()

=== "stack.h"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.h"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/stack.h"
    ```

=== "stack.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.c"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/stack.c"
    ```

=== "user.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/user.c"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/user.c"
    ```

??? success "Factory pattern veikia!"
    ```c
    struct Stack *pst1 = create();
    // ... naudojimas ...
    destroy(pst1);
    ```

---

## Etapas 09: Completing LIFECYCLE
### Pilnas lifecycle valdymas

=== "stack.h"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.h"
    ```

=== "stack.c"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.c"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.c"
    ```

=== "user.c"

    ```c title="09_Completing_LIFECYCLE/01_OK/user.c"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/user.c"
    ```

??? success "Pilnas C ADT!"
    - ✅ Information hiding (opaque pointer)
    - ✅ Lifecycle management (create/destroy)
    - ✅ Multiple instances
    - ✅ Factory pattern

---

## Evoliucijos santrauka

### 9 etapų kelias

| Nr | Etapas | Failai | Žingsnių | Info Hiding? | Lifecycle? | Esmė |
|----|--------|--------|----------|--------------|------------|------|
| **01** | Running_PROGRAM | `usestack.c` | 1 | ❌ | ❌ | Monolitas |
| **02** | Decomposing_to_UNITS | `stack.c, user.c` | 3 | ❌ | ❌ | NL klaidos |
| **03** | Discovering_C_MODULE | `stack.h/c, user.c` | 4 | ❌ | ❌ | Modulis |
| **04** | Protecting_IMPLEMENTATION | `stack.h/c, user.c` | 2 | ✅ (1 stekas) | ❌ | `static` |
| **05** | Defining_USER_TYPE | `usestack.c` | 3 | ❌ | ❌ | Struct monolite |
| **06** | ENCAPSULATING_UDT | `stack.h/c, user.c` | 2 | ❌ | ❌ | Struct + modulis |
| **07** | HIDING_UDT_Information | `stack.h/c, user.c` | 3 | ✅ | ❌ | Opaque pointer |
| **08** | Acquiring_RESOURCES | `stack.h/c, user.c` | 1 | ✅ | ✅ (manual) | Factory |
| **09** | Completing_LIFECYCLE | `stack.h/c, user.c` | 1 | ✅ | ✅ | Pilnas ADT |

---

## Šuolis į C++

### C ADT (Etapas 09):
```c
struct Stack *s = create();
push(s, 'a');
destroy(s);
```

### C++ Class:
```cpp
Stack s;               // Konstruktorius
s.push('a');          // Metodas
// Destruktorius automatiškai
```

**Kitas žingsnis:** C++ Stack evoliucija! 🚀
