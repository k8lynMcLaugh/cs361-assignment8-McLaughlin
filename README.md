# cs361-assignment8-McLaughlin

Endpoints:

        POST /register
                Body: { "email": "user@example.com", "password": "password123" }

        POST /login
                Body: { "email": "user@example.com", "password": "password123" }

        POST /assign-role
                Body: { "userId": "12345", "role": "Coach" }
                Header: Authorization: Bearer <auth_token>

Response Format:
All responses are JSON:

{ "status": "success", "message": "User registration successful" }

{ "token": "abc123", "role": "Coach" }

{ "status": "error", "message": "Invalid email or password" }
