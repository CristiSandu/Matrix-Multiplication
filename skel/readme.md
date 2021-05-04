# Tema 2 - Matrix Multipication

In acesta tema o sa implementez operatia **`C = A * B * B_tr + A_tr * A`**  
( A_tr este **transpusa** lui A, B_tr este **transpusa** lui B si
A este o matrice triunghiularain )  
Tema va contine urmatoarele implementari:

- **blas** varinat cea mai optima utilizand functii blas ;
- **neopt** implementarea default cu optimizarile doar pentru A care este tridiagonala;
- **opt** prezinta implementare optimizata a variantei _neopt_;

## **neopt**

Am tinut cont ca A este superior triunghiulara astfel facand anumite operati in minus (acelea care erau influentate de partea inferioara a matricei A). Am ales sa fac urmatoare impartire a operatiilor.

### BB_tr = B \* B_tr

Aici nu B este o matrice normala inmultirea facandu-se normal. Singura "optimizare" sa facut la B_tr nu am mai transpus matricea doar am parcurs lini la coloane si coloane la lini pe B .

### ABB_tr = A \* BB_tr

Aici am tinut cont de faptul ca A este triunghiulara astfel cand am facut inmultirea am parcurs ulimul for de la i la N astfel facand doar inmultirile relevante petru o matrice superior triunghiulara.

### AA_tr = A_tr \* A

Aici avem o inultire intre o matrice inferior tiunghiulara si un superior triunghiulara. Astfel trebuie sa tinem cont de elementele din ambele matrici care ar trebui evitate la inmultire. Astfel la ultimul for trebuie sa avem de la 0 la minimul dintre lini si coloane astfel evitand inmultirile inutile.

### out = ABB_tr + AA_tr

La final se aduna rezultatele calculelor precedente.

## **blas**

La aceasta implementare m-am folosit de functiile din [**BLAS Atlas**](http://www.netlib.org/blas/) astfel:

- **B \* B_tr = DGEMM** (cblas_dgemm) - am ales aceasta functie deoarece B nu este triunghiulara
- **A \* BB_tr = DTRMM** (cblas_dtrmm) - am ales aceasta functie deoarece A este superior triunghiulara
- **A_tr \* A = DTRMM** (cblas_dtrmm) - acelasi criteriu A este superior triunghiulara si A_tr autoamt inferior triunghiulara

**DGEMM** rezolva o ecuatie de forma `rez <= alpha*A*B + beta*rez` astfel pentru cazul nostru de fata B \* B*tr avem : \_beta* = 0.0, _alpha_ = 1.0 , _A_ = B si _B_ = B_tr
Ca si format de apelare avem:

```c
cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
           m, n, k, alpha, A, k, B, n, beta, C, n);
```

unde:

- CblasRowMajor - arata ca matricea este stocata row major order
- CblasNoTrans - Arata tipul atricei A si B daca trebuie transpuse inainte de operatie
- m, n, k - dimensiunile matricilor

Aplicand pe cazul nostru avem :

```c
 cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans,
            N, N, N, 1.0, B, N, B, N, 0.0, BB_tr, N);
```

**DTRMM** rezolva o ecuatie de forma `B <= alpha*op( A )*B` astfel pentru ambele cazuri avem : _alpha_ = 1.0.
Am ales aceast metoda deoarece avem de aface cu o matrice triunghiulara astfel inmultim matricea A in cazul 1 si A_tr in cazul 2 cu un scalar 1, iar rezultatul il inmultim cu cealata matrce care devine si acumulator. Astfel pentru fiecare caz am salvat cu `memcpy` a doua matrice in variabila in care vreau sa retin rezultatul.
Ca si la functia precedenta trebuie sa punem niste flag-uri care sa tina cont de CblasRowMajor, CblasTrans sau CblasNoTrans, CblasUpper sau CblasLower.

Rezultatul final l-am adunat normal parcurgand matricile rezultate din operatiile anterioare.

## **opt**