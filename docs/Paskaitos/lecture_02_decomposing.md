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
├── 02_NL/              # Not Linking - linkavimo klaida
│   ├── stack.c         # Stack funkcijos
│   └── user.c          # main() + naudojimas
└── 03_OK_Wrong/        # Veikia, bet antipattern
    ├── stack.c
    └── user.c
```

---

## Žingsnis 1: Tiesiog padalijimas (02_NL)

Intuityvus sprendimas - tiesiog **supjaustome** monolitą į du failus. Bet kas nutinka?

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

## Žingsnis 2: Antipattern su #include (03_OK_Wrong)

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

Po šio etapo studentai supranta **kompiliavimo vieneto** (translation unit) koncepciją, **patiria** linkavimo klaidas (NL) - ne teoriškai, bet praktiškai, žino, kad `#include "*.c"` yra antipattern, mato **poreikį header failams** (etapas 03), suvokia, kad funkcijų prototipai ≠ kintamųjų deklaracijos.

!!! quote "Principas"
    **Kompiliavimo klaidos yra mokymosi įrankis**, ne problema, kurią reikia slėpti. Jos formuoja gilų supratimą.

---

## Kitas žingsnis

Etape **03: Discovering C MODULE** išmoksime sukurti **header** failą (`stack.h`), naudoti `extern` raktinius žodžius, header guards (`#ifndef`), tikrą C modulio struktūrą.

??? tip "README failai su detaliais paaiškinimais"
    
    - [02_NL README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL)
    - [03_OK_Wrong README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong)
