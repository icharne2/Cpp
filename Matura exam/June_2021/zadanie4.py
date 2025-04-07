dane = []
with open('napisy.txt', 'r+') as pliki:
    for i in pliki:
        dane.append(i.rstrip())
print(dane)

print("Zadanie 4.1")
cyfry = 0
for i in dane:
    for n in range(0, 50):
        liczba = ord(i[n])
        if liczba >= 48 and liczba <= 57:
            cyfry += 1
print(cyfry)

print("Zadanie 4.2")
haslo = ''
n = 0
for i in range(19,1000,20):
    haslo += dane[i][n]
    n += 1

print(haslo, '\nZadanie 4.3')

def czy_palindrom(slowo):
    slowo = slowo.lower()
    do = int((len(slowo)) / 2)
    for i in range(1, do):
        if slowo[i] != slowo[-i]:
            return False
    return True

for i in dane:
    if czy_palindrom(i):
        if i[1] == i[49]:
            i = i + i[0]
        if i[0] == i[48]:
            i = i[49] + i
        print(i[25], end="")

print('\nZadanie 4.4')

cyferki = []
haslo = ''
end = 0
for i in dane:
    napis = ''
    for n in range(0, len(dane[1])):
        l = ord(i[n])
        if l >= 48 and l <= 57:
           napis += i[n]
    if len(napis)%2 != 0:
        napis = napis[:len(napis)-1]
    for x in range(0, len(napis), 2):
        grupowanie = napis[x] + napis[x+1]
        grupowanie = int(grupowanie)
        if (grupowanie >= 65) and (grupowanie <= 90):
            zamiana = chr(grupowanie)
            if zamiana == 'X':
                end+=1
            haslo += str(zamiana)
    if end == 3:
        break

print(haslo)