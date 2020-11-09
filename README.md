# Mano blockchain

Šioje repozicijoje kuriama uždara blokų grandinė.

### v0.1

- Generuoja 1000 vartotojų 
- Generuoja 10 000 transakcijų
- Sukuria *genesis block*, kurio hašas prasideda 5 nuliais
- Galima ⛏ kasti blokus

**Vartotojas turi**:
- Viešąjį raktą
- Vardą
- Atsitiktinę sumą kreditų

**Transakcija sudaryta iš**:
- Siuntėjo(User)
- Gavėjo (User)
- Atsitiktinės sumos kreditų, nuo 0 iki siuntėjo turimo kreditų kiekio

**Bloko *proof-of-work* realizuotas** pasiimant Nonce ir do-while ciklu didinant jo reikšmę, kol hašas turės tiek nulių, kiek yra numatyta *Difficulty Target*.

**Genesis block hašas**:

![](https://i.imgur.com/anisM5I.png)

Bloko sunkumas numatytas toks, kad hašas turėtų 5 nulius pradžioje.

 ⛏ **Kasimas** ⛏ 
 
![](https://i.imgur.com/nj87MVB.png)
