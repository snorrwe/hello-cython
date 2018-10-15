import pytest
import random
from greeting import int_sort


@pytest.fixture
def random_list_of_ints():
    a = list(i for i in range(int(1e6)))
    random.shuffle(a)
    return a


def test_sort(random_list_of_ints):
    result = int_sort(random_list_of_ints)
    assert result
