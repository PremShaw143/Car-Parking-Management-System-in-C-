 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

class Vehicle
{
public:
    string owner;
    string number;
    string type;
    int hours;
};

int calculateFee(string type, int hours)
{
    if(type == "Bike")
        return hours * 20;
    else if(type == "Car")
        return hours * 50;
    else if(type == "SUV")
        return hours * 80;

    return 0;
}

void parkVehicle()
{
    Vehicle v;

    cin.ignore();

    cout << "\nEnter Owner Name : ";
    getline(cin, v.owner);

    cout << "Enter Vehicle Number : ";
    getline(cin, v.number);

    cout << "Enter Vehicle Type (Bike/Car/SUV) : ";
    getline(cin, v.type);

    int rate = 0;

    if(v.type == "Bike")
    {
        rate = 20;
        cout << "\nParking Rate : Rs.20 per hour\n";
    }
    else if(v.type == "Car")
    {
        rate = 50;
        cout << "\nParking Rate : Rs.50 per hour\n";
    }
    else if(v.type == "SUV")
    {
        rate = 80;
        cout << "\nParking Rate : Rs.80 per hour\n";
    }
    else
    {
        cout << "\nInvalid Vehicle Type!\n";
        return;
    }

    cout << "\nEnter Hours Stayed : ";
    cin >> v.hours;

    int fee = calculateFee(v.type, v.hours);

    ofstream file("vehicles.csv", ios::app);

    file << v.owner << ","
         << v.number << ","
         << v.type << ","
         << v.hours << ","
         << fee << endl;

    file.close();

    cout << "\n===================================";
    cout << "\nVehicle Parked Successfully!";
    cout << "\nHours Stayed : " << v.hours;
    cout << "\nRate         : Rs." << rate << "/hour";
    cout << "\nTotal Fee    : Rs." << fee;
    cout << "\n===================================\n";
}

void showVehicles()
{
    ifstream file("vehicles.csv");

    string line;

    getline(file, line);

    cout << "\n========== ALL VEHICLES ==========\n";

    while(getline(file, line))
    {
        string owner, number, type, hours, fee;

        int p1 = line.find(',');
        int p2 = line.find(',', p1 + 1);
        int p3 = line.find(',', p2 + 1);
        int p4 = line.find(',', p3 + 1);

        owner = line.substr(0, p1);
        number = line.substr(p1 + 1, p2 - p1 - 1);
        type = line.substr(p2 + 1, p3 - p2 - 1);
        hours = line.substr(p3 + 1, p4 - p3 - 1);
        fee = line.substr(p4 + 1);

        cout << "\nOwner Name   : " << owner;
        cout << "\nVehicle No   : " << number;
        cout << "\nVehicle Type : " << type;
        cout << "\nHours Stayed : " << hours;
        cout << "\nParking Fee  : Rs." << fee;
        cout << "\n----------------------------\n";
    }

    file.close();
}

void searchVehicle()
{
    string vehicleNo;
    string line;

    cin.ignore();

    cout << "\nEnter Vehicle Number : ";
    getline(cin, vehicleNo);

    ifstream file("vehicles.csv");

    getline(file, line);

    bool found = false;

    while(getline(file, line))
    {
        if(line.find(vehicleNo) != string::npos)
        {
            found = true;

            string owner, number, type, hours, fee;

            int p1 = line.find(',');
            int p2 = line.find(',', p1 + 1);
            int p3 = line.find(',', p2 + 1);
            int p4 = line.find(',', p3 + 1);

            owner = line.substr(0, p1);
            number = line.substr(p1 + 1, p2 - p1 - 1);
            type = line.substr(p2 + 1, p3 - p2 - 1);
            hours = line.substr(p3 + 1, p4 - p3 - 1);
            fee = line.substr(p4 + 1);

            cout << "\n===== VEHICLE DETAILS =====\n";
            cout << "Owner Name   : " << owner << endl;
            cout << "Vehicle No   : " << number << endl;
            cout << "Vehicle Type : " << type << endl;
            cout << "Hours Stayed : " << hours << endl;
            cout << "Parking Fee  : Rs." << fee << endl;
            cout << "===========================\n";
        }
    }

    if(!found)
    {
        cout << "\nVehicle Not Found!\n";
    }

    file.close();
}

void removeVehicle()
{
    string vehicleNo;
    string line;

    cin.ignore();

    cout << "\nEnter Vehicle Number To Remove : ";
    getline(cin, vehicleNo);

    ifstream file("vehicles.csv");
    ofstream temp("temp.csv");

    bool found = false;

    getline(file, line);
    temp << line << endl;

    while(getline(file, line))
    {
        if(line.find(vehicleNo) == string::npos)
        {
            temp << line << endl;
        }
        else
        {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("vehicles.csv");
    rename("temp.csv", "vehicles.csv");

    if(found)
        cout << "\nVehicle Removed Successfully!\n";
    else
        cout << "\nVehicle Not Found!\n";
}

void revenueReport()
{
    ifstream file("vehicles.csv");

    string line;
    int revenue = 0;

    getline(file, line);

    while(getline(file, line))
    {
        size_t pos = line.rfind(',');

        if(pos != std::string::npos)
        {
            revenue += stoi(line.substr(pos + 1));
        }
    }

    file.close();

    cout << "\nTotal Revenue : Rs." << revenue << endl;
}

void totalVehicles()
{
    ifstream file("vehicles.csv");

    string line;
    int count = 0;

    getline(file, line);

    while(getline(file, line))
    {
        count++;
    }

    file.close();

    cout << "\nTotal Vehicles Parked : " << count << endl;
}

void exportToCSV()
{
    ifstream source("vehicles.csv");
    ofstream destination("parking_report.csv");

    string line;

    while(getline(source, line))
    {
        destination << line << endl;
    }

    source.close();
    destination.close();

    cout << "\n==================================" << endl;
    cout << "Data Exported Successfully!" << endl;
    cout << "File Name : parking_report.csv" << endl;
    cout << "==================================" << endl;
}

int main()
{
    int choice;

    fstream checkFile("vehicles.csv", ios::in);

    if(checkFile.peek() == EOF)
    {
        ofstream headerFile("vehicles.csv");

        headerFile
        << "Owner Name,Vehicle Number,Vehicle Type,Hours Stayed,Parking Fee\n";

        headerFile.close();
    }

    checkFile.close();

    cout << "======================================" << endl;
    cout << "     CAR PARKING MANAGEMENT SYSTEM    " << endl;
    cout << "     Developed By Prem Kumar Shaw     " << endl;
    cout << "======================================" << endl;

    do
    {
        cout << "\n1. Park Vehicle";
        cout << "\n2. Show All Vehicles";
        cout << "\n3. Search Vehicle";
        cout << "\n4. Remove Vehicle";
        cout << "\n5. Revenue Report";
        cout << "\n6. Total Vehicles";
        cout << "\n7. Export Data To CSV";
        cout << "\n8. Exit";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                parkVehicle();
                break;

            case 2:
                showVehicles();
                break;

            case 3:
                searchVehicle();
                break;

            case 4:
                removeVehicle();
                break;

            case 5:
                revenueReport();
                break;

            case 6:
                totalVehicles();
                break;

            case 7:
                exportToCSV();
                cout << "\nFiles are being saved in the current project folder." << endl;
                break;
            case 8:
                cout << "\nThank You For Using The System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 8);

    return 0;
} 