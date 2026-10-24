# 🚐 Autonomous Shuttle & Passenger Scheduling System

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)]()
[![Architecture](https://img.shields.io/badge/Design-SOLID%20Principles-brightgreen.svg)]()
[![Course](https://img.shields.io/badge/SIT-INF1009%20OOP-orange.svg)]()

A modular, layered C++ transit dispatch and route planning system developed for **Singapore Institute of Technology (INF1009 Object-Oriented Programming)**. The system models an autonomous on-demand shuttle service that dynamically matches passengers to available shuttles under strict capacity limits, pickup route constraints, and a 10-minute arrival window.

---

## 📌 Key Features

- **Automated Scheduling Engine:** Matches passenger pickup requests with autonomous shuttles based on route alignment and seat availability.
- **Strict 10-Minute Window Constraint:** Enforces temporal arrival/departure limits to ensure schedule reliability.
- **Robust Input & State Validation:** Verifies shuttle-package integrity and passenger booking parameters before dispatch assignment.
- **File Serialization & Persistence:** Parses and exports schedule data to and from flat files (`passenger.txt`, `shuttle.txt`, `final_schedule.txt`).
- **Interactive Console Interface:** Clean CLI menu for viewing real-time fleet statuses, loading batch records, and triggering dispatch calculations.

---

## 🏗️ System Architecture & SOLID Implementation

The codebase adheres strictly to object-oriented design and **SOLID** principles to avoid tight coupling:

| Component | Responsibility / Mapping | SOLID Alignment |
| :--- | :--- | :--- |
| **`Entity` / `Passenger` / `Shuttle`** | Core domain models representing passengers, vehicles, and active states. | **S (Single Responsibility):** Pure data models isolated from I/O or scheduling logic. |
| **`Route`** | Encapsulates pickup, dropoff, and waypoint sequencing. | **O (Open/Closed):** Easily extendable to handle multi-stop or looped routes without rewriting entity definitions. |
| **`ValidService`** | Business logic validation for passenger capacity, route validity, and time windows. | **S / D:** Decouples validation logic from file parsing and UI rendering. |
| **`SchedGenerator`** | Core dispatch algorithm matching passenger trips with available vehicles. | **D (Dependency Inversion):** Operates on abstract entity interfaces rather than concrete I/O classes. |
| **`SchedRepo` & `FileParser`** | Handles persistent storage, file ingestion, formatting, and disk serialization. | **I (Interface Segregation):** Keeps disk operations isolated from business scheduling logic. |
| **`UIControl` & `Main.cpp`** | CLI presentation layer managing user menus and session states. | High cohesion; passes user actions cleanly to backend services. |

---

## 📂 Project Structure

```text
RoutePlan/
├── .vscode/               # VS Code task and build configurations
│   └── tasks.json
├── Entity.h / .cpp        # Base entity abstraction
├── Passenger.h / .cpp     # Passenger domain model & states
├── Shuttle.h / .cpp       # Autonomous shuttle vehicle model
├── Route.h / .cpp         # Route coordinates & waypoint management
├── ValidService.h / .cpp  # Business validation & constraint verification
├── SchedGenerator.h / .cpp# Schedule generation & passenger-shuttle matching
├── SchedRepo.h / .cpp     # Schedule persistence repository
├── FileParser.h / .cpp    # Input flat-file tokenization & parsing
├── UIControl.h / .cpp     # CLI menu & user interaction controller
├── Main.cpp               # Application entry point
├── RoutePlan.slnx / vcxproj # Visual Studio solution & project files
└── data/                  # Input datasets & output schedules (.txt)
