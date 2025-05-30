# OOP_exam

## Aprašymas

Ši C++ programa analizuoja tekstinį failą (`text.txt`) ir atlieka šias užduotis:

1. **Žodžių skaičiavimas:** Suskaičiuoja, kiek kartų kiekvienas žodis pasikartoja tekste (ignoruojant skyrybos ženklus ir didžiąsias/mažąsias raides).
2. **Cross-reference lentelė:** Sukuria lentelę, kurioje nurodoma, kuriose teksto eilutėse kiekvienas daugiau nei vieną kartą pasikartojantis žodis buvo paminėtas.
3. **URL paieška:** Išskiria galimus URL adresus pagal tam tikrus kriterijus ir išveda juos į atskirą failą.

## Naudojimas

1. Į katalogą įdėkite šiuos failus:
   - `main.cpp` (programos kodas)
   - `text.txt` (analizuojamas tekstas)
   - `existing_urls.txt` (galimų URL galūnių sąrašas, pvz., `.lt`, `.com`, `.org` ir pan.)

2. Kompiliuokite programą:
   ```sh
   g++ -std=c++17 main.cpp -o oop_exam