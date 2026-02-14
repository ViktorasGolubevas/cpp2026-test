# Etapas 02: Decomposing to UNITS
## Nuo monolito iki fizinio padalijimo

!!! tip "Šio etapo tikslas"
    Išmokti **fiziškai** atskirti programą į kompiliavimo vienetus, suprasti `#include` mechanizmą ir **patirti** tipines kompiliavimo/linkavimo klaidas kaip mokymosi įrankį.

---

## 🎯 Problema, kurią sprendžiame

Etape 01 turėjome **monolitinį failą** - visa logika vienoje vietoje. Tai veikė, bet:

- Sunku palaikyti didesnį kodą
- Negalima pakartotinai naudoti stack.c kituose projektuose
- Jokio moduliškumo
- Visi globalūs kintamieji matomit visur

**Sprendimas:** Fiziškai padalinti į atskirus **kompiliavimo vienetus** (translation units).

---

## 📂 Tikslinė struktūra

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

## 🔴 Žingsnis 1: Tiesiog padalijimas (NL klaida)

Intuityvus sprendimas - tiesiog **supjaustome** monolitą į du failus. Bet kas nutinka?

=== "stack.c"

    ```c title="02_NL/stack.c"
    #include <stdio.h>
    #define STACK_SIZE 10

    char stack[STACK_SIZE];
    int  top = 0;

    void push(char c) {
        if (top < STACK_SIZE) 
            stack[top++] = c;
        else  
            printf("Stekas pilnas\n");
    }

    char pop(void) {
        if (top > 0) 
            return stack[--top];
        printf("\nStekas tuscias");
        return '\n';
    }
    ```

=== "user.c"

    ```c title="02_NL/user.c"
    #include <stdio.h>

    void push(char c);  // ⚠️ Deklaracija be apibrėžimo
    char pop(void);

    int main(void) {
        int c;
        
        while ('\n' != (c=getchar())) push(c);
        while ('\n' != (c=pop())) putchar(c);
        
        return 0;
    }
    ```

=== "Kompiliavimas"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    ```

### 💥 Kas nutinka?

```
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `stack'; 
stack.o:(.bss+0x0): first defined here
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `top'; 
stack.o:(.bss+0x0): first defined here
```

**Linkavimo klaida (NL)!** Kodėl?

!!! danger "Diagnozė: Funkcijų deklaracijos prototipai ≠ kintamųjų deklaracijos"
    
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

## 🟡 Žingsnis 2: Antipattern su #include (OK_Wrong)

Studentai dažnai bando "išspręsti" tiesiog įtraukdami `stack.c` į `user.c`:

=== "user.c"

    ```c title="03_OK_Wrong/user.c"
    #include <stdio.h>
    #include "stack.c"  // ⚠️ ANTIPATTERN!

    int main(void) {
        int c;
        
        while ('\n' != (c=getchar())) push(c);
        while ('\n' != (c=pop())) putchar(c);
        
        return 0;
    }
    ```

=== "Kompiliavimas"

    ```bash
    gcc user.c -o app  # ✅ Veikia!
    ```

### ⚠️ Kodėl tai BLOGAI?

Nors kompiliuojasi, tai **antipattern**, nes:

1. **Nėra tikro padalijimo** - viskas vėl viename kompiliavimo vienete
2. **stack.c negali būti naudojamas** kitur atskirai
3. **Pakartotinio kompiliavimo** problema dideliuose projektuose
4. **Prieštarauja** C/C++ filosofijai

!!! warning "Pamoka"
    `#include "*.c"` yra **ANTIPATTERN**. `#include` skirtas tik **header** failams (.h), ne implementation failams (.c).

---

## ✅ Žingsnis 3: Teisingas kelias (Etapas 03)

Teisingas sprendimas bus **03 etape** - sukurti **header** failą (`stack.h`), kuris deklaruoja funkcijas ir eksportuojamus kintamuosius.

**Kas pasikeis:**

```
03_Discovering_C_MODULE/
├── stack.h         # ← Prototipai + extern deklaracijos
├── stack.c         # ← Implementacija
└── user.c          # ← #include "stack.h"
```

---

## 🎓 Mokymosi rezultatai

Po šio etapo studentai:

- ✅ Supranta **kompiliavimo vieneto** (translation unit) koncepciją
- ✅ **Patiria** linkavimo klaidas (NL) - ne teoriškai, bet praktiškai
- ✅ Žino, kad `#include "*.c"` yra antipattern
- ✅ Mato **poreikį header failams** (etapas 03)
- ✅ Suvokia, kad funkcijų prototipai ≠ kintamųjų deklaracijos

!!! quote "Principas"
    **Kompiliavimo klaidos yra mokymosi įrankis**, ne problema, kurią reikia slėpti. Jos formuoja gilų supratimą.

---

## 🔗 Kitas žingsnis

Etape **03: Discovering C MODULE** išmoksime:

- Sukurti **header** failą (`stack.h`)
- `extern` raktinius žodžius
- Header guards (`#ifndef`)
- Tikrą C modulio struktūrą

[→ Eiti į Etapą 03](lecture_03_module.md){ .md-button .md-button--primary }
