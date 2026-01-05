package com.example.todo.exception;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.Data;
import org.springframework.http.HttpStatus;

import java.time.LocalDateTime;
import java.util.List;

@Data
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ApiError {
    @JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "dd-MM-yyyy hh:mm:ss")
    private LocalDateTime timestamp;

    private HttpStatus status;
    private int statusCode;
    private String error;
    private String message;
    private String path;
    private List<ApiValidationError> validationErrors;

    public ApiError() {
        this.timestamp = LocalDateTime.now();
    }

    public ApiError(HttpStatus status, String message) {
        this();
        this.status = status;
        this.statusCode = status.value();
        this.error = status.getReasonPhrase();
        this.message = message;
    }

    public ApiError(HttpStatus status, String message, String path) {
        this(status, message);
        this.path = path;
    }
}