// Includes the standard input/output library, which provides functions like printf(), scanf(), fopen(), etc.
#include <stdio.h>
// Includes the standard library, which provides functions like exit(), malloc(), free(), etc.
#include <stdlib.h>
// Includes the string library, which provides functions for string manipulation like strcpy(), strcmp(), strlen(), etc.
#include <string.h>
// Includes the character type library, which provides functions like isdigit(), isalpha(), toupper(), etc.
#include <ctype.h>

// Defines a structure named 'Student' to hold all the data for a single student.
struct Student
{
    // A character array to store the student's number, up to 10 digits plus a null terminator.
    char studentNumber[11];
    // A character array to store the student's full name, up to 30 characters plus a null terminator.
    char fullName[31];
    // A single character to store the student's gender ('M' or 'F').
    char gender;
    // A character array to store the student's program/course code, up to 5 characters plus a null terminator.
    char program[6];
    // An integer to store the student's year level (e.g., 1, 2, 3, 4).
    int yearLevel;
    // An integer to store the total number of units the student is enrolled in.
    int units;
    // A float to store the student's preliminary grade.
    float prelim;
    // A float to store the student's midterm grade.
    float midterm;
    // A float to store the student's final grade.
    float final;
    // A float to store the student's calculated overall grade in the Philippine grading system.
    float overall_ph_grade;
    // A character array to store the student's remarks ("Passed" or "Failed").
    char remarks[20];
    // A character array to store the student's academic standing (e.g., "President's Lister").
    char academicStanding[20];
}; // The semicolon marks the end of the structure definition.

// Declares a global array named 'students' that can hold up to 10 'Student' structures.
struct Student students[10];
// Declares and initializes a global integer 'count' to 0. This variable keeps track of the current number of student records in the array.
int count = 0;

// This function determines if a student passed or failed based on their Philippine-system grade.
void getRemarksFromPhGrade(float phGradeValue, char *remarksBuffer)
{
    // Checks if the grade is 3.0 or better (lower is better in this system).
    if (phGradeValue <= 3.0)
    {
        // If the condition is true, copy the string "Passed" into the provided buffer.
        strcpy(remarksBuffer, "Passed");
    }
    // If the grade is worse than 3.0.
    else
    {
        // Copy the string "Failed" into the provided buffer.
        strcpy(remarksBuffer, "Failed");
    }
} // End of the getRemarksFromPhGrade function.

// This function determines a student's academic standing based on their overall grade.
void getAcademicStanding(float overallPhGrade, char *standingBuffer)
{
    // Checks if the grade is between 1.00 and 1.50, inclusive.
    if (overallPhGrade >= 1.00 && overallPhGrade <= 1.50)
    {
        // If true, the student is a President's Lister.
        strcpy(standingBuffer, "President's Lister");
    }
    // If not a President's Lister, check if the grade is between 1.51 and 1.75.
    else if (overallPhGrade > 1.50 && overallPhGrade <= 1.75)
    {
        // If true, the student is a Dean's Lister.
        strcpy(standingBuffer, "Dean's Lister");
    }
    // If not a Dean's Lister, check if the grade is between 1.76 and 3.00.
    else if (overallPhGrade > 1.75 && overallPhGrade <= 3.00)
    {
        // If true, the student has a Regular standing.
        strcpy(standingBuffer, "Regular");
    }
    // If not Regular, check if the grade is between 3.01 and 5.00.
    else if (overallPhGrade > 3.00 && overallPhGrade <= 5.00)
    {
        // If true, the student is considered a Dropout.
        strcpy(standingBuffer, "Dropout");
    }
    // If the grade does not fall into any of the above categories.
    else
    {
        // Assign an "Unknown" status.
        strcpy(standingBuffer, "Unknown/Invalid Grade");
    }
} // End of the getAcademicStanding function.

