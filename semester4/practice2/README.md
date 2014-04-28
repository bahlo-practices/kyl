# Praktikum 2

## Aufgabe 1
- Beim AES wird blockweise gearbeitet
- Der AES macht vor der Substitution noch ein `XOR` mit dem letzten Block.

## Aufgabe 2
2. Eine Permutation ändert die Reihenfolge von Abbildungen (beispielsweise Zeichen). Sie wird zum Berechnen des Rundenschlüssels benötigt.
3. Weil sie linear ist, d.h. wenn man den Ciphertext und den Klartext hat, kann man beliebige andere mit dem gleichen Schlüssel verschlüsselte Ciphertexte entschlüsseln
4. Zur Diffusion (durchmischung)

## Aufgabe 3
2. Substitutionen sind nichtlineare Abbildungen, die Zeichen komplett ersetzen. Sie wird ebenfalls für die Berechnung des Rundenschlüssels benötigt, ist dabei vor allem für den Teil der Konfusion verantwortlich
3. Die Substitution ist nicht ausreichend, da durch eine Häufigkeitsanalyse nach und nach der Text entschlüsselt werden kann.

## Aufgabe 4
Weil XOR in beide Richtungen funktioniert, im Gegensatz zu AND oder OR.
Beispiel:
- `110011 ^ 111100 = 001111` kann zurückgerechnet werden: `111100 ^ 001111 = 110011`
- `110011 & 111100 = 110000` kann nicht zurückgerechnet werden: `111100 & 110000 = 110000`
- `110011 | 111100 = 111111` kann ebenfalls nicht zurückgerechnet werden: `111100 | 111111 = 111111`

