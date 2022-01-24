# Architecture des ordinateurs

## Les Bases

C / Rust / ... \
    ↓ \
<span style="color:red;font-weight:700;font-size:20px">Assembleur</span>\
    ↓\
    ↓\
    ↓\
<span style="color:red;font-weight:700;font-size:20px">Processeur</span>\
___

    ↑
Transistor\
    ↑\
Physique Quantique

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

(Ici architecture particulière non exisante mais inspirée par d'autres architectures - Le Y86 - inspiré et simplifié du IA32)

Registre IP : Instruction Pointer
Exemples de nom de registres :

- %eap
- %abx
- %ecx
- %eai

Additoner : addl reg1, reg2

Soustraire : subl reg1, reg2

iaddl : const, reg2\
isubl : const, reg2\
Avec des constantes... (i = immediate)

Exemple :

addl %eax, %ebx
___

m r movl addresse, reg ==> Copie de ce qui se trouve a l'addresse dans le registre

r r movl reg1, reg2 ==> Reg 1 va dans reg2

irmovl const, reg2 ==> Const va dans reg2

rmmovl reg, addresse ==> Copie du registre en mémoire