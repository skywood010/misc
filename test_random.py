import random

def create_random_num(a, b):
    return random.randint(a, b)

def new_function():
    return "hello world"


if __name__ == "__main__":
    print(create_random_num())
    print(new_function())

