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

def pmap(inmap: Map, indent= 0, max_depth= -1):
    out = ''
    for k,v in inmap.items():
        out += f'{"  " * indent}{k}: '
        if isinstance(v, Map):
            if indent == max_depth: out += '...'
            else: out += '\n'+pmap(v, indent + 1, max_depth)
        else: out += str(v)
        if out[-1] != '\n': out += '\n'
    if indent == 0: print(out, end='')
    else: return out

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

def pmem(max_depth= -1): pmap(mem, max_depth= max_depth)

def cls(): clear(); pmem()

def dumpmem(): dumpmap(mem, 'pymem')

def loadmem(): loadmap(mem, 'pymem')

try: loadmem()
except FileNotFoundError: print('Previous session memory not found. mem = Map()')
