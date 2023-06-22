from sys import argv
from items import *
from mcpi.minecraft import Minecraft
mc = Minecraft.create()


# Error protection
try:
    x, y, z = mc.player.getTilePos()
    y+=int(argv[1])
    mc.setBlock(int(x), int(y), int(z), Block["glass"])
except:

    # Try more stuff that can cause errors
    try:

        # Tell the user something went wrong
        mc.postToChat(f'Could not set block "glass" at {x} {y} {z}')

    # Oops
    except:

        # Tell the user something went terribly wrong
        mc.postToChat("Command failed")
