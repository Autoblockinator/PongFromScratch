import os, sys, json, yaml
from copy import copy, deepcopy

def clear(): os.system('clear')



class Map(dict):
    
    def __init__(self, **kwargs):
        for k,v in kwargs.items(): self[k] = v
        return
    
    def __getattr__(self, name):
        if name in self: return self[name]
        else: return super().__getattr__(name)
    
    def __setattr__(self, name, value): self[name] = value
    
    def __delattr__(self, name): del self[name]
    
    pass

def pmap(inmap: Map, indent = 0):
    for k,v in inmap.items():
        print(f'{"  " * indent}{k}: ', end= '')
        if isinstance(v, Map): print(); pmap(v, indent + 1)
        else: print(v)
    return

def map2dict(inmap: Map) -> dict:
    out = {}
    for k,v in inmap.items():
        if isinstance(v, Map): out[k] = map2dict(v)
        else: out[k] = v
    return out

def dict2map(indict: dict) -> Map:
    out = Map()
    for k,v in indict.items():
        if isinstance(v, dict): out[k] = dict2map(v)
        else: out[k] = v
    return out

def writefile(path, data):
    with open(path, 'w') as file: file.write(data)

def readfile(path) -> str:
    with open(path, 'r') as file: return file.read()

def dumpmap(inmap: Map, path: str):
    with open(path+'.json', 'w') as file:
        json.dump(map2dict(inmap), file, indent='\t')

def loadmap(inmap: Map, path: str):
    with open(path+'.json', 'r') as file:
        for k,v in dict2map(dict(json.load(file))).items(): inmap[k] = deepcopy(v)



mem = Map(methods= Map())

def pmem(): pmap(mem)

def cls(): clear(); pmem()

def dumpmem(): dumpmap(mem, 'pymem')

def loadmem(): loadmap(mem, 'pymem')

