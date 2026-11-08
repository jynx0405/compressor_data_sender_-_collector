
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from datetime import datetime
import csv
import os

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

CSV_FILE = "data.csv"

class SensorData(BaseModel):
    c1_on: int
    c1_load: int
    c2_on: int
    c2_load: int
    c3_on: int
    c3_load: int
    c4_on: int
    c4_load: int
    pressure_voltage: float
    pressure_current: float
    pressure_bar: float

@app.get("/")
def home():
    return {"status": "API is running"}

@app.post("/store")
def store_data(data: SensorData):

    row = data.model_dump()
    row["time"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    file_exists = os.path.exists(CSV_FILE) and os.path.getsize(CSV_FILE) > 0

    with open(CSV_FILE, "a", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=row.keys())

        if not file_exists:
            writer.writeheader()

        writer.writerow(row)

    return {"message": "Data stored"}

@app.get("/read")
def read_data():

    if not os.path.exists(CSV_FILE):
        return []

    with open(CSV_FILE, "r", newline="") as file:
        reader = csv.DictReader(file)
        records = list(reader)

    return records[-10:]
