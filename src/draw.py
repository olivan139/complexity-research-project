from matplotlib import pyplot
from matplotlib import style
import pandas as pd

style.use('seaborn-white')

pyplot.title('BIG ADS HW')
pyplot.ylabel('time')
pyplot.xlabel('digits')

print("введите путь к файлу и его имя без указания его формата")
path = input()
path = path + ".csv"

data = pd.read_csv(path, delimiter=";", names=['digits', 'grade', 'd_c', 'karatsuba'])

pyplot.plot(data['digits'], data['grade'], 'r', label='School multiplication al.')
pyplot.plot(data['digits'], data['d_c'], 'b', label='Divide and conquer al.')
pyplot.plot(data['digits'], data['karatsuba'], 'g', label='Karatsuba al.')

pyplot.legend()
pyplot.show()