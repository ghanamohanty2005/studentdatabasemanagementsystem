#include <stdio.h>
#include <stdlib.h> // For system("cls") or system("clear")
#include <string.h>
#include <ctype.h>

#define FILE_NAME "students.dat"
char adminMessage[1000] = "";

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[15];
    float cgpa;
    int projects;
    char semester[5];  // e.g., "1st", "2nd", etc.
    char department[50];
    char address[100];
    char dob[15];
    char gender[10];  // Must be Male or Female
    char hobbies[50];
    char projectDetails[10][100]; // Array to store details for up to 10 projects
    char password[50]; // Password for login (email before '@')
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void addProjectDetails();
void displayProjectDetails();
void editStudentDetails();
void contactUs();
void aboutUs();
void sendEmailToAllStudents();
void studentMenu(int studentID); // Student-specific menu
void adminMenu(); // Admin-specific menu

/* Helper functions for validation */
int isValidPhone(char phone[]);
int isValidEmail(char email[]);
int isValidSemester(char sem[]);
int isValidGender(char gender[]);
int authenticateStudent(int id, char password[]); // Authenticate student
int authenticateAdmin(char password[]); // Authenticate admin

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/Mac
    #endif
}

int main() {
    int choice;
    int studentID;
    char password[50];

    while (1) {
        clearScreen(); // Clear the screen before displaying the main menu
        printf("  **********************************************************************\n");
        printf("  *                                                                    *\n");
        printf("  *                  C.V. Raman Global University                      *\n");
        printf("  *                      Bhubaneswar, Odisha                           *\n");
        printf("  *                                                                    *\n");
        printf("  *--------------------------------------------------------------------*\n");
        printf("  *                        STUDENTSPHERE                               *\n");
        printf("  *                                                                    *\n");
        printf("  *             A Student Database Management System                   *\n");
        printf("  *                                                                    *\n");
        printf("  *           ~ Designed By :- GHANSYAMA MOHANTY                       *\n");
        printf("  *                            APARNA PRIYADARSHINI                    *\n");
        printf("  *                            AYUSHMAN ROUT                           *\n");
        printf("  *                            SHAKTI PRASAD SWAIN                     *\n");
        printf("  *                            JAYASHREE BEHERA                        *\n");
        printf("  **********************************************************************\n");
        printf("\n");
        printf("  ======================================================================\n");
        printf("  |                                                                    |\n");
        printf("  |                /\\ WELCOME TO OUR DASHBOARD /\\                      |\n");
        printf("  |                                                                    |\n");
        printf("  |--------------------------------------------------------------------|\n");
        printf("  |                                                                    |\n");
        printf("  |         Manage Student Records with Ease and Security              |\n");
        printf("  |                                                                    |\n");
        printf("  ======================================================================\n");
        printf("\n===========================================\n");
        printf("   STUDENT DATABASE MANAGEMENT SYSTEM\n");
        printf("===========================================\n");
        printf("1. Student Login\n");
        printf("2. Admin Login\n");
        printf("3. Exit\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen(); // Clear the screen before student login
                printf("\nEnter Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Password (email before '@'): ");
                scanf("%s", password);
                if (authenticateStudent(studentID, password)) {
                    studentMenu(studentID);
                } else {
                    printf("\nInvalid ID or password!\n");
                    getchar(); // Wait for user input before clearing the screen
                    getchar();
                }
                break;
            case 2:
                clearScreen(); // Clear the screen before admin login
                printf("\nEnter Admin Password: ");
                scanf("%s", password);
                if (authenticateAdmin(password)) {
                    adminMenu();
                } else {
                    printf("\nInvalid password!\n");
                    getchar(); // Wait for user input before clearing the screen
                    getchar();
                }
                break;
            case 3:
                printf("\nExiting program...\n");
                printf("\n THANK YOU!! ");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
                getchar(); // Wait for user input before clearing the screen
                getchar();
        }
    }

    return 0;
}

