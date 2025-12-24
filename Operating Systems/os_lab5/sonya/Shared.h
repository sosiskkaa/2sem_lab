#pragma once

// Перечисление типов сообщений для протокола взаимодействия
enum TaskType
{
    TASK_PROCESS,   // Команда на выполнение вычислений
    TASK_TERMINATE  // Команда на корректное завершение процесса
};

// Структура входных данных (имитация RGB пикселя)
struct Pixel
{
    float r, g, b;
};

// Структура задачи, которую Browser отправляет в Worker
struct Task
{
    TaskType type;  // Флаг: работать или завершаться
    Pixel data;     // Данные для обработки
};

// Структура ответа, которую Worker возвращает в Browser
struct Response
{
    float result;   // Результат вычисления фильтра "Сепия"
};