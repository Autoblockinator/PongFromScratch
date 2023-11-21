import os, sys, json, yaml
from copy import copy, deepcopy

def clear(): os.system('clear')



class Map(dict):
    
    def __init__(self, **kwargs):
        for k,v in kwargs.items(): self[k] = v
        return
    
    def __getattr__(self, name):
        if name in self: return self[name]
        else: return super().__getattribute__(name)
    
    def __setattr__(self, name, value): self[name] = value
    
    def __delattr__(self, name): del self[name]
    
    pass

def pmap(inmap: Map, max_depth= -1, hide = [],  _indent= 0, _path = ''):
    out = ''
    for k,v in inmap.items():
        if _path+'.'+k in hide: continue
        out += f'{"  " * _indent}{k}: '
        if isinstance(v, Map):
            if _indent == max_depth: out += '{...}'
            else: out += '\n'+pmap(v, max_depth, hide,  _indent + 1, _path+'.'+k)
        else: out += str(v)
        if out[-1] != '\n': out += '\n'
    if _indent == 0: print(out, end='')
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



mem = Map(func= Map(), settings= Map(default_hides = ['.func', '.settings']))

def pmem(max_depth= -1, hide= mem.settings.default_hides): pmap(mem, max_depth, hide)

def cls(max_depth= -1, hide= mem.settings.default_hides): clear(); pmem(max_depth, hide)

def save(): dumpmap(mem, 'pymem')

def load(): loadmap(mem, 'pymem')



def leave(code= 0): save(); exit()



try: load()
except FileNotFoundError: print('Previous session memory not found. mem = Map()')

cls()
