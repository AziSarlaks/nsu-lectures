from typing import List, Union
V = "аеёиоуыэюяaeiouy"
C = "бвгджзйклмнпрстфхцчшщъьbcdfghjklmnpqrstvwxz"
P = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

def reverse_string(s: str) -> str:
    """
    
    Возвращает реверсированную строку.

    Аргументы:
        s: Исходная строка

    Возвращает:
        Реверсированная строка
    
    Пример:
        >>> reverse_string("hello")
        'olleh'
    
    """
    return s[::-1]

def is_palindrome(s: str) -> bool:
    """
    
    Проверяет является ли строка палиндромом.

    Аргументы:
        s: Исходная строка

    Возвращает:
        True - если строка является палиндромом, иначе False
    
    Пример:
        >>> is_palindrome("helleh")
        True
        >>> is_palindrome("hello")
        False
    
    """
    return s[::-1] == s

def count_of_letters(s: str, t: str) -> int:
    """
    
    Считает количество гласных или согласных букв в строке.

    Аргументы:
        s: Исходная строка
        t: Какие буквы искать ("VOWELS"/"CONSONANTS")

    Возвращает:
        Количество букв
    
    Пример:
        >>> count_of_letters("абвг", "VOWELS")
        1
        >>> count_of_letters("абвг", "CONSONANTS")
        3
    
    """
    return sum([(s.lower()).count(i) for i in V]) if t.lower() == "vowels" else sum([(s.lower()).count(i) for i in C])

def are_anagrams(s1: str, s2: str) -> bool:
    """
    
    Проверяет являются ли строки анаграммами.

    Аргументы:
        s1: Первая строка
        s2: Вторая строка

    Возвращает:
        True - если строки анаграммы, иначе False
    
    Пример:
        >>> are_anagrams("абвг", "гБва")
        True
        >>> are_anagrams("абвг", "абвгд")
        False
    
    """

    return sorted([i for i in s1.lower()]) == sorted([j for j in s2.lower()])

def phone_number_format(phone: str):
    """
    
    Форматирует номер телефона с 8 на +7.

    Аргументы:
        phone: Номер телефона в формате 8....

    Возвращает:
        Номер телефона в формате +7....
    
    Пример:
        >>> phone_number_format("81234567899")
        +71234567899
    
    """

    return "+7" + phone[1:]

if __name__ == "__main__":
    print(f"1) Реверс строки: {reverse_string("ABC")}")
    print(f"2) Является ли строка палиндромом: {is_palindrome("FAAF")}")
    print(f"3.1) Подсчет количества гласных букв: {count_of_letters("fffaaf", "VOWELS")}")
    print(f"3.2) Подсчет количества согласных букв: {count_of_letters("fffaaf", "CONSONANTS")}")
    print(f"4) Являются ли строки анаграммами: {are_anagrams("fafd", "dAfF")}")
    print(f"5) Форматирование номера телефона: {phone_number_format("81234567899")}")