#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

// Returns numeric type from a string '__str'
template <typename T>
T str_to_num(const std::string &__str)
{
    // Input string stream
    std::istringstream iss(__str);

    // Numeric variable to return
    T num{};

    // Writing string to numeric type from a string stream
    iss >> num;

    // Returning result number
    return num;
}

// Returns true if string is a floating number (float, double, etc.)
bool is_floating_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.cbegin();

    // Count of points in string (must be 1 point in number)
    // Same thing with minus sign
    unsigned int count_point{0U}, count_minus{0U};

    // Iterating by symbols in string
    while (it != __str.end())
    {
        // Counting all minuses in string
        if ((*it == '-'))
            count_minus++;

        // Counting all points in string
        if ((*it == '.'))
            count_point++;

        // Incrementing iterator
        ++it;
    }

    // Exception case when point stay in the beginning of string
    if (__str.at(0UL) == '.')
        return false;

    // Moving iterator to the begin of string
    it = __str.begin();

    // If number contains less or 1 point or minus -> continue
    if (count_point <= 1U && count_minus <= 1U)
    {
        // Using 'while' loop to check if all symbols in string are digits
        while (it != __str.end() && (std::isdigit(*it) || (*it) == '.' || (*it) == '-'))
        {
            // Incrementing iterator
            ++it;
        }
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns user's input as floating number
template <typename T>
T input_to_floating(const char *msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_floating_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an floating number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_num<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool is_uint_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Using 'while' loop to check if all symbols in string are digits
    while (it != __str.end() && std::isdigit(*it))
    {
        // Incrementing iterator
        ++it;
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns user's input as unsigned integer number
template <typename T>
T input_to_uint(const char *msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_uint_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an unsigned integer number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_num<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

class Employee
{
private:
    // ID of employer
    unsigned int m_ID{0U};

    // Name, lastname and patronymic in one string (separated by space ' ')
    std::string m_lnp{" "};

    // Count of worked hours
    unsigned int m_work_hours{0U};

    // Job post of employer
    std::string m_job_post{" "};

    // Salary for 1 hour
    double m_hour_salary{0.0};

    // Currency of salary
    const char m_kcurrency = '$';

protected:
    // Implementation of copy semantics for 'Employee' object
    void copy(const Employee &__employee)
    {
        // Copying data members from '__employee' to current object
        m_ID = __employee.m_ID;
        m_lnp = __employee.m_lnp;
        m_work_hours = __employee.m_work_hours;
        m_job_post = __employee.m_job_post;
        m_hour_salary = __employee.m_hour_salary;
    }

    // Zeros out all data members of 'Employee' object
    void clear(Employee &__employee)
    {
        // Zeroing out all data members of current object
        __employee.m_ID = 0U;
        __employee.m_lnp.clear();
        __employee.m_work_hours = 0U;
        __employee.m_job_post.clear();
        __employee.m_hour_salary = 0.0;
    }

    // Returns true if file exists
    inline bool is_file_exist(const char *__filename) const
    {
        // Input file stream
        std::ifstream ifs(__filename);

        // Returning state of file
        return ifs.good();
    }

    // Returns true if file successfully created or if file already exists
    bool is_file_created(const char *__filename) const
    {
        // Checking if this file is already exist
        if (!is_file_exist(__filename))
        {
            // Creating a file
            std::ofstream ofs(__filename, std::ios_base::out);

            // If file has a good state
            if (ofs.good())
            {
                // Closing file
                ofs.close();

                return true;
            }
            // Otherwise: returning 'false' as a result
            else
                return false;
        }
        // Else file is already exist we no need to create it again
        else
            return true;
    }

    // Returns true if file contains string '__str'
    bool is_contain(const std::string &__str, const char *__filename) const
    {
        // Openning file to read data from it
        std::ifstream ifs(__filename, std::ios_base::in);

        // Stores symbols from 1 line from file
        std::string line{};

        while (ifs.good())
        {
            // Reading data line by line
            while (std::getline(ifs, line))
            {
                // If read string is same with parameter string -> return false
                if (__str == line)
                    return true;
            }
        }

        return false;
    }

    // Returns salary as double number
    inline double calc_salary() const
    {
        return m_hour_salary * static_cast<double>(m_work_hours);
    }

    // Returns all read properties of an employeer from a file as a vector of an appropriate type
    // char 'D' - ID
    // char 'c' - lastname, name, patronymic
    // char 's' - work hours
    // char 't' - job post
    // char 'r' - payment per hour
    // By default returns all IDs
    // '__dec' - decrement for gettting deffirent properties
    // Because in file we have "h." in 'Work hours' field, therefore we need to remove excess symbols
    // For 'Work hours' - '__dec' = 3U
    // For 'Payment per hour' - '__dec' = 2U
    std::vector<std::string> get_property_from_file(const char *__filename = "data.txt",
                                                    const char &__property_ch = 'D',
                                                    const size_t &__inc = 3UL,
                                                    const size_t &__dec = 0UL) const
    {
        // Vector of properties
        std::vector<std::string> property_vec;

        // If file doesn't exist -> return empty vector
        if (!is_file_exist(__filename))
        {
            // Pushing back zero to vector to get next ID - 1
            property_vec.push_back("0");
            return property_vec;
        }

        // Input file stream for reading data from the file
        std::ifstream ifs;

        // Opening file in input mode
        ifs.open(__filename, std::ios_base::in);

        // String that contains property as an unsigned ineteger value
        std::string str{};

        // If file is in good state -> write data into
        if (ifs.good())
        {
            // Line from the file
            std::string line{};

            // Reading line by line from a file
            while (std::getline(ifs, line))
            {
                // Certain index that contains 1st digit of property
                size_t certain_index{0UL};

                // Iterating by symbols in line
                for (size_t index{0UL}; index < line.length(); index++)
                {
                    if ((index + 1UL) < line.length() && line.at(index) == __property_ch && line.at(index + 1UL) == ':')
                    {
                        // Zeroing out 'str' to avoid insufficient digits in property
                        str.clear();

                        // Certain index is the next after the certain symbols
                        certain_index = index + __inc;

                        // Iterating by symbols in line, starting with the digit of the property
                        for (size_t property_index{certain_index};
                             property_index < line.length() - __dec; property_index++)
                        {
                            // Adding symbols to 'str'
                            str.push_back(line.at(property_index));
                        }

                        // Adding next property to vector
                        property_vec.push_back(str);
                    }
                }
            }
        }

        // Closing the file
        ifs.close();

        // Returning vector of IDs
        return property_vec;
    }

public:
    // Default string
    static const std::string default_str;

    // Default unsigned integer number
    static const unsigned int default_uint_num;

    // Default double value
    static const double default_double_num;

    // Default constructor
    explicit Employee() : m_ID(get_IDs_from_file().back() + 1U),
                          m_lnp(default_str), m_work_hours(default_uint_num),
                          m_job_post(default_str), m_hour_salary(default_double_num){};

    // Constructor with 2 parameters
    explicit Employee(const std::string &__lnp) : m_ID(get_IDs_from_file().back() + 1U),
                                                  m_lnp(__lnp),
                                                  m_work_hours(default_uint_num),
                                                  m_job_post(default_str), m_hour_salary(default_double_num){};

    // Constructor with all parameters
    explicit Employee(const unsigned int &__ID,
                      const std::string &__lnp,
                      const unsigned int &__work_hours,
                      const std::string &__job_post,
                      const double &__salary) : m_ID(__ID), m_lnp(__lnp),
                                                m_work_hours(__work_hours),
                                                m_job_post(__job_post), m_hour_salary(__salary){};

    // Copy constructor
    explicit Employee(const Employee &__employee) { copy(__employee); };

    // Move constructor
    explicit Employee(Employee &&__employee);

    // Assignment operator
    Employee &operator=(const Employee &__employee);

    // Move assignment ooperator
    Employee &operator=(Employee &&__employee) noexcept;

    // Defalt virtual destructor
    virtual ~Employee() = default;

    // Getters for members of Employee class
    inline unsigned int get_ID() { return m_ID; }
    inline std::string get_lnp() { return m_lnp; }
    inline unsigned int get_work_hours() { return m_work_hours; }
    inline std::string get_job_post() { return m_job_post; }
    inline double get_hour_salary() { return m_hour_salary; }

    // Setters for members of Employee class
    inline void set_lnp(const std::string &__lnp) { m_lnp = __lnp; }
    inline void set_work_hours(const unsigned int &__wh) { m_work_hours = __wh; }
    inline void set_job_post(const std::string &__jp) { m_job_post = __jp; }
    inline void set_hour_salary(const double &__hs) { m_hour_salary = __hs; }

    // Returns choice of user as unsigned integer number
    // Prints menu to terminal
    inline unsigned int print_menu() const;

    // Returns true if string doesn't contains digits
    inline bool is_characters(const std::string &__lnp) const;

    // Returns object where the user entered data
    Employee &user_input();

    // Writes data to a file
    void write_to_file(const char *__filename) const;

    // Prints data from file to terminal
    void read_from_file(const char *__filename) const;

    // Prints current employee data to terminal
    virtual void print_data() const;

    // Prints data of '__employee' object to terminal
    virtual void print_data(const Employee &__employee) const;

    // Changes all parameters of current employeer
    void edit_data(const std::string &__lnp, const unsigned int &__work_hours,
                   const std::string &__job_post, const double &__hour_salary);

    // Returns vector of IDs from a file
    std::vector<unsigned int> get_IDs_from_file(const char *__filename = "data.txt") const;

    // Returns vector of lastname, name & patronymic
    inline std::vector<std::string> get_lnp_from_file(const char *__filename = "data.txt") const;

    // Returns vector of work hours from a file
    std::vector<unsigned int> get_work_hours_from_file(const char *__filename = "data.txt") const;

    // Returns vector of job posts of each employeers from a file
    std::vector<std::string> get_job_posts_from_file(const char *__filename = "data.txt") const;

    // Returns vector of payments per hour of each employeers from a file
    std::vector<double> get_hour_salaries_from_file(const char *__filename = "data.txt") const;

    // Returns all employeers from a file
    std::vector<Employee> get_employeers_from_file(const char *__filename = "data.txt") const;

    // Prints all info about employeers that contains in file
    void print_all_data(const char *__filename = "data.txt") const;

    // Perfoms options from menu
    void do_option(unsigned int &__option);
};

const std::string Employee::default_str("empty");
const unsigned int Employee::default_uint_num(1U);
const double Employee::default_double_num(1.0);

Employee::Employee(Employee &&__employee)
{
    // Copying from '__employee' to current object
    copy(__employee);

    // Zeroing out all data members of __employee object
    clear(__employee);
}

Employee &Employee::operator=(const Employee &__employee)
{
    // Checking self-assignment
    if (this == &__employee)
        return *this;

    // Copying from '__employee' to current object
    copy(__employee);

    // Returning current object
    return *this;
}

Employee &Employee::operator=(Employee &&__employee) noexcept
{
    // Checking self-assignment
    if (this == &__employee)
        return *this;

    // Zeroing out all data members of current object
    clear(*this);

    // Copying from '__employee' to current object
    copy(__employee);

    // Zeroing out all data members of '__employee' object
    clear(__employee);

    // Returning current object
    return *this;
}

inline unsigned int Employee::print_menu() const
{
    std::cout << "... Menu ...\n";
    std::cout << "1. New employer\n2. Edit data\n3. Find employer\n4. Delete data\n5. Save data to file\n"
              << "6. Load data from file\n7. Show all employers\n8. Sort data\n9. Quit\n\n";

    // Returning option from menu as unsigned integer number
    return input_to_uint<unsigned int>("Enter option: ");
}

inline bool Employee::is_characters(const std::string &__name) const
{
    // Iterating by characters in string
    for (const auto &ch : __name)
    {
        // If symbol is digit or space -> return false
        if (isdigit(ch))
            return false;
    }

    // Returning true if all symbols in string are characters
    return true;
}

Employee &Employee::user_input()
{
    std::cout << "Enter lastname, name and patronymic separated by a space: ";

    // Avoid skipping of input
    getchar();

    while (true)
    {
        // Inputting name, lastname and patronymic separated by a space
        std::getline(std::cin, m_lnp);

        // If some digits found in 'm_lnp' string -> clearing the string and printing message
        if (!is_characters(m_lnp))
        {
            m_lnp.clear();
            std::cout << "Incorrect input. Try again.\n";
        }

        // Count of spaces in string
        short int spaces{0};

        // Counting spaces in string
        for (const auto &ch : m_lnp)
        {
            // If symbol is space -> incrementing counter
            if (ch == ' ')
                spaces++;
        }

        // If we have 2 spaces in string -> break the infinity loop
        if (spaces == 2)
            break;
        else
            std::cout << "Incorrect count of spaces. Try again.\n";
    }

    m_work_hours = input_to_uint<unsigned int>("Enter work hours: ");

    std::cout << "Enter job post: ";

    // This std::cin is for skip
    std::cin.get();

    while (true)
    {
        // Inputting job post
        std::getline(std::cin, m_job_post);

        // If digits not found in 'm_job_post' string -> break the infinity loop
        if (is_characters(m_job_post))
            break;
        else
        {
            m_job_post.clear();
            std::cout << "Incorrect input. Try again.\n";
        }
    }

    m_hour_salary = input_to_floating<double>("Enter salary per hour: ");

    return *this;
}

void Employee::write_to_file(const char *__filename) const
{
    // Output file stream variable to write data
    std::ofstream ofs;

    // Check is file successfully created
    if (is_file_created(__filename))
    {
        // Opening file in append mode
        ofs.open(__filename, std::ios_base::app);

        // If file is in good state -> write data into
        if (ofs.good())
        {
            // Writing all object members to the file
            ofs << "ID: " << m_ID << "\nLastname, name & patronymic: " << m_lnp
                << "\nWork hours: " << m_work_hours << " h."
                << "\nJob post: " << m_job_post << "\nPayment per hour: " << m_hour_salary
                << ' ' << m_kcurrency << "\nSalary: " << calc_salary() << ' ' << m_kcurrency << "\n"
                << std::endl;

            std::cout << "Data has been written into a file " << __filename << std::endl;
        }
    }
    else
        std::cerr << "Can't write data to a file " << __filename << std::endl;

    // Closing the file
    ofs.close();
}

void Employee::read_from_file(const char *__filename) const
{
    // Input file stream for reading data from the file
    std::ifstream ifs;

    // Check is file successfully created
    if (is_file_created(__filename))
    {
        // Opening file in input mode
        ifs.open(__filename, std::ios_base::in);

        // If file is in good state -> write data into
        if (ifs.good())
        {
            // Line from the file
            std::string line{};

            while (std::getline(ifs, line))
            {
                std::cout << line << '\n';
            }
        }
    }
    else
        std::cerr << "Occured error with a file " << __filename << std::endl;

    // Closing the file
    ifs.close();
}

void Employee::print_data() const
{
    std::cout << "ID: " << m_ID << '\n';
    std::cout << "Lastname, name, patronymic: " << m_lnp << '\n';
    std::cout << "Job post: " << m_job_post << '\n';
    std::cout << "Payment per hour: " << m_hour_salary << ' ' << m_kcurrency << '\n';
    std::cout << "Hours: " << m_work_hours << " h.\n";
    std::cout << "Salary: " << calc_salary() << ' ' << m_kcurrency << std::endl;
}

void Employee::print_data(const Employee &__employee) const
{
    std::cout << "ID: " << __employee.m_ID << '\n';
    std::cout << "Lastname, name, patronymic: " << __employee.m_lnp << '\n';
    std::cout << "Job post: " << __employee.m_job_post << '\n';
    std::cout << "Payment per hour: " << __employee.m_hour_salary << ' ' << m_kcurrency << '\n';
    std::cout << "Hours: " << __employee.m_work_hours << " h.\n";
    std::cout << "Salary: " << __employee.calc_salary() << ' ' << m_kcurrency << std::endl;
}

void Employee::edit_data(const std::string &__lnp, const unsigned int &__work_hours,
                         const std::string &__job_post, const double &__hour_salary)
{
    // Copying data from parameters to current object
    m_lnp = __lnp;
    m_work_hours = __work_hours;
    m_job_post = __job_post;
    m_hour_salary = __hour_salary;
}

std::vector<unsigned int> Employee::get_IDs_from_file(const char *__filename) const
{
    // Vector of IDs
    std::vector<unsigned int> id_vec(0U);

    // Getting IDs as a vector of string
    std::vector<std::string> str_vec{get_property_from_file(__filename)};

    // Iterating by strings in vector of strings
    for (auto it{str_vec.cbegin()}; it != str_vec.cend(); ++it)
    {
        // Converting string of ID to unsigned integer value
        unsigned int next_ID{str_to_num<unsigned int>(*it)};

        // Adding next ID to vector of IDs
        id_vec.push_back(next_ID);
    }

    // Returning vector of IDs
    return id_vec;
}

inline std::vector<std::string> Employee::get_lnp_from_file(const char *__filename) const
{
    // Vector of lastname, name & patronymic
    std::vector<std::string> lnp_vec{get_property_from_file(__filename, 'c', 3UL)};

    // Returning vector of lnp
    return lnp_vec;
}

std::vector<unsigned int> Employee::get_work_hours_from_file(const char *__filename) const
{
    // Vector of work hours
    std::vector<unsigned int> wh_vec(0U);

    // Getting work hour as a vector of string
    std::vector<std::string> str_vec{get_property_from_file(__filename, 's', 3UL, 3UL)};

    // Iterating by strings in vector of strings
    for (auto it{str_vec.cbegin()}; it != str_vec.cend(); ++it)
    {
        // Converting string of work hours to unsigned integer value
        unsigned int next_wh{str_to_num<unsigned int>(*it)};

        // Adding next work hour to vector of work hours
        wh_vec.push_back(next_wh);
    }

    // Returning vector of work hours
    return wh_vec;
}

std::vector<std::string> Employee::get_job_posts_from_file(const char *__filename) const
{
    // Vector of job posts
    std::vector<std::string> jp_vec{get_property_from_file(__filename, 't')};

    // Returning vector of job posts
    return jp_vec;
}

std::vector<double> Employee::get_hour_salaries_from_file(const char *__filename) const
{
    // Vector of hour salaries in string representation
    std::vector<std::string> property_vec{get_property_from_file(__filename, 'r', 3UL, 2UL)};

    // Vector of hour salaries in double representation
    std::vector<double> hs_vec{};

    // Iterating by vector of hour salaries as a string
    for (size_t index{0UL}; index < property_vec.size(); index++)
    {
        // Converting string represenation of hour salaries to double
        double next_hs{str_to_num<double>(property_vec.at(index))};

        // Adding double represenation of hour salaries to vector of hour salaries
        hs_vec.push_back(next_hs);
    }

    // Returning vector of hour salaries
    return hs_vec;
}

std::vector<Employee> Employee::get_employeers_from_file(const char *__filename) const
{
    // Vectors with properties of all employeers
    std::vector<unsigned int> IDs{get_IDs_from_file(__filename)};
    std::vector<std::string> lnps{get_lnp_from_file(__filename)};
    std::vector<unsigned int> work_hours{get_work_hours_from_file(__filename)};
    std::vector<std::string> job_posts{get_job_posts_from_file(__filename)};
    std::vector<double> hour_salaries{get_hour_salaries_from_file(__filename)};

    // Vector of employeers
    std::vector<Employee> employeers_vec;

    // Instance of employee to add it to vector of employeers
    Employee next_employee;

    // Iterating by elements of one of the property (all of them must be one size)
    for (size_t index{0UL}; index < IDs.size(); index++)
    {
        // Copying all properties of each employee
        next_employee.m_ID = IDs.at(index);
        next_employee.m_lnp = lnps.at(index);
        next_employee.m_work_hours = work_hours.at(index);
        next_employee.m_job_post = job_posts.at(index);
        next_employee.m_hour_salary = hour_salaries.at(index);

        // Adding this instance to vector of employeers
        employeers_vec.push_back(next_employee);

        // Clearing instance of 'Employee' object
        next_employee.m_ID = 0U;
        next_employee.m_lnp.clear();
        next_employee.m_work_hours = 0U;
        next_employee.m_job_post.clear();
        next_employee.m_hour_salary = 0.0;
    }

    // Returning vector of employeers
    return employeers_vec;
}

void Employee::print_all_data(const char *__filename) const
{
    // Vector of employeers
    std::vector<Employee> employeers_vec{get_employeers_from_file(__filename)};

    for (size_t index{0UL}; index < employeers_vec.size(); index++)
    {
        // Move to next employee
        Employee employee{employeers_vec.at(index)};

        // Printing data to terminal
        print_data(employee);

        // Move to next line
        std::cout << '\n';
    }
}

void Employee::do_option(unsigned int &__option)
{
    while (__option != 9U)
    {
        if (__option == 1U)
        {
            std::cout << "Creating new employeer: " << std::endl;
            user_input();
        }
        else if (__option == 2U)
        {
            user_input();
            edit_data(m_lnp, m_work_hours, m_job_post, m_hour_salary);
        }
        else if (__option == 5U)
        {
            std::cout << "Enter name of file: ";

            // Name of file
            std::string filename{""};
            std::cin >> filename;

            // Writing data to a file
            write_to_file(filename.c_str());
        }
        else if (__option == 6U)
        {
            std::cout << "Reading data from a file: " << std::endl;
            while (true)
            {
                std::cout << "Enter name of file: ";

                // Name of a file
                std::string filename{};
                std::cin >> filename;

                // If file exists -> read from it
                if (is_file_exist(filename.c_str()))
                {
                    std::cout << "\nData from a file " << filename << "\n";
                    read_from_file(filename.c_str());
                    break;
                }
                // Otherwise: print message & go back to beginning of an infinity loop
                else
                    std::cout << "There is no such file. Try again.\n";
            }
        }

        std::cout << '\n';
        __option = print_menu();
    }
    std::cout << "Exiting ... " << std::endl;
    exit(EXIT_SUCCESS);
}
