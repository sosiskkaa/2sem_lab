package com.example.todo.service;

import com.example.todo.dto.TaskRequest;
import com.example.todo.dto.TaskResponse;
import com.example.todo.exception.TaskNotFoundException;
import com.example.todo.model.Task;
import com.example.todo.repository.TaskRepository;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TaskService {

    private final TaskRepository taskRepository;

    public TaskService(TaskRepository taskRepository) {
        this.taskRepository = taskRepository;
    }

    @Cacheable(value = "tasks")
    public List<TaskResponse> getAllTasks() {
        return taskRepository.findAll()
                .stream()
                .map(TaskResponse::fromEntity)
                .toList();
    }

    @Cacheable(value = "tasks", key = "#status")
    public List<TaskResponse> getTasksByStatus(Task.TaskStatus status) {
        return taskRepository.findByStatus(status)
                .stream()
                .map(TaskResponse::fromEntity)
                .toList();
    }

    @Cacheable(value = "taskById", key = "#id")
    public TaskResponse getTaskById(Long id) {
        Task task = taskRepository.findById(id)
                .orElseThrow(() -> new TaskNotFoundException(id));
        return TaskResponse.fromEntity(task);
    }

    @CacheEvict(value = {"tasks", "taskById"}, allEntries = true)
    public TaskResponse createTask(TaskRequest request) {
        Task task = new Task(
                request.getTitle(),
                request.getDescription(),
                request.getStatus()
        );
        Task saved = taskRepository.save(task);
        return TaskResponse.fromEntity(saved);
    }

    @CacheEvict(value = {"tasks", "taskById"}, allEntries = true)
    public TaskResponse updateTask(Long id, TaskRequest request) {
        Task existing = taskRepository.findById(id)
                .orElseThrow(() -> new TaskNotFoundException(id));

        existing.setTitle(request.getTitle());
        existing.setDescription(request.getDescription());
        existing.setStatus(request.getStatus());

        Task updated = taskRepository.save(existing);
        return TaskResponse.fromEntity(updated);
    }

    @CacheEvict(value = {"tasks", "taskById"}, allEntries = true)
    public TaskResponse patchTask(Long id, TaskRequest request) {
        Task existing = taskRepository.findById(id)
                .orElseThrow(() -> new TaskNotFoundException(id));

        if (request.getTitle() != null && !request.getTitle().isBlank()) {
            existing.setTitle(request.getTitle());
        }
        if (request.getDescription() != null) {
            existing.setDescription(request.getDescription());
        }
        if (request.getStatus() != null) {
            existing.setStatus(request.getStatus());
        }

        Task updated = taskRepository.save(existing);
        return TaskResponse.fromEntity(updated);
    }

    @CacheEvict(value = {"tasks", "taskById"}, allEntries = true)
    public void deleteTask(Long id) {
        if (!taskRepository.existsById(id)) {
            throw new TaskNotFoundException(id);
        }
        taskRepository.deleteById(id);
    }

    public long getTaskCount() {
        return taskRepository.count();
    }
}
