from greeting import PyGreeting


def test_kenobi():
    greet = PyGreeting(b"Hello there!")
    assert greet.greet(b"General Kenobi") == b"Hello there! General Kenobi!\n"
