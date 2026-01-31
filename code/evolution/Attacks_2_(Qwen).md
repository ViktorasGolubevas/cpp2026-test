Puiku! Štai **visi trys papildomi resursai**, paruošti jūsų studentų laboratorinei veiklai – viskas struktūrizuota, lengvai naudojama ir tiesiogiai susiję su jūsų C evoliucijos projekto logika.

---

## 📦 1. **Visi „atakų“ testiniai failai (atskiri `.c`)**

Išsaugokite šiuos failus kartu su savo ADT implementacijomis (pvz., `03\_stack.h`, `07\_stack.h` ir t.t.).

### 🔴 `attack\_global.c`

```c
// attack\_global.c – veikia tik su globaliais stack\[]/top
#include <stdio.h>
extern char stack\[];
extern int top;

int main(void) {
    top = 2;
    stack\[0] = 'A';
    stack\[1] = 'B';
    stack\[top++] = '!';  // neteisinga įterpimo operacija
    while (top > 0) putchar(stack\[--top]);
    putchar('\\n');
    return 0;
}
```

### 🔴 `attack\_reset.c`

```c
// attack\_reset.c – bandymas prieiti prie static funkcijos
#include <stdio.h>
extern void reset(void);  // deklaruojame, bet neapibrėžiame

int main(void) {
    reset();  // linkerio klaida, jei reset() yra static
    return 0;
}
```

### 🔴 `attack\_struct\_fields.c`

```c
// attack\_struct\_fields.c – veikia, kai struct Stack viešas
#include <stdio.h>
#include "06\_stack.h"  // arba 03\_stack.h, jei ten yra struct

int main(void) {
    struct Stack st;
    init(\&st);
    push(\&st, 'X');
    st.stack\[st.top++] = '?';  // tiesioginė manipuliacija
    while (!isEmpty(\&st)) putchar(pop(\&st));
    putchar('\\n');
    return 0;
}
```

### 🟢 `attack\_opaque.c`

```c
// attack\_opaque.c – BANDYMAS atakuoti opaque ADT
#include <stdio.h>
#include "07\_stack.h"  // turi būti: typedef struct Stack Stack;

int main(void) {
    Stack \*pst = create();
    init(pst);
    push(pst, 'X');

    // ŠI EILUTĖ TURI SUGENERUOTI KOMPIACIJOS KLAIDĄ:
    pst->stack\[pst->top++] = '!';

    while (!isEmpty(pst)) putchar(pop(pst));
    putchar('\\n');
    destroy(pst);
    return 0;
}
```

### 🟡 `test\_two\_stacks.c`

```c
// test\_two\_stacks.c – ar galima turėti du stekus?
#include <stdio.h>
#include "07\_stack.h"  // arba 06\_stack.h – NE 04\_stack.h!

int main(void) {
    Stack \*s1 = create();
    Stack \*s2 = create();
    init(s1); init(s2);
    push(s1, 'A');
    push(s2, 'B');
    printf("s1: %c\\n", pop(s1));  // A
    printf("s2: %c\\n", pop(s2));  // B
    destroy(s1); destroy(s2);
    return 0;
}
```

> 💡 \*\*Pastaba\*\*: Jei naudojate `06\_` versiją (kur nėra `create()`), pakeiskite:
> ```c
> struct Stack s1, s2;
> init(\&s1); init(\&s2);
> // ...
> ```

---

## ⚙️ 2. **Makefile – automatinis testavimas**

Sukurkite `Makefile` tame pačiame kataloge, kur yra jūsų ADT failai ir šie testai.