void studentMenu(int studentID) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    Student s;
    int found = 0;

    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == studentID) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nStudent with ID %d not found.\n", studentID);
        return;
    }

    int choice;
    while (1) {
        clearScreen(); // Clear the screen before displaying the student menu
        printf("\n===========================================\n");
        printf("   STUDENT MENU\n");
        printf("===========================================\n");
        printf("1. View Email\n");
        printf("2. View CGPA\n");
        printf("3. Logout\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen(); // Clear the screen before displaying messages
                printf("\nEmail sent to you:\n");
                if (strlen(adminMessage)) {
                    printf("Admin: %s\n", adminMessage);
                    printf("\nPress enter to continue !!");
                } else {
                    printf("No Email from admin.\n");
                    printf("\nPress enter to continue!!");
                }
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 2:
                clearScreen(); // Clear the screen before displaying CGPA
                printf("\nYour Current CGPA: %.2f\n", s.cgpa);
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 3:
                printf("\nLogging out...\n");
                printf("\n THANK YOU!!");
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
        }
    }
}

void adminMenu() {
    int choice;

    while (1) {
        clearScreen(); // Clear the screen before displaying the admin menu
        printf("\n===========================================\n");
        printf("   ADMIN MENU\n");
        printf("===========================================\n");
        printf("1.  Add Student\n");
        printf("2.  Display All Students\n");
        printf("3.  Search Student by ID\n");
        printf("4.  Delete Student by ID\n");
        printf("5.  Add Project Details\n");
        printf("6.  Display Project Details\n");
        printf("7.  Edit Student Details\n");
        printf("8.  Send Email to All Students\n");
        printf("9.  Contact Us\n");
        printf("10. About Us\n");        
        printf("11. Logout\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen(); // Clear the screen before adding a student
                addStudent();
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 2:
                clearScreen(); // Clear the screen before displaying students
                displayStudents();
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 3:
                clearScreen(); // Clear the screen before searching a student
                searchStudent();
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 4:
                clearScreen(); // Clear the screen before deleting a student
                deleteStudent();
                printf("\nPress enter to continue!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 5:
                clearScreen(); // Clear the screen before adding project details
                addProjectDetails();
                printf("\nPress ENTER!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 6:
                clearScreen(); // Clear the screen before displaying project details
                displayProjectDetails();
                printf("\nPress ENTER!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 7:
                clearScreen(); // Clear the screen before editing student details
                editStudentDetails();
                printf("\nPress ENTER!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
                break;
            case 8:
                clearScreen(); // Clear the screen before sending a message
                sendEmailToAllStudents();
                printf("\nPress ENTER!!");
                getchar(); // Wait for user input before clearing the screen
                break;
            case 9:
            	clearScreen(); // Clear the screen before sending a message
                contactUs();
                printf("\nPress ENTER!!");
                getchar();
				getchar(); // Wait for user input before clearing the screen
                break;
            case 10:
            	clearScreen(); // Clear the screen before sending a message
                aboutUs();
                printf("\nPress ENTER!!");
                getchar(); 
				getchar();// Wait for user input before clearing the screen
                break;
            case 11:
                printf("\nLogging out...\n");
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("\nPress ENTER!!");
                getchar(); // Wait for user input before clearing the screen
                getchar();
        }
    }
}

// Rest of the functions remain unchanged...
int authenticateStudent(int id, char password[]) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        return 0;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == id) {
            char *emailPart = strtok(s.email, "@");
            if (strcmp(emailPart, password) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int authenticateAdmin(char password[]) {
    // Hardcoded admin password for demonstration
    return (strcmp(password, "admin123") == 0);
}

void addStudent() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    getchar();  

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    do {
        printf("Enter Email (Gmail only): ");
        fgets(s.email, 50, stdin);
        s.email[strcspn(s.email, "\n")] = '\0';
        if (!isValidEmail(s.email))
            printf("Invalid email format! Must end with '@gmail.com'.\n");
    } while (!isValidEmail(s.email));

    // Set password as email before '@'
//    char *emailPart = strtok(s.email, "@");
//    strcpy(s.password, emailPart);

    do {
        printf("Enter Phone Number (10 digits only): ");
        fgets(s.phone, 15, stdin);
        s.phone[strcspn(s.phone, "\n")] = '\0';
        if (!isValidPhone(s.phone))
            printf("Invalid phone number! Must be 10 digits.\n");
    } while (!isValidPhone(s.phone));

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);

    printf("Enter Number of Projects: ");
    scanf("%d", &s.projects);
    getchar();

    do {
        printf("Enter Current Semester (e.g., 1st, 2nd, 3rd): ");
        fgets(s.semester, 5, stdin);
        s.semester[strcspn(s.semester, "\n")] = '\0';
        if (!isValidSemester(s.semester))
            printf("Invalid semester format! Example: '1st', '2nd'.\n");
    } while (!isValidSemester(s.semester));

    printf("Enter Department: ");
    fgets(s.department, 50, stdin);
    s.department[strcspn(s.department, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(s.address, 100, stdin);
    s.address[strcspn(s.address, "\n")] = '\0';

    printf("Enter Date of Birth (DD/MM/YYYY): ");
    fgets(s.dob, 15, stdin);
    s.dob[strcspn(s.dob, "\n")] = '\0';

    do {
        printf("Enter Gender (Male/Female): ");
        fgets(s.gender, 10, stdin);
        s.gender[strcspn(s.gender, "\n")] = '\0';
        if (!isValidGender(s.gender))
            printf("Invalid gender! Must be 'Male' or 'Female'.\n");
    } while (!isValidGender(s.gender));

    printf("Enter Hobbies: ");
    fgets(s.hobbies, 50, stdin);
    s.hobbies[strcspn(s.hobbies, "\n")] = '\0';

    // Initialize project details
    for (int i = 0; i < s.projects; i++) {
        strcpy(s.projectDetails[i], "No details added yet.");
    }

    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    Student s;

    printf("\n ================================================================================================\n");
    printf("| %-5s | %-20s | %-30s | %-12s | %-15s |\n", 
           "ID", "Name", "Email", "Phone", "Department");
    printf(" ------------------------------------------------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, file) ){
        printf("| %-5d | %-20s | %-30s | %-12s | %-15s |\n", 
               s.id, s.name, s.email, s.phone, s.department);
    }
    
    printf(" ================================================================================================\n");
char *emailPart = strtok(s.email, "@");
    strcpy(s.password, emailPart);
    fclose(file);
}

void searchStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    int searchID, found = 0;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchID);

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == searchID) {
            printf("\nStudent Found!\n");
            printf("\n---------------------------------------\n");
            printf(" ID           : %d\n", s.id);
            printf(" Name         : %s\n", s.name);
            printf(" Email        : %s\n", s.email);
            printf(" Phone        : %s\n", s.phone);
            printf(" CGPA         : %.2f\n", s.cgpa);
            printf(" Projects     : %d\n", s.projects);
            printf(" Semester     : %s\n", s.semester);
            printf(" Department   : %s\n", s.department);
            printf(" Address      : %s\n", s.address);
            printf(" Date of Birth: %s\n", s.dob);
            printf(" Gender       : %s\n", s.gender);
            printf(" Hobbies      : %s\n", s.hobbies);
            printf(" Project Details:\n");
            for (int i = 0; i < s.projects; i++) {
                printf(" Project %d: %s\n", i+1, s.projectDetails[i]);
            }
            printf("---------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", searchID);
    }
    
    fclose(file);
}

void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    int deleteID, found = 0;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &deleteID);

    FILE *tempFile = fopen("temp.dat", "wb");
    Student s;

    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == deleteID) {
            printf("\nStudent with ID %d deleted successfully!\n", deleteID);
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (!found) {
        printf("\nStudent with ID %d not found.\n", deleteID);
    }
}

