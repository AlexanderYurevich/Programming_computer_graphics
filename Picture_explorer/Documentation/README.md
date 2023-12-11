# Picture explorer
Приложение разработано в качестве лабораторной работы №2 по предмету "Программирование компьютерной графики"

Используемые языки программирования и среды разработки:
- C++
- Qt Creator 4.11.1 Использовался комплект "Desktop Qt 5.14.2 MinGW 32-bit".

Основные объекты приложения:
- В центре приложения таблица, где размещается информация о изображениях.
- Чуть выше рабочего окна располагаются поле ввода и две кнопки.

В приложении предоставляется следующая информация о графических файлах:
- Имя файла
- Размер файла(в пикселях)
- Разрешение файла(в формате dot/inch)
- Глубина цвета
- Сжатие(для файлов, где оно применимо)

Реализован следующий функционал:
- По нажатию кнопки "Open file" проверяются файлы в веденном директории и для графических фалов представляется ключевая информация в виде таблицы, при введению несуществующего директория выводится сообщение об ошибке
- Информация предоставляется только по выбранным ГРАФИЧЕСКИМ файлам. При выборе не графического файла информация не будет обновляться
- Также при нажатии кнопки "Chose file" можно выбрать несколько файло вручную

Используемые библиотеки:
- QUrl(для передачи точных путей к файлам)
- QImageWriter(для измерения параметров изображения)
- QFileInfoList(получение информации о файлах)
- QMainWindow(родительский класс приложения)
- QDir(для работы с объектами файловой системы)
- QTableWidget(представление информации в виде таблицы)
- QFileDialog(функционал для множественного выбора файлов)

Работа с репозиторием:
- В репозитории хранятся исходники приложения, .exe файл и файли отчета.