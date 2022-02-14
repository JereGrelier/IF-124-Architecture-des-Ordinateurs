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

## Les portes logiques
