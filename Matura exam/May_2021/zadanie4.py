polecenia = []
with open('przyklad.txt', 'r+') as pliczek:
    for value in pliczek:
        w = value.split()
        polecenia.append(w)
print(polecenia)

print("Zadanie 4.1")
napis = []
for i in range(0, len(polecenia)):
    if polecenia[i][0] == "DOPISZ":
        napis.append(polecenia[i][1])
    if polecenia[i][0] == "ZMIEN":
        napis[-1] = polecenia[i][1]
    if polecenia[i][0] == "USUN":
        napis.pop(-1)
    if polecenia[i][0] == "PRZESUN":
        for n in range(0, len(napis)):
            if polecenia[i][1] == napis[n]:
                if napis[n] == "Z":
                    napis[n] = "A"
                else:
                    napis[n] = chr(ord(polecenia[i][1])+1)
                break
print("Całkowita długość naisu wynosi: ", len(napis))

print("Zadanie 4.2")
max = 0
polecenie = ""
dlugosc = 1

for i in range(0, len(polecenia)-1):
    if polecenia[i][0] == polecenia[i+1][0]:
        dlugosc += 1
        if max < dlugosc:
            max = dlugosc
            polecenie = polecenia[i][0]
    else:
        dlugosc = 1

print(polecenie, max)

print("Zadnie 4.3")
max_slowo = ""
ilosc = 1
suma = 1
dopisywane = []
for i in range(0, len(polecenia)):
    if polecenia[i][0] == "DOPISZ":
        dopisywane.append(polecenia[i][1])

for i in range(0, len(dopisywane)):
    for x in range(i+1, len(dopisywane)):
        if dopisywane[i] == dopisywane[x]:
            suma += 1
        if ilosc < suma:
            max_slowo = dopisywane[i]
            ilosc = suma
    suma = 1

print(max_slowo, ilosc)

print("Zadnie 4.4")
for i in napis:
    print(i, end="")

