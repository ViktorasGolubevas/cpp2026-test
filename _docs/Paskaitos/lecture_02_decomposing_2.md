# Etapas 02: Decomposing to UNITS
## Nuo monolito iki fizinio padalijimo

!!! tip "Šio etapo tikslas"
    Išmokti **fiziškai** atskirti programą į kompiliavimo vienetus, suprasti `#include` mechanizmą ir **patirti** tipines kompiliavimo/linkavimo klaidas kaip mokymosi įrankį.

---

## Problema, kurią sprendžiame

Etape 01 turėjome **monolitinį failą** - visa logika vienoje vietoje. Tai veikė, bet sunku palaikyti didesnį kodą, negalima pakartotinai naudoti stack.c kituose projektuose, jokio moduliškumo. Visi globalūs kintamieji matomi visur.

**Sprendimas:** Fiziškai padalinti į atskirus **kompiliavimo vienetus** (translation units).

---

## Struktūra

```
02_Decomposing_to_UNITS/
├── 01_NC/              # Not Compiling - kompiliavimo klaida
│   ├── stack.c         
│   └── user.c          
├── 02_NL/              # Not Linking - linkavimo klaida
│   ├── stack.c         
│   └── user.c          
└── 03_OK_Wrong/        # Veikia, bet antipattern
    ├── stack.c
    └── user.c
```

---

## Žingsnis 1: Trūkstami prototipai (01_NC)

Studentas bando tiesiog "nukirpti" monolitą į du failus - bet **užmiršta deklaruoti** funkcijas `user.c` faile. Kas nutinka priklauso nuo kompiliatoriaus!

=== "stack.c"

    ```c title="stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/stack.c"
    ```

=== "user.c"

    ```c title="user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/user.c"
    ```

=== "GCC (Warning)"

    ```bash
    $ gcc -c user.c
    user.c: In function 'main':
    user.c:6:5: warning: implicit declaration of function 'init'
    user.c:7:37: warning: implicit declaration of function 'push'
    user.c:8:13: warning: implicit declaration of function 'isEmpty'
    user.c:8:32: warning: implicit declaration of function 'pop'
    ```
    
    ⚠️ **GCC leidžia kompiliuoti** - tik įspėjimai!

=== "Clang (Error)"

    ```bash
    $ clang -c user.c
    user.c:6:5: error: call to undeclared function 'init'; 
    ISO C99 and later do not support implicit function declarations
    user.c:7:37: error: call to undeclared function 'push'
    user.c:8:13: error: call to undeclared function 'isEmpty'
    user.c:8:32: error: call to undeclared function 'pop'
    4 errors generated.
    ```
    
    ❌ **Clang atsisako kompiliuoti!**

### Kas vyksta?

**GCC** (legacy režimas) leidžia **implicit function declarations** - naudoja `int func()` kaip default prototipą. **Clang** (modernesnė C99+ interpretacija) **reikalauja aiškių deklaracijų**.

??? danger "Pamoka: Kompiliatorių skirtumai"
    
    **C89/C90:** Leido implicit declarations (GCC default elgesys dėl backward compatibility)
    
    **C99+:** Nebeleidžia implicit declarations (Clang griežtai laikosi standarto)
    
    **Išvada:** 
    - Visada rašykite funkcijų **prototipus** (forward declarations)
    - Naudokite `-std=c11 -Werror` su GCC, kad versti warnings → errors
    - Nesikliauk vien GCC - testuok ir su Clang!

---

## Žingsnis 2: Pridėjus prototipus (02_NL)

Dabar pridedame funkcijų deklaracijas `user.c` pradžioje. Bet atsiranda nauja problema!

=== "stack.c"

    ```c title="stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/stack.c"
    ```

=== "user.c"

    ```c title="user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/user.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    ```

### Kas nutinka?

```
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `stack'; 
stack.o:(.bss+0x0): first defined here
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `top'; 
stack.o:(.bss+0x0): first defined here
```

**Linkavimo klaida (NL)!** Kodėl?

??? danger "Diagnozė: Funkcijų deklaracijos prototipai ≠ kintamųjų deklaracijos"
    
    **Funkcijoms:**
    ```c
    void push(char c);  // ✅ Deklaracija (prototipas)
    ```
    
    **Kintamiesiems globaliam apimties lygyje:**
    ```c
    char stack[STACK_SIZE];  // ❌ Apibrėžimas (definition)!
    int  top = 0;            // ❌ Apibrėžimas!
    ```
    
    **Problema:** Kintamieji **abiejuose** failuose tampa **apibrėžimais**, todėl linkeris mato **dubliavimąsi** (multiple definition).

---

## Žingsnis 3: Antipattern su #include (03_OK_Wrong)

Studentai dažnai bando "išspręsti" tiesiog įtraukdami `stack.c` į `user.c`:

=== "stack.c"

    ```c title="stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
    ```

=== "user.c"

    ```c title="user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc user.c -o app  # ✅ Veikia!
    ```

### Kodėl tai BLOGAI?

Nors kompiliuojasi, tai **antipattern**, nes viskas vėl viename kompiliavimo vienete, stack.c negali būti naudojamas kitur atskirai, pakartotinio kompiliavimo problema dideliuose projektuose, prieštarauja C/C++ filosofijai.

??? example "Pilnas user.c kodas su #include antipattern"

    ```c
    #include <stdio.h>
    #include "stack.c"  // ⚠️ ANTIPATTERN!

    int main(void) {
        int c;
        
        while ('\n' != (c=getchar())) push(c);
        while ('\n' != (c=pop())) putchar(c);
        
        return 0;
    }
    ```

!!! warning "Pamoka"
    `#include "*.c"` yra **ANTIPATTERN**. `#include` skirtas tik **header** failams (.h), ne implementation failams (.c).

---

## Teisingas kelias → Etapas 03

Teisingas sprendimas bus **03 etape** - sukurti **header** failą (`stack.h`), kuris deklaruoja funkcijas ir eksportuojamus kintamuosius.

**Kas pasikeis:**

```
03_Discovering_C_MODULE/
├── stack.h         # ← Prototipai + extern deklaracijos
├── stack.c         # ← Implementacija
└── user.c          # ← #include "stack.h"
```

---

## Mokymosi rezultatai

Po šio etapo studentai supranta **kompiliavimo vieneto** (translation unit) koncepciją, **patiria** skirtingų kompiliatorių elgesį (GCC vs Clang), mato kodėl **implicit function declarations** yra pavojinga, **patiria** linkavimo klaidas (NL) - ne teoriškai, bet praktiškai, žino, kad `#include "*.c"` yra antipattern, suvokia poreikį **header failams** su prototipais (etapas 03).

??? quote "Principas"
    **Kompiliavimo klaidos yra mokymosi įrankis**, ne problema, kurią reikia slėpti. Jos formuoja gilų supratimą.
    
    **Kompiliatorių skirtumai** (GCC leidžia, Clang draudžia) moko rašyti **standartinį** kodą, o ne pasikliauti vieno kompiliatoriaus tolerancija.

---

## Kitas žingsnis

Etape **03: Discovering C MODULE** išmoksime sukurti **header** failą (`stack.h`), naudoti `extern` raktinius žodžius, header guards (`#ifndef`), tikrą C modulio struktūrą.

??? tip "README failai su detaliais paaiškinimais"
    
    - [01_NC README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC)
    - [02_NL README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL)
    - [03_OK_Wrong README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong)
