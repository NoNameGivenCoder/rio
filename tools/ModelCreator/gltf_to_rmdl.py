from structs import Model

#from obj_reader import read_obj
from gltf_reader import read_gltf
from packer import pack

import sys

meshes = read_gltf(sys.argv[1])

model = Model()
#model.meshes = [ meshes[1], meshes[0] ]
model.meshes = meshes
model.materials = []

dataLE = pack(model, '<')
with open(sys.argv[2], "wb") as outf:
	outf.write(dataLE)
