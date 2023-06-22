from mcpi.minecraft import Minecraft
from sys import argv
mc = Minecraft.create()

if len(argv)>1:
    mc.restoreCheckpoint()
else:
    mc.postToChat("This will restore your world from the last command you posted.")
    mc.postToChat("All progress made since then will be deleted")
    mc.postToChat("If you want to continue, use /undo yes")