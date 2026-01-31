Puiku! Štai **testiniai „atakų“ scenarijai**, kurie aiškiai parodo, **kas paslėpta ir kas ne** kiekviename C evoliucijos etape. Jie skirti **studentų laboratorinėms užduotims** – leidžia patikrinti, ar ADT yra saugus nuo netinkamos prieigos.

---

## 🧪 **Testinių „atakų“ scenarijų rinkinys**

Kiekvienas scenarijus bandys:

* tiesiogiai modifikuoti steko vidinę būklę (`stack\[]`, `top`),
* naudoti „vidinius“ metodus (pvz., `reset()`),
* sukurti du stekus ir patikrinti, ar jie nepersidengia.

---

### 🔴 **1. Ataka: Tiesioginė prieiga prie globalių kintamųjų**

**Taikomas etapams**: `01\_`, `03\_` (kur `stack\[]` ir `top` yra globalūs)

```c
// attack\_global.c
#include <stdio.h>
extern char stack\[];
extern int top;

int main(void) {
    // Simuliuojame, kad stekas jau naudojamas
    top = 2;
    stack\[0] = 'A';
    stack\[1] = 'B';

    // "Ataka": įterpiame simbolį be push()
    stack\[top++] = '!';

    while (top > 0) {
        putchar(stack\[--top]);
    }
    putchar('\\n');
    return 0;
}
```

✅ **Tikėtinas rezultatas**: `!BA`  
❌ **Problema**: ADT nėra apsaugotas – bet kas gali keisti vidinę būklę.

---

### 🔴 **2. Ataka: Naudojimas „vidinio“ metodo (`reset`)**

**Taikomas etapams**: `04\_` (kur `reset()` yra `static`, bet bandoma iškviesti iš išorės)

```c
// attack\_reset.c
#include <stdio.h>
extern void reset(void);  // bandome „atgauti“ vidinę funkciją

int main(void) {
    reset();  // linkerio klaida, jei reset() yra static
    return 0;
}
```

✅ **Tikėtinas rezultatas**:

* **Klaida**: `undefined reference to 'reset'` → **apsauga veikia**
* Jei kompiliuojasi – **slėpimas sugedęs**

---

### 🔴 **3. Ataka: Tiesioginė prieiga prie struktūros laukų**

**Taikomas etapams**: `06\_` (kur `struct Stack` pilnai matomas header’yje)

```c
// attack\_struct\_fields.c
#include <stdio.h>
#include "06\_stack.h"

int main(void) {
    struct Stack st;
    init(\&st);
    push(\&st, 'X');
    // "Ataka": tiesioginis laukų pakeitimas
    st.stack\[st.top++] = '?';
    while (!isEmpty(\&st)) {
        putchar(pop(\&st));
    }
    putchar('\\n');
    return 0;
}
```

✅ **Tikėtinas rezultatas**: `?X`  
❌ **Problema**: Nors naudojamas tipas, **vidiniai laukai vieši** → nėra abstrakcijos.

---

### 🟢 **4. Bandyta ataka: Prieiga prie opaque struktūros laukų**

**Taikomas etapams**: `07\_`, `077\_` (kur `struct Stack;` tik forward declaration)

```c
// attack\_opaque.c
#include <stdio.h>
#include "07\_stack.h"

int main(void) {
    struct Stack \*pst = create();
    init(pst);
    push(pst, 'X');

    // "Ataka": bandome tiesiogiai prieiti prie laukų
    pst->stack\[pst->top++] = '!';  // ← KOMPIACIJOS KLAIDA!

    while (!isEmpty(pst)) {
        putchar(pop(pst));
    }
    putchar('\\n');
    destroy(pst);
    return 0;
}
```

✅ **Tikėtinas rezultatas**:

* **Kompiliacijos klaida**: `invalid use of undefined type 'struct Stack'`
* **Apsauga veikia!** – studentas negali „atakuoti“ vidinių duomenų.

---

### 🟡 **5. Testas: Ar galima turėti du stekus?**

**Taikomas etapams**: `04\_` (su `static`) vs `06\_`/`07\_`

```c
// test\_two\_stacks.c
#include <stdio.h>
// Pasirinkite tinkamą headerį: 04\_stack.h, 06\_stack.h, arba 07\_stack.h

int main(void) {
    // Etapas 04: NEVEIKS – nėra dviejų stekų
    // Etapas 06/07: VEIKS

    struct Stack \*s1 = create();  // arba tiesiog struct Stack s1;
    struct Stack \*s2 = create();

    init(s1); init(s2);
    push(s1, 'A');
    push(s2, 'B');

    printf("s1: %c\\n", pop(s1));  // turėtų būti 'A'
    printf("s2: %c\\n", pop(s2));  // turėtų būti 'B'

    destroy(s1); destroy(s2);
    return 0;
}
```

✅ **Tikėtinas rezultatas**:

* **04\_**: Neįmanoma sukurti dviejų stekų → **ribojimas**
* **06\_/07\_**: Veikia → **ADT palaiko daugelį egzempliorių**

---

## 📋 Rekomenduojamas naudojimas

1. **Paskirstykite šiuos scenarijus kaip „užduotis“**:  
   *„Pabandykite sukompiliuoti kiekvieną ataką su skirtingais jūsų ADT versijomis. Užpildykite lentelę: veikia / neveikia / kodėl.“*
2. **Lentelės pavyzdys studentams**:

|ADT versija|Ataka 1 (global)|Ataka 2 (reset)|Ataka 3 (struct fields)|Ataka 4 (opaque)|Dviejų stekų testas|
|-|-|-|-|-|-|
|`03\_`|✅ veikia|–|–|–|✅|
|`04\_`|❌ neveikia|❌ klaida|–|–|❌ neįmanoma|
|`06\_`|–|–|✅ veikia|–|✅|
|`07\_`|–|–|❌ klaida|❌ klaida|✅|

> ✅ = sauga \*\*neveikia\*\* (atakavimas pavyko)  
> ❌ = sauga \*\*veikia\*\* (atakavimas nepavyko)

---

Jei norite, galiu:

* Sugeneruoti **visus failus kaip atskirus `.c`**, paruoštus parsisiuntimui,
* Sukurti **Makefile**, kuris automatiškai paleistų visas „atakų“ versijas,
* Paruošti **atsakymų raktą dėstytojui**.

Ar norėtumėte tokių papildomų resursų?

