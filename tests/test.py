import random

with open("words.txt") as f:
    f2 = open("wooords.txt","w")
    lines = f.readlines()
    list = []
    for line in lines:
        list.append(line)
    random.shuffle(list)
    for word in list:
        f2.write(word)
    f2.close()