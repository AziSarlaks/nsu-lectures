import math
from typing import List, Union
PI = 3.141592653589793
E = 2.718281828459045

def add(a: Union[int, float], b: Union[int, float]) -> Union[int, float]:
    """
    Сложение двух чисел.
    
    Аргументы:
        a: Первое число
        b: Второе число
    
    Возвращает:
        Сумма a и b
    
    Пример:
        >>> add(5, 3)
        8
        >>> add(2.5, 1.5)
        4.0
    """
    return a + b

def subtract(a: Union[int, float], b: Union[int, float]) -> Union[int, float]:
    """
    Вычитание двух чисел.
    
    Аргументы:
        a: Уменьшаемое
        b: Вычитаемое
    
    Возвращает:
        Разность a и b
    
    Пример:
        >>> subtract(10, 4)
        6
    """
    return a - b

def multiply(a: Union[int, float], b: Union[int, float]) -> Union[int, float]:
    """
    Умножение двух чисел.
    
    Аргументы:
        a: Первый множитель
        b: Второй множитель
    
    Возвращает:
        Произведение a и b
    
    Пример:
        >>> multiply(3, 7)
        21
    """
    return a * b

def divide(a: Union[int, float], b: Union[int, float]) -> float:
    """
    Обычное деление (/) двух чисел.
    
    Аргументы:
        a: Делимое
        b: Делитель
    
    Возвращает:
        Результат деления a на b
    
    Ошибки:
        ZeroDivisionError: Если b равно 0
    
    Пример:
        >>> divide(10, 2)
        5.0
    """
    if b == 0:
        raise ZeroDivisionError("Деление на ноль невозможно")
    return a / b

def floor_divide(a: Union[int, float], b: Union[int, float]) -> int:
    """
    Целочисленное деление (//) двух чисел.
    
    Аргументы:
        a: Делимое
        b: Делитель
    
    Возвращает:
        Целая часть от деления a на b
    
    Ошибки:
        ZeroDivisionError: Если b равно 0
    
    Пример:
        >>> floor_divide(10, 3)
        3
    """
    if b == 0:
        raise ZeroDivisionError("Деление на ноль невозможно")
    return a // b

def modulus(a: Union[int, float], b: Union[int, float]) -> Union[int, float]:
    """
    Остаток от деления (%) двух чисел.
    
    Аргументы:
        a: Делимое
        b: Делитель
    
    Возвращает:
        Остаток от деления a на b
    
    Ошибки:
        ZeroDivisionError: Если b равно 0
    
    Пример:
        >>> modulus(10, 3)
        1
    """
    if b == 0:
        raise ZeroDivisionError("Деление на ноль невозможно")
    return a % b

def power(base: Union[int, float], exponent: Union[int, float]) -> Union[int, float]:
    """
    Возведение числа в степень.
    
    Аргументы:
        base: Основание
        exponent: Показатель степени
    
    Возвращает:
        base в степени exponent
    
    Пример:
        >>> power(2, 3)
        8
        >>> power(4, 0.5)
        2.0
    """
    return base ** exponent

def factorial(n: int) -> int:
    """
    Вычисление факториала числа.
    
    Аргументы:
        n: Неотрицательное целое число
    
    Возвращает:
        Факториал числа n
    
    Ошибки:
        ValueError: Если n < 0
    
    Пример:
        >>> factorial(5)
        120
        >>> factorial(0)
        1
    """
    if n < 0:
        raise ValueError("Факториал определен только для неотрицательных чисел")
    if n == 0:
        return 1
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result

def is_prime(n: int) -> bool:
    """
    Проверка, является ли число простым.
    
    Аргументы:
        n: Проверяемое число
    
    Возвращает:
        True если число простое, иначе False
    
    Пример:
        >>> is_prime(7)
        True
        >>> is_prime(10)
        False
    """
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True

def average(numbers: List[Union[int, float]]) -> float:
    """
    Вычисление среднего арифметического списка чисел.
    
    Аргументы:
        numbers: Список чисел
    
    Возвращает:
        Среднее арифметическое
    
    Ошибки:
        ValueError: Если список пустой
    
    Пример:
        >>> average([1, 2, 3, 4, 5])
        3.0
    """
    if not numbers:
        raise ValueError("Список чисел не может быть пустым")
    return sum(numbers) / len(numbers)

def create_matrix(rows: int, cols: int, fill_value: Union[int, float] = 0) -> List[List[Union[int, float]]]:
    """
    Создание матрицы заданного размера.
    
    Аргументы:
        rows: Количество строк
        cols: Количество столбцов
        fill_value: Значение для заполнения матрицы
    
    Возвращает:
        Двумерный список (матрица)
    
    Пример:
        >>> create_matrix(2, 3, 1)
        [[1, 1, 1], [1, 1, 1]]
    """
    return [[fill_value for _ in range(cols)] for _ in range(rows)]