void addProjectDetails() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    int studentID, found = 0;
    printf("\nEnter Student ID to add project details: ");
    scanf("%d", &studentID);

    Student s;
    while (fread(&s, sizeof(Student), 1, file) ){
        if (s.id == studentID) {
            printf("\nStudent Found: %s\n", s.name);
            printf("Number of Projects: %d\n", s.projects);

            for (int i = 0; i < s.projects; i++) {
                printf("Enter details for Project %d: ", i+1);
                getchar(); // Consume newline character
                fgets(s.projectDetails[i], 100, stdin);
                s.projectDetails[i][strcspn(s.projectDetails[i], "\n")] = '\0';
            }

            fseek(file, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, file);
            found = 1;
            printf("\nProject details added successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", studentID);
    }

    fclose(file);
}

void displayProjectDetails() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    int studentID, found = 0;
    printf("\nEnter Student ID to display project details: ");
    scanf("%d", &studentID);

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == studentID) {
            printf("\nName: %s\n", s.name);
            printf("Project Details for Student ID %d:\n", studentID);
            printf("---------------------------------------\n");
            for (int i = 0; i < s.projects; i++) {
                printf("Project %d: %s\n", i + 1, s.projectDetails[i]);
            }
            printf("---------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", studentID);
    }

    fclose(file);
}

