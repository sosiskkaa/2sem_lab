package com.example.todo.service;

import com.example.todo.exception.TaskNotFoundException;
import com.example.todo.model.Task;
import com.example.todo.model.Task.TaskStatus;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Collectors;

@Service
public class TaskService {
    private final List<Task> tasks = new ArrayList<>();
    private final AtomicLong idCounter = new AtomicLong(1);

    // Инициализация демо-данных
    public TaskService() {
        tasks.add(new Task(idCounter.getAndIncrement(), "Купить молоко",
                "Обязательно 3.2% жирности", TaskStatus.TODO));
        tasks.add(new Task(idCounter.getAndIncrement(), "Запустить API",
                "Настроить Spring Boot приложение", TaskStatus.IN_PROGRESS));
        tasks.add(new Task(idCounter.getAndIncrement(), "Прочитать документацию",
                "Изучить Spring REST", TaskStatus.DONE));
    }

    // Получить все задачи
    public List<Task> getAllTasks() {
        return new ArrayList<>(tasks);
    }

    // Получить все задачи с фильтрацией по статусу
    public List<Task> getTasksByStatus(TaskStatus status) {
        return tasks.stream()
                .filter(task -> task.getStatus() == status)
                .collect(Collectors.toList());
    }

    // Получить задачу по ID
    public Task getTaskById(Long id) {
        return tasks.stream()
                .filter(task -> task.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(id));
    }

    // Создать новую задачу
    public Task createTask(Task task) {
        Task newTask = new Task(
                idCounter.getAndIncrement(),
                task.getTitle(),
                task.getDescription(),
                task.getStatus()
        );
        tasks.add(newTask);
        return newTask;
    }

    // Полностью обновить задачу
    public Task updateTask(Long id, Task task) {
        Task existingTask = getTaskById(id);
        existingTask.setTitle(task.getTitle());
        existingTask.setDescription(task.getDescription());
        existingTask.setStatus(task.getStatus());
        return existingTask;
    }

    // Частично обновить задачу (PATCH)
    public Task patchTask(Long id, Task taskUpdates) {
        Task existingTask = getTaskById(id);

        if (taskUpdates.getTitle() != null) {
            existingTask.setTitle(taskUpdates.getTitle());
        }

        if (taskUpdates.getDescription() != null) {
            existingTask.setDescription(taskUpdates.getDescription());
        }

        if (taskUpdates.getStatus() != null) {
            existingTask.setStatus(taskUpdates.getStatus());
        }

        return existingTask;
    }

    // Удалить задачу
    public void deleteTask(Long id) {
        Task taskToDelete = getTaskById(id);
        tasks.remove(taskToDelete);
    }

    // Получить количество задач
    public long getTaskCount() {
        return tasks.size();
    }
}