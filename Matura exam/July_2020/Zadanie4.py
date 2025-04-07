identyfikatory = []
with open('identyfikator.txt','r+') as pliczek:
    for dane in pliczek:
        identyfikatory.append(dane.rstrip())

print("Zadanie 4.1")

sumy = [[],[]]
max = 0
for id in identyfikatory:
    suma = 0
    for i in range (3, 9):
        suma += int(id[i])
    if max < suma:
        max = suma
    sumy[0].append(suma)
    sumy[1].append(id)

for i in range(0, len(sumy[0])):
    if max == sumy[0][i]:
        print(sumy[1][i])

print("Zadanie 4.2")

def czy_palindrom(text):
    text = text.lower()
    for i in range(0, int(len(text)/2)):
        if text[i-1] != text[-i]:
            return False
    return True

seria = []
numer = []
for i in identyfikatory:
    seria.append(i[0:3])
    numer.append(i[3:])

for i in range(0, len(seria)):
    if czy_palindrom(str(numer[i])) or czy_palindrom(str(seria[i])):
        print(identyfikatory[i])

print("Zadanie 4.3")
iloczyn1 = []

for i in seria:
    wynik1 = 0
    wynik1 = ((ord(i[0])-55)*7)+((ord(i[1])-55)*3)+((ord(i[2])-55)*1)
    iloczyn1.append(wynik1)

n = 0
for i in numer:
    wynik2 = 0
    wynik2 = ((int(i[1])*7) + (int(i[2])*3) + (int(i[3])*1) + (int(i[4])*7) + (int(i[5])*3))
    sum = wynik2 + iloczyn1[n]
    if sum%10 != int(i[0]):
        print(identyfikatory[n])
    n += 1

