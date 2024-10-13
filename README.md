# Image-Processor
Task 1
-se parcurge fiecare linie din matrice
-se parcurg coloanele pana la jumatate (flipul se face pe orizontala)
-se interschimba valorile pixelului de pe pozitia i, j cu cele ale simetricului sau fata de axa de simetrie in raport cu coloanele imaginii
-se returneaza imaginea primita ca paramaetru in urma modificarilor
Task 2
-se aloca b, o matrice cu dimensiunile potrivite (latimea=lungimea celei parametru, lungimea=latimea celei parametru)
-pentru a roti imaginea, el. de pe linia i, se afla pe  coloana i
-se descopera relatia b[i][j]=image[j][M-1-i] intre pixelii matricei pe care dorim sa o obtinem si cea transmisa
-se dezaloca imaginea primita ca parametru (nu mai este necesara, dorim sa o obtinem pe cea modificata)
-se returneaza b
Task 3
-se verfica daca parametrii primiti sunt potriviti pentru matricea primita (x, y nu pot avea valori mai mari decat lungimea, respectiv latimea img; suma dintre coord pct de pornire si dimensiunile matricei rezultat nu pot depasi dimensiunile matricei primite(nu exista val pt el. ce depasesc conturul))
-se aloca b, o matrice cu dimensiunile potrivite( w, h, primite ca parametrii)
-se salveaza in b valorile din matricea primita, aceasta parcurgandu-se pornind de la (x,y) pana la (x+h-1, y+w-1) inclusiv (pentru a se obtine dimensiunile cerute)
-se dezaloca matricea primita ca parametru (nu mai este necesara, dorim sa o obtinem pe cea modificata)
-se returneaza b
Task 4
-se aloca b, o matrice cu dimensiunile potrivite (latimea=latime initiala + 2*cols, lungime=lungime+2*rows) (adaugam linii atat deasupra, cat si dedesubt; adaugam coloane atat in stanga, cat si in dreapta)
-populam matricea b, verificand daca coord pozitiei curente nu sunt din matricea primita, punand in acest caz, valorile primite drept parametrii pentru fiecare culoare, altfel pastram valorile din matricea primita
-se dezaloca matricea primita ca parametru (nu mai este necesara, dorim sa o obtinem pe cea modificata)
-se returneaza b
Task 5
-se modifica valorile din matricea destinatie incepand cu el de pe linia y si coloana x (pornim de la el de coord (y,x))
-elementele din matricea sursa, ale caror valori se copiaza in matricea destinatie, pornesc din origine ((0,0)), astfel se obtine relatia image_dst[i][j][k]=image_src[i-y][j-x][k] (se copiaza valoarea fiecarei culori pt fiecare din acesti pixeli) (verificare: image_dst[y][x][k]=image_src[0][0][k])
-de asemenea, asiguram ignorarea elementelor din matricea sursa care depasesc marginile matricei destinatie prin conditia:
linia pe care se afla elementul din imaginea sursa sa aiba valoare mai mica sau egala cu lungimea matricei destinatie (i-y<M_dst)
SI
coloana pe care se afla elementul din imaginea sursa sa aiba valoare mai mica sau egala cu latimea matricei destinatie (j-x<N_dst)
-se returneaza imaginea destinatie
Task 6
-se creeaza o copie cu valorile matricei parametru pentru a putea accesa aceste valori(care se modifca pe parcurs in aplicarea filtrului, altfel am pierde vecinii initiali), necesare pentru a calcula noile valori R, G, B pt fiecare pixel
-se parcurge matricea destinatie, iar pentru fiecare pixel se calculeaza noile valori pt R, G, B implementand suma data in enunt
-pt calcularea acestor valori, parcurgem vecinii in functie de marimea filtrului ( pornim de la copie[i-f][j-f]), verficand ca acestia exista (coord lor nu depasesc dimensiunile matricei)
-astfel, obtinem valori reale (filtrul are val de tip float; in calcularea noilor valori R, G, B castam valorile imaginii in float pt a putea realiza inmultirea) pe care le castam in intregi pentru a le putea atribui matricei primite cu el de tip int
-asiguram fiabilitatea noilor valori R, G, B si le atribuim pixelului
-se dezaloca copie, care nu mai este necesara
-se returneaza matricea modificata
Task 7
-pt a salva imaginile la un anumit index se creeaza tabloul de 4 dimensiuni image;
image[i][j][k][p] -- i=index, j=linia matricei de la indexul i, k=coloana matricei de la indexul i; p=0 -> valoarea R pt pixelul de la linia j si coloana k a imaginii de la indexul i, p=1 -> valoarea G pt pixelul de la linia j si coloana k a imaginii de la indexul i, p=2 -> valoarea B pt pixelul de la linia j si coloana k a imaginii de la indexul i
-se citeste comanda de la tastaura si se compara sirul de caractere cu cele corespunzatoare comenzilor definite si se executa actiunile corespunzatoare
-pt a astepta si citi comenzi noi se realizeaza o bucla cu whiile(1), ce se intrerupe cu comanda "e"(contine break)
-comanda 'e'
    -dezaloca matricea image, in care sunt salvati pointeri la imaginile salvate, dar si vectorii care salveaza dimensiunile fiecarei imagini
    -dezaloca matricea filter, in care sunt salvati pointeri la filtrele create(tablouri bidimensionale), dar si vectorul care salveaza marimea fiecarui filtru
    -iese din bucla cu break;
