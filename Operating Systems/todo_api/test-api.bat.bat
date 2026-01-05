@echo off
echo Testing To-Do List API
echo.

set BASE_URL=http://localhost:8080/api/v1/tasks

echo 1. Get all tasks:
curl -s -X GET "%BASE_URL%"

echo.
echo 2. Get task by ID (1):
curl -s -X GET "%BASE_URL%/1"

echo.
echo 3. Create new task:
curl -s -X POST "%BASE_URL%" ^
  -H "Content-Type: application/json" ^
  -d "{\"title\": \"New task\", \"description\": \"Test\", \"status\": \"TODO\"}"

echo.
echo 4. Update task (ID 1):
curl -s -X PUT "%BASE_URL%/1" ^
  -H "Content-Type: application/json" ^
  -d "{\"title\": \"Updated\", \"description\": \"Updated\", \"status\": \"IN_PROGRESS\"}"

echo.
echo 5. Partial update (ID 1):
curl -s -X PATCH "%BASE_URL%/1" ^
  -H "Content-Type: application/json" ^
  -d "{\"status\": \"DONE\"}"

echo.
echo Testing completed.
pause