void editStudentDetails() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    int studentID, found = 0;
    printf("\nEnter Student ID to edit: ");
    scanf("%d", &studentID);

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == studentID) {
            printf("\nEditing Student ID %d:\n", studentID);
            printf("---------------------------------------\n");

            printf("Enter Name: ");
            getchar(); // Consume newline character
            fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            do {
                printf("Enter Email (Gmail only): ");
                fgets(s.email, 50, stdin);
                s.email[strcspn(s.email, "\n")] = '\0';
                if (!isValidEmail(s.email))
                    printf("Invalid email format! Must end with '@gmail.com'.\n");
            } while (!isValidEmail(s.email));

            do {
                printf("Enter Phone Number (10 digits only): ");
                fgets(s.phone, 15, stdin);
                s.phone[strcspn(s.phone, "\n")] = '\0';
                if (!isValidPhone(s.phone))
                    printf("Invalid phone number! Must be 10 digits.\n");
            } while (!isValidPhone(s.phone));

            printf("Enter CGPA: ");
            scanf("%f", &s.cgpa);

            printf("Enter Number of Projects: ");
            scanf("%d", &s.projects);
            getchar();

            do {
                printf("Enter Current Semester (e.g., 1st, 2nd, 3rd): ");
                fgets(s.semester, 5, stdin);
                s.semester[strcspn(s.semester, "\n")] = '\0';
                if (!isValidSemester(s.semester))
                    printf("Invalid semester format! Example: '1st', '2nd'.\n");
            } while (!isValidSemester(s.semester));

            printf("Enter Department: ");
            fgets(s.department, 50, stdin);
            s.department[strcspn(s.department, "\n")] = '\0';

                        printf("Enter Address: ");
            fgets(s.address, 100, stdin);
            s.address[strcspn(s.address, "\n")] = '\0';

            printf("Enter Date of Birth (DD/MM/YYYY): ");
            fgets(s.dob, 15, stdin);
            s.dob[strcspn(s.dob, "\n")] = '\0';

            do {
                printf("Enter Gender (Male/Female): ");
                fgets(s.gender, 10, stdin);
                s.gender[strcspn(s.gender, "\n")] = '\0';
                if (!isValidGender(s.gender))
                    printf("Invalid gender! Must be 'Male' or 'Female'.\n");
            } while (!isValidGender(s.gender));

            printf("Enter Hobbies: ");
            fgets(s.hobbies, 50, stdin);
            s.hobbies[strcspn(s.hobbies, "\n")] = '\0';

            fseek(file, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, file);
            found = 1;
            printf("\nStudent details updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", studentID);
    }

    fclose(file);
}

