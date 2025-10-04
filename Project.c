#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* GENERAL INSTRUCTIONS

Global variables may not be used in any of the assignments.
Write user friendly programs:
• When user is requested to input a value, the program must clearly state what the user is
expected to enter
• Error message shall be displayed if the user enters an invalid value.
• Validate input that is read from a file and display a descriptive error message is data is not
valid.
• Comment your code and use meaningful variable and function names to make it more
understandable.
Reports must print data in forma ed columns where printed data is aligned by columns. For
example, when prin ng numbers make the field width large enough to hold largest number that you
are going to print.
Take care that array bounds are not violated - especially with strings!
Do not use “magic numbers” - use #define for array sizes and any other limits/constants that you
may need.
Start by thinking what type of input you need to ask from the user of read from a file. Write func ons
that perform error checking for types that you need.
Use func ons to structure your program.

STUDENT GRADE CALCULATOR INSTRUCTIONS

Student grade calculator
Write a program that calculates and displays the final grades for a student based on their scores in
different subjects. The program should allow the user to input scores for mul ple subjects and then
calculate the average grade and overall grade for the student.
Requirements:
• The program should start by asking the user for their name.
• Then, it should ask the user how many subjects they want to calculate grades for.
• For each subject, the program should prompt the user to enter the subject name and the
score (as a percentage).
• Calculate the average grade based on the scores and display it.
• Determine and display the overall grade based on the following grading scale:
o 5: 90-100
o 4: 80-89
o 3: 70-79
o 2: 60-69
o 1: 50-59
o 0: Below 50
• The program must also write the same report to a file
 */

#define MAX_NAME_LEN 64 // max. characters for student name
#define MAX_SUBJECT_NAME_LEN 64 //max. characters for subject name
#define MAX_SUBJECTS 50 //max. number of subjects allowed
#define REPORT_FILENAME "grade_report.txt" //file for the report

// structure for subject informations
typedef struct {
    char name[MAX_SUBJECT_NAME_LEN];
    int  score;  // 0–100
    int  grade;  // 0–5
} Subject;

char* get_line(char *buffer, int size);
void read_nonempty_line(const char *prompt, char *buffer, int size);
int read_integer(const char *prompt);
int read_integer_in_range(const char *prompt, int min, int max);
int score_to_grade(int score);
int overall_from_average(double avg_grade);

void print_report(FILE *out, const char *student_name,
const Subject *subjects, int count,
double avg_grade, int overall_grade);

int write_report_to_file(const char *filename, const char *student_name,
const Subject *subjects, int count,
double avg_grade, int overall_grade);

int main(void)
{
    char student_name[MAX_NAME_LEN];   // buffer for the student's name

    printf("Welcome to the Student Grade Calculator!\n");

    //ask for student name (cannot be empty)
    read_nonempty_line("Please enter your name: ", student_name, sizeof(student_name));

    //ask for how many subjects and validate that it’s between 1 and MAX_SUBJECTS
    int subject_count = read_integer_in_range
    (
    "How many subjects do you want to calculate grades for(1-50)?: ",
        1, MAX_SUBJECTS
    );

    // allocate dynamic array of subjects
    Subject *subjects = (Subject*)calloc((size_t)subject_count, sizeof(Subject));
    if (!subjects)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // quit program if memory failed
    }

    int total_grade_points = 0;

    // loop to get each subject name and score
    for (int i = 0; i < subject_count; ++i)
    {
        char prompt_name[96];
        snprintf(prompt_name, sizeof(prompt_name), "Enter subject %d name: ", i + 1);
        read_nonempty_line(prompt_name, subjects[i].name, sizeof(subjects[i].name));

        char prompt_score[128];
        snprintf(prompt_score, sizeof(prompt_score),
                 "Enter your score for %s (0-100): ", subjects[i].name);

        //validated input between 0–100
        subjects[i].score = read_integer_in_range(prompt_score, 0, 100);

        //convert percentage score into grade (0–5 scale)
        subjects[i].grade = score_to_grade(subjects[i].score);

        total_grade_points += subjects[i].grade;
    }

    // calculate average grade and overall grade
    double average_grade = (double)total_grade_points / subject_count;
    int overall_grade = overall_from_average(average_grade);

    // print results to console
    print_report(stdout, student_name, subjects, subject_count, average_grade, overall_grade);

    // also save results to a file
    if (write_report_to_file(REPORT_FILENAME, student_name, subjects, subject_count, average_grade, overall_grade) == 0)
        {
            printf("The report has also been saved to \"%s\".\n", REPORT_FILENAME);
        }
    else
        {
            printf("Failed to write the report to a file.\n");
        }

    free(subjects); // free the memory we allocated
    return 0;
}

