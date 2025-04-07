liczby = []
with open('liczby.txt','r+') as pliczek:
    for value in pliczek:
        liczby.append(int(value))

def silnia(liczba):
    liczba = str(liczba)
    suma = 0
    for i in range(0, len(liczba)):
        silnia = 1
        for n in range(1, int(liczba[i])+1):
            silnia *= n
        suma += silnia
    return suma

print(liczby)

print("Zadanie 4.1")
potegi = []
for i in range(12):
    potegi.append(pow(3, i))

ilosc = 0
for i in liczby:
    for n in potegi:
        if i == n:
            ilosc +=1
print(ilosc)

print("Zadanie 4.2")
for i in liczby:
    if i == silnia(i):
        print(i)

print("Zadanie 4.3")
print(liczby)
def nwd(liczba1, liczba2):  #lub z biblioteki math math.gcd(liczba1, liczba2)
    liczba1 = int(liczba1)
    liczba2 = int(liczba2)
    while liczba2 != 0:
        liczba1, liczba2 = liczba2, liczba1%liczba2
    return liczba1

with open('wyniki4_3.txt', 'w') as plik:
    max = 0
    max_nwd = 0
    begin = 0
    for i in range(0, len(liczby)-1):
        ciag = 1
        poczatek = 0
        n = i
        max_nwd = liczby[n]
        while nwd(max_nwd, liczby[n + 1]) != 1:
            ciag += 1
            max_nwd = nwd(max_nwd, liczby[n + 1])
            if poczatek == 0:
                poczatek = liczby[n]
            n += 1
        if ciag > max:
            max = ciag
            najwiekszy = max_nwd
            begin = poczatek
    wynik = "Nwd: " + str(najwiekszy) + "\nDlugosc: " + str(max) + "\nPocztek: " + str(begin)
    plik.write(wynik)
print("nwd:", najwiekszy, "dlugosc:", max, "pocztek", begin)







