from mcpi.minecraft import Minecraft
from sys import argv
mc = Minecraft.create()

#Creating the function
def place(BID):
    #Getting Pos1 and Pos2 from the text files.
    with open('pos1.txt') as f:
        P1=f.read()

    with open('pos2.txt') as g:
        P2=g.read()

    P1=P1.split()
    P2=P2.split()

    #Setting the blocks
    try:
        mc.setBlocks(int(P1[0]), int(P1[1]), int(P1[2]), int(P2[0]), int(P2[1]), int(P2[2]), int(BID))
    except ValueError:
        mc.postToChat("invalid block ID")

#Getting the args.
if len(argv)>1:
    try:
        place(argv[1])
    except FileNotFoundError:
        mc.postToChat("All pos aren't set. Use /pos to know how to set pos.")
else:
    mc.postToChat("I can't work if ya don't get me a block ID!")