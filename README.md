# Compressor Data Collector

A FastAPI application for collecting and managing compressor data.

## Getting Started

### 1. Activate the Virtual Environment

**PowerShell:**
```powershell
.\.venv\Scripts\Activate.ps1
```

**Command Prompt (cmd):**
```cmd
.\.venv\Scripts\activate.bat
```

**Git Bash / bash:**
```bash
source .venv/Scripts/activate
```

### 2. Run the Development Server

**Local access only (`127.0.0.1`):**
```powershell
uvicorn main:app --reload
```

**LAN access (accessible to other devices on your local network):**
```powershell
uvicorn main:app --host 0.0.0.0 --port 8000 --reload
```

*(Or using the `.venv` path directly without activating:)*
```powershell
.\.venv\Scripts\python.exe -m uvicorn main:app --host 0.0.0.0 --port 8000 --reload
```

### 3. API Documentation

Once the server is running:
- **Interactive Swagger UI**: [http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)
- **ReDoc UI**: [http://127.0.0.1:8000/redoc](http://127.0.0.1:8000/redoc)

