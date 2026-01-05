package com.example.todo.exception;

import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ApiValidationError {
    private String field;
    private Object rejectedValue;
    private String message;

    public ApiValidationError(String field, String message) {
        this.field = field;
        this.message = message;
    }
}