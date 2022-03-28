# Architecture des ordinateurs

## Les Bases

C / Rust / ... \
 ↓ \
<span style="color:red;font-weight:700;font-size:20px">Assembleur</span>\
 ↓\
 ↓\
 ↓\
<span style="color:red;font-weight:700;font-size:20px">Processeur</span>

---
 ↑\
Transistor\
 ↑\
Physique Quantique

---

## 3 Phases

1. Assembleur
   Langage suffisament pauvre pour être utilisé par le processeur

2. Logique / Circuit logique
   Manipulation de portes logiques

## Addition binaires / Dépassement de capacités

'- + +' => jamais de dépassement

'+ + +' => Dépassement si res < 0

'- + -' => Dépassement si res > 0

## L'assembleur

CPU : Central Processing Unit contient des registres

(Ici architecture particulière non exisante
mais inspirée par d'autres architectures - Le Y86 - inspiré et simplifié du IA32)

Registre IP : Instruction Pointer
Exemples de nom de registres :

- %eap
- %abx
- %ecx
- %eai

__Additoner__ : addl reg1, reg2

__Soustraire__ : subl reg1, reg2

__iaddl__ : const, reg2\
__isubl__ : const, reg2\
Avec des constantes... (i = immediate)

Exemple :
_addl %eax, %ebx_

---

### Commandes

<br />
addl reg1, reg2 -> reg2 = reg1 + reg2

subl reg1, reg2 -> reg2 = reg1 - reg2

iaddl const, reg1 -> reg2 = const + reg2

isubl const, reg1 -> reg2 = const - reg2

mrmovl addr, reg -> copie addr dans reg (reg = addr)

rmmovl reg, addr -> copie reg dans addr (addr = reg)

rrmovl reg1, reg2 -> copie reg1 dans reg2 (reg2 = reg1)

irmovl const, reg -> copie const dans reg (reg = const)

<br />

jmp <"debut"> -> goto <"debut">

jle <"debut"> -> goto <"debut"> si <= 0

jl <"debut"> -> goto <"debut"> si < 0

je <"debut"> -> goto <"debut"> si = 0

jn <"debut"> -> goto <"debut"> si != 0

jge <"debut"> -> goto <"debut"> si >= 0

jg <"debut"> -> goto <"debut"> si > 0

<br />

---
<br />

### Les pointeurs et les tableaux

rmmovl %eax, 0x200

rmovl %eax, (%eax)

rmovl %eax, toto(%ecx) = adresse toto + %ecx
<br> <br>

### Exemples : ( C ≡ Y86 )

<br> <br>
"eax=toto;" ≡ mrmovl toto, %eax

"eax = &toto;" ≡ irmovl toto, %eax

"eax = *toto;" ≡ mrmovl toto, %eax & mrmovl (%ecx), %eax

<br />

---

<br />

### La pile

<br />

— La pile est une zone spécifique de la mémoire,
 gérée par un registre particulier : le pointeur de pile, %esp (« stack pointer »).

 <br />

— Les deux opérations élémentaires que l'on peut effectuer sur une pile sont :

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— l'empilage (« push »), qui ajoute une valeur au sommet de la pile.

L'instruction pushl %eax fait la chose suivante :

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— On décrémente %esp de 4

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— On écrit la valeur de %eax en mémoire à l'adresse %esp.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— le dépilage (« pop »), qui retire la valeur située au sommet de la pile.

L'instruction popl %eax fait l'inverse de pushl %eax.
L'appel de fonctions en y86, comme en x86, repose sur un certain nombre de conventions.

— La valeur de retour d'une fonction est contenue dans le registre %eax.

— Les paramètres sont passés sur la pile. Ils sont donc empilés par
l'appelant avant d'effectuer call,
et utilisés sur place par l'appelé. C'est l'appelant qui s'occupe de les enlever
de la pile.

<br />

— Concernant l'utilisation et la sauvegarde des registres lors des appels de fonction,
on distingue
deux types de registres :

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— registres « caller save » (« sauvegardés par l'appelant ») :
ces registres sontlibrement utilisables
par la fonction appelée, et doivent être sauvegardés si nécessaire par
la fonction appelante. Ce
sont les registres %eax, %ecx et %edx.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
— registres « callee save » (« sauvegardés par l'appelé ») :
ces registres doivent être restitués
intacts à la fonction appelante.
Toute fonction désireuse de les utiliser doit en sauvegarder la
valeur puis la restaurer avant de terminer.
Ce sont les registres %ebx, %esi, %edi et %ebp.
Le registre %esp est à part, car il est directement impliqué dans l'appel de fonction.

<br />

---

### Appel de fonctions (TD-03)

- __call f__ :
Calcul de l'adresse de retour (adresse ligne suivante) et empilement
puis jump dans f

- __ret__ : Dépilement de l'adresse de retour puis _goto_ %esp (généralement adresse
de retour)

- __paramètres__ : empilement du paramètre sur la pile puis call.
Le paramètre est recupéré a l'adresse du registre suivant (+ 4)
si plusieurs paramètres : Définition de l'ordre de récupération : f(a,b) =>
_Push b | push a_ (paramètre n°i : @esp + 4i)

- __Fonctions récurrentes__ : On empile le nouveau paramètre à l'adresse
de l'ancien paramètre

⚠ : Si empilement avant ret : \
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - soit on popl la pile
   jusqu'a retour au ret

   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - soit on iaddl x a %esp pour
   repointer sur l'adresse de retour

## Etude détaillée du y86 -- HCL

eax = rA

intsig = #define

fetch : Recupere l'instruction en mémoire et calcul du pc increment

### Exemple ajout decl dans le hcl

L’instruction decl %reg décrémente un registre, c’est-à-dire lui retranche 1.
Elle est équivalente à l’instruction isubl 1, %reg, mais est censée prendre moins
de place en mémoire, afin de réduire la taille
des programmes qui l’utilisent.

Ajout dans intsig
Ajout dans need_regids

### Exemple ncall

fetch needreg {pushl};
destE {
   icode == PUSHL: rESP;
}

AluA icode == PUSHL : -4;

alub icode == PUSHL: valB

srcB icode == PUSHL: rESP;

memWrite PUSHL;

addr icode == PUSHL : valE;

data  icode == PUSHL : valA;

srcA icode == PUSHL rA;ù

## Les portes logiques

### TD05

#### <u>Exercice 2 : Additionneur</u>

- [__Demi-Additioneur__](https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVVw5HCjsKaQBR9w59kw7/DgcOMwrNuBgREw5M0wrFqE8KTLm52TcOTwqTDqcKDw4LCqMKkw4hYGMK6bjbDu8OvHRgMCGfCiH3Cg3PDjzlzwrnDt3LDp8O9w77CrsOXI8KvYSAOZGLCmMKUw7YLw6DDgMOCw71BwpDCiXsBw5IDf11zHm3DucKZTETCkjEFwosLw7Qzf8Otw7XDnsKJeDsxMiHDsxnDucOoN8Kww5ULAMK/LcOmbcOwKUsPwqvDnU4TwojDm8O4wprDr8O3EWvDo8OeasOdBsKnHjjDksKDw6jDqhl5AsOwBwQhw7UUw4ZJUV0UwonDmA4Ewr5kw6kSfMK1woRXGcKgW8KfLQB+QsOgNhTCo8KUw63CpVM7w7jDjMOFJnlbw4Q+D1gCGcKmw6DDlsKcFcOxw44gFD9mZwjCmhDDlVlIHAjDpsOswojDnAsYOn3DjcKiaBrDgMOvw7DCuMKAwpJpHHTDoAYYJlzCh8OFwp9sE2HCpwDCn8Kwwox9wojDi2pDw5zDkzTDuCXDm2IfAA0WYEB0woNTw6BIMcKLw4XDgMKDwrDDjB1GTsKZdsOAZMOMY2fCsTzDgVDCnsOEJsO+wo1jw7zDuMKYRTA0wo0ywojDjyLDrmMzw5Qfw5B8w7TCo34PEyHCmz9AwoJLwqwQw6bCsV9qw6UGw6xvw6jCsxTCrsOcPgkDw7kkKVQ+w4vCtWw4bsKfwrzCkcKJaTt9Em3CtizDksOsw6ZywoFWBsKGMjBdZWAMawYbworDt3jCpTbClcOaHTvDqnjDi8Ktw5Qzwo5KwpHCr8OfSj9UemdoFnrCm1rClR4uw6pWw77DliV/w5ouw4AWw6TCn8OfFMKVw5pWasKLKsO1wrgmw5ZeKcKVw5opw5UjwrPCpcOGd8OPw5XDmcKjUm1aKnPDo8O/DnfClcOcdmhbwq7Cu8OjKsO1wrgsfFk2w4M2KzXCusOMwq7Dm27DkMOrwr5fw4lTejXDhz7Cj2PDpgvCnsOUR3nCl8OwY2nDtRDDhsK5wpvDoMOlQD/DiMKxwqnDt8KtwqLCmg3DqlBPHTbCqEY3w5XCqFEtPcOVwro9V8O7w7YEwpwGw5XDrsKmw57CmMOrwqjDocOaQXVvw4/DlW0kMMOSU8OHDVfCp8KbWnd1w7VUwoM2bMOHJcK3wpjCuMO7wrvCj38=)

- [__Additioneur__](https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVWXcKPwppAFH3Dn2TDv8KDw6FZN3zCiWDCmiZWbWLDksOFZsOXNMKbNH1QGMKVFBnCi0PDl8ONZsO/e8KHwq8Cw4MZw5Qnw6XDnHPDjsOcO3PDp8OCw7vDvV3Cr8KnwrwGPsObK2NNV8OVfgbDrEnCsMObM2VswpfDgGlPX1fClMKGG3pWw4YsTkgOwrMSw7rCmT7DtnrDrwp7OxJlwqzDjMKmw4pHX8OAwpbDjwDDvDbCn8K1w4HDr8OJacK/w5xuJcKBwqjCjcKvw6huF8KSNsOuLldtcMOiwoIlXcKILsKfwpAnAF8gCMKpw4cgworCs8OdRcKRwpBsQcOgS3JawoDCqjnCvEwAw53DvGwCw7ATAjcBG8Kdw4jCjjvCtcKDT8KUwq3Do8K3ecOkUcKfw4TCkMKhM2rDjkgWw68MQsOxY3LChsKgDlHCmQXDh8KBYEYOw4g9woPCocOTw5ckDCc+wqzDg8KlDEomwpHDn8KBa8KgwpnDsD7DjMO/JMOrEDvDuXjChUXDpEHCnMOvNsOEXcOJAT8nG8OsA8Kgw4EcNMKIwqxxMhwpwqYRG8K4EMOmwrnDg8OIMcKRNhjCj8K5w6TDjBZHGErCk1hHwr9xwoweHsKTEMKGJmECw7FpSD1swobDjgccPsK6wqg/woLCmMOxw4MfIEEZw4vChGnDrFc+cn3DsjfDsMOIwqk9csKLGcOYVwLCnz9xwprDisO/w7PDkWwYVl95w6PDk13Dk8O7SsK4w57CkMKQwofDl8KqdMKIVgZaw5Mgw7stDcK8QD7ChisHwr3DqcKgwpt2w6XCsAEpwqRDwrhSG8K5ejgqw5TDvGXDtF8tG8OXwpXDmsOMw5XClm3Dp2rDncKsw5RoLjfDhMODXGxrw4XDkkPDqwbCscOVXMOZwqhvPBI3wqseCVXDm8KXwqpuw4rDrcKmw5xww7QLw7LCl0bDrk5ReMK6W2nDk8OUw48cwr/DpBpyTW3Dln5Zwp9+AMOUw7RFw485ZcOTw6rCtcKOOcKBwo4Rw6RFw4M5ZsKewr5uw5UOw53Co8OoDsKmXyU1woPCosOnNMObbB98w7pRU8K7wokewo0iw6IxGsOXL8OjNsKmwofDosO6PQRRwrobwozClsOWDzzCgXoJFVfCu8KBwqvDn8OANQTCrsOaTcOVw6rCtnLCqinCuHYkYArCriM5dSjCuMKaw53DlMK6wqslwqdawoJrRwLClsOgasOLwqkjw4FVw6/Cpl7CucKvw7bDtcKnZQvCrh0JOGLCv3TDmDrDlyfCq8KJw73DnWHCm3HCr0xXE8OvwoLDk8OBFcOvw4LCsMOgZsK3w7TDvsOuw6Mf)

- __Addtionneur 8bits__ : Utiliser 8 fulladders avec a0 et b0 --> a8 b8.

#### <u>Exercice 3 : Codeurs, décodeurs, multiplexeurs, démultiplexeurs</u>

- [__Codeur 2 bits__](https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wo1Vw6/Ci8OaMBjDvn5ww7/Cg8OkwrMeNsKNw5rDiRg4dSDDrMOqw6HDiRjCjH3DkDZqWWxcwpvDrMKUw6PDvsO3w4XCtmLDmj4VP2nCn19vwpPCvH3Ds8O+w7jDkGrCkcK3KFQ7MnRowrfDm8OOwoAdwo/CtjtFwobDngVId8OybSnCpVjDiyMZwqpEw7McVhfDqMOXw7nCscOVeifDqnTDoGRIJmPDssORwq5gw7NXAH7Cn07DqsOgwotOd8Ozw43CpsKBwojDq8O4Um7Ct8KCw5dxf8K+wqzCgyMfwpTDtCE6X8KgTADDvsKEIMKUHsKiOMOJdhcxwoJvAMOxVcKnM8KwagPDjzXCkMKzLwzCgMKfEcK4wo7DlCDDpVvCk1QnF1LCrcKSw5M0DmTDiBPCqMKgSsKyCcOPw7jCmyQ0P8OrIwQpRMKbIgwODBPCvkfDqRkMwpPCvmkhRiFcwocvFcK0wozDosOwBsOuwoBmw4LDuzDDvcKrVwInwoXCuMOCLA4gbnYbw6J+w4MBwr/DqjXDjgFQZwoawqTCqXEyHDnDhsKxw6rDuBA2w68OwpnCg25sMMODw7nDvMKoZgdIwp1fYhXDv8OBwpzDnD9rAcKpwpHDkBAfCxnDoDB0PsOgw7DDkcKHw7ojSsKUOcO8DjJcwrjDjHjDpn7DpyM3w6TDv8KiwoDCp8O1wpFbw4zDgDbCiULDs2RkXcOzw5/CjGbDqsOSNjnCmV8zw4vCiVjCrcK5MMO0wqrDmzhEwq8BTiXCoMOPwqwAw5DDoMK1AFoOcHvDlApAwp/DrcOYMsK7woXCmcOlXsK3f8O1wqLDm8KlVsKcwpXCizPDplnDhV18E13DncK9w5zDrRXDpcOpw4B6w7UUbF7DmcOdL8K7XWbDrRwcDQvDizzDiMONPcKnw5jDtk/DlsOKw5HChVIye8KFwpl2w7PDih4rwpvCrU4KZBzDs0DDicOEbsKmTSLDt0XDuzxFw7HCucKFwpQsw47Do0lqZcKvw7wqdcOuwpfDksO7wqXDrH5pwq8iHTRLw7sVwqnDlywdVMKkw45twqljSVnCs8OUwqvCpMOSw5tSwpTCmh3DosOjw4PDh38=)

- [__Decodeur 2 bits__](https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVVXcKPwppAFH3Dn2TDv8KDw6FZN8OMOMOAaMKaJlZtYsOSw4Vmw5c0TcKaPijCjErCisKMw4XCocKrw5nDrH8vDBBhwrjCjMO4wqbDp8Oec8OmfhzCr8Ovwo8Pwr3CnsOxFsO4Ym/CjBE2w43CvgTDtizDmMOtwoUxwqYlcMOaw7PCtxXDp8OhwobCn8KNwrHCiBPClsODwqLChH5lX3vCvXdDXMKOw4wYG8KzwqnDscORV8Kww6UrAH7Cm8OPwprDoMO3w6TCtF9uwrctwoHCqMKJwq/DuG4XwrImw64uV01ww6ICT8K6IMK6fMKBNAHDsCcIwoLCqcOHIMKKw6V0wqFIw4jCtkDDoEtyWgBdwqfDsDIBw5LDiWcCwoDCnyBwEwjDp8OEdsKpUjPDuMOCw4U6wr7DjCPCj8O7LAYzwrDDoGTDhmRcGwTDicOPw4kZBDHCiMK2ScKkOEDCmMKxA8KkLmFQw6lrEsKGEx/DrMODw6UCwqRMIl/CgyPDgEzDsBzDpn/Ck3UIK8O5w7ALwovDiAPDsXTDmiDDrsK2LMO4NcOZw4A6ADTCmAMGaTPCjsOEIcOGNBIDF8KEw5PDmsOBw4gxaTVYGnPDmVkswo5gKCtiHcO9woFjw7zDsMKcwoRgaBImID4NwrkHwotBw7sBwpYPw71QfwTCsUjClz/CgAhlTBLCs8OYw6/DvMOkw7rDrF/DoMKxE3hyw7tGw6DCp8Kfw5IUM8O9wpzCnmVkw5PCvnExw4ZDbMO2wo1wwr1hYcOLbcOODsOlwpXCjXI2GcOiJhs8wqnDmRXCv8OScU7Cp8KkeMOcwq7DkMOBe1/Cpw/Dq3RMbsORwrPDk33CpcKTwpxuwps5XcKOwqDCpMKDR8K+w77CulV/HWF6w5fDq3ZOd8KKw4HCo8KhfcOjw7U6w50pwoovJsKPw6nCrcOiw6t0WsK8wo5pR3rDscOHeVUYw6UKwpjCmlLCgVTCh8K/BH7DkcKKcQrDn0nCmsOcHcK9w6HCnHrDvQjDlcO7J8KmeVfDvwjDlwdAMMK5a8O5SMOxwp7ChcOvw7MeUsOMZ8Ohw7vDtsKHCsO3w5nCtMKowp/DnsOqwr/CsUBkwpcbLDxgVRw4M8K7KDh1woXDusOxQMK1a8Okw7EoYsKew6Bxw7UgbWN+KMKkwp7CgijCs8KEw6DCpcO0E09EwrXCiGsuVnNxe8OuUMOJwqXDrcKpRMKVNcO1wrnCqMKaw5vCnmopwrJ2e8Kqwq3CpBJ9asK1woBRe8KqwqPDtsKlwqnDgMOpw54XVWQ1C8Kjw53Cix0pwqrCmh3CpMO7w6nDnhhqGEzCp8KMw5QxaMKaQw07asKGJsKTO8KOAsKpw55FwpYmwrnDoV7DnTAaw7bDlcO1wqcaWFfCssKlCmsswoxUwrvDqzbCosKawrjDjMKVF8Omw7HDocOjPw==)

- [__Multiplexeur 2 bits__](https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVWXWvDmzAUfS/DtD8EP8Knw4XCsmVHDWPCkDUZFFZnwrRlDMOGHsKSWEnDjFwrc8OkwrXCpcO0wr9Pw74IwpHCrWPChcK8JcOnwp5zLMOrHl/DqcO9w7JiMHBewpJYbsKdMcOxXHdYAVvCnmzCtsOSGcKzA8Kww5/CisKXJyHDksKleHXDhjIveA3DiwPDtMKrw7w7GMK8O8OybcOHwp3CsTPCvXU+woYdbMO+CMOAb8KzwqkJfi/DtsObw7l6w51Tw4hMw7xJbDYpN8OxaMO+ZMKCwpMIPDLCgsOow7wBeQLDsCcEIXXCl2R5wrXCu8KowpLDsjUofCnDtnfDoMKtFTwvAMKdfsKmAMO8woTDgGUiR3vCvlFOZsOxQcOIRcO+NsOLViLDpjlkeFLDkCnCr8Oqw5YiFMOfF8KvEMO0IMOaZ8KhcCDCmMOyZ8OkXsOBw5DDqWvCkcKmwpMYwr5HJCTClEzCssOYwoITECbCvA/Cs8K/w4Uiw4VOMX7Dgl3CtsKCwrjDmm3CiEc9DX4swpbDmAdAVzMQwpDCvsOgVDhSw5xmw7IqwoLCsFo7wqzDrMKKw57CgMKpWsOEX8Olw50OwpbDikUswrI/wrgmwp7Dr8KLFMKWJmkBw7HDm1TCrMKwGcOqD2g+w7pQfyTCuVTDjcK/QsKCQ8KtEsKWwrXDn8O1w4jCjcO5wr9kw4XDt8Omw4htZsOgw5BJYsO1T8ORXMO1W8KNZsOfY0PDp01Ndz8cOsOpYsOJU1VewrjCvUPDtGhAw5oGw6XDqXA0AAE3DMK8wo4Bw5MNw4BnaxjDuG0DP8OwNAMfwo/DtsKjwprDlsOqw5DDt8OqDWDDtMKowobDo8K+LQ/DmnIvCMOPwpLCh8KNwpzCusO1w5rDi3c4Qz5qw4spOcO1dHXDlhzDlcKsVsKPKMKtw5fCrsKrw5HCocOUEsOfNMOiwqB+cT9kdsKxOsOswrXDkDTCsSPDjcKjwqnDnnR0LWjCq8Kbw4wxZsOuORLCm8KZbTLDpzVdwqPCvhbCmcK+a8KCw6nDondcGDvDrcKiwp/ChsKaVcKTQsOfbcO2woNqVsOWA8K0wr0xQXtFwoEeZnjDm8OSO0rCmjDCsjIHw5XCl3jCosKlw6XCtUzCk8KPDl1xTcO5w55tw43Cp8KVw4gywr7CkiLDl0fDlDoXw4/DjVDCuk7CsjIhUhwafi0KwqlPwqMjwpfCnMOBw7XDjsOgw7pncGnCh8Orw5rCqUTCt8Klw73DnMKgwrsEO8OVwrQlwpAbdmzCvX7DmxDDmnrCkDvDqsOYw7rDvcK2I2jDq0Muw6vDmFrDtsKLdWzCg37Dqk3DhzXCtFN1w5fCkSXCi0bDgCxJIEbDgmzDpG7DhMKIwqVrw4QIwpnCpRcVw5nDk8OJwpZtI8Odw6zCsBNcfRU3Fm43PMOkw5DCkGpoXF58w7wH)
