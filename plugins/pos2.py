from mcpi.minecraft import Minecraft
mc = Minecraft.create()
try:
	pos1=None
	while not pos1:
		blockEvents = mc.events.pollBlockHits()
		if blockEvents:
			for blockEvent in blockEvents:
				pos1 = blockEvent.pos
				x,y,z=pos1
				with open('pos2.txt', 'w') as writer:
					text=str(int(x)) + " " + str(int(y)) + " " + str(int(z))
					writer.write(text)
				mc.postToChat(f'Set pos 2 to ({x}, {y}, {z})')
except: mc.postToChat('Command failed')