#!/bin/bash

echo "Копирую .clang-format..."
cp materials/linters/.clang-format src/ || {
    echo "Ошибка: не удалось скопировать файл .clang-format"
    exit 1
}

echo "Проверяю форматирование..."
clang-format -n src/*.c || {
    echo "Ошибка форматирования кода"
    exit 1
}
clang-format -i src/*.c || {
    echo "Ошибка применения форматирования"
    exit 1
}

echo "Запуск cppcheck..."
cppcheck src/ || {
    echo "Ошибка при проверке cppcheck"
    exit 1
}

echo "Компиляция файлов..."
for file in src/*.c; do
    filename=$(basename "$file" .c)
    echo "Компилирую $filename..."
    gcc -Werror -Wextra -Wall -std=c11 "$file" -o "src/$filename.out" || {
        echo "Ошибка компиляции файла $file"
        exit 1
    }
done

echo "Удаляю .clang-format..."
rm src/.clang-format || {
    echo "Предупреждение: не удалось удалить файл .clang-format"
}

echo "Все операции выполнены успешно!"
