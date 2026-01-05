package com.example.todo.service;

import com.example.todo.dto.TaskRequest;
import com.example.todo.dto.TaskResponse;
import com.example.todo.exception.TaskNotFoundException;
import com.example.todo.model.Task;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Collectors;

@Service
public class TaskService {
    private final List<Task> tasks = new ArrayList<>();
    private final AtomicLong idCounter = new AtomicLong(1);

    public TaskService() {
        tasks.add(new Task(idCounter.getAndIncrement(), "Купить молоко",
                "Обязательно 3.2% жирности", Task.TaskStatus.TODO));
        tasks.add(new Task(idCounter.getAndIncrement(), "Запустить API",
                "Настроить Spring Boot приложение", Task.TaskStatus.IN_PROGRESS));
        tasks.add(new Task(idCounter.getAndIncrement(), "Прочитать документацию",
                "Изучить Spring REST", Task.TaskStatus.DONE));
    }

    public List<TaskResponse> getAllTasks() {
        return tasks.stream()
                .map(TaskResponse::fromEntity)
                .collect(Collectors.toList());
    }

    public List<TaskResponse> getTasksByStatus(Task.TaskStatus status) {
        return tasks.stream()
                .filter(task -> task.getStatus() == status)
                .map(TaskResponse::fromEntity)
                .collect(Collectors.toList());
    }

    public TaskResponse getTaskById(Long id) {
        Task task = tasks.stream()
                .filter(t -> t.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(id));

        return TaskResponse.fromEntity(task);
    }

    public TaskResponse createTask(TaskRequest request) {
        Task newTask = new Task(
                idCounter.getAndIncrement(),
                request.getTitle(),
                request.getDescription(),
                request.getStatus()
        );
        tasks.add(newTask);

        return TaskResponse.fromEntity(newTask);
    }

    public TaskResponse updateTask(Long id, TaskRequest request) {
        Task existingTask = tasks.stream()
                .filter(t -> t.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(id));

        existingTask.setTitle(request.getTitle());
        existingTask.setDescription(request.getDescription());
        existingTask.setStatus(request.getStatus());

        return TaskResponse.fromEntity(existingTask);
    }

    public TaskResponse patchTask(Long id, TaskRequest request) {
        Task existingTask = tasks.stream()
                .filter(t -> t.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(id));

        if (request.getTitle() != null) {
            existingTask.setTitle(request.getTitle());
        }

        if (request.getDescription() != null) {
            existingTask.setDescription(request.getDescription());
        }

        if (request.getStatus() != null) {
            existingTask.setStatus(request.getStatus());
        }

        return TaskResponse.fromEntity(existingTask);
    }

    public void deleteTask(Long id) {
        Task taskToDelete = tasks.stream()
                .filter(t -> t.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(id));

        tasks.remove(taskToDelete);
    }

    public long getTaskCount() {
        return tasks.size();
    }
}