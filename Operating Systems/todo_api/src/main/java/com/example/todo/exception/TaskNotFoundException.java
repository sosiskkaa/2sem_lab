package com.example.todo.exception;

public class TaskNotFoundException extends RuntimeException {
    private final Long taskId;

    public TaskNotFoundException(Long taskId) {
        super(String.format("Task with id '%d' not found", taskId));
        this.taskId = taskId;
    }

    public Long getTaskId() {
        return taskId;
    }
}