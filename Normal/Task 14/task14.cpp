#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

// Class that describing employee with follows features:
// Lastname, work experince, salary per hour and count of work hours
class Employee final {
    private: 
    string m_lastname {};
    uint16_t m_experience {};
    double m_salaryPerHour {};
    int m_countOfWorkHours {};

    protected:
    // Protected method which returns award accural per hour (начисление премии) as double
    virtual double calculateAwardAccrual(Employee& employee) const {
        const double primarySalaryPerHour { employee.m_salaryPerHour };

        if(employee.m_experience > 1 && employee.m_experience <= 3)
            employee.m_salaryPerHour += employee.m_salaryPerHour * 0.05d;
        else if(employee.m_experience > 3 && employee.m_experience <= 5)
            employee.m_salaryPerHour += employee.m_salaryPerHour * 0.08d;
        else if(employee.m_experience > 5)
            employee.m_salaryPerHour += employee.m_salaryPerHour * 0.15d;

        if(employee.m_salaryPerHour == primarySalaryPerHour)
            employee.m_salaryPerHour = 0;

        return employee.m_salaryPerHour;
    }

    // Protected method which returns award accural for certain work time (начисление премии) as double
    virtual double calculateAwardAccrual(Employee& employee, const int workTime) const final {
        return calculateAwardAccrual(employee) * workTime;
    }

    // Protected method which is calculate salary of employee
    inline double calculateSalary(const Employee& employee) const {
        return employee.m_salaryPerHour * employee.m_countOfWorkHours;
    }

    public:
    // Zero-argument ctor
    inline explicit Employee() {};

    // Copy constructor
    explicit Employee(const Employee& employee){
        m_lastname = employee.m_lastname;
        m_experience = employee.m_experience;
        m_salaryPerHour = employee.m_salaryPerHour;
        m_countOfWorkHours = employee.m_countOfWorkHours;
    }

    // Move ctor
    explicit Employee(Employee&& employee){
        m_lastname = employee.m_lastname;
        employee.m_lastname.clear();

        m_experience = employee.m_experience;
        employee.m_experience = 0;

        m_salaryPerHour = employee.m_salaryPerHour;
        employee.m_salaryPerHour = 0.0d;

        m_countOfWorkHours = employee.m_countOfWorkHours;
        employee.m_countOfWorkHours = 0;
    }

    // Assignment operator
    Employee& operator=(const Employee& employee){
        if(this == &employee) return *this;

        m_lastname = employee.m_lastname;
        m_experience = employee.m_experience;
        m_salaryPerHour = employee.m_salaryPerHour;
        m_countOfWorkHours = employee.m_countOfWorkHours;

        return *this;
    }

    // Move assignment operator
    Employee& operator=(Employee&& employee){
        if(this == &employee) return *this;

        m_lastname.clear();
        m_lastname = employee.m_lastname;
        employee.m_lastname.clear();

        m_experience = 0;
        m_experience = employee.m_experience;
        employee.m_experience = 0;

        m_salaryPerHour = 0.0d;
        m_salaryPerHour = employee.m_salaryPerHour;
        employee.m_salaryPerHour = 0.0d;

        m_countOfWorkHours = 0;
        m_countOfWorkHours = employee.m_countOfWorkHours;
        employee.m_countOfWorkHours = 0;

        return *this;
    }

    // Virtual destructor
    virtual ~Employee() {};

    // Getters & setters for all properties (features)
    // Lastname
    inline string getLastname(){ return m_lastname; }
    inline void setLastname(const string& newLastname) { m_lastname = newLastname; }

    // Experience
    inline uint16_t getExperience(){ return m_experience; }
    inline void setExperience(const uint16_t& newExperience){ m_experience = newExperience; }

    // Salary per hour
    inline double getSalaryPerHour() { return m_salaryPerHour; }
    inline void setSalaryPerHour(const double& newSalaryPerHour) { m_salaryPerHour = newSalaryPerHour; }

    // Count of work time
    inline int getCountOfWorkHours() { return m_countOfWorkHours; }
    inline void setCoutnOfWorkHours(const int& newCountOfWorkHours) { m_countOfWorkHours = newCountOfWorkHours; }
    // Ending of getters & setters

    // Entering info about employee
    void fillEmployee() {
        cout << "Enter lastname: ";
        cin >> m_lastname;

        cout << "Enter experience of this worker: ";
        cin >> m_experience;

        cout << "Enter worker's hourly wag: ";
        cin >> m_salaryPerHour;

        cout << "Enter how much hours worker is do his job: ";
        cin >> m_countOfWorkHours;
    }

    // Showing employee data
    void showEmployee(Employee& employee){
        Employee bkp;
        bkp = employee;

        cout << endl << "Emloyee info: " << endl;
        cout << "Lastname: " << bkp.m_lastname << endl;
        cout << "Experience: " << bkp.m_experience << endl;
        cout << "Hourly wag: " << bkp.m_salaryPerHour << endl;
        cout << "Working hours: " << bkp.m_countOfWorkHours << endl;
        cout << "Salary: " << calculateSalary(bkp) << endl;
        cout << "Award accrual per hour: " << calculateAwardAccrual(bkp) << endl;
        cout << "Award accrual: " << calculateAwardAccrual(bkp, employee.m_countOfWorkHours) << endl;
        cout << "Ending of emloyee info " << endl << endl;
    }

    // Method for write data in file
    void writeEmployeeToFile(Employee& employee) const {
        Employee bkp;
        bkp = employee;

        ofstream employeeInfoFile;
        employeeInfoFile.open("Employee info.txt");
        employeeInfoFile << "Starting of employee info - " << m_lastname << endl << 
        "Lastname: " << bkp.m_lastname << endl << 
        "Experience: " << bkp.m_experience << endl << 
        "Hourly wag: " << bkp.m_salaryPerHour << endl << 
        "Working hours: " << bkp.m_countOfWorkHours << endl << 
        "Salary: " << calculateSalary(bkp) << endl << 
        "Award accrual per hour: " << calculateAwardAccrual(bkp) << endl << 
        "Award accrual: " << calculateAwardAccrual(bkp, bkp.m_countOfWorkHours) << endl <<
        "Ending of " << bkp.m_lastname << "'s employee info. " << endl << endl;
        employeeInfoFile.close();

        cout << "Data was successfully written in file. " << endl;
    }
};

int main(int argc, char* argv[]){
    Employee employee;

    employee.fillEmployee();
    employee.showEmployee(employee);
    employee.writeEmployeeToFile(employee);

    return EXIT_SUCCESS;
}