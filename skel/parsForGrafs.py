import matplotlib.pyplot as plt

filenames = ["opt_m.graf","neopt.graf", "blas.graf"]
elements_disct = dict()

for file in filenames:
    f = open(file, "r")
    file_N = list()
    file_T = list()
    total_NT = list()
    for x in f:
        elements = x.split(":")
        if len(elements) > 1 :
            nns = elements[1].split("=")
            tts = elements[2].split("=")
            file_N.append(nns[1])
            file_T.append(float(tts[1]))
            total_NT.append(file_N)
            total_NT.append(file_T)
    elements_disct[file] = total_NT

print(elements_disct[filenames[1]][1])

for f in filenames :
    plt.plot(elements_disct[f][0], elements_disct[f][1], label=f)

plt.ylabel('Durata (s)')
plt.xlabel('N = Dimensiune Matrice')
plt.title('Comparatie performanta implementari')
plt.ylim(top=50.23)
plt.legend()
plt.savefig('comparatie.png')
plt.savefig('comparatie.svg')
plt.show()