//void sendMessageToAllStudents() {
//    FILE *file = fopen(FILE_NAME, "rb");
//    if (file == NULL) {
//        printf("\nNo student records found!\n");
//        return;
//    }
//
//    char message[1000];
//    printf("\nEnter message to send to all students: ");
//    getchar(); // Consume newline character
//    fgets(message, 1000, stdin);
//    message[strcspn(message, "\n")] = '\0';
//
//    printf("\nSending message to all students...\n");
//    printf("Message: %s\n", message);
//
//    fclose(file);
//}

void sendEmailToAllStudents() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Email to send to all students: ");
    getchar(); // Consume newline character
    fgets(adminMessage, 1000, stdin);
    adminMessage[strcspn(adminMessage, "\n")] = '\0';

    printf("\nSending Email to all students...\n");
    printf("Message: %s\n", adminMessage);

    fclose(file);
}
void contactUs() {
    printf("Contact Us\n");
    printf("Bhubaneswar - 752054\n");
    printf("+91 9040272733 / +91 9040272755\n");
    printf("+91-674-663 6555 (Admission)\n");
    printf("9040021102 (Admission)\n");
    printf("info@cgu-odisha.ac.in\n");
    printf("admission@cgu-odisha.ac.in\n");
}
// About Us function
void aboutUs() {
    printf("==== About Us ====\n\n");
    printf("Established in accordance with the Odisha Act 01 of 2020, C. V. Raman Global University, Odisha\n");
    printf("(CGU, Odisha) introduces students to new and innovative ways of learning. It is a vibrant community\n");
    printf("of students, faculty, and staff members committed to making a difference in society by leading with\n");
    printf("innovation and purpose.\n\n");
    printf("We take pride in our ethos and collaborative culture that foster intellectual engagement and growth.\n");
    printf("At CGU, Odisha, students learn to challenge the status quo and solve the most difficult problems\n");
    printf("with analytical rigor and creativity. We continue to add interdisciplinary courses to our existing\n");
    printf("portfolio to offer a truly global education in the field of science and technology.\n");

    printf("\n\n");
    
    printf("===== Evolution of leadership ==== \n\n ");
    printf("CGU, Odisha rests on the legacy and leadership of C.V. Raman College of Engineering (CVRCE)\n");
    printf("which began its transformative journey in 1997. It grew in record time imparting technical\n");
    printf("education with a larger purpose and impact through world-class laboratories, research-intensive\n");
    printf("learning pedagogy, unmatched Centres of Excellence and unhindered connectivity to some of the\n");
    printf("finest libraries in the world.\n\n");
    printf("CGU, Odisha imbibes the same institutional values of CVRCE and aims to offer a dynamic learning\n");
    printf("environment to students through its responsive support system, robust infrastructure and global\n");
    printf("exposure (enabled via international seminars, conferences and workshops.) Committed to offering\n");
    printf("quality education to all, it aims to push the frontiers of knowledge with cutting-edge research,\n");
    printf("innovation and unconventional thinking.\n");
 }

/* Helper functions for validation */
int isValidPhone(char phone[]) {
    if (strlen(phone) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidEmail(char email[]) {
    char *domain = strstr(email, "@gmail.com");
    return (domain != NULL && strlen(domain) == 10);
}

int isValidSemester(char sem[]) {
    if (strlen(sem) != 3) {
        return 0;
    }
    if (!isdigit(sem[0])) {
        return 0;
    }
    if (strcmp(&sem[1], "st") != 0 && strcmp(&sem[1], "nd") != 0 && strcmp(&sem[1], "rd") != 0 && strcmp(&sem[1], "th") != 0) {
        return 0;
    }               
    return 1;
}

int isValidGender(char gender[]) {
    return (strcasecmp(gender, "Male") == 0 || strcasecmp(gender, "Female") == 0);
}