// Reads a full line from stdin, trims newline, flushes extra characters
char* get_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) != NULL)
    {
        if (strchr(buffer, '\n') == NULL)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { } // flush remainder
        }
        else
        {
            buffer[strcspn(buffer, "\n")] = '\0'; // strip newline
        }
        return buffer;
    }
    return NULL;
}

//Keeps asking until user types a non-empty line (eg. for names)
//Limited retries to prevent infinite loop if input keeps failing
void read_nonempty_line(const char *prompt, char *buffer, int size)
{
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;
    int success = 0;

    while (!success && attempts < MAX_ATTEMPTS)
    {
        printf("%s", prompt);
        if (!get_line(buffer, size))
        {
            printf("Error: input failed, try again.\n");
            attempts++;
            continue;
        }
        // trim whitespace
        char *start = buffer;
        while (isspace((unsigned char)*start)) start++;
        char *end = start + strlen(start);
        while (end > start && isspace((unsigned char)end[-1])) end--;
        *end = '\0';

        if (*start == '\0')
        {
            printf("Error: input cannot be empty.\n");
            attempts++;
            continue;
        }

        if (start != buffer) memmove(buffer, start, strlen(start) + 1);
        success = 1; // success, break loop
    }

    if (!success)
    {
        printf("Too many invalid attempts. Exiting.\n");
        exit(1);
    }
}

//Reads one integer from the user. Repeats until input is valid (limited retries)
int read_integer(const char *prompt)
{
    int value;
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { } // flush
            return value;
        }
        printf("Error: please enter an integer value.\n");
        attempts++;
        scanf("%*s"); // discard invalid token
    }

    printf("Too many invalid attempts. Exiting.\n");
    exit(1);
}

// Reads an integer and checks that it is between min and max (inclusive).
// Retry limit to avoid infinite loops
int read_integer_in_range(const char *prompt, int min, int max)
{
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (attempts < MAX_ATTEMPTS)
    {
        int v = read_integer(prompt);
        if (v < min || v > max)
        {
            printf("Error: value must be between %d and %d.\n", min, max);
            attempts++;
        }
        else
        {
            return v;
        }
    }

    printf("Too many invalid attempts. Exiting.\n");
    exit(1);
}

//Convert a 0–100 percentage score into grade 0–5.
int score_to_grade(int score)
{
    if (score >= 90) return 5;
    if (score >= 80) return 4;
    if (score >= 70) return 3;
    if (score >= 60) return 2;
    if (score >= 50) return 1;
    return 0;
}

//Round average grade to nearest integer (0–5).
int overall_from_average(double avg_grade)
{
    int g = (int)(avg_grade + 0.5); // rounding
    if (g < 0) g = 0;
    if (g > 5) g = 5;
    return g;
}

//Prints a formatted report of subjects, scores, grades, and averages
void print_report(FILE *out,
    const char *student_name,
    const Subject *subjects,
    int count,
    double avg_grade,
    int overall_grade)
{
    fprintf(out, "----------------------------------------------\n");
    fprintf(out, "Student: %s\n", student_name);
    fprintf(out, "----------------------------------------------\n");
    fprintf(out, "%-28s %8s %7s\n", "Subject", "Score", "Grade");
    fprintf(out, "----------------------------------------------\n");

    for (int i = 0; i < count; ++i)
    {
        fprintf(out, "%-28s %7d%% %7d\n",
            subjects[i].name,
            subjects[i].score,
            subjects[i].grade);
    }

    fprintf(out, "\nAverage Grade: %.2f\n", avg_grade);
    fprintf(out, "Overall Grade: %d\n", overall_grade);
    fprintf(out, "----------------------------------------------\n");
}

// Saves the same report to a text file
int write_report_to_file(const char *filename,
    const char *student_name, const Subject *subjects,
    int count, double avg_grade,
    int overall_grade)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("Error opening report file");
        return 1;
    }
    print_report(f, student_name, subjects, count, avg_grade, overall_grade);
    fclose(f);
    return 0;
}

