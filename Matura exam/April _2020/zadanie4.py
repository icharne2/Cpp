liczby = []
with open('dane4.txt','r+') as pliczek:
    for i in pliczek:
        liczby.append(int(i.rstrip()))

print("Zadnie 4.1")
min = 2 * pow(10,10)
max = 0
for value in range(len(liczby)-1):
    luka = abs(liczby[value]-liczby[value+1])
    if max < luka:
        max  = luka
    if min > luka:
        min = luka
print("Najmniejsza luka:", min)
print("Największa luka:", max)

print("Zadnie 4.2")

dlugosc = 0
poczatek = 0
koniec = 0
luka_pocz = 0
for i in range(len(liczby)-1):
    if luka_pocz:
        if luka_pocz == abs(liczby[i]-liczby[i+1]):
            dl += 1
        else:
            if dl > dlugosc:
                dlugosc = dl
                poczatek = begin
                koniec = liczby[i]
            luka_pocz = abs(liczby[i] - liczby[i + 1])
            begin = liczby[i]
            dl = 2
    else:
        luka_pocz = abs(liczby[i]-liczby[i+1])
        begin = liczby[i]
        dl = 2

print("Dlugosc:", dlugosc, "\nPocztek:", poczatek, "\nKoniec:", koniec)

print("Zadanie 4.3")
krotnosc_max = 0
wyniki = []
for i in range(len(liczby)-1):
    krotnosc = 0
    luka1 = abs(liczby[i]-liczby[i+1])
    for n in range(1, len(liczby)-1):
        luka2 = abs(liczby[n]-liczby[n+1])
        if luka1 == luka2:
            krotnosc += 1
    if krotnosc_max < krotnosc:
        krotnosc_max = krotnosc

print(krotnosc_max)

for i in range(len(liczby)-1):
    krotnosc = 0
    luka1 = abs(liczby[i]-liczby[i+1])
    for n in range(1, len(liczby)-1):
        luka2 = abs(liczby[n]-liczby[n+1])
        if luka1 == luka2:
            krotnosc += 1
    if krotnosc == krotnosc_max:
        wyniki.append(luka1)

wyniki = set(wyniki)

print("Krotnosc najczestsza:", krotnosc_max, "dla luk:", wyniki)





