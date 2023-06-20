from mcpi.minecraft import Minecraft
from time import sleep
mc = Minecraft.create()

while True:
	blockEvents = mc.events.pollBlockHits()
	if blockEvents:
		for blockEvent in blockEvents:
			x,y,z = blockEvent.pos
			mc.postToChat(f'Set pos 1 to ({x}, {y}, {z}')
