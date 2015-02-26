import sys

try:
    tProbFileName = sys.argv[1]
    outFileName = sys.argv[2]
    tProbFile = open(tProbFileName, 'r')
    outFile = open(outFileName, 'w')
except:
    exit(1)

tProbFile.readline()
tProbFile.readline()
tProbFile.readline()

nodes = []
bonds = []

for line in tProbFile.readlines():
    line = line.split()
    origin = line[0]
    partner = line[1]
    strength = line[2]
    if origin not in nodes:
        nodes.append(origin)
    bonds.append((origin, partner, strength))

outFile.write("parameters \n")
for node in nodes:
    outFile.write("node id " + node + "\n")
for bond in bonds:
    if float(bond[2]) > 0.1:
        outFile.write("bond origin " + bond[0] + " partner " + bond[1] + " strength " + bond[2] + "\n")
