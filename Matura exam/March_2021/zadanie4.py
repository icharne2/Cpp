dane = []
with open('galerie.txt', 'r+') as pliczek:
    for value in pliczek:
        w = value.split(" ")
        dane.append(w)

print("Zadanie 4.1")

kraje =[]
for i in range(0, len(dane)):
    kraje.append(dane[i][0])

kraje = set(kraje)

for n in kraje:
    s = 0
    for i in range(0, len(dane)):
        if n == dane[i][0]:
            s += 1
    print(n, s)

print("Zadanie 4.2")
print("a)")
max = 0
min = pow(10, 1000)
miasto_max = ""
miasto_min = ""
for i in range(0, len(dane)):
    galerie = 0
    suma = 0
    for n in range(2, len(dane[1]),2):
        if int(dane[i][n]) and int(dane[i][n+1]):
            galerie += 1
            powierzchnia = int(dane[i][n])*int(dane[i][n+1])
            suma += powierzchnia
    if min > suma:
        min = suma
        miasto_min = dane[i][1]
    if max < suma:
        max = suma
        miasto_max = dane[i][1]
    print(dane[i][1], suma, galerie)

print("b)")
print("Najwieksza powierzchnia: ", miasto_max, max)
print("Najmniejsza powierzchnia:", miasto_min, min)

print("Zadnie 4.3")
maksimum = 0
miastoMax = ""
miastoMin = ""
minimum = pow(10,1000)

for i in range(0, len(dane)):
    wyniki = []
    text = ""
    for n in range(2,len(dane[1]), 2):
        if int(dane[i][n]) and int(dane[i][n + 1]):
            powierzchnia1 = int(dane[i][n]) * int(dane[i][n + 1])
            if str(powierzchnia1) not in text:
                wyniki.append(powierzchnia1)
                text += str(powierzchnia1) + " "
    if maksimum < len(wyniki):
        maksimum = len(wyniki)
        miastoMax = dane[i][1]
    if minimum > len(wyniki):
        minimum = len(wyniki)
        miastoMin = dane[i][1]

print(miastoMin, minimum)
print(miastoMax, maksimum)




