liczby = []
with open('liczby.txt', 'r+') as pliczek:
    for value in pliczek:
        liczby.append(int(value))

pierwsze = []
with open('pierwsze.txt', 'r+') as dane:
    for value in dane:
        pierwsze.append(value.rstrip())

def czy_pierwsza(liczba):
    do = int(liczba/2)
    for i in range(2,do):
        if liczba%i == 0:
            return False
    return True

def waga(N):
    suma = 0
    for i in range(0, len(N)):
        suma += int(N[i])
    if suma > 9:
        return waga(str(suma))
    return suma

print("Zadanie 4.1")
for i in liczby:
    if czy_pierwsza(i) and ((i >= 100) and (i <= 5000)):
        print(i)

print("Zadanie 4.2")
for i in pierwsze:
    text = ""
    for n in range(0, len(i)):
        text += i[len(i)-1-n]
    if czy_pierwsza(int(text)):
        print(i)

print("Zadanie 4.3")
ilosc = 0
for i in pierwsze:
    if waga(i) == 1:
        ilosc += 1

print("Ilość liczb, dla których waga jest równa 1:", ilosc)







