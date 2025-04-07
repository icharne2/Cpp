liczby = []
parzyste = []
fragmenty = []
with open('pary.txt', 'r+') as pliczek:
    for dane in pliczek:
        liczby.append(dane[:2].rstrip())
        if int(dane[:2])%2 == 0:
            parzyste.append(int(dane[:2]))
        fragmenty.append(dane[2:].strip())

def czy_pierwsza(liczba):
    if liczba == 2:
        return True
    elif liczba % 2 == 0 or liczba < 2:
        return False

    do = int(liczba/2)
    for i in range (3, do, 2):
        if liczba%i == 0:
            return False
    return True

def pierwsze(value):
    pierwsze = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

    w = value - 2
    i = 1
    while czy_pierwsza(w) == False:
        w = value - pierwsze[i]
        d = pierwsze[i]
        i += 1
    print(value, d, w)

print("Zadanie 4.1")
for i in parzyste:
    pierwsze(i)

print("Zadanie 4.2")
print(fragmenty)

for i in fragmenty:
    max = 1
    max_letter = i[0]
    for n in range(len(i)-1):
        if i[n] == i[n+1]:
            suma += 1
        else:
            suma = 1
        if max < suma:
            max = suma
            max_letter = i[n]
    print(max_letter * max, max)

print("Zadanie 4.3")

min_l = 100
min_f = "z"*50
for i in range(0, len(liczby)):
    if int(liczby[i]) == len(fragmenty[i]):
        if min_l > int(liczby[i]) or (min_l == int(liczby[i]) and min_f > fragmenty[i]):
            min_l = int(liczby[i])
            min_f = fragmenty[i]
print(min_l, min_f)