```makefile
# Makefile – testavimo scenarijams

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# ADT variantai (pasirinkite vieną per kompiliaciją)
ADT\_03 = 03\_stack.c
ADT\_04 = 04\_stack.c
ADT\_06 = 06\_stack.c
ADT\_07 = 07\_stack.c
ADT\_077 = 077\_stack.c

.PHONY: all clean test-03 test-04 test-06 test-07

all: clean
	@echo "Naudokite: make test-03, test-04, test-06 arba test-07"

# Testai su 03\_ (vieši globalūs)
test-03:
	$(CC) $(CFLAGS) attack\_global.c $(ADT\_03) -o attack\_global\_03 || echo "attack\_global\_03: KOMPIACIJA NEPRAEJO"
	$(CC) $(CFLAGS) attack\_struct\_fields.c $(ADT\_03) -o attack\_fields\_03 || echo "attack\_fields\_03: KOMPIACIJA NEPRAEJO"
	$(CC) $(CFLAGS) test\_two\_stacks.c $(ADT\_03) -o two\_stacks\_03 || echo "two\_stacks\_03: KOMPIACIJA NEPRAEJO"

# Testai su 04\_ (static – vienas stekas)
test-04:
	$(CC) $(CFLAGS) attack\_reset.c $(ADT\_04) -o attack\_reset\_04 || echo "attack\_reset\_04: KOMPIACIJA NEPRAEJO"
	$(CC) $(CFLAGS) test\_two\_stacks.c $(ADT\_04) -o two\_stacks\_04 \&\& echo "DĖMESIO: two\_stacks\_04 turėtų NEVEIKTI!" || echo "two\_stacks\_04: KOMPIACIJA NEPRAEJO (gerai!)"

# Testai su 06\_ (struct viešas)
test-06:
	$(CC) $(CFLAGS) attack\_struct\_fields.c $(ADT\_06) -o attack\_fields\_06 || echo "attack\_fields\_06: KOMPIACIJA NEPRAEJO"
	$(CC) $(CFLAGS) test\_two\_stacks.c $(ADT\_06) -o two\_stacks\_06 || echo "two\_stacks\_06: KOMPIACIJA NEPRAEJO"

# Testai su 07\_ (opaque – slėpimas)
test-07:
	$(CC) $(CFLAGS) attack\_opaque.c $(ADT\_07) -o attack\_opaque\_07 \&\& echo "DĖMESIO: attack\_opaque\_07 NETURĖJO KOMPIACIJOS PRAEITI!" || echo "attack\_opaque\_07: KOMPIACIJA NEPRAEJO (gerai!)"
	$(CC) $(CFLAGS) test\_two\_stacks.c $(ADT\_07) -o two\_stacks\_07 || echo "two\_stacks\_07: KOMPIACIJA NEPRAEJO"

clean:
	rm -f attack\_\* two\_stacks\_\*
```

**Naudojimas**:

```bash
make test-03   # testuoja 03\_ versiją
make test-07   # testuoja 07\_ versiją (slėpimas)
make clean     # išvalo sukompiliuotus failus
```

> ✅ Jei kompiliacija \*\*nepavyksta\*\* ten, kur turėtų nepavykti – tai \*\*gerai\*\* (apsauga veikia).  
> ❌ Jei kompiliacija \*\*pavyksta\*\* ten, kur neturėtų – tai \*\*blogai\*\* (trūksta slėpimo).

---

## 🔑 3. **Atsakymų raktas dėstytojui**

|Testas|Etapas|Tikėtinas rezultatas|Kodėl?|
|-|-|-|-|
|`attack\_global.c`|`01\_`, `03\_`|✅ Kompiliuojasi ir veikia|Globalūs kintamieji vieši|
|`attack\_global.c`|`04\_`, `07\_`|❌ Kompiliacijos klaida|Nėra globalių `stack\[]`/`top`|
|`attack\_reset.c`|`04\_`|❌ Linkerio klaida|`reset()` yra `static` → internal linkage|
|`attack\_struct\_fields.c`|`06\_`|✅ Kompiliuojasi|`struct Stack` pilnai matomas header’yje|
|`attack\_struct\_fields.c`|`07\_`|❌ Kompiliacijos klaida|`struct Stack` – incomplete type|
|`attack\_opaque.c`|`07\_`, `077\_`|❌ Kompiliacijos klaida|Opaque pointer – laukai neprieinami|
|`test\_two\_stacks.c`|`04\_`|❌ Neįmanoma (arba blogai veikia)|`static` kintamieji → vienas stekas sistemoje|
|`test\_two\_stacks.c`|`06\_`, `07\_`|✅ Veikia teisingai|Kiekvienas egzempliorius atskiras|

> 🎯 \*\*Pedagoginis momentas\*\*:  
> Kai studentas mato, kad `attack\_opaque.c` \*\*nesikompiliuoja\*\*, o `attack\_struct\_fields.c` – \*\*taip\*\*, jis \*\*fiziškai patiria\*\* informacijos slėpimo vertę.

---

## 📥 Kaip naudoti?

1. Išsaugokite visus `.c` failus ir `Makefile` kartu su savo ADT implementacijomis.
2. Leiskite studentams:

   * pabandyti kompiliuoti skirtingus testus su skirtingais ADT,
   * užpildyti lentelę „veikia / neveikia“,
   * padaryti išvadą: **kada ir kodėl reikia opaque pointerio?**

3. Diskutuokite apie **perėjimą į C++**:  
   *„Kodėl C++ klasė su `private` laukais iš karto suteikia tai, ko mes pasiekėme tik 8 etape C?“*

---

Jei norite, galiu:

* Sugeneruoti **ZIP archyvą** su visais failais,
* Paruošti **PDF instrukciją studentams**,
* Sukurti **C++ analogų testus** (pvz., bandymas prieiti prie `private` laukų).

Sakykite – ar reikia toliau plėtoti? 😊