def transpose_matrix(matrix: List[List[Union[int, float]]]) -> List[List[Union[int, float]]]:
    """
    Транспонирование матрицы.
    
    Аргументы:
        matrix: Исходная матрица
    
    Возвращает:
        Транспонированная матрица
    
    Пример:
        >>> transpose_matrix([[1, 2, 3], [4, 5, 6]])
        [[1, 4], [2, 5], [3, 6]]
    """
    if not matrix:
        return []
    
    rows = len(matrix)
    cols = len(matrix[0])
    
    for row in matrix:
        if len(row) != cols:
            raise ValueError("Все строки матрицы должны иметь одинаковую длину")
    
    return [[matrix[i][j] for i in range(rows)] for j in range(cols)]

def circle_area(radius: Union[int, float]) -> float:
    """
    Вычисление площади круга.
    
    Аргументы:
        radius: Радиус круга
    
    Возвращает:
        Площадь круга
    
    Пример:
        >>> circle_area(5)
        78.53981633974483
    """
    if radius < 0:
        raise ValueError("Радиус не может быть отрицательным")
    return PI * radius ** 2

def square_area(side: Union[int, float]) -> Union[int, float]:
    """
    Вычисление площади квадрата.
    
    Аргументы:
        side: Длина стороны квадрата
    
    Возвращает:
        Площадь квадрата
    
    Пример:
        >>> square_area(4)
        16
    """
    if side < 0:
        raise ValueError("Сторона не может быть отрицательной")
    return side ** 2

def triangle_area(base: Union[int, float], height: Union[int, float]) -> float:
    """
    Вычисление площади треугольника.
    
    Аргументы:
        base: Основание треугольника
        height: Высота треугольника
    
    Возвращает:
        Площадь треугольника
    
    Пример:
        >>> triangle_area(6, 4)
        12.0
    """
    if base < 0 or height < 0:
        raise ValueError("Основание и высота не могут быть отрицательными")
    return 0.5 * base * height

def trapezoid_area(base1: Union[int, float], base2: Union[int, float], height: Union[int, float]) -> float:
    """
    Вычисление площади трапеции.
    
    Аргументы:
        base1: Первое основание трапеции
        base2: Второе основание трапеции
        height: Высота трапеции
    
    Возвращает:
        Площадь трапеции
    
    Пример:
        >>> trapezoid_area(5, 7, 4)
        24.0
    """
    if base1 < 0 or base2 < 0 or height < 0:
        raise ValueError("Основания и высота не могут быть отрицательными")
    return 0.5 * (base1 + base2) * height


if __name__ == "__main__":
    
    print("1. Арифметические операции:")
    print(f"   5 + 3 = {add(5, 3)}")
    print(f"   10 - 4 = {subtract(10, 4)}")
    print(f"   6 * 7 = {multiply(6, 7)}")
    print(f"   15 / 4 = {divide(15, 4)}")
    print(f"   15 // 4 = {floor_divide(15, 4)}")
    print(f"   15 % 4 = {modulus(15, 4)}")
    print(f"   2^8 = {power(2, 8)}")
    
    print("\n2. Специальные функции:")
    print(f"   Факториал 5 = {factorial(5)}")
    print(f"   Число 17 простое? {is_prime(17)}")
    print(f"   Число 15 простое? {is_prime(15)}")
    print(f"   Среднее [1,2,3,4,5] = {average([1, 2, 3, 4, 5])}")
    
    print("\n3. Работа с матрицами:")
    matrix = create_matrix(2, 3, 1)
    print(f"   Созданная матрица: {matrix}")
    transposed = transpose_matrix([[1, 2, 3], [4, 5, 6]])
    print(f"   Транспонированная матрица: {transposed}")
    
    print("\n4. Вычисление площадей:")
    print(f"   Площадь круга (r=5): {circle_area(5):.2f}")
    print(f"   Площадь квадрата (a=4): {square_area(4)}")
    print(f"   Площадь треугольника (b=6, h=4): {triangle_area(6, 4)}")
    print(f"   Площадь трапеции (b1=5, b2=7, h=4): {trapezoid_area(5, 7, 4)}")

    print("\n5. Обработка ошибок:")
    try:
        divide(10, 0)
    except ZeroDivisionError as e:
        print(f"   Ошибка деления: {e}")
    
    try:
        factorial(-1)
    except ValueError as e:
        print(f"   Ошибка факториала: {e}")