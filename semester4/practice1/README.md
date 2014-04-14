# Praktikum 1
## Aufgabe 1
1. Der Text wurde mithilfe des Caesar Cipher verschlüsselt
2. Der Schlüssel lautet 19
3. `FUER AUFGABE ZWEI KANN DIE HAEUFIGKEITS-ANALYSE IN JCRYPTOOL HILF-REICH SEIN.`

## Aufgabe 2
### Klartext

```
DIE KRYPTOLOGIE IST EINE WISSENSCHAFT, DIE SICH MIT INFORMATIONS- SICHERHEIT BESCHAEFTIGT.
BIS INS SPAETE 20. JAHRHUNDERT WAREN VE- RSCHLUESEELUNGSVERFAHREN DER EINZIGE
FORSCHUNGSGEGENSTAND. MIT DER ETABLIERUNG DES ELEKTRONISCHEN DATENVERKEHRS KAMEN WEITERE
BEREICHE HINZU. DAZU ZAEHLEN DIGITALE SIGNATUREN, IDENTIFIKATIO- NSPROTOKOLLE,
KRYPTOGRAFISCHE HASHFUNKTIONEN, GEHEIMNISTEILUNG, ELEKTRONISCHE WAHLVERFAHREN UND
ELEKTRONISCHES GELD. HEUTE IST DIE KRYPTOLOGIE IN DIE FACHGEBIETE SYMGETRISCHE
KRYPTOGRAPHIE, PUBLIC- KEY-KRYPTOGRAPHIE, HARDWAREKRYPTOGRAPHIE UND THEORETISCHE
KRYPT- OLOGIE UNTERTEILT
```

### Lösungsweg
1. Mithilfe von JCrypTool die Häufigkeit bestimmer Buchstaben herausgefunde, dabei war der Buchstabe `O` auffallend häufig aufzufinden, wir gehen also davon aus, dass dies der Buchstabe `E` ist.
2. Da das erste Wort höchstwahrscheinlich ein Artikel ist, kommt nur `DIE` infrage.
3. Mit diesem Start können wir nach und nach die Buchstaben ersetzen und kommen auf folgende Tabelle:

```
A = K
B = C
C = L
D = A
E = S
F = P
G = M
H = O
I =
J = D
K = Z
L = T
M = Y
N = G
O = E
P = W
Q = N
R = U
S = F
T = I
U =
V = R
W = J
X = B
Y = V
Z = H
```