// This function re-calculates the remarks and academic standing for every student currently in the system.
void computeGrades()
{
    // Checks if there are any student records to process.
    if (count == 0)
    {
        // If there are no students, print a message to the user.
        printf("No students to compute grades for. Please add students first.\n");
        // Exit the function early since there is nothing to do.
        return;
    }
    // Start a loop that will run for each student in the 'students' array.
    for (int i = 0; i < count; i++)
    {
        // Call the function to determine the remarks for the current student.
        getRemarksFromPhGrade(students[i].overall_ph_grade, students[i].remarks);
        // Call the function to determine the academic standing for the current student.
        getAcademicStanding(students[i].overall_ph_grade, students[i].academicStanding);
    } // End of the for loop.
    // Inform the user that the computation is complete.
    printf("Grades computed successfully for all students!\n");
} // End of the computeGrades function.

// A utility function to clear any leftover characters from the input buffer.
void clearInputBuffer()
{
    // Declare a character variable 'c' to hold the characters being read.
    int c;
    // Loop as long as the character read is not a newline ('\n') or the End-Of-File (EOF) marker.
    while ((c = getchar()) != '\n' && c != EOF)
        ;
} // End of the clearInputBuffer function.

// A function to read an integer from the user, with validation to ensure it's within a specific range.
int readValidatedInt(const char *prompt, int min, int max)
{
    // Declare an integer variable 'value' to store the user's input.
    int value;
    // Declare an integer 'input_success' to check if scanf was successful.
    int input_success;
    // Start a do-while loop to ensure we get valid input. The loop will repeat until the input is correct.
    do
    {
        // Print the prompt message passed to the function (e.g., "Enter year level (1-4): ").
        printf("%s", prompt);
        // Try to read an integer from the user and store the result (1 for success, 0 or EOF for failure) in 'input_success'.
        input_success = scanf("%d", &value);
        // Call the function to clear the input buffer of any extra characters.
        clearInputBuffer();
        // Check if the input failed, or if the value is less than the minimum or greater than the maximum allowed.
        if (input_success != 1 || value < min || value > max)
        {
            // If the input is invalid, print an error message showing the valid range.
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
        // The condition to continue the loop: repeat if scanf failed or the value is out of range.
    } while (input_success != 1 || value < min || value > max);
    // When a valid integer is entered, return it.
    return value;
} // End of the readValidatedInt function.

// A function to read a floating-point number from the user, with validation for a specific range.
float readValidatedFloat(const char *prompt, float min, float max)
{
    // Declare a float variable 'value' to store the user's input.
    float value;
    // Declare an integer 'input_success' to check if scanf was successful.
    int input_success;
    // Start a do-while loop to ensure we get valid input.
    do
    {
        // Print the prompt message passed to the function (e.g., "Enter prelim grade (1.0-5.0): ").
        printf("%s", prompt);
        // Try to read a float from the user and store the result in 'input_success'.
        input_success = scanf("%f", &value);
        // Call the function to clear the input buffer.
        clearInputBuffer();
        // Check if the input failed, or if the value is outside the allowed range.
        if (input_success != 1 || value < min || value > max)
        {
            // If the input is invalid, print an error message showing the valid range.
            printf("Invalid input. Please enter a number between %.2f and %.2f.\n", min, max);
        }
        // The condition to continue the loop: repeat if scanf failed or the value is out of range.
    } while (input_success != 1 || value < min || value > max);
    // When a valid float is entered, return it.
    return value;
} // End of the readValidatedFloat function.

// This function allows the user to enter the details for a new student record.
void enterStudent()
{
    // Checks if the student array is already full.
    if (count >= 10)
    {
        // If full, print a message and stop the function.
        printf("Maximum student limit reached (10). Cannot add more students.\n");
        // Return to the main menu.
        return;
    } // End of the if block.

    // Print a header for this section.
    printf("\n--- Enter New Student Record ---\n");

    // Initialize a flag for student number validation.
    int valid_student_number = 0; // Changed to 0 to enter the loop correctly
    // Create a temporary buffer to read the student number safely.
    char tempStudentNumberBuffer[100];
    // Start a do-while loop that repeats until a valid student number is entered.
    do
    {
        // Prompt the user for the student number.
        printf("Enter student number (1-10 digits, numbers only): ");
        // Read the entire line of input from the user.
        if (fgets(tempStudentNumberBuffer, sizeof(tempStudentNumberBuffer), stdin) == NULL)
        {
            // If there's an error reading input, print a message.
            printf("Error reading input. Please try again.\n");
            // Skip to the next iteration of the loop.
            continue;
        } // End of the if block.

        // Remove the newline character that fgets reads.
        tempStudentNumberBuffer[strcspn(tempStudentNumberBuffer, "\n")] = '\0';

        // Get the length of the input string.
        size_t len = strlen(tempStudentNumberBuffer);
        // Check if the input string is empty.
        if (len == 0)
        {
            // Print an error message if it's empty.
            printf("Student number cannot be empty. Please try again.\n");
            // Skip to the next iteration.
            continue;
            // Check if the input string is too long.
        }
        else if (len > 10)
        {
            // Print an error message if it's too long.
            printf("Student number exceeds maximum length of 10 numbers (%zu numbers entered). Please try again.\n", len);
            // Skip to the next iteration.
            continue;
        } // End of the else if block.

        // Assume the input is valid (setting to 1), then we will try to disprove it
        valid_student_number = 1;
        // Disprove attempt: Loop through each character of the input string.
        for (int i = 0; i < len; i++)
        {
            // Check if the given character is not a digit.
            if (!isdigit(tempStudentNumberBuffer[i]))
            {
                // If a non-digit is found, print an error.
                printf("Student number must contain only digits.\n");
                // Disprove attempt complete! Setting it to 0
                valid_student_number = 0;
                // Exit the for loop since we already disprove
                break;
            } // End of the if block.
        } // End of the for loop.

        // If the validation flag is still 1 (true) after the loop.
        if (valid_student_number)
        {
            // Copy the students[count].studentNumber from the tempStudentNumberBuffer.
            strcpy(students[count].studentNumber, tempStudentNumberBuffer);
        } // End of the if block.

        // Continue the do-while loop as long as the valid_student_number remains 0.
    } while (!valid_student_number);
    // Initialize a flag for full name validation.
    int valid_full_name = 0;

    // Create a temporary buffer to safely read the full name from input.
    char tempFullNameBuffer[256];

    // Start a do-while loop that repeats until a valid name is entered.
    do
    {
        // Prompt the user for the full name with a character limit hint.
        printf("Enter full name (max 30 chars): ");

        // Read a full line of input including spaces using fgets.
        if (fgets(tempFullNameBuffer, sizeof(tempFullNameBuffer), stdin) == NULL)
        {
            // If input fails (e.g., stream error), notify user and retry.
            printf("Error reading input. Please try again.\n");
            // Restart loop since input reading failed.
            continue;
        }

        // Strip newline character if present at the end of the input string.
        tempFullNameBuffer[strcspn(tempFullNameBuffer, "\n")] = '\0';

        // Get the length of the entered name string.
        size_t len = strlen(tempFullNameBuffer);

        // Validate that the name is not too long (more than 30 characters).
        if (len > 30)
        {
            // Show user the problem and how long the name actually was.
            printf("Full name exceeds maximum length of 30 characters (%zu chars entered). Please try again.\n", len);
            // Restart loop due to invalid length.
            continue;
        }
        // Check if the name input is empty (user hit Enter without typing).
        else if (len == 0)
        {
            // Notify the user that empty input is not acceptable.
            printf("Full name cannot be empty. Please try again.\n");
            // Restart loop due to empty input.
            continue;
        }
        // If name length is valid and not empty, check for digits in the name.
        else
        {
            // Initialize flag for detecting digits within the name.
            int hasDigit = 0;
            // Iterate over each character in the input name.
            for (int i = 0; tempFullNameBuffer[i] != '\0'; i++)
            {
                // If a digit is found, set flag and exit loop early.
                if (isdigit(tempFullNameBuffer[i]))
                {
                    hasDigit = 1;
                    break;
                }
            }
            // If a digit was found in the name, input is invalid.
            if (hasDigit)
            {
                // Inform the user that numbers are not allowed in the name.
                printf("Full name cannot contain numbers. Please try again.\n");
            }
            else
            {
                // If no digits found, copy valid name to student record.
                strcpy(students[count].fullName, tempFullNameBuffer);
                // Set validation flag to exit loop.
                valid_full_name = 1;
            }
        }
        // Loop repeats as long as the full name is invalid.
    } while (!valid_full_name);

    // Initialize a flag for gender validation.
    int valid_gender = 0;
    // Start a do-while loop to get a valid gender input.
    do
    {
        // Prompt the user for their gender.
        printf("Enter gender (M/F): ");
        // Declare a character to store the input.
        char gender_char;
        // Read a single character. The space before %c consumes any leftover whitespace.
        if (scanf(" %c", &gender_char) != 1)
        {
            // If scanf fails, clear the buffer and try again.
            clearInputBuffer();
            // Skip to the next iteration.
            continue;
        } // End of the if block.
        // Clear any other characters left on the input line (like the Enter key).
        clearInputBuffer();
        // Convert the input character to uppercase to make the check case-insensitive.
        gender_char = toupper(gender_char);
        // Check if the character is not 'M' and not 'F'.
        if (gender_char != 'M' && gender_char != 'F')
        {
            // If invalid, print an error message.
            printf("Invalid gender. Please enter 'M' or 'F'.\n");
            // If the input is valid.
        }
        else
        {
            // Assign the valid gender to the student record.
            students[count].gender = gender_char;
            // Set the flag to 1 (true) to exit the loop.
            valid_gender = 1;
        } // End of the else block.
        // Continue the loop as long as the gender is not valid.
    } while (!valid_gender);

    // Initialize a flag for program code validation.
    int valid_program = 0;
    // Start a do-while loop to get a valid program code.
    do
    {
        // Prompt the user for the program code.
        printf("Enter program code (e.g., BSIT, BSCS - should contain letters): ");
        // Read a string up to 5 characters long into the student's program field.
        if (scanf(" %5s", students[count].program) != 1)
        {
            // Clear the buffer if scanf fails.
            clearInputBuffer();
            // Print an error message.
            printf("Invalid input for program code. Please try again.\n");
            // Skip to the next iteration.
            continue;
        } // End of the if block.
        // Clear the rest of the input line.
        clearInputBuffer();

        // Assume the program is invalid (purely numeric) until a letter is found.
        valid_program = 0;
        // Loop through each character of the entered program code.
        for (int i = 0; students[count].program[i] != '\0'; i++)
        {
            // Check if the character is an alphabet letter.
            if (isalpha(students[count].program[i]))
            {
                // If a letter is found, the program code is valid.
                valid_program = 1;
                // Exit the for loop since the condition is met.
                break;
            } // End of the if block.
        } // End of the for loop.
        // If after checking all characters, no letter was found.
        if (!valid_program)
        {
            // Print an error message.
            printf("Program code must contain at least one letter and not be purely numeric.\n");
        } // End of the if block.
        // Continue the loop as long as the program code is not valid.
    } while (!valid_program);

    // Call the validation function to read the year level and store it.
    students[count].yearLevel = readValidatedInt("Enter year level (1-4): ", 1, 4);
    // Call the validation function to read the number of units and store it.
    students[count].units = readValidatedInt("Enter units enrolled (1-30): ", 1, 30);
    // Call the validation function to read the prelim grade and store it.
    students[count].prelim = readValidatedFloat("Enter prelim grade (1.0-5.0): ", 1.0, 5.0);
    // Call the validation function to read the midterm grade and store it.
    students[count].midterm = readValidatedFloat("Enter midterm grade (1.0-5.0): ", 1.0, 5.0);
    // Call the validation function to read the final grade and store it.
    students[count].final = readValidatedFloat("Enter final grade (1.0-5.0): ", 1.0, 5.0);

    // Calculate the average of the three grades to get the overall grade.
    students[count].overall_ph_grade = (students[count].prelim + students[count].midterm + students[count].final) / 3.0;
    // Clamp the grade to a minimum of 1.0, in case of calculation quirks.
    if (students[count].overall_ph_grade < 1.0)
        students[count].overall_ph_grade = 1.0;
    // Clamp the grade to a maximum of 5.0.
    if (students[count].overall_ph_grade > 5.0)
        students[count].overall_ph_grade = 5.0;

    // Call the function to determine the remarks ("Passed"/"Failed") for the new student.
    getRemarksFromPhGrade(students[count].overall_ph_grade, students[count].remarks);
    // Call the function to determine the academic standing for the new student.
    getAcademicStanding(students[count].overall_ph_grade, students[count].academicStanding);

    // Increment the global student counter since a new record has been added.
    count++;
    // Print a success message.
    printf("Student record added successfully!\n");
} // End of the enterStudent function.

// This function displays all existing student records in a formatted table.
void displayStudents()
{
    // Check if there are any students to display.
    if (count == 0)
    {
        // If not, print a message and exit the function.
        printf("No student records to display. Please add students first.\n");
        // Return to the main menu.
        return;
    } // End of the if block.

    // Print the table title.
    printf("\n--- All Student Records ---\n");
    // Print the table headers with specific widths for alignment.
    printf("%-12s %-30s %-6s %-4s %-12s %-8s %-20s\n",
           "Student No.", "Full Name", "Course", "Year", "Final Grade", "Remarks", "Academic Standing");
    // Print a line to separate the header from the data.
    printf("----------------------------------------------------------------------------------------------------\n");
    // Loop through each student record in the array.
    for (int i = 0; i < count; i++)
    {
        // Print the data for the current student, formatted to align with the headers.
        printf("%-12s %-30s %-6s %-4d %-12.2f %-8s %-20s\n",
               students[i].studentNumber,     // Student Number string
               students[i].fullName,          // Full Name string
               students[i].program,           // Program string
               students[i].yearLevel,         // Year Level integer
               students[i].overall_ph_grade,  // Final Grade float, formatted to 2 decimal places
               students[i].remarks,           // Remarks string
               students[i].academicStanding); // Academic Standing string
    } // End of the for loop.
    // Print another line at the end of the table.
    printf("----------------------------------------------------------------------------------------------------\n");
} // End of the displayStudents function.

// This function sorts the student records in ascending order based on their final grade (1.0 is highest).
void sortStudents()
{
    // Check if there are enough students to perform a sort (at least 2).
    if (count <= 1)
    {
        // If not, print a message and exit the function.
        printf("Not enough students to sort.\n");
        // Return to the main menu.
        return;
    } // End of the if block.
    // Declare a temporary 'Student' structure to hold a record during a swap.
    struct Student temp;
    // Start the outer loop of the bubble sort algorithm. It runs from the first to the second-to-last element.
    for (int i = 0; i < count - 1; i++)
    {
        // Start the inner loop. It compares the element at 'i' with all subsequent elements.
        for (int j = i + 1; j < count; j++)
        {
            // Compare the grades of the two students.
            if (students[i].overall_ph_grade > students[j].overall_ph_grade)
            {
                // If the 'i' student's grade is "worse" (higher value) than the 'j' student's grade, swap them.
                // Step 1: Store the 'i' student's record in the temporary variable.
                temp = students[i];
                // Step 2: Replace the 'i' student's record with the 'j' student's record.
                students[i] = students[j];
                // Step 3: Place the stored record from 'temp' into the 'j' student's position.
                students[j] = temp;
            } // End of the if block.
        } // End of the inner for loop.
    } // End of the outer for loop.
    // Inform the user that the sorting is complete.
    printf("Students sorted by final grade (ascending, 1.0 being highest grade first).\n");
} // End of the sortStudents function.

// This function searches for a specific student using their student number.
void searchStudent()
{
    // Declare a character array to store the student number input from the user.
    char snum[100];
    // Initialize a flag for input validation.
    int valid_input = 0;
    // Start a do-while loop to ensure the entered student number is in a valid format.
    do
    {
        // Prompt the user to enter the student number to search for.
        printf("Enter student number to search (1-10 digits, numbers only): ");
        // Read the entire line of input to handle potential errors.
        if (fgets(snum, sizeof(snum), stdin) == NULL)
        {
            // If reading fails, print an error and restart the loop.
            printf("Error reading input. Please try again.\n");
            // Go to the next iteration of the loop.
            continue;
        } // End of the if block.

        // Get the length of the input string.
        size_t len = strlen(snum);
        // Check if the last character is a newline (from pressing Enter).
        if (len > 0 && snum[len - 1] == '\n')
        {
            // If it is, replace it with a null terminator to clean the string.
            snum[len - 1] = '\0';
            // Decrement the length to reflect the removal.
            len--;
            // Check if the buffer was filled completely, meaning input might have been truncated.
        }
        else if (len >= sizeof(snum) - 1)
        {
            // Clear the input buffer to remove the rest of the oversized input.
            clearInputBuffer();
        } // End of the else if block.

        // Check if the resulting string is empty.
        if (len == 0)
        {
            // Print an error if the input is empty.
            printf("Student number cannot be empty. Please try again.\n");
            // Set flag to invalid.
            valid_input = 0;
            // Go to the next iteration of the loop.
            continue;
            // Check if the input is too long.
        }
        else if (len > 10)
        {
            // Print an error if the input exceeds 10 digits.
            printf("Student number exceeds maximum length of 10 numbers (%zu numbers entered). Please try again.\n", len);
            // Set flag to invalid.
            valid_input = 0;
            // Go to the next iteration of the loop.
            continue;
        } // End of the else if block.

        // Assume the input is valid at this point.
        valid_input = 1;
        // Loop through each character of the input string.
        for (int i = 0; i < len; i++)
        {
            // Check if the current character is not a digit.
            if (!isdigit(snum[i]))
            {
                // If it's not a digit, print an error.
                printf("Student number must contain only digits.\n");
                // Set the flag to invalid.
                valid_input = 0;
                // Exit the for loop, no need to check further.
                break;
            } // End of the if block.
        } // End of the for loop.
        // Repeat the do-while loop if the input was found to be invalid.
    } while (!valid_input);

    // Initialize a 'found' flag to 0 (false).
    int found = 0;
    // Loop through all the student records currently in the system.
    for (int i = 0; i < count; i++)
    {
        // Compare the student number from the array with the number the user entered.
        if (strcmp(students[i].studentNumber, snum) == 0)
        {
            // If they match, a record has been found.
            // Print a header for the found student's details.
            printf("\n--- Student Found ---\n");
            // Print the student's number.
            printf("Student Number: %s\n", students[i].studentNumber);
            // Print the student's full name.
            printf("Full Name: %s\n", students[i].fullName);
            // Print the student's gender.
            printf("Gender: %c\n", students[i].gender);
            // Print the student's program.
            printf("Program: %s\n", students[i].program);
            // Print the student's year level.
            printf("Year Level: %d\n", students[i].yearLevel);
            // Print the student's enrolled units.
            printf("Units Enrolled: %d\n", students[i].units);
            // Print the student's prelim grade.
            printf("Prelim Grade: %.2f\n", students[i].prelim);
            // Print the student's midterm grade.
            printf("Midterm Grade: %.2f\n", students[i].midterm);
            // Print the student's final exam grade.
            printf("Final Exam Grade: %.2f\n", students[i].final);
            // Print the student's overall final grade.
            printf("Overall Final Grade: %.2f\n", students[i].overall_ph_grade);
            // Print the student's remarks.
            printf("Remarks: %s\n", students[i].remarks);
            // Print the student's academic standing.
            printf("Academic Standing: %s\n", students[i].academicStanding);
            // Set the 'found' flag to 1 (true).
            found = 1;
            // Exit the loop since we found the student.
            break;
        } // End of the if block.
    } // End of the for loop.
    // After the loop, check if the 'found' flag is still 0 (false).
    if (!found)
    {
        // If no student was found, print a "not found" message.
        printf("Student with number '%s' not found.\n", snum);
    } // End of the if block.
} // End of the searchStudent function.

// This function saves the current list of student records to a text file named "records.txt".
void saveToFile()
{
    // Declare a file pointer.
    FILE *fp;
    // Attempt to open "records.txt" in write mode ("w").
    fp = fopen("records.txt", "w");
    // Check if the file failed to open (e.g., due to permissions).
    if (fp == NULL)
    {
        // If it fails, print an error message.
        printf("Error opening file for saving. Make sure 'records.txt' is writable.\n");
        // Exit the function.
        return;
    } // End of the if block.

    // Write the main header to the file.
    fprintf(fp, "					ABC UNIVERSITY\n");
    // Write the sub-header to the file.
    fprintf(fp, "				Academic Records � AY 2024�2025\n");
    // Write the column headers to the file, matching the display format.
    fprintf(fp, "%-12s %-30s %-6s %-4s %-12s %-8s %-20s\n",
            "Student No.", "Full Name", "Course", "Year", "Final Grade", "Remarks", "Academic Standing");

    // Loop through all the student records.
    for (int i = 0; i < count; i++)
    {
        // Write the data for one student to the file, using the same formatting as the display function.
        fprintf(fp, "%-12s %-30.30s %-6s %-4d %-12.2f %-8s %-20s\n",
                students[i].studentNumber,
                students[i].fullName,
                students[i].program,
                students[i].yearLevel,
                students[i].overall_ph_grade,
                students[i].remarks,
                students[i].academicStanding);
    } // End of the for loop.

    // Close the file to ensure all data is written to the disk.
    fclose(fp);
    // Print a success message to the user.
    printf("Data saved to 'records.txt' successfully!\n");
} // End of the saveToFile function.

// This function loads student records from "records.txt" into the program's memory.
void loadFromFile()
{
    // This function is complex and has known issues with parsing fixed-width text.
    // It is provided as is from the original code. A more robust implementation
    // would use a different file format like CSV (Comma-Separated Values).

    // Declare a file pointer.
    FILE *fp;
    // Attempt to open "records.txt" in read mode ("r").
    fp = fopen("records.txt", "r");
    // Check if the file could not be opened (e.g., it doesn't exist).
    if (fp == NULL)
    {
        // Print a message indicating the file was not found.
        printf("No saved file 'records.txt' found to load from.\n");
        // Exit the function.
        return;
    } // End of the if block.

    // Declare a buffer to read lines from the file.
    char buffer[256];
    // Read and discard the first header line. The 'if' is a simple way to call the function.
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    { /* Do nothing */
    }
    // Read and discard the second header line.
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    { /* Do nothing */
    }
    // Read and discard the third header line (the column names).
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    { /* Do nothing */
    }

    // Reset the student count to 0 before loading new data.
    count = 0;
    // Loop while there are still lines in the file and we haven't reached the max student limit.
    while (count < 10 && fscanf(fp, "%s %s %s %d %f %s %[^\n]",
                                students[count].studentNumber,
                                students[count].fullName,
                                students[count].program,
                                &students[count].yearLevel,
                                &students[count].overall_ph_grade,
                                students[count].remarks,
                                students[count].academicStanding) == 7)
    {
        // NOTE: This simple fscanf is likely to fail with names that contain spaces.
        // A more robust parsing method is needed for the original fixed-width format.
        // For simplicity in commenting, we assume a simplified format it can read.

        // Set grades to 0 since they are not in the file.
        students[count].prelim = 0.0;
        // Set grades to 0.
        students[count].midterm = 0.0;
        // Set grades to 0.
        students[count].final = 0.0;

        // Increment the student count for the newly loaded record.
        count++;
    } // End of the while loop.

    // Close the file.
    fclose(fp);
    // Print a success message showing how many records were loaded.
    printf("Data loaded from 'records.txt' successfully! Total students: %d\n", count);
} // End of the loadFromFile function.

// The main function where the program execution begins.
int main()
{
    // Declare a character variable 'choice' to hold the user's menu selection.
    char choice;
    // Start an infinite loop that will run until the user chooses to exit.
    while (1)
    {
        // Print the main menu title.
        printf("\n--- ACADEMIC RECORDS SYSTEM ---\n");
        // Print menu option 'a'.
        printf("a. Enter new student record\n");
        // Print menu option 'b'.
        printf("b. Compute final grades and remarks for all students\n");
        // Print menu option 'c'.
        printf("c. Display all student records\n");
        // Print menu option 'd'.
        printf("d. Sort students by final grade (Highest first)\n");
        // Print menu option 'e'.
        printf("e. Search student by student number\n");
        // Print menu option 'f'.
        printf("f. Save records to file\n");
        // Print menu option 'g'.
        printf("g. Load records from file\n");
        // Print menu option 'h'.
        printf("h. Exit\n");
        // Print a separator line.
        printf("----------------------------------\n");
        // Prompt the user for their choice.
        printf("Enter your choice: ");

        // Read the user's choice as a single character.
        if (scanf(" %c", &choice) != 1)
        {
            // If input fails, print an error message.
            printf("Invalid input. Please enter a single character choice.\n");
            // Clear the input buffer to prevent an infinite loop.
            clearInputBuffer();
            // Skip the rest of this loop iteration and show the menu again.
            continue;
        } // End of the if block.
        // Clear any extra characters from the input buffer.
        clearInputBuffer();

        // Use a switch statement to handle the user's choice. tolower() makes it case-insensitive.
        switch (tolower(choice))
        {
        // If the user chose 'a'.
        case 'a':
            // Call the function to enter a new student.
            enterStudent();
            // Exit the switch statement.
            break;
        // If the user chose 'b'.
        case 'b':
            // Call the function to compute grades.
            computeGrades();
            // Exit the switch statement.
            break;
        // If the user chose 'c'.
        case 'c':
            // Call the function to display all students.
            displayStudents();
            // Exit the switch statement.
            break;
        // If the user chose 'd'.
        case 'd':
            // Call the function to sort students.
            sortStudents();
            // Exit the switch statement.
            break;
        // If the user chose 'e'.
        case 'e':
            // Call the function to search for a student.
            searchStudent();
            // Exit the switch statement.
            break;
        // If the user chose 'f'.
        case 'f':
            // Call the function to save records to a file.
            saveToFile();
            // Exit the switch statement.
            break;
        // If the user chose 'g'.
        case 'g':
            // Call the function to load records from a file.
            loadFromFile();
            // Exit the switch statement.
            break;
        // If the user chose 'h'.
        case 'h':
            // Print an exit message.
            printf("Exiting Academic Records System. Goodbye!\n");
            // Terminate the program successfully.
            exit(0);
        // If the user entered any other character.
        default:
            // Print an error message for an invalid choice.
            printf("Invalid choice. Please enter a valid option (a-h).\n");
            // Exit the switch statement.
            break;
        } // End of the switch statement.
    } // End of the while loop.
    // This line is never reached because of the infinite loop and exit(0), but it's good practice to have it.
    return 0;
} // End of the main function.