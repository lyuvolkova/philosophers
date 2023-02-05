# Philosophers

Задача об [обедающих философах](https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85).


Программа принимает 5 обязательных параметров и 1 необязательный:

- `number_of_philosophers`: количество философов = количество вилок
- `time_to_die` (in milliseconds): если философ не начал есть через time_to_die миллисекунд с начала последнего приема пищи или начала симуляции, он умирает
- `time_to_eat` (in milliseconds): время, которое требуется философу, чтобы поесть. Время нахождения 2 вилок у философа
- `time_to_sleep` (in milliseconds): время сна философа
- `number_of_times_each_philosopher_must_eat` (optional argument): если все
  философы ели по крайней мере `number_of_times_each_philosopher_must_eat` раз симуляция останавливается. Если параметр не указан, то моделирование останавливается, когда
  хотя бы один философ умирает