-comanda 'l'
    -citeste dimensiunile noii imagini si calea la care se afla
    -aloca dinamic prima imagine loaduita si vectorii care salveaza dimensiunile fiecarei imagini
    -realoca image, marindu-i capacitatea cu un sizeof(int***) pt a putea loadui o noua imagine, dar si vectorii care salveaza dimensiunile fiecarei imagini, pentru a putea salva dimensiunile noii imagini
    -salvam in vectori noile dimensiuni
    -folosim functia read_from_bmp cu parametrii corrspunzatori pt a putea loadui imaginea
    -incrementam variabila ce contorizeaza nr img
-comanda 's'
    -citim indexul imaginii loaduite care vrem sa fie salvata si calea unde va fi salvata
    -dam acesti parametrii functiei write_to_bmp, alaturi de dimensiunile imaginii
-comanda 'ah'
    -egalam pointerul image[index] cu cel returnat de functia flip_horizontal ce primeste aceasta imagine ca parametru si o oglindeste pe orizontala
-comanda 'ar'
    -intializam pointerul rot cu rezultatul functiei rotate_left, ce are ca parametru imaginea de la indexul citit de la tastatura
    -realocam imaginea de la indexul dat pt a avea dimenisiunile corespunzatoarea imaginei rotite
    -copiam valorile din rot in imaginea de la indexul dat, realocata corespunzator anterior
    -odata modificata imaginea, dezalocam rot, care devine inutil
    -de asemenea, interschimbam valorile dimensiunilor (valorile acestora se interschimba datorita rotirii)
-comanda 'ac'
    -asemanator 'ar', initializam pointerul matcrop cu rezultatul functiei crop; realocam imaginea de la index cu dimensiunile potrivite rezultatului; copiam valorile; dezalocam matcrop, care devine inutila; salvam noile dimensiuni ale imaginii de la index
-comanda 'ae'
    -asemanator 'ac', initializam pointerul auxae cu rezultatul functiei extend; realocam imaginea de la index cu dimensiunile potrivite rezultatului; copiam valorile; dezalocam auxae, care devine inutila; salvam noile dimensiuni ale imaginii de la index
-comanda 'ap'
    -egalam pointerul image[index-dst] cu rezultatul functiei paste, ce primeste aceasta imagine ca parametru pentru destinatie si o alta pentru imaginea sursa, alaturi de dimensiunile lor
-comanda 'cf'
    -asemantor loaduirii iamginilor, la crearea primului filtru, alocam dinamic taloul tridimensional f, ce asociaza matricele corespunzatoare fiecarui filtru cu indexul,dar si vectroul lf care salveaza dimesniunea fiecarui filtru
    -de la al doilea filtru, realoca f pentru a putea salva un filtru nou si lf pentru a putea salva lungimea noului filtru
    -se citesc valorile noului filtru
    -salvam dimensiunea noului filtru
    -incrementeaza valoarea contorului nr filtrelor
-comanda 'af'
     -egalam pointerul image[index_img] cu rezultatul functiei apply_filter, ce primeste aceasta imagine ca parametru si filtrul de la indexul citit(index_filter), alaturi de dimensiunile lor
     -astfel se modifca in modul dorit imaginea de la indexul dat (dimesniunea este constanta)
-comanda 'df'
    -pornind cu filtrul de la indexul citit pana la penultimul filtru, eliberam memoria aferenta si o alocam cu dimensiunea urmatorului filtru si copiam valorile urmatorului filtru in acesta, analog pentru dimensiuni in lf
    -eliberam memoria ocupata de ultimul filtru, care este deja salvat pe o pozitie anterioara si ii egalam lungimea cu 0
    -astfel, s-a sters filtrul de la index si s-au shiftat celalate cu o pozitie
    -decrementam valoarea contorului pt nr de filtre
    -realocam lf si f, acestea avand o dimensiune mai mica in urma stergerii filtrului
-comanda 'di'
    -analog 'df'(cu o dimensiune in plus), in loc de lf, tratam vectorii pt ambele dimensiuni, width, height.
