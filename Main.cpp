switch (choice) {
case 1:
    ui->displayMatches(repo);
    break;
case 2: {
    // Feature: Add a New Passenger
    string newId, newDest, newTime;
    int newSize;

    cout << "\n--- Add New Passenger ---\n";
    cout << "Enter Passenger ID (e.g., P99): ";
    cin >> newId;
    cout << "Enter Destination (e.g., Mall): ";
    cin >> newDest;
    cout << "Enter Time (e.g., 08:30am): ";
    cin >> newTime;
    cout << "Enter Party Size (e.g., 2): ";
    cin >> newSize;

    // Add to repository and immediately re-run the generator to seat them!
    repo.addPassenger(std::make_unique<Passenger>(newId, newDest, newTime, newSize));
    generator.generateMatches(repo);

    cout << "Passenger added and schedule updated!\n";
    break;
}
case 3: {
    // Feature: Save Schedule to File
    ofstream outFile("final_schedule.txt");
    if (outFile.is_open()) {
        outFile << "=== FINAL DRIVERLESS ROUTE SCHEDULE ===\n\n";
        for (const auto& r : repo.getRoutes()) {
            outFile << "-----------------------------------\n";
            outFile << r.getRouteString() << "\n";
        }
        outFile.close();
        cout << "\nSuccess! Schedule saved to 'final_schedule.txt'.\n";
    }
    else {
        cout << "\nError: Could not open file for writing.\n";
    }
    break;
}
case 4:
    cout << "\nExiting System. Goodbye!\n";
    running = false;
    break;
default:
    cout << "\nInvalid choice. Please select 1-4.\n";
    break;
}