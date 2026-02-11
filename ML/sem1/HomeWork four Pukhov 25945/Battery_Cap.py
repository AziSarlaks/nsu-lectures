import Mendeleev_Table as mt
import re

def molar_mass(formula):
    elements_dict = {}
    molar_mass = 0.0

    pattern = r'([A-Z][a-z]*)(\d*)'
    matches = re.findall(pattern, formula)

    for element, count_str in matches:
        count = 1 if count_str == '' else int(count_str)
        if element in elements_dict:
            elements_dict[element] += count
        else:
            elements_dict[element] = count
    
    for element, count in elements_dict.items():
        atomic_mass = mt.get_atomic_mass(element)
        molar_mass += atomic_mass * count
    
    return molar_mass


def tc(formula, z_electrons):

    F = 96485 
    M = molar_mass(formula)
    
    q = (z_electrons * F) / (3.6 * M)

    return q

molar_mass("Fe4Li2Fe2")