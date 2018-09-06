import random
from greeting import int_sort


def generate():
    a = list(i for i in range(int(1e6)))
    random.shuffle(a)
    return a


def test_sort():
    a = generate()
    result = int_sort(a)
    assert result


def test_builtin_sort():
    a = generate()
    s = sorted(a)
    list(s)
