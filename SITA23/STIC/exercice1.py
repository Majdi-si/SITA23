## Exercice 1 ##

f = {
    0x0: 0x9,
    0x1: 0xb,
    0x2: 0xc,
    0x3: 0x4,
    0x4: 0xa,
    0x5: 0x1,
    0x6: 0x2,
    0x7: 0x6,
    0x8: 0xd,
    0x9: 0x7,
    0xa: 0x3,
    0xb: 0x8,
    0xc: 0xf,
    0xd: 0xe,
    0xe: 0x0,
    0xf: 0x5
}

def sbox(x):
    return f[x]

def split(key):
    return key >> 4, key & 0xf

def round(state, roundKey):
    new_state = sbox(state ^ roundKey)
    return new_state

def encrypt(key, plaintext):
    k0, k1 = split(key)
    state = plaintext
    state = round(state, k0)
    state = round(state, k1)
    return state

print("Chiffré 0x5 avec clé 0xb3 : ", encrypt(0xb3, 0x5))


## Exercice 2 ##

# 1) Il faut que la fonction soit inversible pour déchiffrer

f_inv = {v: k for k, v in f.items()}

def round_inv(state, roundKey):
    new_state = f_inv[state] ^ roundKey
    return new_state

def decrypt(key, ciphertext):
    k0, k1 = split(key)
    state = ciphertext
    state = round_inv(state, k1)
    state = round_inv(state, k0)
    return state

print("Déchiffré 0x4 avec clé 0xb3 : ", decrypt(0xb3, 0x4))

## Exercice 3 ##

# 1) Le type d'attaque la plus faible est l'attaque KPA (Known Plaintext Attack) car il suffit de connaître un seul couple clair/chiffré pour retrouver la clé avec un seul tour de chiffrement 
# 2) Dans notre exemple, ça ne marche pas car pour trouver la clé, il faut connaître 2 couples clair/chiffré. On ne peut pas retrouver la clé avec un seul couple clair/chiffré
# 3) Au premier tour, il y a 16 possibilités pour la clé, au deuxième tour, il y a 256 possibilités pour la clé
# 4) On ne peut pas réaliser une cryptanalyse par ce biais car au bout de 2 tours, on a 256 possibilités pour la clé. Sachant qu'on ne connait le nombre de tours, on ne peut pas déterminer la clé 

## Exercice 4 ##

# 1) Il faut 512 étapes pour brute force la clé car : 16 possibilités pour le premier tour * 16 possibilités pour le deuxième tour = 256 possibilités pour la clé * 2 tours (étapes élémentaires) = 512 possibilités pour la clé
# 2) Il y a 16 messages claires possibles
# 3) Il y a 256 clés possibles
# 4) IL y a 16 messages chiffrés possibles
# 5) Il exite des clés qui chiffrent un même message clair en un même message chiffré
# 6) Donc, on peut trouvé la clé en 32 étapes (16 messages possibles * 2 tours)

## Exercice 5 ##


def bruteforce(m, c):
    possible_keys = set()
    for k0 in range(16):
        for k1 in range(16):
            key = (k0 << 4) | k1
            if encrypt(key, m) == c:
                possible_keys.add(key)
    return possible_keys


print("Clés trouvées : ", bruteforce(0x5, 0x4))