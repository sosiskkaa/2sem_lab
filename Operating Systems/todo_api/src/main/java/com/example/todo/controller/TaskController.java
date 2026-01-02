package com.example.todo.controller;

import com.example.todo.model.Task;
import com.example.todo.model.Task.TaskStatus;
import com.example.todo.service.TaskService;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/v1/tasks")
public class TaskController {

    @Autowired
    private TaskService taskService;

    // GET /api/v1/tasks - Получить все задачи
    @GetMapping
    public ResponseEntity<List<Task>> getAllTasks(
            @RequestParam(required = false) TaskStatus status) {

        List<Task> tasks;
        if (status != null) {
            tasks = taskService.getTasksByStatus(status);
        } else {
            tasks = taskService.getAllTasks();
        }

        // Для GET /tasks возвращаем краткую информацию
        tasks.forEach(task -> task.setDescription(null));
        return ResponseEntity.ok(tasks);
    }

    // GET /api/v1/tasks/{id} - Получить задачу по ID
    @GetMapping("/{id}")
    public ResponseEntity<Task> getTaskById(@PathVariable Long id) {
        Task task = taskService.getTaskById(id);
        return ResponseEntity.ok(task);
    }

    // POST /api/v1/tasks - Создать новую задачу
    @PostMapping
    public ResponseEntity<Task> createTask(@Valid @RequestBody Task task) {
        Task createdTask = taskService.createTask(task);
        return ResponseEntity.status(HttpStatus.CREATED).body(createdTask);
    }

    // PUT /api/v1/tasks/{id} - Полностью обновить задачу
    @PutMapping("/{id}")
    public ResponseEntity<Task> updateTask(
            @PathVariable Long id,
            @Valid @RequestBody Task task) {
        Task updatedTask = taskService.updateTask(id, task);
        return ResponseEntity.ok(updatedTask);
    }

    // PATCH /api/v1/tasks/{id} - Частично обновить задачу
    @PatchMapping("/{id}")
    public ResponseEntity<Task> patchTask(
            @PathVariable Long id,
            @RequestBody Task taskUpdates) {
        Task updatedTask = taskService.patchTask(id, taskUpdates);
        return ResponseEntity.ok(updatedTask);
    }

    // DELETE /api/v1/tasks/{id} - Удалить задачу
    @DeleteMapping("/{id}")
    public ResponseEntity<Map<String, Object>> deleteTask(@PathVariable Long id) {
        taskService.deleteTask(id);
        Map<String, Object> response = new HashMap<>();
        response.put("success", true);
        response.put("message", "Task deleted successfully");
        response.put("deletedId", id);
        return ResponseEntity.ok(response);
    }

    // GET /api/v1/tasks/count - Получить количество задач
    @GetMapping("/count")
    public ResponseEntity<Map<String, Long>> getTaskCount() {
        long count = taskService.getTaskCount();
        Map<String, Long> response = new HashMap<>();
        response.put("count", count);
        return ResponseEntity.ok(response);
    }

    // GET /api/v1/tasks/status/{status} - Получить задачи по статусу
    @GetMapping("/status/{status}")
    public ResponseEntity<List<Task>> getTasksByStatus(@PathVariable TaskStatus status) {
        List<Task> tasks = taskService.getTasksByStatus(status);
        tasks.forEach(task -> task.setDescription(null));
        return ResponseEntity.ok(tasks);
    }
}